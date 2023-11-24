
#include "MD_header.h"



void gotoxy(int x, int y);
void MD_main_UI();        // ���� ȭ��
void gotoxy_c(int x, int y);
void write_entry(Entry* entry, const char* filename);
void change_diary(char* selected_date);
void delete_diary(char* selected_date);
void choose_diary_UI_c();


void gotoxy(int x, int y)
{
	COORD Pos = { x - 1, y - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void MD_main_UI()
{
	system("cls");
	int i;

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

	gotoxy(51, 10);
	printf("My Diary");

	gotoxy(13, 16);
	printf("1. �޷� ����");
	gotoxy(13, 20);
	printf("2. ����");
	gotoxy(1, 30);
	printf("END");

	

}

void print_calendar_ui_t1() {
	int i, j, date = 1;
	printf("������������������������������������������������������������������������������������������������������������������");

	for (i = 0; i < 5; i++) {
		for (j = 0; j < 7; j++) {
			if (date <= 31) {
				printf("��  %2d   ", date);
				date++;
			}
			else {
				printf("��       ");
			}
		}
		printf("��");
		if (i != 4) {
			printf("������������������������������������������������������������������������������������������������������������������");
		}
	}

	printf("������������������������������������������������������������������������������������������������������������������");
}


void MD_main_calinder()
{
	system("cls");
	int i;

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

	
}


void MD_main_UI_c(int cur_y)
{

	system("cls");
	int i;

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

	gotoxy(51, 10);
	printf("My Diary");

	gotoxy(13, 16);
	printf("1. �޷� ����");
	gotoxy(13, 20);
	printf("2. ����");
	gotoxy(1, 30);
	printf("END");

	// '�޷� ����'�� '����'�� ���� ���� ���õ� �׸��� ǥ��
	gotoxy(13, 16);
	if (cur_y == 0)
		printf("> 1. �޷� ����");
	else
		printf("  1. �޷� ����");

	gotoxy(13, 20);
	if (cur_y == 1)
		printf("> 2. ����");
	else
		printf("  2. ����");

}

void choose_menu(int cur_y)
{
	system("cls");
	int i;

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
	printf("���õ� ��¥ : %s", select_date);

	gotoxy(13, 13);
	printf(cur_y == 0 ? "> 1. �ϱ� �ۼ�" : "  1. �ϱ� �ۼ�");
	gotoxy(13, 16);
	printf(cur_y == 1 ? "> 2. �޸� �ۼ�" : "  2. �޸� �ۼ�");
	gotoxy(13, 19);
	printf(cur_y == 2 ? "> 3. �ϱ� ����" : "  3. �ϱ� ����");
	gotoxy(13, 22);
	printf(cur_y == 3 ? "> 4. �޸� ����" : "  4. �޸� ����");

	gotoxy(1, 29);
	printf("END");

}

void write_diary_UI()
{
	system("cls");
	int i, j = 0;

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
	printf("�ۼ��� : %s", select_date);

	gotoxy(5, 8);
	printf("�ϱ� �ۼ��� >> ");

	// �ϱ� ���� �Է¹ޱ�
	Entry diary_entry;
	strcpy(diary_entry.date, select_date);  // ���õ� ��¥ ����
	char line[101];  // �� ���� �ϱ� ������ �ӽ� ������ ����

	for (i = 0; i < 27; i++) {  // �� �ٿ� ����
		gotoxy(20, 8 + i);  // ���ο� ���� ���� ��ǥ ����
		fgets(line, 101, stdin);  // �� ���� �ϱ� ������ �ӽ� ������ ����

		// ���͸� �� �� �Է��ϸ� �ϱ� �ۼ� ����
		if (strcmp(line, "\n") == 0) 
		{
			break;
		}

		strcpy(&diary_entry.content[j], line);  // �ӽ� ������ ������ diary_entry.content�� ����
		j += strlen(line);  // ���� ���� ���� ��ġ�� �̵�
	}



	//fgets(diary_entry.content, sizeof(diary_entry.content), stdin);

	// �ϱ� ������ ���Ͽ� ����
	write_entry(&diary_entry, "diary.txt");

	gotoxy(1, 30);
	printf("END");


}

void write_memo_UI()
{
	system("cls");
	int i;

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
	printf("�ۼ��� : %s", select_date);

	gotoxy(5, 8);
	printf("�޸� �ۼ��� >>");

	gotoxy(1, 30);
	printf("END");

}

void ask_secure_UI(int cur_x)
{
	int i;


	for (i = 6; i <= 19; i++)
	{
		gotoxy(18, i);
		printf("��                                                 ��");
	}

	gotoxy(18, 6);
	for (i = 0; i < 50; i++)
		printf("��");

	gotoxy(18, 20);
	for (i = 0; i < 50; i++)
		printf("��");



	gotoxy(18, 6);
	printf("��");
	gotoxy(68, 6);
	printf("��");
	gotoxy(18, 20);
	printf("��");
	gotoxy(68, 20);
	printf("��");

	gotoxy(34, 10);
	printf("���� �Ͻðڽ��ϱ�?");

	// ���� ���� ��ġ�� ���� ���� ǥ��
	gotoxy(30, 16);
	printf(cur_x == 0 ? "> �� " : " ��");
	gotoxy(51, 16);
	printf(cur_x == 1 ? "> �ƴϿ� " : " �ƴϿ�");

	/*
	gotoxy(80, 20);
	printf("3");
	Sleep(1000);
	gotoxy(80, 20);
	printf("2");
	Sleep(1000);
	gotoxy(80, 20);
	printf("1");
	Sleep(1000);
	*/

	gotoxy(1, 30);
	printf("END");
}

void choose_diary_UI()
{
	system("cls");
	int i;

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

	gotoxy(37, 2);
	printf("������� �ϱ��� ��¥�� �������ּ���.");

	/*
	gotoxy(8, 8);
	printf(">>");

	gotoxy(8, 25);
	printf(">>>");
	*/

	gotoxy(1, 30);
	printf("END");

}

void show_diary_UI(char* selected_date, char* diary_content, int *source_file)
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

	gotoxy(37, 2);
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
				// �����ϱ�
				change_diary(selected_date, *source_file);
			}
			else
			{
				// �����ϱ�
				delete_diary(selected_date, *source_file);
			}
			return;
		}

	}


	gotoxy(1, 30);
	printf("END");
}

void change_diary(char* selected_date, int source_file)
{
	char new_content[MAX_LEN];
	gotoxy(10, 12);
	printf("���ο� �ϱ� ������ �Է��ϼ���>> ");
	fgets(new_content, MAX_LEN, stdin);

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









