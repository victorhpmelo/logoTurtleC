#ifndef DRAWSQUARE_H
#define DRAWSQUARE_H
#include <curses.h>

class drawsquare
{

      void drawsquare(int newturtle[], WINDOW *window) {
    int i;
    char trace = '-';
    for (i = 0; i < 12; i++) {
        newturtle[1] += 1;
        mvwaddch(window, newturtle[0], newturtle[1], trace);
    }
    trace = '|';
    for (i = 0; i < 6; i++) {
        newturtle[0] += 1;
        mvwaddch(window, newturtle[0], newturtle[1], trace);
    }
    trace = '-';
    for (i = 0; i < 12; i++) {
        newturtle[1] -= 1;
        mvwaddch(window, newturtle[0], newturtle[1], trace);
    }
    trace = '|';
    for (i = 0; i < 6; i++) {
        newturtle[0] -= 1;
        mvwaddch(window, newturtle[0], newturtle[1], trace);
    }


};

};

#endif // DRAWSQUARE_H
