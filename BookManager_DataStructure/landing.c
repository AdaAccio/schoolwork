#include <stdio.h>
#include <stdlib.h>//���а���system����
#include <conio.h>//������ͨ������̨���� �������� ����������ĺ�������getch������
#include <string.h>//�����ַ�����
#include <math.h>

#define LEN2 sizeof(struct land)//�йص�¼ϵͳ�Ľṹ��
#include "test.h"
void landingmenu()//��ʾ��¼�˵�
{


	printf("\n\n\t    ��ӭʹ�û�Ա��¼ϵͳ\n\n");
	printf("**********************************************");
	printf("\n\n\t\t1.��¼ϵͳ\n\n");
	printf("\n\n\t\t2.�����˺�\n\n");
	printf("\n\n\t\t3.�޸�����\n\n");
	printf("\n\n\t\t4.�˳�ϵͳ\n\n");
	printf("\n\n\t    �밴��ѡ�񣬻س�ȷ��\n");
	printf("**********************************************");
	return;
}


void landingmain()//��¼���ܺ���
{
	void land();
	void create();
	char choose;
	landingmenu();
	scanf(" %c", &choose);
	switch (choose)//���ܺ���
	{
	case'1':
		land();
		break;
	case'2':
		create();
		break;
	case'3':
		altercode();
		break;
	case'4':
		system("cls");
		getch();
		exit(0);
		system("cls");
		break;
	}
}



void create()//�½��˻�����
{
	FILE* fp;
	int ID_card;
	char password[100], password1[100];
	char hit = 0;
	if ((fp = fopen("land.txt", "r")) == NULL)//if��䣺��ͼ����ļ��������ڴ��ļ����½�
	{
		fp = fopen("land.txt", "w");
		fclose(fp);
	}
	system("cls");
	fp = fopen("land.txt", "a");
	for (;;)//������������ȷ�ϣ�������ͬ����ȷ��
	{
		printf("\n�밴���¸�ʽ�����˻�:\nѧ�� ����\n");
		printf("������:");
		scanf("%d %s", &ID_card, password);
		printf("�ٴ���������:\n");
		scanf("%s", password1);
		if (strcmp(password, password1) == 0)
		{
			fprintf(fp, "%d %s\n", ID_card, password);
			break;
		}
		else
		{
			printf("�����������벻һ�£������������س����˳���ESC");
			hit = getch();
			if (hit = 27)
				system("cls");
			landingmain();
		}
	}
	fclose(fp);
	printf("�����ɹ��������������");
	getch();
	system("cls");
	landingmain();
}



int match(int m, char a[100])//ƥ�����ݿ��е��˺�����
{
	FILE* fp;
	int n = 0, i = 0;
	int ID_card;
	char password[100];

	if ((fp = fopen("land.txt", "r")) == NULL)//�����ڶ����ļ�
	{
		system("cls");
		printf("\n ��δ�����û�!���½��˻�");
		getch();
		system("cls");
		landingmain();

	}


	for (; !feof(fp);)
	{
		fscanf(fp, "%d%s", &ID_card, password);
		if (m == ID_card)
		{
			if (strcmp(a, password) == 0)
				return 1;
			else
			{
				return -1;
			}
		}
	}
	return 0;
}

void land()//�����˻�����ĵ�¼����
{
	int ID_card;
	char password[100];
	int i = 2, j, k, n;
	char hit = 0;
	system("cls");
	do
	{
		printf("\n�������˺�:\n");
		scanf("%d", &ID_card);
		printf("ȷ�������밲�س������������밴ECS");
		hit = getch();//��ͣ����i���պ������һ��ָ��
		for (; hit != 13 && hit != 27;)//��ֻ֤����CR��ESC�����˳�ѭ��,���������ַ����ã���ͣ���򣬰�'CR'������
		{
			hit = getch();
		}
	} while (hit == 27);
	printf("\n����������:\n");
	scanf("%s", password);
	i = match(ID_card, password);
	if (i == 1)
	{
		printf("��½�ɹ�!�����������");
		getch();
		mainfunction();
	}
	else
	{
		if (i == -1)
		{
			printf("�������!");
			getch();
			land();
		}
		if (i == 0)
			printf("�����ڴ��û�");
		getch();
		system("cls");
		landingmain();
	}
}

void alter(int z, char m[100])//�޸ĺ���
{
	FILE* fp;
	int ID_card1, n = 0, j, k;
	char mima1[100];
	struct land* head = NULL, * p = NULL, * p1 = NULL, * p2 = NULL;

	fp = fopen("land.txt", "r");
	j = statistic_book3();
	for (k = 0; k <= j; k++)
	{
		fscanf(fp, "%d %s", &ID_card1, mima1);
		if (z != ID_card1)//�Ƚ����֣�����ͬ���ֵ���Ϣ���Ƶ�����
		{
			n++;//��ͬ����ֵΪ0��ִ��if������ѭ������ͬ��ִ��ֱ�������в�ͬ����������������
			if (n == 1)//��������
			{
				p1 = p2 = (struct land*)malloc(LEN2);
				head = p1;
			}
			else
			{
				p2->next = p1;
				p2 = p1;
				p1 = (struct land*)malloc(LEN2);//�½�����
			}
			p1->ID_card = ID_card1;
			strcpy(p1->password, mima1);//�����˺�����
		}
	}
	if (n == 0)
	{
		head = NULL;
	}
	else//������������ʣ��һ������ռ䣬���Է��
	{
		p2->next = p1;
		p1->next = NULL;
		fclose(fp);
	}
	fp = fopen("land.txt", "w");//����ļ���ֻд�򿪣�Ȼ��ر�
	fclose(fp);
	fp = fopen("land.txt", "a");//׷���ļ�
	p = head;
	for (; p != NULL;)//���������ݸ��ǵ��ļ�
	{
		fprintf(fp, "%d %s%\n", p->ID_card, p->password);
		p = p->next;
	}
	fprintf(fp, "%d %s\n", z, m);
	fclose(fp);
	system("cls");

}



void altercode()//�޸�����
{

	FILE* fp;
	int zh = 0, k = 0, count = 0, m = 0, n = 0;
	int chazhao, hit;
	char mima[100] = { '\0' }, password1[100] = { '\0' };
	char  mm[100] = { '\0' };
	char i;

	if ((fp = fopen("land.txt", "r")) == NULL)//���ļ�
	{
		system("cls");
		printf("\n��¼�ļ�������!�����������");
		getch();
		system("cls");
		landingmain();
	}
	system("cls");
	printf("����������ʺź;����룺\n");
	scanf("%d %s", &chazhao, mima);
	m = statistic_book3();
	for (n = 0; n <= m; n++)
	{
		fscanf(fp, "%d %s", &zh, mm);
		if (zh == chazhao)
		{
			if (!strcmp(mm, mima))
			{
				printf("�������µ�����");
				scanf("%s", mima);
				printf("�ٴ���������:\n");
				scanf("%s", password1);
				if (strcmp(mima, password1) == 0)
				{
					alter(chazhao, mima);
					getch();
					landingmain();
					system("cls");
				}
				else
				{
					printf("�����������벻һ��,��������˳�");
					hit = getch();
					system("cls");
					landingmain();

				}
			}
			else
			{
				printf("��������󣬰���������أ�");
				getch();
				system("cls");
				landingmain();

			}

		}
	}
	printf("�����ڴ��˺ţ������������");
	fclose(fp);//�޸Ľ���
	getch();
	system("cls");
	landingmain();
}
