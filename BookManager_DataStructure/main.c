#include <stdio.h>
#include <stdlib.h>//���а���system����
#include <conio.h>//������ͨ������̨���� �������� ����������ĺ�������getch������
#include <string.h>//�����ַ�����
#include <math.h>
#define LEN sizeof(struct book)//�й�ͼ����Ϣ�Ľṹ��
#define LEN1 sizeof(struct reader)//�йض�����Ϣ�Ľṹ��
#define LEN2 sizeof(struct land)//�йص�¼ϵͳ�Ľṹ��
#pragma warning(disable:4996);
#include <assert.h>

#include "test.h"


void mainmenu()//���˵�
{
	system("cls");

	printf("**************************************************");

	printf("\n\n 1.ͼ��ϵͳ\n\n");

	printf("\n\n 2.����ϵͳ\n\n");

	printf("\n\n 3.�˳�ϵͳ\n\n");

	printf("\n\n �밴��ѡ�񣬻س�ȷ��\n");

	printf("*************************************************\n");

	return;
}


void bookmenu() //ͼ�����Ϣ�˵�
{
	system("cls");

	printf("****************************************************");

	printf("\n 1.����ͼ��\n\n");

	printf("\n 2.ɾ��ͼ��\n\n");

	printf("\n 3.��ѯͼ��\n\n");

	printf("\n 4.������\n\n");

	printf("\n 5.ģ����ѯ\n\n");

	printf("\n 6.������һ��\n\n");

	printf("\n �밴��ѡ�񣬻س�ȷ��\n");

	printf("***************************************************\n");

	return;

}


void mainfunction()
{
	void borrow_message();
	char choose;
	mainmenu();
	scanf(" %c", &choose);
	switch (choose)//���ܺ���
	{
	case'1':
		libfunction();
		break;
	case'2':
		borrow_message();
		break;
	case'3':
		system("cls");
		getch();
		exit(0);
		system("cls");
		break;
	}
}


void libfunction()
{
	void adds();
	void removes();
	void visit();
	char choose;
	bookmenu();
	scanf(" %c", &choose);
	for (;;)
	{
		switch (choose)
		{
		case'1':
			adds();
			break;
		case'2':
			removes();
			break;
		case'3':
			search();
			break;
		case'4':
			visit();
			break;
		case'5':
			vague();
			break;
		case'6':
			mainfunction();
			break;
		}
	}
}



int main()
{
	system("color 1F");
	landingmain();
	return 0;
}

