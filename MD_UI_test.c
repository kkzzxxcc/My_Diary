/*
#define _CRT_SECURE_NO_WARNINGS  // 비주얼 스튜디오에서 sacnf 오류 무시해주는 정의
// UI

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#define P 38
#define PP P+21
// ┫ ┃ ━ ┓ ┛ ┗ ┏ ┳ ┻ ┣ ╋

void gotoxy(int x, int y);
void MD_main_UI();        // 메인 화면


void gotoxy(int x, int y)
{
	COORD Pos = { x - 1, y - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void MD_main_UI()
{
	system("cls");
	int i;

	for (i = 0; i < 110; i++)
		printf("━");

	gotoxy(1, 2);
	for (i = 0; i < 27; i++)
		printf("┃\t\t\t\t\t\t\t\t\t\t\t\t\t     ┃\n");

	gotoxy(1, 28);
	for (i = 0; i < 110; i++)
		printf("━");

	gotoxy(1, 1);
	printf("┏");
	gotoxy(110, 1);
	printf("┓");
	gotoxy(1, 28);
	printf("┗");
	gotoxy(110, 28);
	printf("┛");

	gotoxy(51, 10);
	printf("My Diary");

	gotoxy(13, 16);
	printf("1. 달력 보기");
	gotoxy(13, 20);
	printf("2. 종료");
	gotoxy(1, 30);
	printf("END");

	

}

void MD_main_calinder()
{
	system("cls");
	int i;

	for (i = 0; i < 110; i++)
		printf("━");

	gotoxy(1, 2);
	for (i = 0; i < 27; i++)
		printf("┃\t\t\t\t\t\t\t\t\t\t\t\t\t     ┃\n");

	gotoxy(1, 28);
	for (i = 0; i < 110; i++)
		printf("━");

	gotoxy(1, 1);
	printf("┏");
	gotoxy(110, 1);
	printf("┓");
	gotoxy(1, 28);
	printf("┗");
	gotoxy(110, 28);
	printf("┛");

	
}


void print_calendar_ui() {
	int i, j, date = 1;
	printf("┏━━━━━━━┳━━━━━━━┳━━━━━━━┳━━━━━━━┳━━━━━━━┳━━━━━━━┳━━━━━━━┓");

		for (i = 0; i < 5; i++) {
			for (j = 0; j < 7; j++) {
				if (date <= 31) {
					printf("┃  %2d   ", date);
					date++;
				}
				else {
					printf("┃       ");
				}
			}
			printf("┃");
				if (i != 4) {
					printf("┣━━━━━━━╋━━━━━━━╋━━━━━━━╋━━━━━━━╋━━━━━━━╋━━━━━━━╋━━━━━━━┫");
				}
		}

	printf("┗━━━━━━━┻━━━━━━━┻━━━━━━━┻━━━━━━━┻━━━━━━━┻━━━━━━━┻━━━━━━━┛");
}

/*
int main() 
{
	print_calendar_ui();
	//MD_main_UI();
	return 0;
}
*/




int get_month_days(int month, int year) {
    int days;

    switch (month) {
    case 4:
    case 6:
    case 9:
    case 11:
        days = 30;
        break;
    case 2:
        if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
            days = 29;
        else
            days = 28;
        break;
    default:
        days = 31;
        break;
    }

    return days;
}

