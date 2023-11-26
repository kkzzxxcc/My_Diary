
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

	/*
	gotoxy(13, 14);
	printf("1. �޷� ����");
	gotoxy(13, 17);
	printf("2. �ϱ� �˻�");
	gotoxy(13, 20);
	printf("3. �޸� �˻�");
	gotoxy(13, 23);
	printf("2. ����");
	
	gotoxy(1, 30);*/

	// '�޷� ����'�� '����'�� ���� ���� ���õ� �׸��� ǥ��
	gotoxy(13, 14);
	if (cur_y == 0)
		printf("> 1. �޷� ����");
	else
		printf("  1. �޷� ����");

	gotoxy(13, 17);
	if (cur_y == 1)
		printf("> 2. �ϱ� �˻�");
	else
		printf("  2. �ϱ� �˻�");

	gotoxy(13, 20);
	if (cur_y == 2)
		printf("> 3. �޸� �˻�");
	else
		printf("  3. �޸� �˻�");

	gotoxy(13, 23);
	if (cur_y == 3)
		printf("> 4. ����");
	else
		printf("  4. ����");

	gotoxy(1, 30);

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

	gotoxy(42, 2);
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



}

void write_memo_UI()
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
	printf("�޸� �ۼ��� >> ");

	// �ϱ� ���� �Է¹ޱ�
	Entry memo_entry;
	strcpy(memo_entry.date, select_date);  // ���õ� ��¥ ����
	char line[101];  // �� ���� �ϱ� ������ �ӽ� ������ ����

	for (i = 0; i < 27; i++) {  // �� �ٿ� ����
		gotoxy(20, 8 + i);  // ���ο� ���� ���� ��ǥ ����
		fgets(line, 101, stdin);  // �� ���� �ϱ� ������ �ӽ� ������ ����

		// ���͸� �� �� �Է��ϸ� �ϱ� �ۼ� ����
		if (strcmp(line, "\n") == 0)
		{
			break;
		}

		strcpy(&memo_entry.content[j], line);  // �ӽ� ������ ������ diary_entry.content�� ����
		j += strlen(line);  // ���� ���� ���� ��ġ�� �̵�
	}



	//fgets(diary_entry.content, sizeof(diary_entry.content), stdin);

	// �ϱ� ������ ���Ͽ� ����
	write_entry(&memo_entry, "memo.txt");

	gotoxy(1, 30);

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
	printf(cur_x == 0 ? "> �� " : "  �� ");
	gotoxy(51, 16);
	printf(cur_x == 1 ? "> �ƴϿ� " : "  �ƴϿ� ");

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

}

void choose_memo_UI()
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
	printf("������� �޸��� ��¥�� �������ּ���.");

	/*
	gotoxy(8, 8);
	printf(">>");

	gotoxy(8, 25);
	printf(">>>");
	*/

	gotoxy(1, 30);

}



void save_secure_UI()
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

	gotoxy(32, 13);
	printf("������ ����Ǿ����ϴ�..");


	gotoxy(60, 13);
	printf("2");
	Sleep(1000);
	gotoxy(60, 13);
	printf("1");
	Sleep(1000);

	gotoxy(1, 30);

}

void ask_password_UI(char *password)
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

	gotoxy(28, 12);
	printf("������ ���� ��й�ȣ�� �Է��ϼ���");
	gotoxy(34, 14);
	printf(">> ");
	gotoxy(37, 14);
	scanf("%s", password);


	gotoxy(1, 30);

}

void check_save_UI()
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

	gotoxy(36, 13);
	printf("����Ǿ����ϴ�..");


	gotoxy(54, 13);
	printf("2");
	Sleep(1000);
	gotoxy(54, 13);
	printf("1");
	Sleep(1000);

	gotoxy(1, 30);

}

void check_password_UI(char* password)
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

	gotoxy(24, 12);
	printf("���ȵ� �ϱ��Դϴ�. ��й�ȣ�� �Է��ϼ���");
	gotoxy(34, 14);
	printf(">> ");
	gotoxy(37, 14);
	scanf("%s", password);


	gotoxy(1, 30);
}

void check_password_UI_m(char* password)
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

	gotoxy(24, 12);
	printf("���ȵ� �޸��Դϴ�. ��й�ȣ�� �Է��ϼ���");
	gotoxy(34, 14);
	printf(">> ");
	gotoxy(37, 14);
	scanf("%s", password);


	gotoxy(1, 30);
}

void check_password_UI_2_0()
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

	gotoxy(32, 13);
	printf("��й�ȣ�� Ʋ�Ƚ��ϴ�..");

	gotoxy(56, 13);
	printf("2");
	Sleep(1000);
	gotoxy(56, 13);
	printf("1");
	Sleep(1000);


	gotoxy(1, 30);
}

void search_UI(char* keyword)
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

	gotoxy(30, 12);
	printf("�˻��� Ű���带 �Է��ϼ���");
	gotoxy(34, 14);
	printf(">> ");
	gotoxy(37, 14);
	fgets(keyword, MAX_LEN, stdin);


	gotoxy(1, 30);
}

void search_diary_UI()
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

	gotoxy(36, 2);
	printf("�˻��Ͻ� Ű���尡 ���Ե� �ϱ��� ��¥�Դϴ�.");

	/*
	gotoxy(8, 8);
	printf(">>");

	gotoxy(8, 25);
	printf(">>>");
	*/

	gotoxy(1, 30);

}

void search_memo_UI()
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

	gotoxy(36, 2);
	printf("�˻��Ͻ� Ű���尡 ���Ե� �޸��� ��¥�Դϴ�.");

	/*
	gotoxy(8, 8);
	printf(">>");

	gotoxy(8, 25);
	printf(">>>");
	*/

	gotoxy(1, 30);

}

void exit_UI()
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

	gotoxy(32, 13);
	printf("���α׷��� �����մϴ�...");


	gotoxy(60, 13);
	printf("2");
	Sleep(1000);
	gotoxy(60, 13);
	printf("1");
	Sleep(1000);

	gotoxy(1, 30);
}

void correct_password_UI()
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

	gotoxy(32, 13);
	printf("��й�ȣ�� ��ġ�մϴ�!");

	/*
	gotoxy(56, 13);
	printf("2");
	Sleep(1000);
	gotoxy(56, 13);
	printf("1");
	Sleep(1000);
	*/


	gotoxy(1, 30);
}











