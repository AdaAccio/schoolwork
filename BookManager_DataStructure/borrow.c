#include <stdio.h>
#include <stdlib.h>//���а���system����
#include <conio.h>//������ͨ������̨���� �������� ����������ĺ�������getch������
#include <string.h>//�����ַ�����
#include <math.h>
#define LEN1 sizeof(struct reader)//�йض�����Ϣ�Ľṹ��

#include "test.h"
void borrowmenu()//��ʾ����˵�
{
	system("cls");
	printf("*****************************************************");
	printf("\n\n 1.����Ǽ�\n\n");
	printf("\n\n 2.����Ǽ�\n\n");
	printf("\n\n 3.��������鿴\n\n");
	printf("\n\n 4.��ѯ����\n\n");
	printf("\n\n 5.������һ��\n\n");
	printf("\n\n �밴��ѡ�񣬻س�ȷ��\n");
	printf("****************************************************");
	return;
}


void borrow_message()//����ϵͳ����
{
	void borrow();
	void returnbook();
	void visit_borrow();
	void inquire();
	char choose;
	borrowmenu();
	scanf(" %c", &choose);
	for (;;)
	{
		switch (choose)
		{
		case'1':
			borrow();
			break;
		case'2':
			returnbook();
			break;
		case'3':
			visit_borrow();
			break;
		case'4':
			inquire();
			break;
		case'5':
			mainfunction();
			break;
		}
	}

}



void borrow()//���麯��
{
	FILE* fp, * fp3;
	struct book* head = NULL;
	struct book* p, * p1 = NULL, * p2 = NULL;
	int i, loop, k, n = 0, flag = 0, s = 0;
	int ID_card = 0;
	int count = 0;
	float tprice = 0;
	char tnamee[100] = { '\0' }, tauthor[100] = { '\0' }, tkind[100] = { '\0' }, tpublisher[100] = { '\0' }, tshuhao[100] = { '\0' },
		ttnamee[100] = { '\0' }, name[100] = { '\0' }, time[100] = { '\0' }, znamee[100] = { '\0' };
	char hit = 0;

	system("cls");
	if ((fp = fopen("library.txt", "r")) == NULL)
	{
		system("cls");
		printf("\n ͼ����޿��!��������˳�!");
		getch();
		exit(0);
	}
	else
	{
		printf("\n�������������:\n������:");
		scanf("%s", znamee);
		k = statistic_book();//ͳ��ͼ����ļ�����

		for (i = 0; i < k; i++)//�Ƚ�ͼ����Ϣ�����������Ŀ��
		{
			fscanf(fp, "%s%s%s%s%s%d%f", tshuhao, tnamee, tauthor, tpublisher, tkind, &count, &tprice);
			n++;
			if (n == 1)
			{
				p1 = p2 = (struct book*)malloc(LEN);
				head = p1;
			}
			else
			{
				p2->next = p1;
				p2 = p1;
				p1 = (struct book*)malloc(LEN);

			}
			strcpy(p1->num, tshuhao);//�������
			strcpy(p1->name, tnamee);//��������
			strcpy(p1->aut, tauthor);//��������
			strcpy(p1->pub, tpublisher);//���Ƴ�����
			strcpy(p1->cat, tkind);//�������
			p1->count = count;//�����ִ���
			p1->price = tprice;//���Ƶ���
		}
		if (n == 0)
			head = NULL;
		else
		{
			p2->next = p1;
			p1->next = NULL;
			fclose(fp);
		}

	}
	p = head;

	for (; p != NULL;)
	{
		if (!(strcmp(p->name, znamee)))//�ж�Ҫ������Ƿ���ڣ���ǵ���1�����ڿ���һ
		{

			flag = 1;
			loop = p->count;
			(p->count)--;
		}
		p = p->next;
	}
	if (flag && (loop > 0))//���ڱ����ͼ�����ִ�������0���ѿ�����仯�����������ļ�
	{

		fp = fopen("library.txt", "w");
		fclose(fp);
		fp = fopen("library.txt", "a");
		p = head;

		for (; p != NULL;)
		{
			fprintf(fp, "%-8s%-100s%-100s%-100s%-100s%-7d%-8.2f\n", p->num, p->name, p->aut, p->pub, p->cat, p->count, p->price);
			p = p->next;
		}
		free(p);
		fclose(fp);

		if ((fp3 = fopen("reader.txt", "r")) == NULL)//�������ļ��д��������Ϣ
		{
			fp3 = fopen("reader.txt", "w");//��ֻ���ļ�
			fclose(fp3);
		}
		fp3 = fopen("reader.txt", "a");

		printf("\n�밴���¸�ʽ���������Ϣ:\n ֤�� ���� �������� ��������\n������:");//¼�������Ϣ
		scanf("%d %s %s %s", &ID_card, name, time, znamee);
		fprintf(fp3, "\n%-8d%-23s%-18s%-10s\n", ID_card, name, time, znamee);
		fclose(fp3);
		printf("����ɹ�!���������ڹ黹�����������������\n");
		getch();//����
		borrow_message();//���ý���ϵͳ
	}
	else
	{
		if (flag != 0)
			printf("�����ѱ�����!�����������!");//������������ѱ�����
		else
			printf("�����޴���!�����������");
	}
	getch();//����
	borrow_message();//���ý���ϵͳ

}


void returnbook()//���麯��
{
	FILE* fp, * fp3;
	struct reader* head = NULL;
	struct reader* p, * p1 = NULL, * p2 = NULL;
	struct book* lhead1 = NULL;
	struct book* zp1, * lp1 = NULL, * lp2 = NULL;
	int txcl = 0, i;
	float tprice = 0;
	char tnamee[100] = { '\0' }, tauthor[100] = { '\0' }, tkind[100] = { '\0' },
		tchuban[100] = { '\0' }, ttnamee[100] = { '\0' }, tshuhao[100] = { '\0' };
	int ttzh = 0, tzhenghao = 0, n = 0, k = 0, t = 0, flag = 0;
	char tname[100] = { '\0' }, ttime[100] = { '\0' }, tznamee[100] = { '\0' }, ttznamee[100] = { '\0' };
	char hitkey = 0;
	system("cls");
	{
		fp = fopen("reader.txt", "r");
		if (fp == NULL)//�����ڶ����ļ�����������ܻ���
		{
			system("cls");
			printf("\n �����ڽ�����!��������˳�!");
			getch();
			system("cls");
			borrow_message();
		}

		else
		{
			{
				printf("\n���������֤�ź�����:\n������:");
				scanf("%d %s", &ttzh, ttznamee);//���뻹��֤�ź�����
				k = statistic_reader();//��ȡ�����ļ�����Ϣ����
				for (i = 0; i <= k; i++)//��ȡ�����ļ�����Ϣ
				{
					fscanf(fp, "%d%s%s%s\n ", &tzhenghao, tname, ttime, tznamee);
					if ((ttzh == tzhenghao) && !strcmp(ttznamee, tznamee))//���֤���������ڣ�����Ϊ1
						flag = 1;
				}
				fclose(fp);
				fp = fopen("reader.txt", "r");//�򿪶����ļ���ɾ��������Ϣ
				if (flag)
				{
					for (i = 0; i < k; i++)//�������ļ����Ƶ�����
					{
						fscanf(fp, "%d%s%s%s\n ", &tzhenghao, tname, ttime, tznamee);//��ȡ�ļ���Ϣ
						if (!((ttzh == tzhenghao) && !strcmp(ttznamee, tznamee)))
						{
							n++;
							if (n == 1)
							{
								p1 = p2 = (struct reader*)malloc(LEN1);//�½�����
								head = p1;
							}
							else
							{
								p2->next = p1;
								p2 = p1;
								p1 = (struct reader*)malloc(LEN1);//�½�����
							}
							p1->ID_card = tzhenghao;//����֤��
							strcpy(p1->borrow_name, tname);//���ƶ�������
							strcpy(p1->time, ttime);//������
							strcpy(p1->return_name, tznamee);//��������
						}
					}
					if (n == 0)
						head = NULL;
					else
					{
						p2->next = p1;
						p1->next = NULL;
						fclose(fp);
					}
					fp = fopen("reader.txt", "w");//��ն����ļ�
					fclose(fp);
					fp = fopen("reader.txt", "a");//׷����Ϣ
					p = head;
					for (; p != NULL;)//���������ݸ��Ƕ����ļ�
					{
						fprintf(fp, "\n%-8d%-23s%-18s%-10s\n", p->ID_card, p->borrow_name, p->time, p->return_name);
						p = p->next;
					}
					free(p);
					fclose(fp);
				}}
		}}

	if (flag)//���Ϊ1��������ʱ���Ŀ��
	{
		{
			{
				printf("ȷ�ϻ����밴�س�!");
				for (; hitkey != 13 && hitkey != 27;)
					hitkey = getch();
				if (hitkey == 13)
					printf("�ɹ�!�����������!");
				n = 0; flag = 0;
				fp3 = fopen("library.txt", "r");//��ͼ����ļ�
				k = statistic_book();//��ȡͼ����ļ�����
				for (i = 0; i < k; i++)//��ͼ����ļ����Ƶ�����
				{
					fscanf(fp3, "%s%s%s%s%s%d%f", tshuhao, tnamee, tauthor, tchuban, tkind, &txcl, &tprice);//��ȡ��Ϣ
					n++;
					if (n == 1)
					{
						lp1 = lp2 = (struct book*)malloc(LEN);//�½�����
						lhead1 = lp1;
					}
					else
					{
						lp2->next = lp1;
						lp2 = lp1;
						lp1 = (struct book*)malloc(LEN);//�½�����
					}
					strcpy(lp1->num, tshuhao);//�������
					strcpy(lp1->name, tnamee);//��������
					strcpy(lp1->aut, tauthor);//��������
					strcpy(lp1->pub, tchuban);//���Ƴ�����
					strcpy(lp1->cat, tkind);//�������
					lp1->count = txcl; //�����ִ���
					lp1->price = tprice;//���Ƶ���
				}
				if (n == 0)
				{
					lhead1 = NULL;
				}
				else
				{
					lp2->next = lp1;
					lp1->next = NULL;
					fclose(fp3);
				}}}
		zp1 = lhead1;
		for (; zp1 != NULL;)
		{
			if (!(strcmp(zp1->name, ttznamee)))//Ѱ��������ͬ
				++(zp1->count);//�ִ�����1
			zp1 = zp1->next;
		}
		fp3 = fopen("library.txt", "w");//���ͼ����ļ�
		fclose(fp);
		fp3 = fopen("library.txt", "a");//׷����Ϣ
		zp1 = lhead1;
		for (; zp1 != NULL;)//���������ݸ���ͼ����ļ�
		{
			fprintf(fp3, "%-8s%-9s%-14s%-16s%-18s%-7d%-8.2f\n",
				zp1->num, zp1->name, zp1->aut, zp1->pub, zp1->cat, zp1->count, zp1->price);
			zp1 = zp1->next;
		}
		fclose(fp3);
		getch();//����
		borrow_message();//���ý���ϵͳ
	}
	else
		printf("�����ڴ���Ϣ!�����������!");
	getch();//����
	borrow_message();//���ý���ϵͳ
}


void visit_borrow()//��ʾ�����������

{
	FILE* fp;
	int ID = 0, xcl = 0, n = 0, i = 0, j = 0;
	char name[100] = { '\0' }, time[100] = { '\0' }, znamee[100] = { '\0' };
	if ((fp = fopen("reader.txt", "r")) == NULL)//�򿪶����ļ���
	{
		system("cls");
		printf("\n��¼�ļ�������!�����������");
		getch();
		borrow_message();
	}
	n = statistic_reader();
	if (n == 0)
	{
		system("cls");
		printf("\n���κμ�¼!");
	}
	fp = fopen("reader.txt", "r");
	system("cls");
	printf("\n֤��\t��������\t\t��������\t����\n");
	for (; !feof(fp);)//����ļ���Ϣ
	{
		fscanf(fp, "%d%s%s%s\n ", &ID, name, time, znamee);
		printf("\n%-8d%-23s%-18s%-10s\n", ID, name, time, znamee);
	}
	fclose(fp);
	printf("\n�����������\n");
	getch();//����
	borrow_message();//���ý���ϵͳ
}

int borrow_humnum()
{

	FILE* fp;
	int t = 0;
	float price = 0;
	int borrownum = 0, k = 0, count = 0, m = 0, n = 0;

	char  borrowname[100] = { '\0' }, borrowtime[100] = { '\0' }, return_name[100] = { '\0' };
	char i;
	fp = fopen("reader.txt", "r");//���ļ�
	for (n = 0; !feof(fp); n++)//������ļ�
		fscanf(fp, "%d%s%s%s", &borrownum, borrowname, borrowtime, return_name);
	n--;
	fclose(fp);//�ر��ļ�
	return (n);//���ظ���
}
void inquire()//��ѯ����
{
	FILE* fp;
	int borrownum = 0, k = 0, count = 0, m = 0, n = 0;

	char  borrowname[100] = { '\0' }, borrowtime[100] = { '\0' }, return_name[100] = { '\0' };
	char i;
	char cz[100] = { '\0' };
	if ((fp = fopen("reader.txt", "r")) == NULL)//���ļ�
	{
		system("cls");
		printf("\n��¼�ļ�������!�����������");
		getch();
		borrow_message();
	}
	system("cls");
	printf("������֤�Ż�������ѯ��\n");
	scanf("%s", cz);
	system("cls");
	m = borrow_humnum();
	for (n = 0; n < m; n++)
	{
		fscanf(fp, "%d%s%s%s", &borrownum, borrowname, borrowtime, return_name);
		if ((!strcmp(cz, borrowname)) || (atoi(cz) == borrownum))
		{
			printf("��ѯ���:\n\n");
			printf("\n֤��\t��������\t\t��������\t����\n");
			printf("\n%-8d%-23s%-18s%-10s\n", borrownum, borrowname, borrowtime, return_name);
			k++;

		}
	}
	if (k == 0)//�ļ���Ϊ��������޼�¼��������һ��
	{
		system("cls");
		printf("\n�޷��ϼ�¼!\n");
		getch();
		borrow_message();
	}
	fclose(fp);//��ѯ����
	getch();
	borrow_message();
}



//ģ����ѯ
void vague()
{
	FILE* fp;
	int k = 0, count = 0, m = 0, n = 0, p = 0, q, p1 = 0, q1 = 0, p2 = 0;
	int end = 0;
	float price = 0;
	char  name[100] = { '\0' }, aut[100] = { '\0' }, cat[100] = { '\0' }, pub[100] = { '\0' }, num[100] = { '\0' };
	char i;
	char ch[100] = { '\0' };
	char* ch1;
	if ((fp = fopen("library.txt", "r")) == NULL)//���ļ�
	{
		system("cls");
		printf("\n��¼�ļ�������!�����������");
		getch();
		libfunction();
	}
	system("cls");
	printf("����������Ҫ��ѯ�����к��е��֣�");
	scanf("%s", ch);
	q1 = strlen(ch);
	system("cls");
	m = statistic_book();
	for (n = 0; n < m; n++)
	{
		end = 0;
		p2 = 0;
		p1 = 0;
		fscanf(fp, "%s%s%s%s%s%d%f", num, name, aut, pub, cat, &count, &price);
		q = strlen(name);
		while (p2 != q1)
		{
			while (p1 != q)
			{
				if (ch[p2] == name[p1])
				{
					end++;
					p1++;
					break;
				}
				else
					p1++;
			}
			p2++;
		}
		if (end == q1)
		{
			if (k == 0)
			{

				printf("���\t����\t����\t\t������\t\t���\t\t�ִ���\t����\n");
			}
			printf("%-8s%-9s%-14s%-16s%-18s%-7d%-8.2f\n", num, name, aut, pub, cat, count, price);
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
