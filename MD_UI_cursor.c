
#include "MD_header.h"

#define WIDTH 7
#define HEIGHT 5

void gotoxy_c(int x, int y) 
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void print_calendar_ui(int cur_y, int cur_x) 
{
    int i, j, date = 1;
    printf("旨收收收收收收收有收收收收收收收有收收收收收收收有收收收收收收收有收收收收收收收有收收收收收收收有收收收收收收收旬\n");

    for (i = 0; i < HEIGHT; i++) {
        for (j = 0; j < WIDTH; j++) {
            if (date <= 31) {
                if (i == cur_y && j == cur_x) {
                    printf("早[%2d]   ", date);
                }
                else {
                    printf("早  %2d   ", date);
                }
                date++;
            }
            else {
                printf("早       ");
            }
        }
        printf("早\n");
        if (i != HEIGHT - 1) {
            printf("曳收收收收收收收朱收收收收收收收朱收收收收收收收朱收收收收收收收朱收收收收收收收朱收收收收收收收朱收收收收收收收朽\n");
        }
    }

    printf("曲收收收收收收收朴收收收收收收收朴收收收收收收收朴收收收收收收收朴收收收收收收收朴收收收收收收收朴收收收收收收收旭\n");
}

int main() {
    int cur_y = 1, cur_x = 3;
    int ch;

    while (1) {
        system("cls");
        print_calendar_ui(cur_y, cur_x);

        ch = _getch();
        switch (ch) {
        case 72:  // UP
            cur_y = cur_y - 1 >= 0 ? cur_y - 1 : HEIGHT - 1;
            break;
        case 80:  // DOWN
            cur_y = (cur_y + 1) % HEIGHT;
            break;
        case 75:  // LEFT
            cur_x = cur_x - 1 >= 0 ? cur_x - 1 : WIDTH - 1;
            break;
        case 77:  // RIGHT
            cur_x = (cur_x + 1) % WIDTH;
            break;
        case 'q':
            return 0;
        }
    }

    return 0;
}
