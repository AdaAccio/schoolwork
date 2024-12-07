#include <stdio.h>
#include <stdlib.h>//���а���system����
#include <conio.h>//������ͨ������̨���� �������� ����������ĺ�������getch������
#include <string.h>//�����ַ�����
#include <math.h>
#include <assert.h>

#define LEN sizeof(struct book)//�й�ͼ����Ϣ�Ľṹ��
#include "test.h"

int statistic_book()//ͳ��ͼ���ı�����
{
	FILE* fp;
	int t = 0, n;
	float price = 0;
	char name[100] = { '\0' }, author[100] = { '\0' }, publisher[100] = { '\0' }, kind[100] = { '\0' }, number[100] = { '\0' };
	fp = fopen("library.txt", "r");//���ļ�
	for (n = 0; !feof(fp); n++)//������ļ�
		fscanf(fp, "%s%s%s%s%s%d%f", number, name, author, publisher, kind, &t, &price);
	n--;
	fclose(fp);//�ر��ļ�
	return (n);//���ظ���
}


int statistic_reader()//ͳ���Ķ��߱���������

{
	FILE* fp;
	int ID_card = 0, n;
	char name1[100] = { '\0' }, time[100] = { '\0' }, name2[100] = { '\0' };
	fp = fopen("reader.txt", "r");//���ļ�
	for (n = 0; !feof(fp); n++)//������ļ�
		fscanf(fp, "%d%s%s%s ", &ID_card, &name1, &time, &name2);
	n--;
	fclose(fp);//�ر��ļ�
	return (n);//���ظ���
}


int statistic_book3()//ͳ���˺������ı�����
{
	FILE* fp;
	int ID = 0, n;
	char code[100] = { '\0' };
	fp = fopen("land.txt", "r");//���ļ�
	for (n = 0; !feof(fp); n++)//������ļ�
		fscanf(fp, "%d %s", &ID, code);
	n--;
	fclose(fp);//�ر��ļ�
	return (n);//���ظ���
}



void adds()//����ͼ��
{
	FILE* fp;
	char i = '0';
	int many = 0;
	float price = 0;
	float price1 = 0;
	int t = 0;
	char  nam[100] = { '\0' }, aut[100] = { '\0' }, cat[100] = { '\0' }, pub[100] = { '\0' }, num[100] = { '\0' };
	char  name[100] = { '\0' }, author[100] = { '\0' }, kind[100] = { '\0' }, publish[100] = { '\0' }, number[100] = { '\0' };
	system("cls");

	if ((fp = fopen("library.txt", "r+")) == NULL)//if��䣺��ͼ����ļ��������ڴ��ļ����½�
	{
		//fp = fopen("library.txt", "r+");
		fclose(fp);
	}
	//fp = fopen("library.txt", "r+");

	printf("\n�밴���¸�ʽ����ͼ����Ϣ:\n��� ���� ���� ������ ��� ������ ����");

	for (; i != 27;)//Ϊ��ʵ������һ�κ�esc�˳�
	{
		printf("������:\n");
		scanf("%s%s%s%s%s%d%f", num, nam, aut, pub, cat, &many, &price);
		int flag = 0;
		fp = fopen("library.txt", "r+");
		for (int n = 0; !feof(fp); n++)//������ļ�
		{
			//printf("1");
			fscanf(fp, "%s%s%s%s%s%d%f", number, name, author, publish, kind, &t, &price1);
			if (atoi(num) == atoi(number))
			{
				flag = 1;
				break;
			}
		}
		if (flag == 1)
		{
			printf("������Ѵ��ڣ����������밴�س������������밴Esc\n");
			i = getch();//��ͣ����i���պ������һ��ָ��
			for (; i != 13 && i != 27;)//��ֻ֤����CR��ESC�����˳�ѭ��,���������ַ����ã���ͣ���򣬰�'CR'������
				i = getch();
			fclose(fp);
			continue;
		}

		fprintf(fp, "%-20s%-20s%-20s%-20s%-20s%-7d%-8.2f\n", num, nam, aut, pub, cat, many, price);
		fclose(fp);
		printf("���������밴�س������������밴Esc\n");
		i = getch();//��ͣ����i���պ������һ��ָ��
		for (; i != 13 && i != 27;)//��ֻ֤����CR��ESC�����˳�ѭ��,���������ַ����ã���ͣ���򣬰�'CR'������
			i = getch();
	}

	fclose(fp);
	printf("\n����ɹ����������������һ��!");
	getch();
	libfunction();//������һ��
}

void removes()//ɾ��ͼ��
{
	int flag = 1;//�жϼ�¼
	struct book* head = NULL;
	struct book* p, * p1 = NULL, * p2 = NULL;
	int tcount = 0, n = 0, j, k;
	float tprice = 0;
	char  tname[100] = { '\0' }, taut[100] = { '\0' }, tcat[100] = { '\0' }, tpub[100] = { '\0' }, tnum[100] = { '\0' };
	char jborrow_name[100] = { '\0' };
	char i;
	FILE* fp;
	if ((fp = fopen("library.txt", "r")) == NULL)//���ļ�
	{
		system("cls");
		printf("\n��¼�ļ�������!�����������");
		getch();
		libfunction();
	}

	else//ʵ��ɾ���Ĺ���
	{
		system("cls");
		printf("\n��������Ҫɾ��������:");//����ɾ��ͼ������
		scanf("%s", jborrow_name);
		printf("\nȷ��ɾ����س���ȡ���밴Esc\n");
		i = getch();
		for (; i != 13 && i != 27;)
			i = getch();
		if (i == 27)
			libfunction();
		fp = fopen("library.txt", "r");
		j = statistic_book();

		for (k = 0; k < j; k++)
		{
			fscanf(fp, "%s%s%s%s%s%d%f", tnum, tname, taut, tpub, tcat, &tcount, &tprice);
			if (strcmp(jborrow_name, tname))//�Ƚ����֣�����ͬ���ֵ���Ϣ���Ƶ�����
			{
				n++;//��ͬ����ֵΪ0��ִ��if������ѭ������ͬ��ִ��ֱ�������в�ͬ����������������
				if (n == 1)//��������
				{
					p1 = p2 = (struct book*)malloc(LEN);
					head = p1;
				}
				else
				{
					p2->next = p1;
					p2 = p1;
					p1 = (struct book*)malloc(LEN);//�½�����
				}

				strcpy(p1->num, tnum);//�������
				strcpy(p1->name, tname);//��������
				strcpy(p1->aut, taut);//������������
				strcpy(p1->pub, tpub);//���Ƴ�����
				strcpy(p1->cat, tcat);//�������
				p1->count = tcount;//���Ƹ���
				p1->price = tprice;//���Ƶ���
			}
		}
		if (n == 0)//���ͼ��ֻ��һ������һ��պú�Ҫɾ������ͬ
		{
			head = NULL;
		}
		else//������������ʣ��һ������ռ䣬���Է��
		{
			p2->next = p1;
			p1->next = NULL;
			fclose(fp);
		}
		if (n == j)
			flag = 0;
	}

	fp = fopen("library.txt", "w");//����ļ���ֻд�򿪣�Ȼ��ر�
	fclose(fp);
	fp = fopen("library.txt", "a");//׷���ļ�
	p = head;

	for (; p != NULL;)//���������ݸ��ǵ��ļ�
	{
		fprintf(fp, "%-30s%-30s%-30s%-30s%-30s%-7d%-8.2f\n", p->num, p->name, p->aut, p->pub, p->cat, p->count, p->price);
		p = p->next;
	}
	fclose(fp);
	system("cls");
	if (flag)
		printf("\nɾ���ɹ� \n�������������һ��\n");
	else
		printf("\n���鲻���ڣ��޷�ɾ����\n");
	getch();//������һ��
	libfunction();
}


void search()//��ѯͼ��
{
	FILE* fp;
	int k = 0, count = 0, m = 0, n = 0;
	float price = 0;
	char  name[100] = { '\0' }, aut[100] = { '\0' }, cat[100] = { '\0' }, pub[100] = { '\0' }, num[100] = { '\0' };
	char i;
	char arr[100] = { '\0' };
	if ((fp = fopen("library.txt", "r")) == NULL)//���ļ�
	{
		system("cls");
		printf("\n��¼�ļ�������!�����������");
		getch();
		libfunction();
	}
	system("cls");
	printf("���������,����,���߻�����ѯ��\n");
	scanf("%s", arr);
	system("cls");
	m = statistic_book();

	for (n = 0; n < m; n++)
	{
		fscanf(fp, "%s%s%s%s%s%d%f", num, name, aut, pub, cat, &count, &price);
		if (!strcmp(arr, num) || !strcmp(arr, name) || !strcmp(arr, aut) || !strcmp(arr, cat))
		{
			if (k == 0)
			{
				printf("��ѯ���:\n\n");
				printf("���\t����\t����\t\t������\t\t���\t\t�ִ���\t����\n");
			}
			printf("%-8s%-30s%-30s%-30s%-30s%-7d%-8.2f\n", num, name, aut, pub, cat, count, price);
			k++;
		}
	}
	if (k == 0)//�ļ���Ϊ��������޼�¼��������һ��
	{
		system("cls");
		printf("\n�޷��ϼ�¼!\n");
		getch();
		libfunction();
	}
	fclose(fp);//��ѯ����
	getch();
	libfunction();
}


void visit()//���ͼ��
{
	FILE* fp;
	int n = 0;
	int k = 0, m = 0, count = 0;
	float price = 0;
	char  name[100] = { '\0' }, aut[100] = { '\0' }, cat[100] = { '\0' }, pub[100] = { '\0' }, num[100] = { '\0' };
	char i;
	if ((fp = fopen("library.txt", "r")) == NULL)//���ļ�
	{
		system("cls");
		printf("\n��¼�ļ�������!�����������");
		getch();//����
		libfunction();
	}
	n = statistic_book();
	if (n == 0)
	{
		system("cls");
		printf("\n���κμ�¼!");
	}

	fp = fopen("library.txt", "r");//��ֻ���ļ�
	system("cls");
	printf("���\t����\t����\t\t������\t\t���\t\t�����\t����\n");

	for (m = 0; m < n; m++)//�������
	{
		fscanf(fp, "%s%s%s%s%s%d%f", num, name, aut, pub, cat, &count, &price);
		printf("%-8s%-30s%-30s%-30s%-30s%-7d%-8.2f\n", num, name, aut, pub, cat, count, price);
	}
	fclose(fp);
	printf("\n�����������\n");
	getch();
	libfunction();
}



