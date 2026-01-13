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

// Draw Menu (with x & y offset) load the items (options) and display
void draw_menu(int x, int y, char *items[], int count, int selected) {
    for (int i = 0; i < count; i++) {
        gotoxy(x, y + i);
        if (i == selected) {
            set_color(0, 15);
            printf(" > %s ", items[i]);
            set_color(15, 0);
        } else {
            printf("   %s ", items[i]);
        }
    }
}

// draw text field (with x & y offset)
void draw_textfield(int x, int y, int w, char *buffer) {
    draw_container(x, y, w, 3);
    gotoxy(x+1, y+1);
    // set_color(0, 15);
    printf("%-*.*s", w-2, w-2, buffer);
    gotoxy(x+1, y+1);
    // set_color(15, 0);
}

// FUCKING FIX THIS SHIT
// Textfield input
void textfield_input(int x, int y, int max_len, char *buffer) {
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
                draw_textfield(x, y, max_len, buffer);
            }
        } else if (ch >= 32 && ch <= 126) {
            if (pos < max_len-1 && pos < max_len-3) {
                buffer[pos++] = ch;
                buffer[pos] = '\0';
                draw_textfield(x, y, max_len, buffer);
            }
        }
    }
}

// Menu Input
int menu_input(int x, int y, char *items[], int count) {
    int selected = 0;
    int ch;

    while (1) {
        draw_menu(x, y, items, count, selected);

        ch = _getch();
        if (ch == 224) ch = _getch(); 

        if (ch == UP) {
            if (selected > 0) selected--;
        } else if (ch == DOWN) {
            if (selected < count - 1) selected++;
        } else if (ch == ENTER) {
            return selected;
        }
    }
}

// Window Shit
int w = 70; 
int h = 20;    
int x = 20;
int y = 0;

int main(int argc, char* argv[]) {
    system("cls");

    draw_container(x, y, w, h);

    char name[256];
    int field_length = 50;

    char *menu_items[] = {
        "Input Mo Mama mo",
        "Exit",
    };

    while (1) {
        int choice = menu_input(x + 3, y + 3, menu_items, 2);

        if (choice == 0) {
            draw_textfield(x + 2, y + 8, field_length, "");
            textfield_input(x + 2, y + 8, field_length, name);

            gotoxy(x + 2, y + 12);
            printf("Prompt?: %s :D*", name);

            name[0] = '\0';
            draw_textfield(x + 2, y + 8, field_length, "");
        }
        else if (choice == 1) {
            break;
        }
    }

    return 0;
}