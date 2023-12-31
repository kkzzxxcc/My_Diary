
#include "MD_header.h"



void gotoxy(int x, int y);
void MD_main_UI();        // 메인 화면
void gotoxy_c(int x, int y);
void write_entry(Entry* entry, const char* filename);
void change_diary(char* selected_date);
void delete_diary(char* selected_date);
void choose_diary_UI_c();

// gotoxy 함수
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

	

}

// 달력
void print_calendar_ui_t1() 
{
	int i, j, date = 1;
	printf("┏━━━━━━━┳━━━━━━━┳━━━━━━━┳━━━━━━━┳━━━━━━━┳━━━━━━━┳━━━━━━━┓");

	for (i = 0; i < 5; i++) 
	{
		for (j = 0; j < 7; j++) 
		{
			if (date <= 31) 
			{
				printf("┃  %2d   ", date);
				date++;
			}
			else 
			{
				printf("┃       ");
			}
		}
		printf("┃");
		if (i != 4) 
		{
			printf("┣━━━━━━━╋━━━━━━━╋━━━━━━━╋━━━━━━━╋━━━━━━━╋━━━━━━━╋━━━━━━━┫");
		}
	}

	printf("┗━━━━━━━┻━━━━━━━┻━━━━━━━┻━━━━━━━┻━━━━━━━┻━━━━━━━┻━━━━━━━┛");
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


void MD_main_UI_c(int cur_y)
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

	/*
	gotoxy(13, 14);
	printf("1. 달력 보기");
	gotoxy(13, 17);
	printf("2. 일기 검색");
	gotoxy(13, 20);
	printf("3. 메모 검색");
	gotoxy(13, 23);
	printf("2. 종료");
	
	gotoxy(1, 30);*/

	gotoxy(13, 14);
	if (cur_y == 0)
		printf("> 1. 달력 보기");
	else
		printf("  1. 달력 보기");

	gotoxy(13, 17);
	if (cur_y == 1)
		printf("> 2. 일기 검색");
	else
		printf("  2. 일기 검색");

	gotoxy(13, 20);
	if (cur_y == 2)
		printf("> 3. 메모 검색");
	else
		printf("  3. 메모 검색");

	gotoxy(13, 23);
	if (cur_y == 3)
		printf("> 4. 종료");
	else
		printf("  4. 종료");

	gotoxy(1, 30);

}

void choose_menu(int cur_y)
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

	gotoxy(42, 2);
	printf("선택된 날짜 : %s", select_date);

	gotoxy(13, 13);
	printf(cur_y == 0 ? "> 1. 일기 작성" : "  1. 일기 작성");
	gotoxy(13, 16);
	printf(cur_y == 1 ? "> 2. 메모 작성" : "  2. 메모 작성");
	gotoxy(13, 19);
	printf(cur_y == 2 ? "> 3. 일기 보기" : "  3. 일기 보기");
	gotoxy(13, 22);
	printf(cur_y == 3 ? "> 4. 메모 보기" : "  4. 메모 보기");

	gotoxy(1, 29);


}

void write_diary_UI()
{
	system("cls");
	int i, j = 0;

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

	gotoxy(40, 2);
	printf("작성일 : %s", select_date);

	gotoxy(5, 8);
	printf("일기 작성중 >> ");

	// 일기 내용 입력받기
	Entry diary_entry; 
	strcpy(diary_entry.date, select_date);  // 선택된 날짜 설정
	char line[101];  // 한 줄씩 저장

	for (i = 0; i < 27; i++) 
	{  
		gotoxy(20, 8 + i);  
		fgets(line, 101, stdin);  // 한 줄식 저장

		// 엔터를 두 번 입력하면 일기 작성 종료
		if (strcmp(line, "\n") == 0) 
		{
			break;
		}

		strcpy(&diary_entry.content[j], line);  // diary_entry.content에 복사
		j += strlen(line);  // 다음 줄의 시작 위치로 이동 j에 라인 배열의 문자열을 더해서 저장
	}



	// 일기 내용을 파일에 쓰기
	write_entry(&diary_entry, "diary.txt");

	gotoxy(1, 30);



}

void write_memo_UI()
{
	system("cls");
	int i, j = 0;

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

	gotoxy(40, 2);
	printf("작성일 : %s", select_date);

	gotoxy(5, 8);
	printf("메모 작성중 >> ");

	// 메모 내용 입력받기
	Entry memo_entry;
	strcpy(memo_entry.date, select_date);  // 선택된 날짜 설정
	char line[101];  // 한 줄씩 저장

	for (i = 0; i < 27; i++) 
	{  
		gotoxy(20, 8 + i); 
		fgets(line, 101, stdin);  // 한 줄씩 저장

		// 엔터를 두 번 입력하면 메모 작성 종료
		if (strcmp(line, "\n") == 0)
		{
			break;
		}

		strcpy(&memo_entry.content[j], line);  // memo_entry.content에 복사
		j += strlen(line);  
	}




	// 메모 내용을 파일에 쓰기
	write_entry(&memo_entry, "memo.txt");

	gotoxy(1, 30);

}

void ask_secure_UI(int cur_x)
{
	int i;


	for (i = 6; i <= 19; i++)
	{
		gotoxy(18, i);
		printf("┃                                                 ┃");
	}

	gotoxy(18, 6);
	for (i = 0; i < 50; i++)
		printf("━");

	gotoxy(18, 20);
	for (i = 0; i < 50; i++)
		printf("━");



	gotoxy(18, 6);
	printf("┏");
	gotoxy(68, 6);
	printf("┓");
	gotoxy(18, 20);
	printf("┗");
	gotoxy(68, 20);
	printf("┛");

	gotoxy(34, 10);
	printf("보안 하시겠습니까?");


	gotoxy(30, 16);
	printf(cur_x == 0 ? "[ 예 ]" : "  예 ");
	gotoxy(51, 16);
	printf(cur_x == 1 ? "[ 아니오 ]" : "  아니오 ");



	gotoxy(1, 30);

}

void choose_diary_UI()
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

	gotoxy(37, 2);
	printf("보고싶은 일기의 날짜를 선택해주세요.");

	/*
	gotoxy(8, 8);
	printf(">>");

	gotoxy(8, 25);
	printf(">>>");
	*/

	gotoxy(1, 30);

}

void choose_memo_UI()
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

	gotoxy(37, 2);
	printf("보고싶은 메모의 날짜를 선택해주세요.");



	gotoxy(1, 30);

}



void save_secure_UI()
{
	int i;


	for (i = 6; i <= 19; i++)
	{
		gotoxy(18, i);
		printf("┃                                                 ┃");
	}

	gotoxy(18, 6);
	for (i = 0; i < 50; i++)
		printf("━");

	gotoxy(18, 20);
	for (i = 0; i < 50; i++)
		printf("━");



	gotoxy(18, 6);
	printf("┏");
	gotoxy(68, 6);
	printf("┓");
	gotoxy(18, 20);
	printf("┗");
	gotoxy(68, 20);
	printf("┛");

	gotoxy(32, 13);
	printf("보안후 저장되었습니다..");


	gotoxy(60, 13);
	printf("2");
	Sleep(1000);
	gotoxy(60, 13);
	printf("1");
	Sleep(1000);

	gotoxy(1, 30);

}

void ask_password_UI(char *password)
{
	int i;
	char ch;
	int password_ = 0;

	for (i = 6; i <= 19; i++)
	{
		gotoxy(18, i);
		printf("┃                                                 ┃");
	}

	gotoxy(18, 6);
	for (i = 0; i < 50; i++)
		printf("━");

	gotoxy(18, 20);
	for (i = 0; i < 50; i++)
		printf("━");



	gotoxy(18, 6);
	printf("┏");
	gotoxy(68, 6);
	printf("┓");
	gotoxy(18, 20);
	printf("┗");
	gotoxy(68, 20);
	printf("┛");

	gotoxy(28, 12);
	printf("보안을 위한 비밀번호를 입력하세요");
	gotoxy(34, 14);
	printf(">> ");
	gotoxy(37, 14);

	while (1)
	{
		ch = _getch();  
		if (ch == '\r')  // Enter key
			break;

		if (ch == '\b' )  // Backspace key
		{
			printf("\b");
			fputs(" ", stdout);
			printf("\b");
			if (password_ > 0)
			{
				password[--password_];
				continue;
			}
		}
		else if (ch != '\b')
		{
			password[password_++] = ch;
			printf("*");  // *로 출력
		}

	}
	password[password_] = '\0';  // 문자열 끝에 NULL 문자 추가
	gotoxy(37, 14);

	//scanf("%s", password);


	gotoxy(1, 30);

}

void check_save_UI()
{
	int i;


	for (i = 6; i <= 19; i++)
	{
		gotoxy(18, i);
		printf("┃                                                 ┃");
	}

	gotoxy(18, 6);
	for (i = 0; i < 50; i++)
		printf("━");

	gotoxy(18, 20);
	for (i = 0; i < 50; i++)
		printf("━");



	gotoxy(18, 6);
	printf("┏");
	gotoxy(68, 6);
	printf("┓");
	gotoxy(18, 20);
	printf("┗");
	gotoxy(68, 20);
	printf("┛");

	gotoxy(36, 13);
	printf("저장되었습니다..");


	gotoxy(54, 13);
	printf("2");
	Sleep(1000);
	gotoxy(54, 13);
	printf("1");
	Sleep(1000);

	gotoxy(1, 30);

}

void check_password_UI(char* password)
{
	int i;
	char ch;
	int password_ = 0;

	for (i = 6; i <= 19; i++)
	{
		gotoxy(18, i);
		printf("┃                                                 ┃");
	}

	gotoxy(18, 6);
	for (i = 0; i < 50; i++)
		printf("━");

	gotoxy(18, 20);
	for (i = 0; i < 50; i++)
		printf("━");



	gotoxy(18, 6);
	printf("┏");
	gotoxy(68, 6);
	printf("┓");
	gotoxy(18, 20);
	printf("┗");
	gotoxy(68, 20);
	printf("┛");

	gotoxy(24, 12);
	printf("보안된 일기입니다. 비밀번호를 입력하세요");
	gotoxy(34, 14);
	printf(">> ");
	gotoxy(37, 14);

	while (1)
	{
		ch = _getch(); 
		if (ch == '\r')  // Enter key
			break;

		if (ch == '\b')  // Backspace key
		{
			printf("\b");
			fputs(" ", stdout);
			printf("\b");
			if (password_ > 0)
			{
				password[--password_];
				continue;
			}
		}
		else if (ch != '\b')
		{
			password[password_++] = ch;
			printf("*");  
		}

	}
	password[password_] = '\0'; 
	gotoxy(37, 14);


	gotoxy(1, 30);
}

void check_password_UI_m(char* password)
{
	int i;
	char ch;
	int password_ = 0;

	for (i = 6; i <= 19; i++)
	{
		gotoxy(18, i);
		printf("┃                                                 ┃");
	}

	gotoxy(18, 6);
	for (i = 0; i < 50; i++)
		printf("━");

	gotoxy(18, 20);
	for (i = 0; i < 50; i++)
		printf("━");



	gotoxy(18, 6);
	printf("┏");
	gotoxy(68, 6);
	printf("┓");
	gotoxy(18, 20);
	printf("┗");
	gotoxy(68, 20);
	printf("┛");

	gotoxy(24, 12);
	printf("보안된 메모입니다. 비밀번호를 입력하세요");
	gotoxy(34, 14);
	printf(">> ");
	gotoxy(37, 14);

	while (1)
	{
		ch = _getch();  
		if (ch == '\r')  // Enter key
			break;

		if (ch == '\b')  // Backspace key
		{
			printf("\b");
			fputs(" ", stdout);
			printf("\b");
			if (password_ > 0)
			{
				password[--password_];
				continue;
			}
		}
		else if (ch != '\b')
		{
			password[password_++] = ch;
			printf("*"); 
		}

	}
	password[password_] = '\0'; 


	gotoxy(1, 30);
}

void check_password_UI_2_0()
{
	int i;

	for (i = 6; i <= 19; i++)
	{
		gotoxy(18, i);
		printf("┃                                                 ┃");
	}

	gotoxy(18, 6);
	for (i = 0; i < 50; i++)
		printf("━");

	gotoxy(18, 20);
	for (i = 0; i < 50; i++)
		printf("━");



	gotoxy(18, 6);
	printf("┏");
	gotoxy(68, 6);
	printf("┓");
	gotoxy(18, 20);
	printf("┗");
	gotoxy(68, 20);
	printf("┛");

	gotoxy(32, 13);
	printf("비밀번호가 틀렸습니다..");

	gotoxy(56, 13);
	printf("2");
	Sleep(1000);
	gotoxy(56, 13);
	printf("1");
	Sleep(1000);


	gotoxy(1, 30);
}

void search_UI(char* keyword)
{
	int i;

	for (i = 6; i <= 19; i++)
	{
		gotoxy(18, i);
		printf("┃                                                 ┃");
	}

	gotoxy(18, 6);
	for (i = 0; i < 50; i++)
		printf("━");

	gotoxy(18, 20);
	for (i = 0; i < 50; i++)
		printf("━");



	gotoxy(18, 6);
	printf("┏");
	gotoxy(68, 6);
	printf("┓");
	gotoxy(18, 20);
	printf("┗");
	gotoxy(68, 20);
	printf("┛");

	gotoxy(30, 12);
	printf("검색할 키워드를 입력하세요");
	gotoxy(34, 14);
	printf(">> ");
	gotoxy(37, 14);
	fgets(keyword, MAX_LEN, stdin);


	gotoxy(1, 30);
}

void search_diary_UI(char* keyword)
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

	gotoxy(32, 2);
	printf("검색하신 키워드가 포함된 일기의 날짜입니다.");
	gotoxy(45, 3);
	printf("키워드 : %s", keyword);



	gotoxy(1, 30);

}

void search_memo_UI(char *keyword)
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

	gotoxy(36, 2);
	printf("검색하신 키워드가 포함된 메모의 날짜입니다.");
	gotoxy(45, 3);
	printf("키워드 : %s", keyword);



	gotoxy(1, 30);

}

void exit_UI()
{
	int i;


	for (i = 6; i <= 19; i++)
	{
		gotoxy(18, i);
		printf("┃                                                 ┃");
	}

	gotoxy(18, 6);
	for (i = 0; i < 50; i++)
		printf("━");

	gotoxy(18, 20);
	for (i = 0; i < 50; i++)
		printf("━");



	gotoxy(18, 6);
	printf("┏");
	gotoxy(68, 6);
	printf("┓");
	gotoxy(18, 20);
	printf("┗");
	gotoxy(68, 20);
	printf("┛");

	gotoxy(32, 13);
	printf("프로그램을 종료합니다...");


	gotoxy(60, 13);
	printf("2");
	Sleep(1000);
	gotoxy(60, 13);
	printf("1");
	Sleep(1000);
	gotoxy(60, 13);
	printf("0");

	gotoxy(1, 30);
	system("cls");
}

void correct_password_UI()
{
	int i;

	for (i = 6; i <= 19; i++)
	{
		gotoxy(18, i);
		printf("┃                                                 ┃");
	}

	gotoxy(18, 6);
	for (i = 0; i < 50; i++)
		printf("━");

	gotoxy(18, 20);
	for (i = 0; i < 50; i++)
		printf("━");



	gotoxy(18, 6);
	printf("┏");
	gotoxy(68, 6);
	printf("┓");
	gotoxy(18, 20);
	printf("┗");
	gotoxy(68, 20);
	printf("┛");

	gotoxy(32, 13);
	printf("비밀번호가 일치합니다!");

	/*
	gotoxy(56, 13);
	printf("2");
	Sleep(1000);
	gotoxy(56, 13);
	printf("1");
	Sleep(1000);
	*/


	gotoxy(1, 30);
}











