#define _CRT_SECURE_NO_WARNINGS  // 비주얼 스튜디오에서 sacnf 오류 무시해주는 정의


#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>

#define P 38
#define PP P+21
// ┫ ┃ ━ ┓ ┛ ┗ ┏ ┳ ┻ ┣ ╋

#define WIDTH 7
#define HEIGHT 5
#define MAX_LEN 1000 // 일기 내용을 위한 최대 문자 수

typedef struct
{
    char password[100];
    char date[11]; // YYYY-MM-DD 형식의 날짜
    char content[MAX_LEN]; // 일기 또는 메모 내용
} Entry;



char select_date[11];  // 선택된 날짜를 저장

// 파일관련
extern void write_entry(Entry* entry, const char* filename);
extern void secure_file(const char* filename, const char* password, Entry* entry);
extern int show_diary(const char* date, char* content);


extern void gotoxy_c(int x, int y);
extern void print_calendar_ui(int cur_y, int cur_x);

extern void main_cursor_test();
extern void MD_main_UI();
extern void MD_main_UI_c(int cur_y);
extern void choose_menu(int cur_y);

extern void write_diary_UI();
extern void write_memo_UI();

extern void ask_secure_c_test();
extern void ask_secure_UI(int cur_x);
extern void check_password_UI_m(char* password);

extern void choose_diary_UI();
extern void choose_memo_UI();

extern void show_diary_UI(char* selected_date, char* diary_content, int source_file);
extern void show_mome_UI(char* selected_date, char* memo_content, int source_file);
extern void choose_diary_UI_c();
extern void choose_memo_UI_c();

extern void change_diary(char* selected_date, int source_file);
extern void delete_diary(char* selected_date, int source_file);

extern void search_UI(char* keyword);
extern void search_diary_UI();
extern void search_diary_UI_c();
extern void search_memo_UI();
extern void search_memo_UI_c();