#include <curses.h>
#ifndef FIGURES_H
#define FIGURES_H


class figures
{
    public:


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
}

void drawtriangle(int newturtle[], WINDOW *window) {
    int i;
    char trace = '/';
    for (i = 0; i < 6; i++) {
        newturtle[0] -= 1;
        newturtle[1] += 1;
        mvwaddch(window, newturtle[0], newturtle[1], trace);
    }
    trace = '\\';
    for (i = 0; i < 7; i++) {
        newturtle[0] += 1;
        newturtle[1] += 1;
        mvwaddch(window, newturtle[0], newturtle[1], trace);
    }
    trace = '-';
    for (i = 0; i < 14; i++) {
        newturtle[1] -= 1;
        mvwaddch(window, newturtle[0], newturtle[1], trace);
    }
}

void drawdiamond(int newturtle[], WINDOW *window) {
    int i;
    char trace = '/';
    for (i = 0; i < 6; i++) {
        newturtle[0] -= 1;
        newturtle[1] += 1;
        mvwaddch(window, newturtle[0], newturtle[1], trace);
    }
    trace = '\\';
    for (i = 0; i < 6; i++) {
        newturtle[0] += 1;
        newturtle[1] += 1;
        mvwaddch(window, newturtle[0], newturtle[1], trace);
    }
    trace = '/';
    for (i = 0; i < 6; i++) {
        newturtle[0] += 1;
        newturtle[1] -= 1;
        mvwaddch(window, newturtle[0], newturtle[1], trace);
    }
    trace = '\\';
    for (i = 0; i < 6; i++) {
        newturtle[0] -= 1;
        newturtle[1] -= 1;
        mvwaddch(window, newturtle[0], newturtle[1], trace);
    }
}

void drawcircle(int newturtle[], WINDOW *window) {
    int i;
    char trace = '-';
    for (i = 0; i < 7; i++) {
        newturtle[1] += 1;
        mvwaddch(window, newturtle[0], newturtle[1], trace);
    }
    trace = '\\';
    for (i = 0; i < 2; i++) {
        newturtle[0] += 1;
        newturtle[1] += 1;
        mvwaddch(window, newturtle[0], newturtle[1], trace);
    }
    trace = '|';
    for (i = 0; i < 2; i++) {
        newturtle[0] += 1;
        mvwaddch(window, newturtle[0], newturtle[1], trace);
    }
    trace = '/';
    for (i = 0; i < 2; i++) {
        newturtle[0] += 1;
        newturtle[1] -= 1;
        mvwaddch(window, newturtle[0], newturtle[1], trace);
    }
    trace = '-';
    for (i = 0; i < 7; i++) {
        newturtle[1] -= 1;
        mvwaddch(window, newturtle[0], newturtle[1], trace);
    }
    trace = '\\';
    for (i = 0; i < 2; i++) {
        newturtle[0] -= 1;
        newturtle[1] -= 1;
        mvwaddch(window, newturtle[0], newturtle[1], trace);
    }
    trace = '|';
    for (i = 0; i < 2; i++) {
        newturtle[0] -= 1;
        mvwaddch(window, newturtle[0], newturtle[1], trace);
    }
    trace = '/';
    for (i = 0; i < 2; i++) {
        newturtle[0] -= 1;
        newturtle[1] += 1;
        mvwaddch(window, newturtle[0], newturtle[1], trace);
    }
}

void figuredraw(char type[], int newturtle[], WINDOW *window) {
    char trace;
    if (strcmp(type, "sq") == 0) {
        drawsquare(newturtle, window);
    } else if (strcmp(type, "tg") == 0) {
        drawtriangle(newturtle, window);
    } else if (strcmp(type, "dm") == 0) {
        drawdiamond(newturtle, window);
    } else if (strcmp(type, "ci") == 0) {
        drawcircle(newturtle, window);
    }
}

int nturt() {
    WINDOW *window;
    int newturtle[2] = {0, 0};
    char type[2];

    initscr();
    window = newwin(20, 20, 0, 0);
    refresh();

    strcpy(type, "sq");
    drawfigure(type, newturtle, window);

    wrefresh(window);
    getch();

    endwin();

    return 0;
}




};

#endif // FIGURES_H
