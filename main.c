#include <stdio.h>
#include <windows.h>
#include <conio.h>

void gotoxy(int x, int y) {
    COORD pos = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void set_color(int fg, int bg) {
    CONSOLE_CURSOR_INFO ci = {1, FALSE};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ci);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (bg << 4) | fg);
}

void draw_container(int x, int y, int w, int h) {
    gotoxy(x, y); printf("+");
    for (int i = 0; i < w-2; i++) printf("-");
    printf("+");
    for (int i = 1; i < h-1; i++) {
        gotoxy(x, y+i); printf("|");
        gotoxy(x+w-1, y+i); printf("|");
        for (int j = 1; j < w-1; j++) { gotoxy(x+j, y+i); printf(" "); }
    }
    gotoxy(x, y+h-1); printf("+");
    for (int i = 0; i < w-2; i++) printf("-");
    printf("+");
}

int main(int argc, char* argv) {
    system("cls");


    int w = 50;
    int h = 20;
    printf("Hello there");
    while(1) {
        draw_container(0, 0, w, h);
        gotoxy(2, 2);
        set_color(15, 0);

        int ch = _getch();
    }

}