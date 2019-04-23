// Terminal utility functions
// $Revision: 1.1 $
//   $Log: term.cpp,v $
//   Revision 1.1  2017/02/12 18:15:24  root
//   Initial revision
//
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <cstdlib>
#include "term.h"


void getTermSize(int &width, int &height)
{
  struct winsize ws;

  /* try to retrieve the size */
  if(ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1) {
    width = -1;
    height= -1;
    return;
  }

  /* get the size and return */
  height = ws.ws_row;
  width  = ws.ws_col;

  return;

}
