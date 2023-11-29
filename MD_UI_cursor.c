
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
    printf("������������������������������������������������������������������������������������������������������������������\n");

    for (i = 0; i < HEIGHT; i++) 
    {
        for (j = 0; j < WIDTH; j++) 
        {
            if (date <= 31) 
            {
                if (i == cur_y && j == cur_x) 
                {
                    printf("�� [%2d]  ", date);
                }
                else 
                {
                    printf("��  %2d   ", date);
                }
                date++;
            }
            else 
            {
                printf("��       ");
            }
        }
        printf("��\n");
        if (i != HEIGHT - 1) 
        {
            printf("������������������������������������������������������������������������������������������������������������������\n");
        }
    }

    printf("������������������������������������������������������������������������������������������������������������������\n");

    gotoxy(7, 13);
    printf("�ϱ� �Ǵ� �޸� �ۼ��� ��¥�� �������ּ���");
}


void MD_main_test()
{

    int cur_y = 0; // ���Ϸ� �̵��ϴ� Ŀ�� ��ġ
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
                main_cursor_test(); // Ŀ�� ��ġ�� ���� ��¥ ����ȭ������ �̵�
            else if (cur_y == 1)
                search_diary_UI_c(); // Ŀ�� ��ġ�� ���� �ϱ� �˻��ϱ�� �̵�
            else if (cur_y == 2)
                search_memo_UI_c(); // Ŀ�� ��ġ�� ���� �޸� �˻��ϱ�� �̵�
            else if (cur_y == 3) // Ŀ�� ��ġ�� ���� ���α׷� ����
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
            break;  // 'q' �Ǵ� 'Q'�� ������ ���� ����
        }
    }

    return 0;
}
    

void main_cursor_test() 
{
    setlocale(LC_ALL, ""); // ��Ķ ����

    int cur_y = 1, cur_x = 3;
    int ch;

    Entry diary_entry;

    time_t t = time(NULL); // ���� �ð��� �� ������ ����
    struct tm tm = *localtime(&t); // ���� �ð��� ����ü�� ��ȯ

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
   
    int cur_y = 0; // ���Ϸ� �̵��ϴ� Ŀ�� ��ġ
    int ch;

    while (1) {
        choose_menu(cur_y); // �޴� �����ϱ� uiȣ��

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
                write_diary_UI(); // �ϱ⾲�� ui ȣ��
            else if (cur_y == 1)
                write_memo_UI();  // �޸𾲱� ui ȣ��
            else if (cur_y == 2)
                choose_diary_UI_c(); // �ϱ� �����ϱ� ui ȣ��
            else if (cur_y == 3)
                choose_memo_UI_c();  // �޸� �����ϱ� ui ȣ��
            else
                return 0; 
        }
        
        if (ch == 'q' || ch == 'Q')
        {
            MD_main_test(); // ����ȭ������ ���ư���
            break;  // 'q' �Ǵ� 'Q'�� ������ ���� ����
        }
            
    }

    return 0;
}

// Ű������ ����Ű �¿�
int left_right_key()
{
    int ch = _getch();
    if (ch == 0 || ch == 224)
    {
        switch (_getch())
        {
        case 75: // ���� ����Ű
            return 0;
        case 77: // ������ ����Ű
            return 1;
        default:
            return -1;
        }
    }

    return -1;
}



void choose_diary_UI_c()
{
    char dates[100][11] = { 0 }; // �ϱ� ��¥�� ������ �迭
    int date_count = 0;  // �ϱ� ��¥ ����
    int selected_index = 0;  // ���� ���õ� ��¥�� �ε���
    int ch;
    char diary_content[MAX_LEN];

    // �ϱ��� ��ó�� �����ϴ� ����
    int source_file[100] = { 0 };  // 0: �Ϲ� ����, 1: ���� ����

    // �Ϲ� ���Ͽ��� ��¥ ��������
    FILE* file = fopen("diary.txt", "rb");
    if (file != NULL)
    {
        Entry entry;
        while (fscanf(file, "%[^|]|%[^|]|", entry.date, entry.content) != EOF)
        {
            strcpy(dates[date_count], entry.date);  // ��¥ ����
            source_file[date_count] = 0; // �Ϲ����� ��ó ����
            date_count++;
        }
        fclose(file);
    }


    // ���� ���Ͽ��� ��¥ ��������
    file = fopen("diary.txt.secure", "rb");
    if (file != NULL)
    {
        char password[100];
        Entry entry;
        while (fscanf(file, "%[^|]|%[^|]|%[^|]|", entry.password, entry.date, entry.content) != EOF)
        {
            strcpy(dates[date_count], entry.date);  // ��¥ ����
            source_file[date_count] = 1;  // �������� ��ó ����
            date_count++;
        }
        fclose(file);
    }

    // ��¥�� �ֱ� ������ ����
    sort_dates(dates, date_count);

    // Ű����� ��¥ ����
    while (1)
    {
        // ��¥ ���� ui 
        choose_diary_UI();

        // �ϱ� ��¥ ���
        int i;
        for (i = 0; i < date_count; i++)
        {
            gotoxy(10, 8 + i % 17);
            printf("%s", dates[i]);
        }

        // ���� ���õ� ��¥ ���
        gotoxy(8, 8 + selected_index % 17);
        printf(">>");
        gotoxy(8, 25);
        printf(">>> %s", dates[selected_index]);

        // Ű���� �Է� Ȯ��
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
            // ������ ��¥�� �ش��ϴ� �ϱ� �����ֱ�
            //show_diary(dates[selected_index], diary_content, &source_file[selected_index]);  // ������ ��¥�� �ϱ� ���� ��������
            //show_diary_UI(dates[selected_index], diary_content, &source_file[selected_index]);
            //break;
            int result = show_diary(dates[selected_index], diary_content, &source_file[selected_index]);
            if (result == 0)  // ��й�ȣ�� �¾��� ���
            {
                show_diary_UI(dates[selected_index], diary_content, &source_file[selected_index]);
                return;
            }
            // ��й�ȣ�� Ʋ���� ���, �ٽ� ��¥ ���� ȭ������ ���ư�
            break;
        }
        }

        if (ch == 'q' || ch == 'Q')
        {
            main_choose_test(); // �޴� ����ȭ������ ���ư�
            break;  // 'q' �Ǵ� 'Q'�� ������ ���� ����
        }

        Sleep(100);  // CPU ��뷮�� ���̱� ���� �Ͻ� ����
    }
}

void choose_memo_UI_c()
{
    char dates[100][11] = { 0 }; // �޸� ��¥�� ������ �迭
    int date_count = 0;  // �޸� ��¥ ����
    int selected_index = 0;  // ���� ���õ� ��¥�� �ε���
    int ch;
    char memo_content[MAX_LEN];

    // �޸��� ��ó�� �����ϴ� ���� �߰�
    int source_file[100] = { 0 };  // 0: �Ϲ� ����, 1: ���� ����

    // �Ϲ� ���Ͽ��� ��¥ ��������
    FILE* file = fopen("memo.txt", "rb");
    if (file != NULL)
    {
        Entry entry;
        while (fscanf(file, "%[^|]|%[^|]|", entry.date, entry.content) != EOF)
        {
            strcpy(dates[date_count], entry.date);  // ��¥ ����
            source_file[date_count] = 0; // �Ϲ����� ��ó ����
            date_count++;
        }
        fclose(file);
    }


    // ���� ���Ͽ��� ��¥ ��������
    file = fopen("memo.txt.secure", "rb");
    if (file != NULL)
    {
        char password[100];
        Entry entry;
        while (fscanf(file, "%[^|]|%[^|]|%[^|]|", entry.password, entry.date, entry.content) != EOF)
        {
            strcpy(dates[date_count], entry.date);  // ��¥ ����
            source_file[date_count] = 1;  // �������� ��ó ����
            date_count++;
        }
        fclose(file);
    }

    sort_dates(dates, date_count);

    // Ű����� ��¥ ����
    while (1)
    {
        // �޸� ���� ui
        choose_memo_UI();

        // �޸� ��¥ ���
        int i;
        for (i = 0; i < date_count; i++)
        {
            gotoxy(10, 8 + i % 17);
            printf("%s", dates[i]);
        }

        // ���� ���õ� ��¥ ���
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
            // ������ ��¥�� �ش��ϴ� �޸� �����ֱ�
            int result = show_memo(dates[selected_index], memo_content, &source_file[selected_index]);
            if (result == 0)  // ��й�ȣ�� �¾��� ���
            {
                show_memo_UI(dates[selected_index], memo_content, &source_file[selected_index]);
                return;
            }
            // ��й�ȣ�� Ʋ���� ���, �ٽ� ��¥ ���� ȭ������ ���ư��ϴ�.
            break;
        }
        }

        if (ch == 'q' || ch == 'Q')
        {
            main_choose_test(); // �޴� ����ȭ������ ���ư�
            break;  // 'q' �Ǵ� 'Q'�� ������ ���� ����
        }

        Sleep(100);  // CPU ��뷮�� ���̱� ���� �Ͻ� ����
    }
}

void show_diary_UI(char* selected_date, char* diary_content, int* source_file)
{
    system("cls");
    int i;
    int ch;
    int cur_x = 0;

    for (i = 0; i < 110; i++)
        printf("��");

    gotoxy(1, 2);
    for (i = 0; i < 27; i++)
        printf("��\t\t\t\t\t\t\t\t\t\t\t\t\t     ��\n");

    gotoxy(1, 28);
    for (i = 0; i < 110; i++)
        printf("��");

    gotoxy(1, 1);
    printf("��");
    gotoxy(110, 1);
    printf("��");
    gotoxy(1, 28);
    printf("��");
    gotoxy(110, 28);
    printf("��");

    gotoxy(40, 2);
    printf("%s ��¥�� �ϱ��Դϴ�.", selected_date);

    gotoxy(8, 8);
    printf(">> %s", diary_content);

    // Ű����� ��� ����
    while (1)
    {
        gotoxy(21, 25);
        printf(cur_x == 0 ? "[ �����ϱ� ]" : "  �����ϱ�  ");

        gotoxy(80, 25);
        printf(cur_x == 1 ? "[ �����ϱ� ]" : "  �����ϱ�  ");

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
                // �����ϱ�          �Ϲ��������� ������������ ���� �Ѱ���
                change_diary(selected_date, *source_file);
            }
            else
            {
                // �����ϱ�          �Ϲ��������� ������������ ���� �Ѱ���
                delete_diary(selected_date, *source_file);
            }
            return;
        }

        if (ch == 'q' || ch == 'Q')
        {
            choose_diary_UI_c(); // ��¥ �������� ���ư�
            break;  // 'q' �Ǵ� 'Q'�� ������ ���� ����
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
        printf("��");

    gotoxy(1, 2);
    for (i = 0; i < 27; i++)
        printf("��\t\t\t\t\t\t\t\t\t\t\t\t\t     ��\n");

    gotoxy(1, 28);
    for (i = 0; i < 110; i++)
        printf("��");

    gotoxy(1, 1);
    printf("��");
    gotoxy(110, 1);
    printf("��");
    gotoxy(1, 28);
    printf("��");
    gotoxy(110, 28);
    printf("��");

    gotoxy(40, 2);
    printf("%s ��¥�� �޸��Դϴ�.", selected_date);

    gotoxy(8, 8);
    printf(">> %s", memo_content);

    // Ű����� ��� ����
    while (1)
    {
        gotoxy(21, 25);
        printf(cur_x == 0 ? "[ �����ϱ� ]" : "  �����ϱ�  ");

        gotoxy(80, 25);
        printf(cur_x == 1 ? "[ �����ϱ� ]" : "  �����ϱ�  ");

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
                // �����ϱ�
                change_memo(selected_date, *source_file);
            }
            else
            {
                // �����ϱ�
                delete_memo(selected_date, *source_file);
            }
            return;
        }
        if (ch == 'q' || ch == 'Q')
        {
            choose_memo_UI_c(); // �޸� ��¥ ����ȭ������ ���ư�
            break;  // 'q' �Ǵ� 'Q'�� ������ ���� ����
        }

    }


    gotoxy(1, 30);

}


// �ϱ� �˻� �Լ�
void search_diary_UI_c()
{
    char keyword[MAX_LEN];
    search_UI(keyword);  // �˻��� Ű���� �Է¹ޱ�

    // fgets �Լ��� ���ڿ� ���� ' ' ���ڸ� ���Խ�Ű�Ƿ� ����
    int len = strlen(keyword);
    if (keyword[len - 1] == ' ') keyword[len - 1] = '\0';

    char dates[100][11] = { 0 }; // �ϱ� ��¥�� ������ �迭
    int date_count = 0;  // �ϱ� ��¥ ����
    int selected_index = 0;  // ���� ���õ� ��¥�� �ε���
    int ch;
    char diary_content[MAX_LEN];

    // �ϱ��� ��ó�� �����ϴ� ���� �߰�
    int source_file[100] = { 0 };  // 0: �Ϲ� ����, 1: ���� ����

    // �Ϲ� ���Ͽ��� �˻�
    FILE * file = fopen("diary.txt", "rb");
    if (file != NULL)
    {
        Entry entry;
        while (fscanf(file, "%[^|]|%[^|]|", entry.date, entry.content) != EOF)
        {
            if (strstr(entry.content, keyword) != NULL)  // �ϱ� ���뿡 Ű���尡 ���ԵǾ� �ִ��� Ȯ��
            {
                strcpy(dates[date_count], entry.date);  // ��¥ ����
                source_file[date_count] = 0;  // �Ϲ����� ��ó ����
                date_count++;
            }
        }
        fclose(file);
    }

    // ���� ���Ͽ��� �˻�
    file = fopen("diary.txt.secure", "rb");
    if (file != NULL)
    {
        Entry entry;
        while (fscanf(file, "%[^|]|%[^|]|%[^|]|", entry.password, entry.date, entry.content) != EOF)
        {
            if (strstr(entry.content, keyword) != NULL)  // �ϱ� ���뿡 Ű���尡 ���ԵǾ� �ִ��� Ȯ��
            {
                strcpy(dates[date_count], entry.date);  // ��¥ ����
                source_file[date_count] = 1;  // �������� ��ó ����
                date_count++;
            }
        }
        fclose(file);
    }

    sort_dates(dates, date_count);

    // Ű����� ��¥ ����
    while (1)
    {
        // �˻� uiȣ��
        search_diary_UI(keyword);

        // �ϱ� ��¥ ���
        int i;
        for (i = 0; i < date_count; i++)
        {
            gotoxy(10, 8 + i % 17);
            printf("%s", dates[i]);
        }

        // ���� ���õ� ��¥ ���
        gotoxy(8, 8 + selected_index % 17);
        printf(">>");
        gotoxy(8, 25);
        printf(">>> %s", dates[selected_index]);

        // Ű���� �Է� Ȯ��
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
            // ������ ��¥�� �ش��ϴ� �ϱ� �����ֱ�
            int result = show_diary(dates[selected_index], diary_content, &source_file[selected_index]);
            if (result == 0)  // ��й�ȣ�� �¾��� ���
            {
                show_diary_UI(dates[selected_index], diary_content, &source_file[selected_index]);
                return;
            }
            // ��й�ȣ�� Ʋ���� ���, �ٽ� ��¥ ���� ȭ������ ���ư��ϴ�.
            break;
        }
        }

        if (ch == 'q' || ch == 'Q')
        {
            break;  // 'q' �Ǵ� 'Q'�� ������ ���� ����
        }

        Sleep(100);  // CPU ��뷮�� ���̱� ���� �Ͻ� ����
    }
}

// �޸� �˻� �Լ�
void search_memo_UI_c()
{
    char keyword[MAX_LEN];
    search_UI(keyword);  // Ű���� �Է¹ޱ�

    // fgets �Լ��� ���ڿ� ���� ' ' ���ڸ� ���Խ�Ű�Ƿ� ����
    int len = strlen(keyword);
    if (keyword[len - 1] == ' ') keyword[len - 1] = '\0';

    char dates[100][11] = { 0 }; // �޸� ��¥�� ������ �迭
    int memo_count = 0;  // �޸� ��¥ ����
    int selected_index = 0;  // ���� ���õ� ��¥�� �ε���
    int ch;
    char memo_content[MAX_LEN];

    // �޸��� ��ó�� �����ϴ� ����
    int source_file[100] = { 0 };  // 0: �Ϲ� ����, 1: ���� ����

    // �Ϲ� ���Ͽ��� �˻�
    FILE* file = fopen("memo.txt", "rb");
    if (file != NULL)
    {
        Entry entry;
        while (fscanf(file, "%[^|]|%[^|]|", entry.date, entry.content) != EOF)
        {
            if (strstr(entry.content, keyword) != NULL)  // �޸� ���뿡 Ű���尡 ���ԵǾ� �ִ��� Ȯ��
            {
                strcpy(dates[memo_count], entry.date);  // ��¥ ����
                source_file[memo_count] = 0;  // �Ϲ����� ��ó ����
                memo_count++;
            }
        }
        fclose(file);
    }

    // ���� ���Ͽ��� �˻�
    file = fopen("memo.txt.secure", "rb");
    if (file != NULL)
    {
        Entry entry;
        while (fscanf(file, "%[^|]|%[^|]|%[^|]|", entry.password, entry.date, entry.content) != EOF)
        {
            if (strstr(entry.content, keyword) != NULL)  // �ϱ� ���뿡 Ű���尡 ���ԵǾ� �ִ��� Ȯ��
            {
                strcpy(dates[memo_count], entry.date);  // ��¥ ����
                source_file[memo_count] = 1;  // �������� ��ó ����
                memo_count++;
            }
        }
        fclose(file);
    }

    sort_dates(dates, memo_count);

    // Ű����� ��¥ ����
    while (1)
    {
        // �޸� �˻� ui
        search_memo_UI(keyword);

        // �޸� ��¥ ���
        int i;
        for (i = 0; i < memo_count; i++)
        {
            gotoxy(10, 8 + i % 17);
            printf("%s", dates[i]);
        }

        // ���� ���õ� ��¥ ���
        gotoxy(8, 8 + selected_index % 17);
        printf(">>");
        gotoxy(8, 25);
        printf(">>> %s", dates[selected_index]);

        // Ű���� �Է� Ȯ��
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
            // ������ ��¥�� �ش��ϴ� �޸� �����ֱ�
            int result = show_memo(dates[selected_index], memo_content, &source_file[selected_index]);
            if (result == 0)  // ��й�ȣ�� �¾��� ���
            {
                show_memo_UI(dates[selected_index], memo_content, &source_file[selected_index]);
                return;
            }
            // ��й�ȣ�� Ʋ���� ���, �ٽ� ��¥ ���� ȭ������ ���ư��ϴ�.
            break;
        }
        }

        if (ch == 'q' || ch == 'Q')
        {
            break;  // 'q' �Ǵ� 'Q'�� ������ ���� ����
        }

        Sleep(100);  // CPU ��뷮�� ���̱� ���� �Ͻ� ����
    }
}



// ��¥�� �ֱټ����� �������ֱ����� ��¥ ���ڿ��� ���ڷ� ��ȯ�Ͽ� ũ�⸦ ���Ͽ� ���� ū ���ڰ� �ֱ��� �ȴ�.
// �����ϱ� ���� ���������� ���, ȿ���� �������� �ϱ� ��¥ ������ �����ϱ� ������  ������ ���
void sort_dates(char dates[100][11], int date_count)
{
    int i, j;
    for (i = 0; i < date_count - 1; i++)
    {
        for (j = 0; j < date_count - i - 1; j++)
        {
            // ��¥�� ���ڷ� ��ȯ
            int year1, month1, day1, date_num1;
            sscanf(dates[j], "%d-%d-%d", &year1, &month1, &day1);
            date_num1 = year1 * 10000 + month1 * 100 + day1;

            int year2, month2, day2, date_num2;
            sscanf(dates[j + 1], "%d-%d-%d", &year2, &month2, &day2);
            date_num2 = year2 * 10000 + month2 * 100 + day2;

            // ��¥ �� �� ��ȯ
            if (date_num1 < date_num2)
            {
                char temp[12];  // 'temp' ������ ũ�⸦ 12�� ����
                strcpy(temp, dates[j]);
                strcpy(dates[j], dates[j + 1]);
                strcpy(dates[j + 1], temp);
            }
        }
    }
}












