#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <stdbool.h>

#define UP 72
#define DOWN 80
#define ENTER 13
#define BACKSPACE 8
#define DELETE_KEY 83

void gotoxy(int x, int y) {
    COORD pos = {x, y};
    CONSOLE_CURSOR_INFO ci = {1, FALSE};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ci);
}

void set_color(int fg, int bg) {
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

void draw_textfield(int x, int y, int w, char *buffer) {
    draw_container(x, y, w, 3);
    gotoxy(x+1, y+1);
    set_color(0, 15);
    printf("%-*.*s", w-2, w-2, buffer);
    gotoxy(x+1, y+1);
    set_color(15, 0);
}

void textfield_input(int x, int y, int w, char *buffer, int max_len) {
    int pos = 0;
    buffer[0] = '\0';
    while (1) {
        gotoxy(x+1+pos, y+1);
        int ch = _getch();
        if (ch == ENTER) break;
        else if (ch == BACKSPACE) {
            if (pos > 0) {
                pos--;
                buffer[pos] = '\0';
                draw_textfield(x, y, w, buffer);
            }
        } else if (ch >= 32 && ch <= 126) {
            if (pos < max_len-1 && pos < w-3) {
                buffer[pos++] = ch;
                buffer[pos] = '\0';
                draw_textfield(x, y, w, buffer);
            }
        }
    }
}

int main(int argc, char* argv) {
    system("cls");

    int w = 20;
    int h = 30;    
    int x = 10;
    int y = 0;
    draw_container(x, y, w, h);
    char name[256];
    int input;
    bool field = false;

    while (1) {
        gotoxy(x + 2, y + 2);
        printf("[]");
        if (input == 0 || input == 224) {
            input = _getch();  
        }
    }

}
