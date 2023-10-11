#include <iostream>
#include <X11/Xlib.h>
#include <string.h>
#include <stdlib.h>
#include <X11/keysym.h>

int main(){
    Display *d;
    Window w;
    XEvent e;
    int s;
    const char *test = "this will not work";
    d = XOpenDisplay(NULL);
    if (d==NULL){
        fprintf(stderr, "oops!\n");
        exit(1);
    }
    s = DefaultScreen(d);
    w=XCreateSimpleWindow(d, RootWindow(d, s), 10, 10, 200, 200, 1, BlackPixel(d, s), WhitePixel(d, s));
    XSelectInput(d, w, ExposureMask| KeyPressMask);
    XMapWindow(d, w);
    while(1){
        XNextEvent(d, &e);
        if (e.type == Expose){
            XFillRectangle(d, w, DefaultGC(d, s), 20, 20, 10, 10);
            XDrawString(d, w, DefaultGC(d, s), 10, 50, test, strlen(test));
        }
        if(e.type == KeyPress){
            if (e.xkey.keycode !=NULL){
                fprintf(stdout, "not null\n");
            }
            std::cout << e.xkey.keycode << "\n";
            if(XKeycodeToKeysym(d, e.xkey.keycode, NULL) == XK_c){
                break;
            }
        }
        
    }
    XCloseDisplay(d);
    return 0;
}