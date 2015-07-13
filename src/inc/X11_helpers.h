#include <stdlib.h>
#include <X11/Xos.h>
#include <X11/Xmu/Error.h>
#include <X11/XKBlib.h>

typedef struct{
  int delay;
  int interval;  
}kbrate;

kbrate* xkbset_repeatrate(Display *dpy, int delay, int interval);


