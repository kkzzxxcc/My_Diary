#define _CRT_SECURE_NO_WARNINGS  // ���־� ��Ʃ������� sacnf ���� �������ִ� ����


#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>

#define P 38
#define PP P+21
// �� �� �� �� �� �� �� �� �� �� ��

#define WIDTH 7
#define HEIGHT 5
#define MAX_LEN 1000 // �ϱ� ������ ���� �ִ� ���� ��

typedef struct
{
    char password[100];
    char date[11]; // YYYY-MM-DD ������ ��¥
    char content[MAX_LEN]; // �ϱ� �Ǵ� �޸� ����
} Entry;



char select_date[11];  // ���õ� ��¥�� ����

// ���ϰ���
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