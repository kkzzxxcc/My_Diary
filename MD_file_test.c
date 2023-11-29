// 파일 입출력 테스트
#include "MD_header.h"

void print_calendar_ui(int cur_y, int cur_x);
void gotoxy_c(int x, int y);

void main_cursor_test();
void MD_main_UI();
void MD_main_UI_c(int cur_y);


// 보안 파일에 저장할 때
void secure_file(const char* filename, const char* password, Entry* entry)
{
    char secure_filename[100];
    sprintf(secure_filename, "%s.secure", filename); // 기존 파일 이름에 .secure 확장자를 붙여서 보안 파일 생성

    FILE* secure_file = fopen(secure_filename, "ab");

    if (secure_file != NULL)
    {
        // 보안 파일에 비밀번호와 일기 내용 추가
        fprintf(secure_file, "%s|%s|%s|", password, entry->date, entry->content);

        fclose(secure_file);
    }
    else
    {
        printf("보안에 실패했습니다.");
    }
}


// 보안 파일을 읽을 때
void read_secure_file(const char* filename)
{
    // 비밀번호 입력
    char password[100];
    printf("비밀번호를 입력하세요: ");
    scanf("%s", password);

    char secure_filename[100];
    sprintf(secure_filename, "%s.secure", filename); // 보안 파일 이름 생성

    FILE* secure_file = fopen(secure_filename, "rb");

    if (secure_file != NULL)
    {
        Entry entry;
        char stored_password[100];

        // 보안 파일에서 비밀번호와 일기 내용을 읽음
        while (fscanf(secure_file, "%[^|]|%[^|]|%[^|]|", stored_password, entry.date, entry.content) != EOF)
        {
            // 비밀번호 확인
            if (strcmp(password, stored_password) == 0)
            {
                // 비밀번호가 일치하면 일기 내용을 출력
                printf("날짜: %s 일기 내용 : % s", entry.date, entry.content);
            }
            else
            {
                // 비밀번호가 일치하지 않으면 액세스 거부 메시지 출력
                printf("액세스가 거부되었습니다. 비밀번호가 일치하지 않습니다.");
                break;
            }
        }

        fclose(secure_file);
    }
    else
    {
        printf("파일을 열 수 없습니다.");
    }
}


void write_test() 
{
    setlocale(LC_ALL, ""); // 로캘 설정

    Entry diary_entry;

    strcpy(diary_entry.date, select_date);  // 선택된 날짜

    printf("일기 내용을 입력하세요 : ");
    fgets(diary_entry.content, sizeof(diary_entry.content), stdin);

    time_t t = time(NULL); // 현재 시간을 초 단위로 읽음
    struct tm tm = *localtime(&t); // 현재 시간을 구조체로 변환

    // 일기 내용 끝에 현재 시간 추가
    char current_time[20];
    sprintf(current_time, "\n작성 시간: %04d-%02d-%02d %02d:%02d:%02d",
        tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday,
        tm.tm_hour, tm.tm_min, tm.tm_sec);
    strcat(diary_entry.content, current_time);

    write_entry(&diary_entry, "diary.txt");  

    /*
    char answer;
    printf("보안 파일을 읽으시겠습니까? (y/n): ");
    scanf(" %c", &answer);

    if (answer == 'y' || answer == 'Y')
    {
        read_secure_file("diary.txt");
    }
    else
    {
        read_entry("diary.txt");
    }
    */
    

    return 0;
}

void main_test2()
{
    setlocale(LC_ALL, "");

    int cur_y = 0; // 상하로 이동하는 커서 위치
    int ch;

    while (1) {
        system("cls");
        MD_main_UI_c(cur_y);

        ch = _getch();
        switch (ch) {
        case 72:  // UP
            cur_y = cur_y - 1 >= 0 ? cur_y - 1 : 1;
            break;
        case 80:  // DOWN
            cur_y = (cur_y + 1) % 2;
            break;
        case '\r':  // Enter key
            if (cur_y == 0)
                main_cursor_test();
            else
                return 0;
            break;
        }
    }

    return 0;
}



