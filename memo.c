
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


// �޸𾲱� �Լ�
void write_memo(Entry* entry, const char* filename)
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

        ask_password_UI(password);

        secure_file(filename, &password, entry);
        save_secure_UI();
    }
    else
    {
        FILE* file = fopen(filename, "ab"); // 'ab' ���� ���� ������ �̹� �ִٸ� �̾�� ����
        // �ѱ� ���ڿ��� ����� ����ϱ� ���� �ؽ�Ʈ ��尡 �ƴ� ���̳ʸ� ��� ���

        if (file != NULL)
        {
            fprintf(file, "%s|%s|", entry->date, entry->content); // '|' ���ڷ� ��¥�� ������ ����

            fclose(file); // ���� �ݱ�

            printf("�޸� ����Ǿ����ϴ�.");
        }
        else
        {
            printf("������ �� �� �����ϴ�.");
        }
    }
}

int show_memo(const char* date, char* memo_content, int* source_file)
{
	// �Ϲ� ���Ͽ��� �޸� ���� ��������
	if (*source_file == 0)
	{
		FILE* file = fopen("memo.txt", "rb");
		if (file != NULL)
		{
			Entry entry;
			while (fscanf(file, "%[^|]|%[^|]|", entry.date, entry.content) != EOF)
			{
				if (strcmp(date, entry.date) == 0)  // ���õ� ��¥�� ��ġ�ϴ��� Ȯ��
				{
					strcpy(memo_content, entry.content);  // �޸� ���� ����
					*source_file = 0;  // �Ϲ� ���Ϸ� ����
					fclose(file);
					return;
				}
			}
			fclose(file);
		}
	}

	// ���� ���Ͽ��� �޸� ���� ��������
	else if (*source_file == 1)
	{
		FILE *file = fopen("memo.txt.secure", "rb");
		if (file != NULL)
		{
			Entry entry;
			while (fscanf(file, "%[^|]|%[^|]|%[^|]|", entry.password, entry.date, entry.content) != EOF)
			{
				if (strcmp(date, entry.date) == 0)  // ���õ� ��¥�� ��ġ�ϴ��� Ȯ��
				{
					// ���ȵ� �޸��� ��й�ȣ�� ������� �մϴ�.
					char password[100] = "";
					check_password_UI_m(password);

					// �Էµ� ��й�ȣ�� ��ġ�ϴ��� Ȯ��
					if (strcmp(&password, entry.password) == 0)
					{
						strcpy(memo_content, entry.content);  // �ϱ� ���� ����
						*source_file = 1;  // ���� ���Ϸ� ����
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

	strcpy(memo_content, "�޸� ã�� ���߽��ϴ�.");
	return -1;
}

void change_memo(char* selected_date, int source_file)
{
	char new_content[MAX_LEN];
	gotoxy(10, 12);
	printf("���ο� �޸� ������ �Է��ϼ���>> ");
	fgets(new_content, MAX_LEN, stdin);

	if (source_file == 0)
	{
		// �Ϲ� ���Ͽ��� �ϱ� ���� �����ϱ�
		FILE* file = fopen("memo.txt", "rb");
		FILE* temp_file = fopen("temp.txt", "wb");
		if (file != NULL && temp_file != NULL)
		{
			Entry entry;
			int change = 0;
			while (fscanf(file, "%[^|]|%[^|]|", entry.date, entry.content) != EOF)
			{
				if (strcmp(selected_date, entry.date) == 0)  // ���õ� ��¥�� ��ġ�ϴ��� Ȯ��
				{
					strcpy(entry.content, new_content);  // �ϱ� ���� ����
					change = 1;  // ���� �÷��� ����
				}

				if (change)  // ������ ���
				{
					fprintf(temp_file, "%s|%s|", entry.date, new_content);  // ������ �ϱ� ������ �ӽ� ���Ͽ� ����
					change = 0;  // ���� �÷��� �ʱ�ȭ
				}
				else  // �������� ���� ���
				{
					fprintf(temp_file, "%s|%s|", entry.date, entry.content);  // ���� �ϱ� ������ �ӽ� ���Ͽ� ����
				}

				fclose(file);
				fclose(temp_file);
			}

				// ���� ���Ͽ� ������ ������ �����
			remove("memo.txt");
			rename("temp.txt", "memo.txt");
			choose_memo_UI_c();
			
		}
	}

	// ���� ���Ͽ��� �޸� ���� �����ϱ�
	else if (source_file == 1)
	{
		// ���� ���Ͽ��� �޸� ���� �����ϱ�
		FILE* file = fopen("memo.txt.secure", "rb");
		FILE* temp_file = fopen("temp.txt.secure", "wb");
		if (file != NULL && temp_file != NULL)
		{
			Entry entry;
			int change = 0;
			while (fscanf(file, "%[^|]|%[^|]|%[^|]|", entry.password, entry.date, entry.content) != EOF)
			{
				if (strcmp(selected_date, entry.date) == 0)  // ���õ� ��¥�� ��ġ�ϴ��� Ȯ��
				{
					strcpy(entry.content, new_content);  // �ϱ� ���� ����
					change = 1;  // ������
				}

				if (change)  // ������ ���
				{
					fprintf(temp_file, "%s|%s|%s|", entry.password, entry.date, new_content);  // ������ �ϱ� ������ �ӽ� ���Ͽ� ����
					change = 0;  // ������ �ʱ�ȭ
				}
				else 
				{
					fprintf(temp_file, "%s|%s|%s|", entry.password, entry.date, entry.content);  // ���� �ϱ� ������ �ӽ� ���Ͽ� ����
				}
			}
			fclose(file);
			fclose(temp_file);

			// ���� ���Ͽ� ������ ������ �����
			remove("memo.txt.secure");
			rename("temp.txt.secure", "memo.txt.secure");
			choose_memo_UI_c();
		}
	}

	else
	{
		printf("�������� ���Ͽ����ϴ�.");
		choose_memo_UI_c();
	}
}

void delete_memo(char* selected_date, int source_file)
{
	// �Ϲ� ���Ͽ��� �޸� �����ϱ�
	if (source_file == 0)
	{
		FILE* file = fopen("memo.txt", "rb");
		FILE* temp_file = fopen("temp.txt", "wb");
		if (file != NULL && temp_file != NULL)
		{
			Entry entry;
			while (fscanf(file, "%[^|]|%[^|]|", entry.date, entry.content) != EOF)
			{
				if (strcmp(selected_date, entry.date) != 0)  // ���õ� ��¥�� ��ġ���� �ʴ��� Ȯ��
				{
					fprintf(temp_file, "%s|%s|\n", entry.date, entry.content);  // ���õ� ��¥�� �ƴ� �޸� ������ �ӽ� ���Ͽ� ����
				}
			}
			fclose(file);
			fclose(temp_file);

			// ���� ���Ͽ� ������ ������ �����
			remove("memo.txt");
			rename("temp.txt", "memo.txt");
			choose_memo_UI_c();
		}
	}

	// ���� ���Ͽ��� �޸� �����ϱ�
	else if (source_file == 1)
	{
		FILE* file = fopen("memo.txt.secure", "rb");
		FILE* temp_file = fopen("temp.txt.secure", "wb");
		if (file != NULL && temp_file != NULL)
		{
			Entry entry;
			while (fscanf(file, "%[^|]|%[^|]|%[^|]|", entry.password, entry.date, entry.content) != EOF)
			{
				if (strcmp(selected_date, entry.date) != 0)  // ���õ� ��¥�� ��ġ���� �ʴ��� Ȯ��
				{
					fprintf(temp_file, "%s|%s|%s|\n", entry.password, entry.date, entry.content);  // ���õ� ��¥�� �ƴ� �޸� ������ �ӽ� ���Ͽ� ����
				}
			}
			fclose(file);
			fclose(temp_file);

			// ���� ���Ͽ� ������ ������ �����
			remove("memo.txt.secure");
			rename("temp.txt.secure", "memo.txt.secure");
			choose_memo_UI_c();
		}
	}

	else
	{
		printf("�������� ���Ͽ����ϴ�.");
		choose_memo_UI_c();
	}
}
