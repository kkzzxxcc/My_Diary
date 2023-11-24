
#include "MD_header.h"



void gotoxy(int x, int y);
void MD_main_UI();        // 메인 화면
void gotoxy_c(int x, int y);
void write_entry(Entry* entry, const char* filename);
void change_diary(char* selected_date);
void delete_diary(char* selected_date);
void choose_diary_UI_c();


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

void print_calendar_ui_t1() {
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

	gotoxy(13, 16);
	printf("1. 달력 보기");
	gotoxy(13, 20);
	printf("2. 종료");
	gotoxy(1, 30);
	printf("END");

	// '달력 보기'와 '종료'에 대해 현재 선택된 항목을 표시
	gotoxy(13, 16);
	if (cur_y == 0)
		printf("> 1. 달력 보기");
	else
		printf("  1. 달력 보기");

	gotoxy(13, 20);
	if (cur_y == 1)
		printf("> 2. 종료");
	else
		printf("  2. 종료");

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

	gotoxy(40, 2);
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
	printf("END");

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
	char line[101];  // 한 줄의 일기 내용을 임시 저장할 변수

	for (i = 0; i < 27; i++) {  // 각 줄에 대해
		gotoxy(20, 8 + i);  // 새로운 줄의 시작 좌표 설정
		fgets(line, 101, stdin);  // 한 줄의 일기 내용을 임시 변수에 저장

		// 엔터를 두 번 입력하면 일기 작성 종료
		if (strcmp(line, "\n") == 0) 
		{
			break;
		}

		strcpy(&diary_entry.content[j], line);  // 임시 변수의 내용을 diary_entry.content에 복사
		j += strlen(line);  // 다음 줄의 시작 위치로 이동
	}



	//fgets(diary_entry.content, sizeof(diary_entry.content), stdin);

	// 일기 내용을 파일에 쓰기
	write_entry(&diary_entry, "diary.txt");

	gotoxy(1, 30);
	printf("END");


}

void write_memo_UI()
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

	gotoxy(40, 2);
	printf("작성일 : %s", select_date);

	gotoxy(5, 8);
	printf("메모 작성중 >>");

	gotoxy(1, 30);
	printf("END");

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

	// 현재 선택 위치에 따라 강조 표시
	gotoxy(30, 16);
	printf(cur_x == 0 ? "> 예 " : " 예");
	gotoxy(51, 16);
	printf(cur_x == 1 ? "> 아니오 " : " 아니오");

	/*
	gotoxy(80, 20);
	printf("3");
	Sleep(1000);
	gotoxy(80, 20);
	printf("2");
	Sleep(1000);
	gotoxy(80, 20);
	printf("1");
	Sleep(1000);
	*/

	gotoxy(1, 30);
	printf("END");
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
	printf("END");

}

void show_diary_UI(char* selected_date, char* diary_content, int *source_file)
{
	system("cls");
	int i;
	int ch;
	int cur_x = 0;

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
	printf("%s 날짜의 일기입니다.", selected_date);

	gotoxy(8, 8);
	printf(">> %s", diary_content);

	// 키보드로 명령 선택
	while (1)
	{
		gotoxy(21, 25);
		printf(cur_x == 0 ? "[ 수정하기 ]" : "  수정하기  ");

		gotoxy(80, 25);
		printf(cur_x == 1 ? "[ 삭제하기 ]" : "  삭제하기  ");

		ch = _getch();
		switch (ch)
		{
		case 75:  // LEFT
			cur_x = 0;
			break;
		case 77:  // RIGHT
			cur_x = 1;
			break;
		case '\r':  // Enter key
			if (cur_x == 0)
			{
				// 수정하기
				change_diary(selected_date, *source_file);
			}
			else
			{
				// 삭제하기
				delete_diary(selected_date, *source_file);
			}
			return;
		}

	}


	gotoxy(1, 30);
	printf("END");
}

void change_diary(char* selected_date, int source_file)
{
	char new_content[MAX_LEN];
	gotoxy(10, 12);
	printf("새로운 일기 내용을 입력하세요>> ");
	fgets(new_content, MAX_LEN, stdin);

	if (source_file == 0)
	{
		// 일반 파일에서 일기 내용 수정하기
		FILE* file = fopen("diary.txt", "rb");
		FILE* temp_file = fopen("temp.txt", "wb");
		if (file != NULL && temp_file != NULL)
		{
			Entry entry;
			while (fscanf(file, "%[^|]|%[^|]|", entry.date, entry.content) != EOF)
			{
				if (strcmp(selected_date, entry.date) == 0)  // 선택된 날짜와 일치하는지 확인
				{
					strcpy(entry.content, new_content);  // 일기 내용 수정
				}
				fprintf(temp_file, "%s|%s|\n", entry.date, entry.content);  // 수정된 일기 내용을 임시 파일에 쓰기
			}
			fclose(file);
			fclose(temp_file);

			// 원래 파일에 수정된 내용을 덮어쓰기
			remove("diary.txt");
			rename("temp.txt", "diary.txt");
			choose_diary_UI_c();
		}
	}

	// 보안 파일에서 일기 내용 수정하기
	else if (source_file == 1)
	{
		// 보안 파일에서 일기 내용 수정하기
		FILE* file = fopen("diary.txt.secure", "rb");
		FILE* temp_file = fopen("temp.txt.secure", "wb");
		if (file != NULL && temp_file != NULL)
		{
			Entry entry;
			while (fscanf(file, "%[^|]|%[^|]|%[^|]|", entry.password, entry.date, entry.content) != EOF)
			{
				if (strcmp(selected_date, entry.date) == 0)  // 선택된 날짜와 일치하는지 확인
				{
					strcpy(entry.content, new_content);  // 일기 내용 수정
				}
				fprintf(temp_file, "%s|%s|%s|\n", entry.password, entry.date, entry.content);  // 수정된 일기 내용을 임시 파일에 쓰기
			}
			fclose(file);
			fclose(temp_file);

			// 원래 파일에 수정된 내용을 덮어쓰기
			remove("diary.txt.secure");
			rename("temp.txt.secure", "diary.txt.secure");
			choose_diary_UI_c();
		}
	}

	else
	{
		printf("수정하지 못하였습니다.");
		choose_diary_UI_c();
	}
}

void delete_diary(char* selected_date, int source_file)
{
	// 일반 파일에서 일기 삭제하기
	if (source_file == 0)
	{
		FILE* file = fopen("diary.txt", "rb");
		FILE* temp_file = fopen("temp.txt", "wb");
		if (file != NULL && temp_file != NULL)
		{
			Entry entry;
			while (fscanf(file, "%[^|]|%[^|]|", entry.date, entry.content) != EOF)
			{
				if (strcmp(selected_date, entry.date) != 0)  // 선택된 날짜와 일치하지 않는지 확인
				{
					fprintf(temp_file, "%s|%s|\n", entry.date, entry.content);  // 선택된 날짜가 아닌 일기 내용을 임시 파일에 쓰기
				}
			}
			fclose(file);
			fclose(temp_file);

			// 원래 파일에 수정된 내용을 덮어쓰기
			remove("diary.txt");
			rename("temp.txt", "diary.txt");
			choose_diary_UI_c();
		}
	}

	// 보안 파일에서 일기 삭제하기
	else if (source_file == 1)
	{
		FILE* file = fopen("diary.txt.secure", "rb");
		FILE* temp_file = fopen("temp.txt.secure", "wb");
		if (file != NULL && temp_file != NULL)
		{
			Entry entry;
			while (fscanf(file, "%[^|]|%[^|]|%[^|]|", entry.password, entry.date, entry.content) != EOF)
			{
				if (strcmp(selected_date, entry.date) != 0)  // 선택된 날짜와 일치하지 않는지 확인
				{
					fprintf(temp_file, "%s|%s|%s|\n", entry.password, entry.date, entry.content);  // 선택된 날짜가 아닌 일기 내용을 임시 파일에 쓰기
				}
			}
			fclose(file);
			fclose(temp_file);

			// 원래 파일에 수정된 내용을 덮어쓰기
			remove("diary.txt.secure");
			rename("temp.txt.secure", "diary.txt.secure");
			choose_diary_UI_c();
		}
	}

	else
	{
		printf("삭제하지 못하였습니다.");
		choose_diary_UI_c();
	}
}









