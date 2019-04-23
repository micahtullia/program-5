// A small library for doing tty things with an istream
// Revision: $Revision: 1.2 $
// Change Log
//   $Log: keystream.cpp,v $
//   Revision 1.2  2017/02/12 01:17:53  root
//   Added a missing include file so keystream would compile.
//
//   Revision 1.1  2016/03/17 15:46:30  pngwen
//   Initial revision
//

#include <iostream>
#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <sys/poll.h>
#include <stdexcept>
#include <exception>
#include "keystream.h"

//our lone default instance
KeyStream kin;


//this is a low level character buffer, it uses read
class ttyinbuf : public std::streambuf
{
public:
  ttyinbuf()
  {
    if(!isatty(STDIN_FILENO)) {
      throw std::runtime_error{"STDIN is not a tty!"};
    }
    
    //we initially start with no available input
    setg(buf, buf+9, buf+9);
  }

  
protected:
  virtual int underflow()
  {
    //attempt to read a single character
    if(read(STDIN_FILENO, buf+9, 1) <=  0)
      return -1;

    //make the character available
    setg(buf, buf+9, buf + 10);

    return buf[9];
  }
  

private:
  char buf[10];
};


//constructor & Destructor
KeyStream::KeyStream()
{
  //set up our buffer to be stdin
  this->rdbuf(new ttyinbuf);
  
  //get the original termios
  if(tcgetattr(STDIN_FILENO, &_originalTermios)==-1) {
    throw std::runtime_error{"Termios tcgeattr failed."};
  }

  //the default state is cooked!
  cookedMode();
}


KeyStream::~KeyStream()
{
  //restore the original tty state
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &_originalTermios);
}


//macro modes
void
KeyStream::cookedMode()
{
  _echo=true;
  _special=true;
  _signal=true;
  _canonical=true;
  setTermiosFlags();
}


void
KeyStream::rawMode()
{
  _echo=false;
  _special=false;
  _signal=false;
  _canonical=false;
  setTermiosFlags();
}


void
KeyStream::cbreakMode()
{
  _echo=false;
  _canonical=false;
  _signal=true;
  _special=true;
  setTermiosFlags();
}


//specific status flags
bool
KeyStream::echo()
{
  return _echo;
}


void
KeyStream::echo(bool flag)
{
  _echo = flag;
  setTermiosFlags();
}


bool
KeyStream::canonical()
{
  return _canonical;
}


void
KeyStream::canonical(bool flag)
{
  _canonical = flag;
  setTermiosFlags();
}


bool
KeyStream::signal()
{
  return _signal;
}


void
KeyStream::signal(bool flag)
{
  _signal = flag;
  setTermiosFlags();
}


bool
KeyStream::special()
{
  return _special;
}


void
KeyStream::special(bool flag)
{
  _special = flag;
  setTermiosFlags();
}

//extensions to the normal IO stuff
keycode
KeyStream::getKey()
{
  keycode result=0x00;
  char c;

  //we may be getting more than one character!
  c=get();  //get a character
  result = c;

  //if this is not an escape sequence, go ahead and return it
  if(c != 0x1b || !hasInput()) {
    return result;
  }

  //ok, so we have an escape sequence going!, get the second character
  c = get();  //get the next character in the sequence
  result = result << 8 | c;  //add it to the result code

  //If this is not one of our known sequences, then we
  //stop here.  (We also stop if there is nothing else to do)
  if(!hasInput() || (c != 0x5b && c != 0x4f)) {
    return result;
  }

  //still here?  Let there be a third!
  c = get();
  result = result << 8 | c;

  //now, there is only one known situation in which we have a fourth.
  //look for it!
  if(!hasInput() | !(c & 0x30)) {
    return result;
  }

  //ok, 4, but that's it.  NO MORE
  c = get();
  result = result << 8 | c;
  
  return result;
}


bool
KeyStream::hasInput()
{
  struct pollfd fds;
  int pres;

  fds.fd=STDIN_FILENO;
  fds.events=POLLIN;
  pres = poll(&fds, 1, 70);

  return pres==1;
}


void
KeyStream::setTermiosFlags()
{
  //start with the default mode for this tty 
  struct termios t=_originalTermios;

  //tweakify!
  
  //echo handling
  if(_echo) {
    //set the ECHO flag
    t.c_lflag |= ECHO;
  } else {
    //clear the ECHO flag
    t.c_lflag &= ~ECHO;
  }

  //canonical handling
  if(_canonical) {
    t.c_lflag |= ICANON;
    //t.c_iflag |= ICRNL;
  } else {
    t.c_lflag &= ~ICANON;
    //t.c_iflag &= ~ICRNL;
  }

  //singal handling
  if(!_signal) {
    t.c_lflag &= ~(ISIG | IEXTEN);
  }


  //special processing handling
  if(!_special) {
    t.c_iflag &= ~(BRKINT | INPCK | IGNBRK | ISTRIP | IGNCR | IXON | INLCR | PARMRK);
    //t.c_oflag &= ~OPOST;
  }

  t.c_cc[VMIN] = 1;  
  t.c_cc[VTIME] = 0;
  
  //set the ttye info
  if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &t) == -1)
    throw std::runtime_error{"Termios tcsetattr failed."};
}
