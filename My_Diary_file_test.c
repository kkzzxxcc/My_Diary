// 파일 입출력 테스트
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <locale.h>

#define MAX_LEN 1000 // 일기 내용을 위한 최대 문자 수

// 일기 또는 메모의 날짜와 내용을 저장하는 구조체
typedef struct
{
    char date[11]; // YYYY-MM-DD 형식의 날짜
    char content[MAX_LEN]; // 일기 또는 메모 내용
} Entry;

// 일기 파일 보안 함수
void secure_file(const char* filename)
{
    char secure_filename[100];
    sprintf(secure_filename, "%s.secure", filename); // 기존 파일 이름에 .secure 확장자를 붙여서 보안 파일 이름 생성

    // 기존 파일을 읽어오기
    FILE* file = fopen(filename, "rb");
    FILE* secure_file = fopen(secure_filename, "ab");

    if (file != NULL && secure_file != NULL)
    {
        Entry entry;

        while (fscanf(file, "%[^|]|%[^|]|", entry.date, entry.content) != EOF)
        {
            // 보안 파일에 일기 내용 추가
            fprintf(secure_file, "%s|%s|", entry.date, entry.content);
        }

        fclose(file);
        fclose(secure_file);

        // 기존 파일 삭제
        remove(filename);

        // 보안 파일 이름을 기존 파일 이름으로 변경
        //rename(secure_filename, filename);

        printf("파일이 보안되었습니다.\n");
    }

    else
    {
        printf("파일 보안에 실패했습니다.\n");
    }
}


// 파일쓰기 함수
void write_entry(Entry* entry, const char* filename)
{
    FILE* file = fopen(filename, "ab"); // 'ab' 모드로 오픈 파일이 이미 있다면 이어쓰기 가능
    // 한글 문자열을 제대로 사용하기 위해 텍스트 모드가 아닌 바이너리 모드 사용

    if (file != NULL) 
    {
        fprintf(file, "%s|%s|", entry->date, entry->content); // '|' 문자로 날짜와 내용을 구분

        fclose(file); // 파일 닫기

        printf("일기가 저장되었습니다.");

        // 파일 보안 여부를 묻는 부분 추가
        char answer;

        printf("파일을 보안하시겠습니까? (y/n): ");
        scanf(" %c", &answer);

        if (answer == 'y' || answer == 'Y')
        {
            // 비밀번호 입력
            char password[100];

            printf("보안을 위한 비밀번호를 입력하세요: ");
            scanf("%s", password);

            secure_file(filename, password);
        }

        else if (answer == 'n' || answer == 'N')
        {
            printf("파일이 보안되지 않고 그냥 저장되었습니다.\n");
        }

        else
        {
            printf("잘못된 입력입니다. 파일이 보안되지 않았습니다.\n");
        }
    }

    else
    {
        printf("파일을 열 수 없습니다.\n");
    }
}

// 보안된 파일 읽기 함수
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

        // 비밀번호 확인
        // 비밀번호가 일치하면 일기 내용을 출력
        // 비밀번호가 일치하지 않으면 액세스 거부 메시지 출력
        // 여기서는 비밀번호가 "password"인 경우에만 허용한다고 가정
        if (strcmp(password, password) == 0)
        {
            while (fscanf(secure_file, "%[^|]|%[^|]|", entry.date, entry.content) != EOF)
            {
                printf("날짜: %s 일기 내용 : % s", entry.date, entry.content);
            }
        }
        else
        {
            printf("액세스가 거부되었습니다. 비밀번호가 일치하지 않습니다.");
        }

        fclose(secure_file);
    }
    else
    {
        printf("비밀번호가 틀렸습니다..");
    }
}


// 파일 읽기 함수
void read_entry(const char* filename)
{
    FILE* file = fopen(filename, "rb"); // 'rb' 바이너미 모드로 읽기

    if (file != NULL) 
    {
        Entry entry;

        // 일기 내용을 한줄씩 읽어서 출력
        while (fscanf(file, "%[^|]|%[^|]|", entry.date, entry.content) != EOF) // 구분문자를 기준으로 날짜와 내용을 읽음
            printf("날짜: %s\n 일기 내용: %s\n", entry.date, entry.content); // 각 항목의 날짜와 내용을 출력

        fclose(file); 
    }
}

void main_test() 
{
    setlocale(LC_ALL, ""); // 로캘 설정

    Entry diary_entry;

    time_t t = time(NULL); // 현재 시간을 초 단위로 읽음
    struct tm tm = *localtime(&t); // 현재 시간을 구조체로 변환

    sprintf(diary_entry.date, "%04d-%02d-%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday); //현재 날짜 설정


    // 개행 문자 제거
    diary_entry.content[strcspn(diary_entry.content, "\n")] = '\0';


    printf("일기 내용을 입력하세요 : ");
    fgets(diary_entry.content, sizeof(diary_entry.content), stdin);

    write_entry(&diary_entry, "diary.txt");  //"diary.txt"라는 이름의 텍스트파일에 일기 저장

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
    

    return 0;
}
