
#include "MD_header.h"


void secure_file(const char* filename, const char* password, Entry* entry);
void write_entry(Entry* entry, const char* filename);
void ask_secure_UI(int cur_x);
void ask_password_UI(char* password);
void save_secure_UI();
void exit_UI();
void secure_file(const char* filename, const char* password, Entry* entry);
void choose_diary_UI_c();
void show_diary_UI(char* selected_date, char* diary_content, int* source_file);
int show_diary(const char* date, char* content);
void check_password_UI(char* password);
void check_password_UI_2_0();
void delete_diary(char* selected_date, int source_file);
void change_diary(char* selected_date, int source_file);

// 파일쓰기 함수
void write_entry(Entry* entry, const char* filename)
{
    int secure = 0;
    int cur_x = 0;
    int ch;

    while (1)
    {
        ask_secure_UI(cur_x);  // 보안 UI에 현재 선택 위치 전달

        ch = _getch();
        switch (ch) {
        case 75:  // LEFT
            cur_x = cur_x - 1 >= 0 ? cur_x - 1 : 0;
            break;
        case 77:  // RIGHT
            cur_x = cur_x + 1 <= 1 ? cur_x + 1 : 1;
            break;

        case '\r':  // Enter key
            secure = cur_x == 0 ? 1 : 0;  // 현재 선택 위치가 보안 여부
            break;
        }

        if (ch == '\r')
            break;  // 엔터를 누르면 루프 종료
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
        // 한글 문자열을 제대로 사용하기 위해 텍스트 모드가 아닌 바이너리 모드 사용

        if (file != NULL)
        {
            fprintf(file, "%s|%s|", entry->date, entry->content); // '|' 문자로 날짜와 내용을 구분

            fclose(file); // 파일 닫기

            printf("일기가 저장되었습니다.");
        }
        else
        {
            printf("파일을 열 수 없습니다.");
        }
    }
}


int show_diary(const char* date, char* diary_content, int* source_file)
{
    // 일반 파일에서 일기 내용 가져오기
    FILE* file = fopen("diary.txt", "rb");
    if (file != NULL)
    {
        Entry entry;
        while (fscanf(file, "%[^|]|%[^|]|", entry.date, entry.content) != EOF)
        {
            if (strcmp(date, entry.date) == 0)  // 선택된 날짜와 일치하는지 확인
            {
                strcpy(diary_content, entry.content);  // 일기 내용 복사
                *source_file = 0;  // 일반 파일로 설정
                fclose(file);
                return;
            }
        }
        fclose(file);
    }

    // 보안 파일에서 일기 내용 가져오기
    file = fopen("diary.txt.secure", "rb");
    if (file != NULL)
    {
        Entry entry;
        while (fscanf(file, "%[^|]|%[^|]|%[^|]|", entry.password, entry.date, entry.content) != EOF)
        {
            if (strcmp(date, entry.date) == 0)  // 선택된 날짜와 일치하는지 확인
            {
                // 보안된 일기라면 비밀번호를 물어봄
                char password[100] = "";
                check_password_UI(password);

                // 입력된 비밀번호가 일치하는지 확인
                if (strcmp(password, entry.password) == 0)
                {
                    strcpy(diary_content, entry.content);  // 일기 내용 복사
                    *source_file = 1;  // 보안 파일로 설정
                    fclose(file);
                    return 0;
                }
                else
                {
                    //strcpy(diary_content, "비밀번호가 틀렸습니다.");  // 오류 메시지 복사
                    check_password_UI_2_0();
                    fclose(file);
                    return -1;
                }
            }
        }
        fclose(file);
    }

    // 일기를 찾지 못한 경우
    strcpy(diary_content, "일기를 찾지 못했습니다.");
}

/*
void change_diary(char* selected_date, int source_file)
{
	char new_content[MAX_LEN];
	gotoxy(10, 12);
	printf("새로운 일기 내용을 입력하세요>> ");
	//scanf("%[^\n]", new_content);
	//getchar(); // 줄 바꿈 문자를 제거합니다.
	fgets(new_content, MAX_LEN, stdin);
	// fgets 함수는 문자열 끝에 '\n' 문자를 포함시키므로 이를 제거합니다.
	int len = strlen(new_content);
	if (new_content[len - 1] == '\n') new_content[len - 1] = '\0';

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
*/
void change_diary(char* selected_date, int source_file)
{
    char new_content[MAX_LEN];
    gotoxy(10, 12);
    printf("새로운 일기 내용을 입력하세요>> ");
    fgets(new_content, MAX_LEN, stdin);

    // fgets 함수는 문자열 끝에 '' 문자를 포함시키므로 이를 제거합니다.
    int len = strlen(new_content);
    if (new_content[len - 1] == ' ') 
        new_content[len - 1] = '\0';

    if (source_file == 0)
    {
        FILE* file = fopen("diary.txt", "rb");
            FILE* temp_file = fopen("temp.txt", "wb");
            if (file != NULL && temp_file != NULL)
            {
                Entry entry;
                int ischange = 0;
                while (fscanf(file, "%[^|]|%[^|]|", entry.date, entry.content) != EOF)
                {
                    if (strcmp(selected_date, entry.date) == 0)  // 선택된 날짜와 일치하는지 확인
                    {
                        strcpy(entry.content, new_content);  // 일기 내용 수정
                        ischange = 1;  // 수정 플래그 설정
                    }

                    if (ischange)  // 수정된 경우
                    {
                        fprintf(temp_file, "%s|%s|", entry.date, entry.content);  // 수정된 일기 내용을 임시 파일에 쓰기
                        ischange = 0;  // 수정 플래그 초기화
                    }
                    else  // 수정되지 않은 경우
                    {
                        fprintf(temp_file, "%s|%s|", entry.date, entry.content);  // 원래 일기 내용을 임시 파일에 쓰기
                    }
                }
                fclose(file);
                fclose(temp_file);

                remove("diary.txt");
                rename("temp.txt", "diary.txt");
                choose_diary_UI_c();
            }
    }
    else if (source_file == 1)
    {
        FILE* file = fopen("diary.txt.secure", "rb");
        FILE* temp_file = fopen("temp.txt.secure", "wb");
        if (file != NULL && temp_file != NULL)
        {
            Entry entry;
            while (!feof(file))
            {
                fscanf(file, "%[^|]|%[^|]|%[^|]|", entry.password, entry.date, entry.content);
                if (strcmp(selected_date, entry.date) == 0)  // 선택된 날짜와 일치하는지 확인
                {
                    strcpy(entry.content, new_content);  // 일기 내용 수정
                    fprintf(temp_file, "%s|%s|%s|", entry.password, entry.date, entry.content);  // 수정된 일기 내용을 임시 파일에 쓰기
                }
                else
                {
                    fprintf(temp_file, "%s|%s|%s|", entry.password, entry.date, entry.content);  // 원래 일기 내용을 임시 파일에 쓰기
                }
            }
            fclose(file);
            fclose(temp_file);

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