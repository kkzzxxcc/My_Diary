
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

void show_diary_UI(char* selected_date, char* diary_content, int *source_file);
void show_memo_UI(char* selected_date, char* memo_content, int* source_file);
int show_diary(const char* date, char* content);
int show_memo(const char* date, char* content);

void sort_dates(char dates[100][11], int date_count);
void ask_secure_UI(int cur_x);
void ask_password_UI(char* password);
void save_secure_UI();
void check_password_UI(char* password);
void check_password_UI_2_0();
void exit_UI();
void delete_diary(char* selected_date, int source_file);
void change_diary(char* selected_date, int source_file);

void search_UI(char* keyword);
void search_diary_UI_c();
void search_diary_UI(char *keyword);
void search_memo_UI(char* keyword);
void search_memo_UI_c();


void gotoxy_c(int x, int y) 
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void print_calendar_ui(int cur_y, int cur_x) 
{
    system("cls");
    int i, j, date = 1;
    printf("┏━━━━━━━┳━━━━━━━┳━━━━━━━┳━━━━━━━┳━━━━━━━┳━━━━━━━┳━━━━━━━┓\n");

    for (i = 0; i < HEIGHT; i++) 
    {
        for (j = 0; j < WIDTH; j++) 
        {
            if (date <= 31) 
            {
                if (i == cur_y && j == cur_x) 
                {
                    printf("┃ [%2d]  ", date);
                }
                else 
                {
                    printf("┃  %2d   ", date);
                }
                date++;
            }
            else 
            {
                printf("┃       ");
            }
        }
        printf("┃\n");
        if (i != HEIGHT - 1) 
        {
            printf("┣━━━━━━━╋━━━━━━━╋━━━━━━━╋━━━━━━━╋━━━━━━━╋━━━━━━━╋━━━━━━━┫\n");
        }
    }

    printf("┗━━━━━━━┻━━━━━━━┻━━━━━━━┻━━━━━━━┻━━━━━━━┻━━━━━━━┻━━━━━━━┛\n");

    gotoxy(7, 13);
    printf("일기 또는 메모를 작성할 날짜를 선택해주세요");
}


void MD_main_test()
{

    int cur_y = 0; // 상하로 이동하는 커서 위치
    int ch;

    while (1) {
        MD_main_UI_c(cur_y);

        ch = _getch();
        switch (ch) 
        {
        case 72:  // UP
            cur_y = cur_y - 1 >= 0 ? cur_y - 1 : 0;
            break;
        case 80:  // DOWN
            cur_y = cur_y + 1 <= 3 ? cur_y + 1 : 3;
            break;

        case '\r':  // Enter key
            if (cur_y == 0)
                main_cursor_test(); // 커서 위치에 따라 날짜 선택화면으로 이동
            else if (cur_y == 1)
                search_diary_UI_c(); // 커서 위치에 따라 일기 검색하기로 이동
            else if (cur_y == 2)
                search_memo_UI_c(); // 커서 위치에 따라 메모 검색하기로 이동
            else if (cur_y == 3) // 커서 위치에 따라 프로그램 종료
            {
                exit_UI();
                exit(0);
            }
            else
                break;
        }

        if (ch == 'q' || ch == 'Q') 
        {
            exit_UI();
            break;  // 'q' 또는 'Q'를 누르면 루프 종료
        }
    }

    return 0;
}
    

void main_cursor_test() 
{
    setlocale(LC_ALL, ""); // 로캘 설정

    int cur_y = 1, cur_x = 3;
    int ch;

    Entry diary_entry;

    time_t t = time(NULL); // 현재 시간을 초 단위로 읽음
    struct tm tm = *localtime(&t); // 현재 시간을 구조체로 변환

    while (1) {
        system("cls");
        print_calendar_ui(cur_y, cur_x);

        ch = _getch();
        switch (ch) 
        {
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

        case '\r':  // Enter key
            sprintf(select_date, "%04d-%02d-%02d", tm.tm_year + 1900, tm.tm_mon + 1, cur_y * WIDTH + cur_x + 1);
            main_choose_test();
            break;

        case 'q':
            return;
        }
    }
}


void main_choose_test()
{
   
    int cur_y = 0; // 상하로 이동하는 커서 위치
    int ch;

    while (1) {
        choose_menu(cur_y); // 메뉴 선택하기 ui호출

        ch = _getch();
        switch (ch) {
        case 72:  // UP
            cur_y = cur_y - 1 >= 0 ? cur_y - 1 : 0;
            break;
        case 80:  // DOWN
            cur_y = cur_y + 1 <= 3 ? cur_y + 1 : 3;
            break;
        
        case '\r':  // Enter key
            if (cur_y == 0)
                write_diary_UI(); // 일기쓰기 ui 호출
            else if (cur_y == 1)
                write_memo_UI();  // 메모쓰기 ui 호출
            else if (cur_y == 2)
                choose_diary_UI_c(); // 일기 선택하기 ui 호출
            else if (cur_y == 3)
                choose_memo_UI_c();  // 메모 선택하기 ui 호출
            else
                return 0; 
        }
        
        if (ch == 'q' || ch == 'Q')
        {
            MD_main_test(); // 메인화면으로 돌아가기
            break;  // 'q' 또는 'Q'를 누르면 루프 종료
        }
            
    }

    return 0;
}

// 키보드의 방향키 좌우
int left_right_key()
{
    int ch = _getch();
    if (ch == 0 || ch == 224)
    {
        switch (_getch())
        {
        case 75: // 왼쪽 방향키
            return 0;
        case 77: // 오른쪽 방향키
            return 1;
        default:
            return -1;
        }
    }

    return -1;
}



void choose_diary_UI_c()
{
    char dates[100][11] = { 0 }; // 일기 날짜를 저장할 배열
    int date_count = 0;  // 일기 날짜 개수
    int selected_index = 0;  // 현재 선택된 날짜의 인덱스
    int ch;
    char diary_content[MAX_LEN];

    // 일기의 출처를 저장하는 변수
    int source_file[100] = { 0 };  // 0: 일반 파일, 1: 보안 파일

    // 일반 파일에서 날짜 가져오기
    FILE* file = fopen("diary.txt", "rb");
    if (file != NULL)
    {
        Entry entry;
        while (fscanf(file, "%[^|]|%[^|]|", entry.date, entry.content) != EOF)
        {
            strcpy(dates[date_count], entry.date);  // 날짜 저장
            source_file[date_count] = 0; // 일반파일 출처 저장
            date_count++;
        }
        fclose(file);
    }


    // 보안 파일에서 날짜 가져오기
    file = fopen("diary.txt.secure", "rb");
    if (file != NULL)
    {
        char password[100];
        Entry entry;
        while (fscanf(file, "%[^|]|%[^|]|%[^|]|", entry.password, entry.date, entry.content) != EOF)
        {
            strcpy(dates[date_count], entry.date);  // 날짜 저장
            source_file[date_count] = 1;  // 보안파일 출처 저장
            date_count++;
        }
        fclose(file);
    }

    // 날짜를 최근 순으로 정렬
    sort_dates(dates, date_count);

    // 키보드로 날짜 선택
    while (1)
    {
        // 날짜 선택 ui 
        choose_diary_UI();

        // 일기 날짜 출력
        int i;
        for (i = 0; i < date_count; i++)
        {
            gotoxy(10, 8 + i % 17);
            printf("%s", dates[i]);
        }

        // 현재 선택된 날짜 출력
        gotoxy(8, 8 + selected_index % 17);
        printf(">>");
        gotoxy(8, 25);
        printf(">>> %s", dates[selected_index]);

        // 키보드 입력 확인
        ch = _getch();
        switch (ch)
        {
        case 72:  // UP
            selected_index = selected_index - 1 >= 0 ? selected_index - 1 : 0;
            break;
        case 80:  // DOWN
            selected_index = selected_index + 1 < date_count ? selected_index + 1 : date_count - 1;
            break;
        case '\r':  // Enter key
        {
            // 선택한 날짜에 해당하는 일기 보여주기
            //show_diary(dates[selected_index], diary_content, &source_file[selected_index]);  // 선택한 날짜의 일기 내용 가져오기
            //show_diary_UI(dates[selected_index], diary_content, &source_file[selected_index]);
            //break;
            int result = show_diary(dates[selected_index], diary_content, &source_file[selected_index]);
            if (result == 0)  // 비밀번호가 맞았을 경우
            {
                show_diary_UI(dates[selected_index], diary_content, &source_file[selected_index]);
                return;
            }
            // 비밀번호가 틀렸을 경우, 다시 날짜 선택 화면으로 돌아감
            break;
        }
        }

        if (ch == 'q' || ch == 'Q')
        {
            main_choose_test(); // 메뉴 선택화면으로 돌아감
            break;  // 'q' 또는 'Q'를 누르면 루프 종료
        }

        Sleep(100);  // CPU 사용량을 줄이기 위해 일시 정지
    }
}

void choose_memo_UI_c()
{
    char dates[100][11] = { 0 }; // 메모 날짜를 저장할 배열
    int date_count = 0;  // 메모 날짜 개수
    int selected_index = 0;  // 현재 선택된 날짜의 인덱스
    int ch;
    char memo_content[MAX_LEN];

    // 메모의 출처를 저장하는 변수 추가
    int source_file[100] = { 0 };  // 0: 일반 파일, 1: 보안 파일

    // 일반 파일에서 날짜 가져오기
    FILE* file = fopen("memo.txt", "rb");
    if (file != NULL)
    {
        Entry entry;
        while (fscanf(file, "%[^|]|%[^|]|", entry.date, entry.content) != EOF)
        {
            strcpy(dates[date_count], entry.date);  // 날짜 저장
            source_file[date_count] = 0; // 일반파일 출처 저장
            date_count++;
        }
        fclose(file);
    }


    // 보안 파일에서 날짜 가져오기
    file = fopen("memo.txt.secure", "rb");
    if (file != NULL)
    {
        char password[100];
        Entry entry;
        while (fscanf(file, "%[^|]|%[^|]|%[^|]|", entry.password, entry.date, entry.content) != EOF)
        {
            strcpy(dates[date_count], entry.date);  // 날짜 저장
            source_file[date_count] = 1;  // 보안파일 출처 저장
            date_count++;
        }
        fclose(file);
    }

    sort_dates(dates, date_count);

    // 키보드로 날짜 선택
    while (1)
    {
        // 메모 선택 ui
        choose_memo_UI();

        // 메모 날짜 출력
        int i;
        for (i = 0; i < date_count; i++)
        {
            gotoxy(10, 8 + i % 17);
            printf("%s", dates[i]);
        }

        // 현재 선택된 날짜 출력
        gotoxy(8, 8 + selected_index % 17);
        printf(">>");
        gotoxy(8, 25);
        printf(">>> %s", dates[selected_index]);

        
        ch = _getch();
        switch (ch)
        {
        case 72:  // UP
            selected_index = selected_index - 1 >= 0 ? selected_index - 1 : 0;
            break;
        case 80:  // DOWN
            selected_index = selected_index + 1 < date_count ? selected_index + 1 : date_count - 1;
            break;
        case '\r':  // Enter key
        {
            // 선택한 날짜에 해당하는 메모 보여주기
            int result = show_memo(dates[selected_index], memo_content, &source_file[selected_index]);
            if (result == 0)  // 비밀번호가 맞았을 경우
            {
                show_memo_UI(dates[selected_index], memo_content, &source_file[selected_index]);
                return;
            }
            // 비밀번호가 틀렸을 경우, 다시 날짜 선택 화면으로 돌아갑니다.
            break;
        }
        }

        if (ch == 'q' || ch == 'Q')
        {
            main_choose_test(); // 메뉴 선택화면으로 돌아감
            break;  // 'q' 또는 'Q'를 누르면 루프 종료
        }

        Sleep(100);  // CPU 사용량을 줄이기 위해 일시 정지
    }
}

void show_diary_UI(char* selected_date, char* diary_content, int* source_file)
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

    gotoxy(40, 2);
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
                // 수정하기          일반파일인지 보안파일인지 값을 넘겨줌
                change_diary(selected_date, *source_file);
            }
            else
            {
                // 삭제하기          일반파일인지 보안파일인지 값을 넘겨줌
                delete_diary(selected_date, *source_file);
            }
            return;
        }

        if (ch == 'q' || ch == 'Q')
        {
            choose_diary_UI_c(); // 날짜 선택으로 돌아감
            break;  // 'q' 또는 'Q'를 누르면 루프 종료
        }

    }


    gotoxy(1, 30);
}

void show_memo_UI(char* selected_date, char* memo_content, int* source_file)
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

    gotoxy(40, 2);
    printf("%s 날짜의 메모입니다.", selected_date);

    gotoxy(8, 8);
    printf(">> %s", memo_content);

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
                change_memo(selected_date, *source_file);
            }
            else
            {
                // 삭제하기
                delete_memo(selected_date, *source_file);
            }
            return;
        }
        if (ch == 'q' || ch == 'Q')
        {
            choose_memo_UI_c(); // 메모 날짜 선택화면으로 돌아감
            break;  // 'q' 또는 'Q'를 누르면 루프 종료
        }

    }


    gotoxy(1, 30);

}


// 일기 검색 함수
void search_diary_UI_c()
{
    char keyword[MAX_LEN];
    search_UI(keyword);  // 검색할 키워드 입력받기

    // fgets 함수는 문자열 끝에 ' ' 문자를 포함시키므로 제거
    int len = strlen(keyword);
    if (keyword[len - 1] == ' ') keyword[len - 1] = '\0';

    char dates[100][11] = { 0 }; // 일기 날짜를 저장할 배열
    int date_count = 0;  // 일기 날짜 개수
    int selected_index = 0;  // 현재 선택된 날짜의 인덱스
    int ch;
    char diary_content[MAX_LEN];

    // 일기의 출처를 저장하는 변수 추가
    int source_file[100] = { 0 };  // 0: 일반 파일, 1: 보안 파일

    // 일반 파일에서 검색
    FILE * file = fopen("diary.txt", "rb");
    if (file != NULL)
    {
        Entry entry;
        while (fscanf(file, "%[^|]|%[^|]|", entry.date, entry.content) != EOF)
        {
            if (strstr(entry.content, keyword) != NULL)  // 일기 내용에 키워드가 포함되어 있는지 확인
            {
                strcpy(dates[date_count], entry.date);  // 날짜 저장
                source_file[date_count] = 0;  // 일반파일 출처 저장
                date_count++;
            }
        }
        fclose(file);
    }

    // 보안 파일에서 검색
    file = fopen("diary.txt.secure", "rb");
    if (file != NULL)
    {
        Entry entry;
        while (fscanf(file, "%[^|]|%[^|]|%[^|]|", entry.password, entry.date, entry.content) != EOF)
        {
            if (strstr(entry.content, keyword) != NULL)  // 일기 내용에 키워드가 포함되어 있는지 확인
            {
                strcpy(dates[date_count], entry.date);  // 날짜 저장
                source_file[date_count] = 1;  // 보안파일 출처 저장
                date_count++;
            }
        }
        fclose(file);
    }

    sort_dates(dates, date_count);

    // 키보드로 날짜 선택
    while (1)
    {
        // 검색 ui호출
        search_diary_UI(keyword);

        // 일기 날짜 출력
        int i;
        for (i = 0; i < date_count; i++)
        {
            gotoxy(10, 8 + i % 17);
            printf("%s", dates[i]);
        }

        // 현재 선택된 날짜 출력
        gotoxy(8, 8 + selected_index % 17);
        printf(">>");
        gotoxy(8, 25);
        printf(">>> %s", dates[selected_index]);

        // 키보드 입력 확인
        ch = _getch();
        switch (ch)
        {
        case 72:  // UP
            selected_index = selected_index - 1 >= 0 ? selected_index - 1 : 0;
            break;
        case 80:  // DOWN
            selected_index = selected_index + 1 < date_count ? selected_index + 1 : date_count - 1;
            break;
        case '\r':  // Enter key
        {
            // 선택한 날짜에 해당하는 일기 보여주기
            int result = show_diary(dates[selected_index], diary_content, &source_file[selected_index]);
            if (result == 0)  // 비밀번호가 맞았을 경우
            {
                show_diary_UI(dates[selected_index], diary_content, &source_file[selected_index]);
                return;
            }
            // 비밀번호가 틀렸을 경우, 다시 날짜 선택 화면으로 돌아갑니다.
            break;
        }
        }

        if (ch == 'q' || ch == 'Q')
        {
            break;  // 'q' 또는 'Q'를 누르면 루프 종료
        }

        Sleep(100);  // CPU 사용량을 줄이기 위해 일시 정지
    }
}

// 메모 검색 함수
void search_memo_UI_c()
{
    char keyword[MAX_LEN];
    search_UI(keyword);  // 키워드 입력받기

    // fgets 함수는 문자열 끝에 ' ' 문자를 포함시키므로 제거
    int len = strlen(keyword);
    if (keyword[len - 1] == ' ') keyword[len - 1] = '\0';

    char dates[100][11] = { 0 }; // 메모 날짜를 저장할 배열
    int memo_count = 0;  // 메모 날짜 개수
    int selected_index = 0;  // 현재 선택된 날짜의 인덱스
    int ch;
    char memo_content[MAX_LEN];

    // 메모의 출처를 저장하는 변수
    int source_file[100] = { 0 };  // 0: 일반 파일, 1: 보안 파일

    // 일반 파일에서 검색
    FILE* file = fopen("memo.txt", "rb");
    if (file != NULL)
    {
        Entry entry;
        while (fscanf(file, "%[^|]|%[^|]|", entry.date, entry.content) != EOF)
        {
            if (strstr(entry.content, keyword) != NULL)  // 메모 내용에 키워드가 포함되어 있는지 확인
            {
                strcpy(dates[memo_count], entry.date);  // 날짜 저장
                source_file[memo_count] = 0;  // 일반파일 출처 저장
                memo_count++;
            }
        }
        fclose(file);
    }

    // 보안 파일에서 검색
    file = fopen("memo.txt.secure", "rb");
    if (file != NULL)
    {
        Entry entry;
        while (fscanf(file, "%[^|]|%[^|]|%[^|]|", entry.password, entry.date, entry.content) != EOF)
        {
            if (strstr(entry.content, keyword) != NULL)  // 일기 내용에 키워드가 포함되어 있는지 확인
            {
                strcpy(dates[memo_count], entry.date);  // 날짜 저장
                source_file[memo_count] = 1;  // 보안파일 출처 저장
                memo_count++;
            }
        }
        fclose(file);
    }

    sort_dates(dates, memo_count);

    // 키보드로 날짜 선택
    while (1)
    {
        // 메모 검색 ui
        search_memo_UI(keyword);

        // 메모 날짜 출력
        int i;
        for (i = 0; i < memo_count; i++)
        {
            gotoxy(10, 8 + i % 17);
            printf("%s", dates[i]);
        }

        // 현재 선택된 날짜 출력
        gotoxy(8, 8 + selected_index % 17);
        printf(">>");
        gotoxy(8, 25);
        printf(">>> %s", dates[selected_index]);

        // 키보드 입력 확인
        ch = _getch();
        switch (ch)
        {
        case 72:  // UP
            selected_index = selected_index - 1 >= 0 ? selected_index - 1 : 0;
            break;
        case 80:  // DOWN
            selected_index = selected_index + 1 < memo_count ? selected_index + 1 : memo_count - 1;
            break;
        case '\r':  // Enter key
        {
            // 선택한 날짜에 해당하는 메모 보여주기
            int result = show_memo(dates[selected_index], memo_content, &source_file[selected_index]);
            if (result == 0)  // 비밀번호가 맞았을 경우
            {
                show_memo_UI(dates[selected_index], memo_content, &source_file[selected_index]);
                return;
            }
            // 비밀번호가 틀렸을 경우, 다시 날짜 선택 화면으로 돌아갑니다.
            break;
        }
        }

        if (ch == 'q' || ch == 'Q')
        {
            break;  // 'q' 또는 'Q'를 누르면 루프 종료
        }

        Sleep(100);  // CPU 사용량을 줄이기 위해 일시 정지
    }
}



// 날짜를 최근순으로 정렬해주기위해 날짜 문자열을 숫자로 변환하여 크기를 비교하여 가장 큰 숫자가 최근이 된다.
// 구현하기 쉬운 버블정렬을 사용, 효율은 별로지만 일기 날짜 정렬은 간단하기 때문에  버블을 사용
void sort_dates(char dates[100][11], int date_count)
{
    int i, j;
    for (i = 0; i < date_count - 1; i++)
    {
        for (j = 0; j < date_count - i - 1; j++)
        {
            // 날짜를 숫자로 변환
            int year1, month1, day1, date_num1;
            sscanf(dates[j], "%d-%d-%d", &year1, &month1, &day1);
            date_num1 = year1 * 10000 + month1 * 100 + day1;

            int year2, month2, day2, date_num2;
            sscanf(dates[j + 1], "%d-%d-%d", &year2, &month2, &day2);
            date_num2 = year2 * 10000 + month2 * 100 + day2;

            // 날짜 비교 및 교환
            if (date_num1 < date_num2)
            {
                char temp[12];  // 'temp' 변수의 크기를 12로 설정
                strcpy(temp, dates[j]);
                strcpy(dates[j], dates[j + 1]);
                strcpy(dates[j + 1], temp);
            }
        }
    }
}












