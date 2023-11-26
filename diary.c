
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

            printf("�ϱⰡ ����Ǿ����ϴ�.");
        }
        else
        {
            printf("������ �� �� �����ϴ�.");
        }
    }
}


int show_diary(const char* date, char* diary_content, int* source_file)
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
                // ���ȵ� �ϱ��� ��й�ȣ�� ���
                char password[100] = "";
                check_password_UI(password);

                // �Էµ� ��й�ȣ�� ��ġ�ϴ��� Ȯ��
                if (strcmp(password, entry.password) == 0)
                {
                    strcpy(diary_content, entry.content);  // �ϱ� ���� ����
                    *source_file = 1;  // ���� ���Ϸ� ����
                    fclose(file);
                    return 0;
                }
                else
                {
                    //strcpy(diary_content, "��й�ȣ�� Ʋ�Ƚ��ϴ�.");  // ���� �޽��� ����
                    check_password_UI_2_0();
                    fclose(file);
                    return -1;
                }
            }
        }
        fclose(file);
    }

    // �ϱ⸦ ã�� ���� ���
    strcpy(diary_content, "�ϱ⸦ ã�� ���߽��ϴ�.");
}

/*
void change_diary(char* selected_date, int source_file)
{
	char new_content[MAX_LEN];
	gotoxy(10, 12);
	printf("���ο� �ϱ� ������ �Է��ϼ���>> ");
	//scanf("%[^\n]", new_content);
	//getchar(); // �� �ٲ� ���ڸ� �����մϴ�.
	fgets(new_content, MAX_LEN, stdin);
	// fgets �Լ��� ���ڿ� ���� '\n' ���ڸ� ���Խ�Ű�Ƿ� �̸� �����մϴ�.
	int len = strlen(new_content);
	if (new_content[len - 1] == '\n') new_content[len - 1] = '\0';

	if (source_file == 0)
	{
		// �Ϲ� ���Ͽ��� �ϱ� ���� �����ϱ�
		FILE* file = fopen("diary.txt", "rb");
		FILE* temp_file = fopen("temp.txt", "wb");
		if (file != NULL && temp_file != NULL)
		{
			Entry entry;
			while (fscanf(file, "%[^|]|%[^|]|", entry.date, entry.content) != EOF)
			{
				if (strcmp(selected_date, entry.date) == 0)  // ���õ� ��¥�� ��ġ�ϴ��� Ȯ��
				{
					strcpy(entry.content, new_content);  // �ϱ� ���� ����
				}
				fprintf(temp_file, "%s|%s|\n", entry.date, entry.content);  // ������ �ϱ� ������ �ӽ� ���Ͽ� ����
			}
			fclose(file);
			fclose(temp_file);

			// ���� ���Ͽ� ������ ������ �����
			remove("diary.txt");
			rename("temp.txt", "diary.txt");
			choose_diary_UI_c();
		}
	}

	// ���� ���Ͽ��� �ϱ� ���� �����ϱ�
	else if (source_file == 1)
	{
		// ���� ���Ͽ��� �ϱ� ���� �����ϱ�
		FILE* file = fopen("diary.txt.secure", "rb");
		FILE* temp_file = fopen("temp.txt.secure", "wb");
		if (file != NULL && temp_file != NULL)
		{
			Entry entry;
			while (fscanf(file, "%[^|]|%[^|]|%[^|]|", entry.password, entry.date, entry.content) != EOF)
			{
				if (strcmp(selected_date, entry.date) == 0)  // ���õ� ��¥�� ��ġ�ϴ��� Ȯ��
				{
					strcpy(entry.content, new_content);  // �ϱ� ���� ����
				}
				fprintf(temp_file, "%s|%s|%s|\n", entry.password, entry.date, entry.content);  // ������ �ϱ� ������ �ӽ� ���Ͽ� ����
			}
			fclose(file);
			fclose(temp_file);

			// ���� ���Ͽ� ������ ������ �����
			remove("diary.txt.secure");
			rename("temp.txt.secure", "diary.txt.secure");
			choose_diary_UI_c();
		}
	}

	else
	{
		printf("�������� ���Ͽ����ϴ�.");
		choose_diary_UI_c();
	}
}
*/
void change_diary(char* selected_date, int source_file)
{
    char new_content[MAX_LEN];
    gotoxy(10, 12);
    printf("���ο� �ϱ� ������ �Է��ϼ���>> ");
    fgets(new_content, MAX_LEN, stdin);

    // fgets �Լ��� ���ڿ� ���� '' ���ڸ� ���Խ�Ű�Ƿ� �̸� �����մϴ�.
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
                    if (strcmp(selected_date, entry.date) == 0)  // ���õ� ��¥�� ��ġ�ϴ��� Ȯ��
                    {
                        strcpy(entry.content, new_content);  // �ϱ� ���� ����
                        ischange = 1;  // ���� �÷��� ����
                    }

                    if (ischange)  // ������ ���
                    {
                        fprintf(temp_file, "%s|%s|", entry.date, entry.content);  // ������ �ϱ� ������ �ӽ� ���Ͽ� ����
                        ischange = 0;  // ���� �÷��� �ʱ�ȭ
                    }
                    else  // �������� ���� ���
                    {
                        fprintf(temp_file, "%s|%s|", entry.date, entry.content);  // ���� �ϱ� ������ �ӽ� ���Ͽ� ����
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
                if (strcmp(selected_date, entry.date) == 0)  // ���õ� ��¥�� ��ġ�ϴ��� Ȯ��
                {
                    strcpy(entry.content, new_content);  // �ϱ� ���� ����
                    fprintf(temp_file, "%s|%s|%s|", entry.password, entry.date, entry.content);  // ������ �ϱ� ������ �ӽ� ���Ͽ� ����
                }
                else
                {
                    fprintf(temp_file, "%s|%s|%s|", entry.password, entry.date, entry.content);  // ���� �ϱ� ������ �ӽ� ���Ͽ� ����
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
        printf("�������� ���Ͽ����ϴ�.");
        choose_diary_UI_c();
    }
}



void delete_diary(char* selected_date, int source_file)
{
	// �Ϲ� ���Ͽ��� �ϱ� �����ϱ�
	if (source_file == 0)
	{
		FILE* file = fopen("diary.txt", "rb");
		FILE* temp_file = fopen("temp.txt", "wb");
		if (file != NULL && temp_file != NULL)
		{
			Entry entry;
			while (fscanf(file, "%[^|]|%[^|]|", entry.date, entry.content) != EOF)
			{
				if (strcmp(selected_date, entry.date) != 0)  // ���õ� ��¥�� ��ġ���� �ʴ��� Ȯ��
				{
					fprintf(temp_file, "%s|%s|\n", entry.date, entry.content);  // ���õ� ��¥�� �ƴ� �ϱ� ������ �ӽ� ���Ͽ� ����
				}
			}
			fclose(file);
			fclose(temp_file);

			// ���� ���Ͽ� ������ ������ �����
			remove("diary.txt");
			rename("temp.txt", "diary.txt");
			choose_diary_UI_c();
		}
	}

	// ���� ���Ͽ��� �ϱ� �����ϱ�
	else if (source_file == 1)
	{
		FILE* file = fopen("diary.txt.secure", "rb");
		FILE* temp_file = fopen("temp.txt.secure", "wb");
		if (file != NULL && temp_file != NULL)
		{
			Entry entry;
			while (fscanf(file, "%[^|]|%[^|]|%[^|]|", entry.password, entry.date, entry.content) != EOF)
			{
				if (strcmp(selected_date, entry.date) != 0)  // ���õ� ��¥�� ��ġ���� �ʴ��� Ȯ��
				{
					fprintf(temp_file, "%s|%s|%s|\n", entry.password, entry.date, entry.content);  // ���õ� ��¥�� �ƴ� �ϱ� ������ �ӽ� ���Ͽ� ����
				}
			}
			fclose(file);
			fclose(temp_file);

			// ���� ���Ͽ� ������ ������ �����
			remove("diary.txt.secure");
			rename("temp.txt.secure", "diary.txt.secure");
			choose_diary_UI_c();
		}
	}

	else
	{
		printf("�������� ���Ͽ����ϴ�.");
		choose_diary_UI_c();
	}
}