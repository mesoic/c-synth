#include <stdlib.h>
#include <X11/Xos.h>
#include <X11/Xmu/Error.h>
#include <X11/XKBlib.h>

typedef struct{
  int delay;
  int interval;  
}kbrate;

kbrate* xkbset_repeatrate(Display *dpy, int delay, int interval) {
  kbrate* kb_bak = malloc(sizeof(kbrate));
  XkbDescPtr xkb = XkbAllocKeyboard();
  if (!xkb){return;}
  XkbGetControls(dpy, XkbRepeatKeysMask, xkb);
  kb_bak->delay = xkb->ctrls->repeat_delay;
  kb_bak->interval = xkb->ctrls->repeat_interval;
  xkb->ctrls->repeat_delay = delay;
  xkb->ctrls->repeat_interval = interval;
  XkbSetControls(dpy, XkbRepeatKeysMask, xkb);
  // Need to call GetControls again to reload into the server?
  XkbGetControls(dpy, XkbRepeatKeysMask, xkb);
  return kb_bak;
}
