
#include "MD_header.h"

typedef struct
{
    char date[11];
    int isSecure;
} DiaryLocation;

char select_date[11];  // 선택된 날짜를 저장


void secure_file(const char* filename, const char* password, Entry* entry);
void choose_menu(int cur_y);
void main_choose_test();
void write_diary_UI();
void write_entry(Entry* entry, const char* filename);
void ask_secure_UI(int cur_x);
void choose_diary_UI();
void show_diary_UI(char* selected_date, char* diary_content, int *source_file);
void show_diary(const char* date, char* content);
void sort_dates(char dates[100][11], int date_count);


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

    for (i = 0; i < HEIGHT; i++) {
        for (j = 0; j < WIDTH; j++) {
            if (date <= 31) {
                if (i == cur_y && j == cur_x) {
                    printf("┃[%2d]   ", date);
                }
                else {
                    printf("┃  %2d   ", date);
                }
                date++;
            }
            else {
                printf("┃       ");
            }
        }
        printf("┃\n");
        if (i != HEIGHT - 1) {
            printf("┣━━━━━━━╋━━━━━━━╋━━━━━━━╋━━━━━━━╋━━━━━━━╋━━━━━━━╋━━━━━━━┫\n");
        }
    }

    printf("┗━━━━━━━┻━━━━━━━┻━━━━━━━┻━━━━━━━┻━━━━━━━┻━━━━━━━┻━━━━━━━┛\n");

    gotoxy(1, 15);
    printf("날짜를 선택해주세요");
}
    

void main_cursor_test() 
{
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
    setlocale(LC_ALL, "");

    int cur_y = 0; // 상하로 이동하는 커서 위치
    int ch;

    while (1) {
        choose_menu(cur_y);

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
                write_diary_UI();
            else
                return 0; 
        }
        
        if (ch == 'q' || ch == 'Q')
            break;  // 'q' 또는 'Q'를 누르면 루프 종료
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

        printf("보안을 위한 비밀번호를 입력하세요: ");
        scanf("%s", password);

        secure_file(filename, password, entry);
        printf("일기가 보안 되었습니다.");
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


void choose_diary_UI_c()
{
    char dates[100][11] = { 0 }; // 일기 날짜를 저장할 배열
    int date_count = 0;  // 일기 날짜 개수
    int selected_index = 0;  // 현재 선택된 날짜의 인덱스
    int ch;
    char diary_content[MAX_LEN];

    // 일기의 출처를 저장하는 변수 추가
    int source_file[100];  // 0: 일반 파일, 1: 보안 파일

    // 일반 파일에서 날짜 가져오기
    FILE* file = fopen("diary.txt", "rb");
    if (file != NULL)
    {
        Entry entry;
        while (fscanf(file, "%[^|]|%[^|]|", entry.date, entry.content) != EOF)
        {
            strcpy(dates[date_count], entry.date);  // 날짜 저장
            source_file[date_count] = 0;
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
        while (fscanf(file, "%[^|]|%[^|]|%[^|]|", password, entry.date, entry.content) != EOF)
        {
            strcpy(dates[date_count], entry.date);  // 날짜 저장
            source_file[date_count] = 1;  // 보안 파일에서 읽어옴
            date_count++;
        }
        fclose(file);
    }

    sort_dates(dates, date_count);

    // 키보드로 날짜 선택
    while (1)
    {
        // UI 그리기
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
            // 선택한 날짜에 해당하는 일기 보여주기
            show_diary(dates[selected_index], diary_content, &source_file);  // 선택한 날짜의 일기 내용 가져오기
            show_diary_UI(dates[selected_index], diary_content, &source_file);
            return;
        }

        Sleep(100);  // CPU 사용량을 줄이기 위해 일시 정지
    }
}

void show_diary(const char* date, char* diary_content, int* source_file)
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
                // 보안된 일기라면 비밀번호를 물어봐야 합니다.
                char password[100] = "";
                printf("비밀번호를 입력하세요: ");
                scanf("%s", password);

                // 입력된 비밀번호가 일치하는지 확인
                if (strcmp(password, entry.password) == 0)
                {
                    strcpy(diary_content, entry.content);  // 일기 내용 복사
                    *source_file = 1;  // 일반 파일로 설정
                    fclose(file);
                    return;
                }
                else
                {
                    printf("비밀번호가 틀렸습니다.\n");
                    strcpy(diary_content, "비밀번호가 틀렸습니다.");  // 오류 메시지 복사
                    fclose(file);
                    return;
                }
            }
        }
        fclose(file);
    }

    // 일기를 찾지 못한 경우
    strcpy(diary_content, "일기를 찾지 못했습니다.");
}

// 날짜를 최근순으로 정렬해주기위해 날짜 문자열을 숫자로 변환하여 크기를 비교하여 가장 큰 숫자가 최근이 된다.
// 구현하기 쉬운 버블정렬을 사용, 효율은 별로지만 일기 날짜 정렬은 간단하기 때문에 성능 최적화가 따로 필요없기 때문에 버블을 사용
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





int main()
{
    //main_cursor_test();
    choose_diary_UI_c();
    return 0;

}






