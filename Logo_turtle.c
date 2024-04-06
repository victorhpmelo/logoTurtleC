#include <curses.h>
#include <stdbool.h>
#include <string.h>

#define MAX_INPUT_LENGTH 20


        int h, w;
        int selected_row_idx = 0;
        char cmd;
        char traceback;
        char* menu[] = {"Comandos", "Modo teclado", "Modo texto", "Sair"};

    void print_menu(WINDOW* stdscr, int selected_row_idx) {
            noecho();
            getmaxyx(stdscr, h, w);
            clear();
            box(stdscr, 0, 0);
            mvwprintw(stdscr, (h/2)-4, (w/2)-9, "L O G O  T U R T L E");
            for (int idx = 0; idx < sizeof(menu) / sizeof(menu[0]); idx++) {
                int x = w/2 - strlen(menu[idx])/2;
                int y = h/2 - sizeof(menu) / sizeof(menu[0])/2 + idx;
                if (idx == selected_row_idx) {
                    attron(COLOR_PAIR(1));
                    mvwprintw(stdscr, y, x, menu[idx]);
                    attroff(COLOR_PAIR(1));
                } else {
                    mvwprintw(stdscr, y, x, menu[idx]);
                }
            }
            refresh();
        }

    int start() {
        WINDOW* stdscr = initscr();
        curs_set(0);
        start_color();
        init_pair(1, COLOR_BLACK, COLOR_WHITE);
        int current_row_idx = 0;
        print_menu(stdscr, current_row_idx);
        while (1) {
            int key = getch();
            clear();
            if (key == KEY_UP || key == 'w' || key == 'W') {
                if (current_row_idx > 0) {
                    current_row_idx -= 1;
                }
            } else if (key == KEY_DOWN || key == 's' || key == 'S') {
                if (current_row_idx < sizeof(menu) / sizeof(menu[0]) - 1) {
                    current_row_idx += 1;
                }
            } else if (key == KEY_ENTER || key == 10 || key == 13) {
                mvwprintw(stdscr, 0, 0, "Voce selecionou %s", menu[current_row_idx]);
                refresh();

                if (current_row_idx == sizeof(menu) / sizeof(menu[0]) - 1) {
                    mvwprintw(stdscr, 3, 0, "Ate logo!");
                    getch();
                    break;
                } else if (current_row_idx == sizeof(menu) / sizeof(menu[0]) - 2) {
                    mvwprintw(stdscr, 3, 0, "Iniciando o jogo...");
                    mvwprintw(stdscr, 5, 0, "Pressione Enter");
                    getch();
                    turtleinput();
                    break;
                } else if (current_row_idx == sizeof(menu) / sizeof(menu[0]) - 3) {
                    mvwprintw(stdscr, 3, 0, "Iniciando o jogo...");
                    mvwprintw(stdscr, 5, 0, "Pressione Enter");
                    getch();

                    runKeyboard();
                    break;
                } else if (current_row_idx == sizeof(menu) / sizeof(menu[0]) - 4) {
                    mvwprintw(stdscr, 2, 0, "MODO TECLADO:");
                    mvwprintw(stdscr, 4, 0, "Tecla W = Cima");
                    mvwprintw(stdscr, 4, 19, "Tecla A = Esquerda");
                    mvwprintw(stdscr, 5, 0, "Tecla S = Baixo");
                    mvwprintw(stdscr, 5, 19, "Tecla D = Direita");
                    mvwprintw(stdscr, 6, 0, "Barra de espaço = Para de desenhar");
                    mvwprintw(stdscr, 7, 0, "Diagonais:");
                    mvwprintw(stdscr, 8, 0, "Tecla E = Cima-direita");
                    mvwprintw(stdscr, 8, 26, "Tecla Q = Cima-esquerda");
                    mvwprintw(stdscr, 9, 0, "Tecla C = Baixo-direita");
                    mvwprintw(stdscr, 9, 26, "Tecla Z = Baixo-esquerda");
                    mvwprintw(stdscr, 11, 0, "MODO TEXTO:");
                    mvwprintw(stdscr, 12, 0, "ex. 'up 3' (comando + valor [up,dw < 12; lt,rt < 60])");
                    mvwprintw(stdscr, 13, 0, "up = Cima");
                    mvwprintw(stdscr, 13, 16, "dw = Baixo");
                    mvwprintw(stdscr, 14, 0, "rt = Direita");
                    mvwprintw(stdscr, 14, 16, "lt = Esquerda");
                    mvwprintw(stdscr, 16, 0, "Desenhos:");
                    mvwprintw(stdscr, 17, 0, "sq = Quadrado");
                    mvwprintw(stdscr, 17, 16, "tg = Triangulo");
                    mvwprintw(stdscr, 18, 0, "dm = Diamante");
                    mvwprintw(stdscr, 18, 16, "ci = Circulo");
                    mvwprintw(stdscr, 20, 0, "Ferramentas:");
                    mvwprintw(stdscr, 21, 0, "pc = Para de desenhar/ Volta a desenhar");
                    mvwprintw(stdscr, 22, 0, "cl = Limpa os desenhos");
                    mvwprintw(stdscr, 23, 0, "ex = Sair");
                    mvwprintw(stdscr, 26, 0, "Pressione ENTER para voltar ao Menu Principal");
                    getch();
                }
            }
            print_menu(stdscr, current_row_idx);
            refresh();
        }
        endwin();

    }
 void runKeyboard(){

    int sh, sw;
    initscr();
    curs_set(0);
    nodelay(stdscr, TRUE);
    timeout(100);
    getmaxyx(stdscr, sh, sw);
    WINDOW *w = newwin(sh, sw, 0, 0);
    box(w, 0, 0);

    int turtle[2] = {sh / 2, sw / 2};
    mvwaddch(w, turtle[0], turtle[1], ACS_DIAMOND);
    wrefresh(w);

    noecho();
    bool pen_down = true;
    while (1) {
        int key = wgetch(w);

        int new_turtle[2] = {turtle[0], turtle[1]};

        if (key == ' ') {
            pen_down = !pen_down;
            continue;
        }
        if (key != -1) {
            if (key == KEY_UP || key == 'w' || key == 'W') {
                new_turtle[0] -= 1;
                 traceback = '|';
            } else if (key == KEY_DOWN || key == 's' || key == 'S') {
                new_turtle[0] += 1;
                 traceback = '|';
            } else if (key == KEY_LEFT || key == 'a' || key == 'A') {
                new_turtle[1] -= 1;
                 traceback = '-';
            } else if (key == KEY_RIGHT || key == 'd' || key == 'D') {
                new_turtle[1] += 1;
                 traceback = '-';
            } else if (key == 'e' || key == 'E') {
                new_turtle[0] -= 1;
                new_turtle[1] += 1;
                 traceback = '/';
            } else if (key == 'q' || key == 'Q') {
                new_turtle[0] -= 1;
                new_turtle[1] -= 1;
                 traceback = '\\';
            } else if (key == 'z' || key == 'Z') {
                new_turtle[0] += 1;
                new_turtle[1] -= 1;
                 traceback = '/';
            } else if (key == 'c' || key == 'C') {
                new_turtle[0] += 1;
                new_turtle[1] += 1;
                 traceback = '\\';
            } else {
                continue;
            }

            if (new_turtle[0] < 0 || new_turtle[0] >= sh || new_turtle[1] < 0 || new_turtle[1] >= sw) {
                break;
            }

            if (pen_down) {
                mvwaddch(w, turtle[0], turtle[1],  traceback);
            } else {
                mvwaddch(w, turtle[0], turtle[1], ' ');
            }

            mvwaddch(w, new_turtle[0], new_turtle[1], ACS_DIAMOND);
            wrefresh(w);
            turtle[0] = new_turtle[0];
            turtle[1] = new_turtle[1];
        }
    }
    endwin();
 }



void turtleinput() {
    initscr();
    cbreak();
    noecho();
    curs_set(1);

    int sh, sw;
    getmaxyx(stdscr, sh, sw);

    WINDOW *w = newwin(sh - 3, sw, 0, 0);
    box(w, 0, 0);
    wrefresh(w);

    WINDOW *prompt = newwin(3,sw,sh - 3, 0);
    box(prompt, 0, 0);
    mvwaddstr(prompt, 1, 1, " Comandos:");
    wrefresh(prompt);

    int turtle[2] = {sh / 2 - 3, sw / 2};
    mvwaddch(w, turtle[0], turtle[1], ACS_DIAMOND);
    wrefresh(w);

    bool pen_down = true;

    while (1) {
        mvwaddstr(prompt, 1, 11, "  ");
        wclrtoeol(prompt);
        wrefresh(prompt);
        echo();
        char input[MAX_INPUT_LENGTH];
        wgetstr(prompt, input);
        noecho();

        int new_turtle[2] = {turtle[0],turtle[1]};

        if (strlen(input) == 0) {
            continue;
        }  {
            char cmd[MAX_INPUT_LENGTH];
            int value;

            if (sscanf(input, "%s %d", cmd, &value) != -1) {
                sscanf(input,"%s",cmd);
            } if (strcmp(cmd, "up") == 0 || strcmp(cmd, "dw") == 0 || strcmp(cmd, "rt") == 0 || strcmp(cmd, "lt") == 0 ){
                moveturtle(turtle, sh, sw, w, cmd, value, pen_down);}
            if (strcmp(cmd, "sq") == 0 || strcmp(cmd, "tg") == 0 || strcmp(cmd, "dm") == 0 || strcmp(cmd, "ci") == 0) {
                moveturtle(turtle, sh, sw, w, cmd, value, pen_down);
            } else if (strcmp(cmd, "pc") == 0) {
                pen_down = !pen_down;
            } else if (strcmp(cmd, "cl") == 0) {
                wclear(w);
                box(w, 0, 0);
                mvwaddch(w,turtle[0],turtle[1],ACS_DIAMOND);
                wrefresh(w);
            } else if (strcmp(cmd, "ex") == 0) {
                break;}
        if (new_turtle[0] < 0 ||new_turtle[0] >= sh - 3 || new_turtle[1] < 0 || new_turtle[1] >= sw){
                break;}
        }
            endwin();
    }
}
void moveturtle(int *turtle, int sh, int sw, WINDOW *window,const char *cmd, int value, bool pen_down) {
    int new_turtle[2];

                if (strcmp(cmd, "up") == 0) {
                        new_turtle[0] = turtle[0] - value;
                        new_turtle[1] = turtle[1] ;
                        traceback = '|';
                                if(pen_down){
                                mvwvline(window,new_turtle[0] ,new_turtle[1],traceback, value);}


                }else if (strcmp(cmd, "dw") == 0) {
                        new_turtle[0] = turtle[0] + value;
                        new_turtle[1] = turtle[1];
                        traceback = '|';
                                if(pen_down){
                                mvwvline(window,new_turtle[0] - value ,new_turtle[1],traceback,value);}


                }else if (strcmp(cmd, "rt") == 0) {
                new_turtle[0] = turtle[0];
                new_turtle[1] = turtle[1] + value;
                traceback = '_';
                            if(pen_down){
                            mvwhline(window,new_turtle[0] ,new_turtle[1] - value,traceback, value);}


                }else if (strcmp(cmd, "lt") == 0) {
                new_turtle[0] = turtle[0];
                new_turtle[1] = turtle[1] - value;
                traceback = '_';
                if(pen_down){
                    mvwhline(window,new_turtle[0] ,new_turtle[1],traceback, value);}


                }else if (strcmp(cmd, "sq") == 0) {
                        new_turtle[0] = turtle[0];
                        new_turtle[1] = turtle[1];
                            if(pen_down){
                                traceback = '_';
                                mvwhline(window,new_turtle[0] ,new_turtle[1],traceback, 12);
                                traceback = '|';
                                new_turtle[1] = new_turtle[1] + 12;

                                mvwvline(window,new_turtle[0] - 5,new_turtle[1],traceback,6);
                                traceback = '_';
                                new_turtle[0] = new_turtle[0] - 6;

                                mvwhline(window,new_turtle[0] ,new_turtle[1]-12,traceback, 12);
                                traceback = '|';
                                new_turtle[1] = new_turtle[1] - 12;

                                mvwvline(window,new_turtle[0] + 1 ,new_turtle[1],traceback,6);
                                new_turtle[1] = new_turtle[1] + 12;
                                }

                }else if (strcmp(cmd, "tg") == 0) {
                        new_turtle[0] = turtle[0];
                        new_turtle[1] = turtle[1];
                    if(pen_down){
                            int i;
                                traceback = '\\';

                                new_turtle[0] = new_turtle[0] + 5;
                                new_turtle[1] = new_turtle[1] - 4;

                                for ( i = 0; i <= 4; i++) {
                                    new_turtle[0] -= 1;
                                    new_turtle[1] -= 1;
                                    mvwvline(window, new_turtle[0] - 4, new_turtle[1] + 5, traceback,1);}
                                traceback = '/';
                                new_turtle[0] = new_turtle[0] - 5;
                                new_turtle[1] = new_turtle[1] + 5;

                                for ( i = 0; i <= 4; i++) {
                                    new_turtle[0] += 1;
                                    new_turtle[1] -= 1;
                                    mvwvline(window, new_turtle[0], new_turtle[1], traceback,1);}

                                traceback = '_';
                                mvwhline(window,new_turtle[0],new_turtle[1],traceback, 10);
                                }
                }else if (strcmp(cmd, "dm") == 0) {
                        new_turtle[0] = turtle[0];
                        new_turtle[1] = turtle[1];
                    if(pen_down){
                                int i;

                                traceback = '/';
                                for( i = 0;i < 6;i++){
                                new_turtle[0] -= 1;
                                new_turtle[1] += 1;
                                mvwvline(window,new_turtle[0]+1,new_turtle[1],traceback, 1);}

                                traceback = '\\';
                                for( i = 0;i < 6;i++){
                                new_turtle[0] += 1;
                                new_turtle[1] += 1;
                                mvwvline(window,new_turtle[0],new_turtle[1],traceback, 1);}

                                traceback = '/';
                                for( i = 0;i < 6;i++){
                                new_turtle[0] += 1;
                                new_turtle[1] -= 1;
                                mvwvline(window,new_turtle[0],new_turtle[1] + 1,traceback, 1);}

                                traceback = '\\';
                                for( i = 0;i < 6;i++){
                                new_turtle[0] -= 1;
                                new_turtle[1] -= 1;
                                mvwvline(window,new_turtle[0],new_turtle[1],traceback, 1);}

                                new_turtle[0] = new_turtle[0] + 6;
                                new_turtle[1] = new_turtle[1] + 6;


                    }
                }else if (strcmp(cmd, "ci") == 0) {
                        new_turtle[0] = turtle[0];
                        new_turtle[1] = turtle[1];
                    if(pen_down){
                                int i;
                                new_turtle[0] = new_turtle[0] + 1;
                                new_turtle[1] = new_turtle[1] + 1;
                                traceback = '/';

                                for ( i = 0; i <=2; i++) {
                                new_turtle[0] -= 1;
                                new_turtle[1] += 1;
                                mvwvline(window, new_turtle[0], new_turtle[1], traceback,1);}

                                new_turtle[1] = new_turtle[1] + 1;

                                traceback = '|';
                                for (i = 0; i <= 2; i++) {
                                new_turtle[0] -= 1;
                                mvwvline(window, new_turtle[0], new_turtle[1], traceback,1);}

                                new_turtle[1] = new_turtle[1] + 1;

                                traceback = '\\';
                                for ( i = 0; i <= 2; i++) {
                                    new_turtle[0] -= 1;
                                    new_turtle[1] -= 1;
                                    mvwvline(window, new_turtle[0], new_turtle[1], traceback,1);}
                                new_turtle[0] = new_turtle[0] - 1;

                                    traceback = '_';
                                for ( i = 0; i < 10; i++) {
                                    new_turtle[1] -= 1;
                                    mvwhline(window, new_turtle[0], new_turtle[1], traceback,1);}

                                    traceback = '/';
                                for ( i = 0; i <= 2; i++) {
                                    new_turtle[0] += 1;
                                    new_turtle[1] -= 1;
                                    mvwvline(window, new_turtle[0], new_turtle[1], traceback,1);}

                                   traceback = '|';
                                for (i = 0; i <= 2; i++) {
                                    new_turtle[0] += 1;
                                    mvwvline(window, new_turtle[0], new_turtle[1], traceback,1);}

                                   traceback = '\\';
                                for (i = 0; i <= 2; i++) {
                                    new_turtle[0] += 1;
                                    new_turtle[1] += 1;
                                    mvwvline(window, new_turtle[0], new_turtle[1], traceback,1);}
                                    char traceback = '_';
                                for (i = 0; i < 10; i++) {
                                    new_turtle[1] += 1;
                                    mvwhline(window, new_turtle[0] , new_turtle[1] , traceback,1);}
                    }
                                new_turtle[1] = new_turtle[1] + 13;

                }
            if(pen_down) {
                mvwaddch(window, turtle[0], turtle[1], traceback);

            } {
                mvwaddch(window,turtle[0],turtle[1],' ');
            }

            mvwaddch(window,new_turtle[0],new_turtle[1],ACS_DIAMOND);
            wrefresh(window);

            turtle[0] = new_turtle[0];
            turtle[1] = new_turtle[1];
        }





int main() {
    start();
    endwin();
}



