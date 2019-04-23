/*
 * File: keyStream.h
 * Purpose: A small class which provides a nifty little tty aware input
 *          stream.  This class only works with stdin. 
 *          Also, it's probably a bad idea to touch cin if you're using this thing.
 *          You've been warned!
 * Author: Robert Lowe
 *
 * Revision: $Revision: 1.1 $
 * Change Log
 *   $Log: keystream.h,v $
 *   Revision 1.1  2016/03/17 15:50:30  pngwen
 *   Initial revision
 *
 */
#ifndef KEYSTREAM_H
#define KEYSTREAM_H

#include <iostream>
#include <termios.h>
#include <cstdint>

typedef std::uint32_t keycode;


class KeyStream : public std::istream
{
public:
  //constructor & Destructor
  KeyStream();
  ~KeyStream();

  //macro modes
  virtual void cookedMode();
  virtual void rawMode();
  virtual void cbreakMode();
  
  //specific status flags
  virtual bool echo();
  virtual void echo(bool flag);
  virtual bool canonical();
  virtual void canonical(bool flag);
  virtual bool signal();
  virtual void signal(bool flag);
  virtual bool special();
  virtual void special(bool flag);

  //extensions to the normal IO stuff
  virtual keycode getKey();
  virtual bool hasInput();
  
private:
  bool _echo;
  bool _canonical;
  bool _signal;
  bool _special;
  struct termios _originalTermios;
  
  void setTermiosFlags();
};

extern KeyStream kin;  //the default keyboard stream kin!

/*
 * Keycodes of special keys as reported by getKey
 *   ALT+key is detected by the ALT macro: ALT('a'), ALT('c') etc. 
 *   The others are defined as constants
 */
#define ALT(k) (0x1B00 | (k))
#define UP           0x1B5B41
#define DOWN         0x1B5B42
#define RIGHT        0x1B5B43
#define LEFT         0x1B5B44
#define INSERT       0x1B5B327E
#define DELETE       0x1B5B337E
#define PAGEUP       0x1B5B357E
#define PAGEDOWN     0x1B5B367E
#define HOME         0x1B4F48
#define END          0x1B4F46
#define F1           0x1B4F50
#define F2           0x1B4F51
#define F3           0x1B4F52
#define F4           0x1B4F53
#define ESC          0x1B
#define ENTER        0x0A
#define CTRL_Q       0x11
#define CTRL_W       0x17
#define CTRL_E       0x05
#define CTRL_R       0x12
#define CTRL_T       0x14
#define CTRL_Y       0x19
#define CTRL_U       0x15
#define CTRL_I       0x09
#define CTRL_O       0x0F
#define CTRL_P       0x10
#define CTRL_LSQUARE 0x1B
#define CTRL_RSQUARE 0x1D
#define CTRL_A       0x01
#define CTRL_S       0x13
#define CTRL_D       0x04
#define CTRL_F       0x06
#define CTRL_G       0x07
#define CTRL_H       0x08
#define CTRL_J       0x0A
#define CTRL_K       0x0B
#define CTRL_L       0x0C
#define CTRL_SEMI    0x3B
#define CTRL_QUOTE   0x27
#define CTRL_ENTER   0x0A
#define CTRL_Z       0x1A
#define CTRL_X       0x18
#define CTRL_C       0x03
#define CTRL_V       0x16
#define CTRL_B       0x02
#define CTRL_N       0x0E
#define CTRL_M       0x0D
#define CTRL_COMMA   0x2C
#define CTRL_PERIOD  0x2E
#define CTRL_SLASH   0x1F
#endif
