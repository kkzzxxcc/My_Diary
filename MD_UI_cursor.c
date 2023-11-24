
#include "MD_header.h"

typedef struct
{
    char date[11];
    int isSecure;
} DiaryLocation;

char select_date[11];  // ���õ� ��¥�� ����


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
    printf("������������������������������������������������������������������������������������������������������������������\n");

    for (i = 0; i < HEIGHT; i++) {
        for (j = 0; j < WIDTH; j++) {
            if (date <= 31) {
                if (i == cur_y && j == cur_x) {
                    printf("��[%2d]   ", date);
                }
                else {
                    printf("��  %2d   ", date);
                }
                date++;
            }
            else {
                printf("��       ");
            }
        }
        printf("��\n");
        if (i != HEIGHT - 1) {
            printf("������������������������������������������������������������������������������������������������������������������\n");
        }
    }

    printf("������������������������������������������������������������������������������������������������������������������\n");

    gotoxy(1, 15);
    printf("��¥�� �������ּ���");
}
    

void main_cursor_test() 
{
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
    setlocale(LC_ALL, "");

    int cur_y = 0; // ���Ϸ� �̵��ϴ� Ŀ�� ��ġ
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
            break;  // 'q' �Ǵ� 'Q'�� ������ ���� ����
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

// ���Ͼ��� �Լ�
void write_entry(Entry* entry, const char* filename)
{
    int secure = 0;
    int cur_x = 0;
    int ch;

    while (1) 
    {
        ask_secure_UI(cur_x);  // ���� UI�� ���� ���� ��ġ ����

        ch = _getch();
        switch (ch) {
        case 75:  // LEFT
            cur_x = cur_x - 1 >= 0 ? cur_x - 1 : 0;
            break;
        case 77:  // RIGHT
            cur_x = cur_x + 1 <= 1 ? cur_x + 1 : 1;
            break;

        case '\r':  // Enter key
            secure = cur_x == 0 ? 1 : 0;  // ���� ���� ��ġ�� ���� ����
            break;
        }

        if (ch == '\r')
            break;  // ���͸� ������ ���� ����
    }

    if (secure)
    {
        // ��й�ȣ �Է�
        char password[100];

        printf("������ ���� ��й�ȣ�� �Է��ϼ���: ");
        scanf("%s", password);

        secure_file(filename, password, entry);
        printf("�ϱⰡ ���� �Ǿ����ϴ�.");
    }
    else
    {
        FILE* file = fopen(filename, "ab"); // 'ab' ���� ���� ������ �̹� �ִٸ� �̾�� ����
        // �ѱ� ���ڿ��� ����� ����ϱ� ���� �ؽ�Ʈ ��尡 �ƴ� ���̳ʸ� ��� ���

        if (file != NULL)
        {
            fprintf(file, "%s|%s|", entry->date, entry->content); // '|' ���ڷ� ��¥�� ������ ����

            fclose(file); // ���� �ݱ�

            printf("�ϱⰡ ����Ǿ����ϴ�.");
        }
        else
        {
            printf("������ �� �� �����ϴ�.");
        }
    }
}


void choose_diary_UI_c()
{
    char dates[100][11] = { 0 }; // �ϱ� ��¥�� ������ �迭
    int date_count = 0;  // �ϱ� ��¥ ����
    int selected_index = 0;  // ���� ���õ� ��¥�� �ε���
    int ch;
    char diary_content[MAX_LEN];

    // �ϱ��� ��ó�� �����ϴ� ���� �߰�
    int source_file[100];  // 0: �Ϲ� ����, 1: ���� ����

    // �Ϲ� ���Ͽ��� ��¥ ��������
    FILE* file = fopen("diary.txt", "rb");
    if (file != NULL)
    {
        Entry entry;
        while (fscanf(file, "%[^|]|%[^|]|", entry.date, entry.content) != EOF)
        {
            strcpy(dates[date_count], entry.date);  // ��¥ ����
            source_file[date_count] = 0;
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
        while (fscanf(file, "%[^|]|%[^|]|%[^|]|", password, entry.date, entry.content) != EOF)
        {
            strcpy(dates[date_count], entry.date);  // ��¥ ����
            source_file[date_count] = 1;  // ���� ���Ͽ��� �о��
            date_count++;
        }
        fclose(file);
    }

    sort_dates(dates, date_count);

    // Ű����� ��¥ ����
    while (1)
    {
        // UI �׸���
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
            // ������ ��¥�� �ش��ϴ� �ϱ� �����ֱ�
            show_diary(dates[selected_index], diary_content, &source_file);  // ������ ��¥�� �ϱ� ���� ��������
            show_diary_UI(dates[selected_index], diary_content, &source_file);
            return;
        }

        Sleep(100);  // CPU ��뷮�� ���̱� ���� �Ͻ� ����
    }
}

void show_diary(const char* date, char* diary_content, int* source_file)
{
    // �Ϲ� ���Ͽ��� �ϱ� ���� ��������
    FILE* file = fopen("diary.txt", "rb");
    if (file != NULL)
    {
        Entry entry;
        while (fscanf(file, "%[^|]|%[^|]|", entry.date, entry.content) != EOF)
        {
            if (strcmp(date, entry.date) == 0)  // ���õ� ��¥�� ��ġ�ϴ��� Ȯ��
            {
                strcpy(diary_content, entry.content);  // �ϱ� ���� ����
                *source_file = 0;  // �Ϲ� ���Ϸ� ����
                fclose(file);
                return;
            }
        }
        fclose(file);
    }

    // ���� ���Ͽ��� �ϱ� ���� ��������
    file = fopen("diary.txt.secure", "rb");
    if (file != NULL)
    {
        Entry entry;
        while (fscanf(file, "%[^|]|%[^|]|%[^|]|", entry.password, entry.date, entry.content) != EOF)
        {
            if (strcmp(date, entry.date) == 0)  // ���õ� ��¥�� ��ġ�ϴ��� Ȯ��
            {
                // ���ȵ� �ϱ��� ��й�ȣ�� ������� �մϴ�.
                char password[100] = "";
                printf("��й�ȣ�� �Է��ϼ���: ");
                scanf("%s", password);

                // �Էµ� ��й�ȣ�� ��ġ�ϴ��� Ȯ��
                if (strcmp(password, entry.password) == 0)
                {
                    strcpy(diary_content, entry.content);  // �ϱ� ���� ����
                    *source_file = 1;  // �Ϲ� ���Ϸ� ����
                    fclose(file);
                    return;
                }
                else
                {
                    printf("��й�ȣ�� Ʋ�Ƚ��ϴ�.\n");
                    strcpy(diary_content, "��й�ȣ�� Ʋ�Ƚ��ϴ�.");  // ���� �޽��� ����
                    fclose(file);
                    return;
                }
            }
        }
        fclose(file);
    }

    // �ϱ⸦ ã�� ���� ���
    strcpy(diary_content, "�ϱ⸦ ã�� ���߽��ϴ�.");
}

// ��¥�� �ֱټ����� �������ֱ����� ��¥ ���ڿ��� ���ڷ� ��ȯ�Ͽ� ũ�⸦ ���Ͽ� ���� ū ���ڰ� �ֱ��� �ȴ�.
// �����ϱ� ���� ���������� ���, ȿ���� �������� �ϱ� ��¥ ������ �����ϱ� ������ ���� ����ȭ�� ���� �ʿ���� ������ ������ ���
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





int main()
{
    //main_cursor_test();
    choose_diary_UI_c();
    return 0;

}






