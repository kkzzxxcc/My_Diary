
#include "MD_header.h"


void MD_main_UI_c(int cur_y);
void secure_file(const char* filename, const char* password, Entry* entry);
void choose_menu(int cur_y);
void main_choose_test();

void write_diary_UI();
void write_memo_UI();
void write_entry(Entry* entry, const char* filename);

void choose_diary_UI();
void choose_memo_UI();

void choose_diary_UI_c();
void choose_memo_UI_c();

void show_diary_UI(char* selected_date, char* diary_content, int* source_file);
void show_memo_UI(char* selected_date, char* memo_content, int* source_file);
int show_memo(const char* date, char* content);

void sort_dates(char dates[100][11], int date_count);
void ask_secure_UI(int cur_x);
void ask_password_UI(char* password);
void save_secure_UI();
void check_password_UI(char* password);
void check_password_UI_m(char* password);
void check_password_UI_2_0();
void exit_UI();
void delete_memo(char* selected_date, int source_file);
void change_memo(char* selected_date, int source_file);


// 메모쓰기 함수
void write_memo(Entry* entry, const char* filename)
{
    int secure = 0;
    int cur_x = 0;
    int ch;

    while (1)
    {
        ask_secure_UI(cur_x);  

        ch = _getch();
        switch (ch) 
		{
			case 75:  // LEFT
				cur_x = cur_x - 1 >= 0 ? cur_x - 1 : 0;
				break;
			case 77:  // RIGHT
				cur_x = cur_x + 1 <= 1 ? cur_x + 1 : 1;
				break;

			case '\r':  // Enter key
				secure = cur_x == 0 ? 1 : 0;  
				break;
        }

        if (ch == '\r')
            break;  
    }

    if (secure)
    {
        // 비밀번호 입력
        char password[100];

        ask_password_UI(password);

        secure_file(filename, &password, entry);
        save_secure_UI();
    }
    else
    {
        FILE* file = fopen(filename, "ab"); // 'ab' 모드로 오픈 파일이 이미 있다면 이어쓰기 가능

        if (file != NULL)
        {
            fprintf(file, "%s|%s|", entry->date, entry->content); // '|' 문자로 날짜와 내용을 구분

            fclose(file); 

            printf("메모가 저장되었습니다.");
        }
        else
        {
            printf("파일을 열 수 없습니다.");
        }
    }
}

int show_memo(const char* date, char* memo_content, int* source_file)
{
	// 일반 파일에서 메모 내용 가져오기
	if (*source_file == 0)
	{
		FILE* file = fopen("memo.txt", "rb");
		if (file != NULL)
		{
			Entry entry;
			while (fscanf(file, "%[^|]|%[^|]|", entry.date, entry.content) != EOF)
			{
				if (strcmp(date, entry.date) == 0)  // 선택된 날짜와 일치하는지 확인
				{
					strcpy(memo_content, entry.content);  // 메모 내용 복사
					*source_file = 0;  // 일반 파일로 설정
					fclose(file);
					return;
				}
			}
			fclose(file);
		}
	}

	// 보안 파일에서 메모 내용 가져오기
	else if (*source_file == 1)
	{
		FILE *file = fopen("memo.txt.secure", "rb");
		if (file != NULL)
		{
			Entry entry;
			while (fscanf(file, "%[^|]|%[^|]|%[^|]|", entry.password, entry.date, entry.content) != EOF)
			{
				if (strcmp(date, entry.date) == 0)  // 선택된 날짜와 일치하는지 확인
				{
					// 보안된 메모라면 비밀번호를 물어봐야 합니다.
					char password[100] = "";
					check_password_UI_m(password);

					// 입력된 비밀번호가 일치하는지 확인
					if (strcmp(&password, entry.password) == 0)
					{
						strcpy(memo_content, entry.content);  // 일기 내용 복사
						*source_file = 1;  // 보안 파일로 설정
						fclose(file);
						return 0;
					}
					else
					{
						check_password_UI_2_0();
						fclose(file);
						return -1;
					}
				}
			}
			fclose(file);
		}
	}

	strcpy(memo_content, "메모를 찾지 못했습니다.");
	return -1;
}

void change_memo(char* selected_date, int source_file)
{
	char new_content[MAX_LEN];
	gotoxy(10, 12);
	printf("새로운 메모 내용을 입력하세요>> ");
	fgets(new_content, MAX_LEN, stdin);

	int len = strlen(new_content);
	if (new_content[len - 1] == ' ')
		new_content[len - 1] = '\0';

	if (source_file == 0)
	{
		// 일반 파일에서 일기 내용 수정하기
		FILE* file = fopen("memo.txt", "rb");
		FILE* temp_file = fopen("temp.txt", "wb");
		if (file != NULL && temp_file != NULL)
		{
			Entry entry;
			int change = 0;
			while (fscanf(file, "%[^|]|%[^|]|", entry.date, entry.content) != EOF)
			{
				if (strcmp(selected_date, entry.date) == 0)  // 선택된 날짜와 일치하는지 확인
				{
					strcpy(entry.content, new_content);  // 일기 내용 수정
					change = 1;  // 수정값
				}

				if (change)  // 수정된 경우
				{
					fprintf(temp_file, "%s|%s|", entry.date, new_content);  // 수정된 일기 내용을 임시 파일에 쓰기
					change = 0;  // 수정깂 초기화
				}
				else  // 수정되지 않은 경우
				{
					fprintf(temp_file, "%s|%s|", entry.date, entry.content);  // 원래 일기 내용을 임시 파일에 쓰기
				}

				fclose(file);
				fclose(temp_file);
			}

			// 원래 파일에 수정된 내용을 덮어쓰기
			remove("memo.txt");
			rename("temp.txt", "memo.txt");
			choose_memo_UI_c();
			
		}
	}

	// 보안 파일에서 메모 내용 수정하기
	else if (source_file == 1)
	{
		// 보안 파일에서 메모 내용 수정하기
		FILE* file = fopen("memo.txt.secure", "rb");
		FILE* temp_file = fopen("temp.txt.secure", "wb");
		if (file != NULL && temp_file != NULL)
		{
			Entry entry;
			int change = 0;
			while (fscanf(file, "%[^|]|%[^|]|%[^|]|", entry.password, entry.date, entry.content) != EOF)
			{
				if (strcmp(selected_date, entry.date) == 0)  // 선택된 날짜와 일치하는지 확인
				{
					strcpy(entry.content, new_content);  // 일기 내용 수정
					change = 1;  // 수정값
				}

				if (change)  // 수정된 경우
				{
					fprintf(temp_file, "%s|%s|%s|", entry.password, entry.date, new_content);  // 수정된 일기 내용을 임시 파일에 쓰기
					change = 0;  // 수정값 초기화
				}
				else 
				{
					fprintf(temp_file, "%s|%s|%s|", entry.password, entry.date, entry.content);  // 원래 일기 내용을 임시 파일에 쓰기
				}
			}
			fclose(file);
			fclose(temp_file);

			// 원래 파일에 수정된 내용을 덮어쓰기
			remove("memo.txt.secure");
			rename("temp.txt.secure", "memo.txt.secure");
			choose_memo_UI_c();
		}
	}

	else
	{
		printf("수정하지 못하였습니다.");
		choose_memo_UI_c();
	}
}

void delete_memo(char* selected_date, int source_file)
{
	// 일반 파일에서 메모 삭제하기
	if (source_file == 0)
	{
		FILE* file = fopen("memo.txt", "rb");
		FILE* temp_file = fopen("temp.txt", "wb");
		if (file != NULL && temp_file != NULL)
		{
			Entry entry;
			while (fscanf(file, "%[^|]|%[^|]|", entry.date, entry.content) != EOF)
			{
				if (strcmp(selected_date, entry.date) != 0)  // 선택된 날짜와 일치하지 않는지 확인
				{
					fprintf(temp_file, "%s|%s|\n", entry.date, entry.content);  // 선택된 날짜가 아닌 메모 내용을 임시 파일에 쓰기
				}
			}
			fclose(file);
			fclose(temp_file);

			// 원래 파일에 수정된 내용을 덮어쓰기
			remove("memo.txt");
			rename("temp.txt", "memo.txt");
			choose_memo_UI_c();
		}
	}

	// 보안 파일에서 메모 삭제하기
	else if (source_file == 1)
	{
		FILE* file = fopen("memo.txt.secure", "rb");
		FILE* temp_file = fopen("temp.txt.secure", "wb");
		if (file != NULL && temp_file != NULL)
		{
			Entry entry;
			while (fscanf(file, "%[^|]|%[^|]|%[^|]|", entry.password, entry.date, entry.content) != EOF)
			{
				if (strcmp(selected_date, entry.date) != 0)  // 선택된 날짜와 일치하지 않는지 확인
				{
					fprintf(temp_file, "%s|%s|%s|\n", entry.password, entry.date, entry.content);  // 선택된 날짜가 아닌 메모 내용을 임시 파일에 쓰기
				}
			}
			fclose(file);
			fclose(temp_file);

			// 원래 파일에 수정된 내용을 덮어쓰기
			remove("memo.txt.secure");
			rename("temp.txt.secure", "memo.txt.secure");
			choose_memo_UI_c();
		}
	}

	else
	{
		printf("삭제하지 못하였습니다.");
		choose_memo_UI_c();
	}
}
