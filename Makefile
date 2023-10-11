libs = -L/usr/include/X11/Xlib.h -L/usr/include/X11/keysymdef.h -lX11
testWin: main.cpp 
	c++ $< $(libs) -o testWin
run: testWin
	./testWin