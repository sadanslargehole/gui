#include "main.hh"
#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <X11/Xlib.h>
#include <X11/Xft/Xft.h>
#include <iostream>
#include <string>
#include <vector>
Display *d;
Window w;
XEvent e;
dog mydog;
void clearScreen() {
  XClearWindow(d, w);
  mydog.chars.clear();
}
void render() {}
int main() {

  int s;
  std::string test = "this might work";
  d = XOpenDisplay(NULL);
  if (d == NULL) {
    fprintf(stderr, "oops!\n");
    exit(1);
  }
  s = DefaultScreen(d);
  w = XCreateSimpleWindow(d, RootWindow(d, s), 10, 10, 200, 200, 1,
                          BlackPixel(d, s), WhitePixel(d, s));
  XSelectInput(d, w, ExposureMask | KeyPressMask);
  XMapWindow(d, w);

  mydog.age = 1;
  mydog.name = "tuxi";
  mydog.breed = "dog";


  while (1) {
    XNextEvent(d, &e);
    if (e.type == Expose) {
      char str[mydog.chars.size()];
      std::copy(mydog.chars.begin(), mydog.chars.end(), str);
      XDrawString(d, w, DefaultGC(d, s), 10, 50, str, sizeof(str));
    }
    if (e.type == KeyPress) {
      switch (XKeycodeToKeysym(d, e.xkey.keycode, NULL)) {
      case XK_c:
        clearScreen();
        break;
      case XK_Return:
        mydog.chars.push_back('\n');
        break;
      default:
        mydog.chars.push_back(
            *XKeysymToString(XKeycodeToKeysym(d, e.xkey.keycode, NULL)));
        XEvent toSend;

        toSend.type = Expose;
        toSend.xexpose.display = d;
        toSend.xexpose.send_event = true;
        toSend.xexpose.window = w;
        toSend.xexpose.type = Expose;
        toSend.xexpose.count = 0;
        XSendEvent(d, w, False, 0, &toSend);
      }
    }
  }
  XCloseDisplay(d);
  return 0;
}
