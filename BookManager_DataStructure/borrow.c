#include <stdio.h>
#include <stdlib.h>//其中包含system函数
#include <conio.h>//定义了通过控制台进行 数据输入 和数据输出的函数，如getch函数。
#include <string.h>//定义字符数组
#include <math.h>
#define LEN1 sizeof(struct reader)//有关读者信息的结构体

#include "test.h"
void borrowmenu()//显示借书菜单
{
	system("cls");
	printf("*****************************************************");
	printf("\n\n 1.借书登记\n\n");
	printf("\n\n 2.还书登记\n\n");
	printf("\n\n 3.借阅情况查看\n\n");
	printf("\n\n 4.查询借书\n\n");
	printf("\n\n 5.返回上一层\n\n");
	printf("\n\n 请按键选择，回车确定\n");
	printf("****************************************************");
	return;
}


void borrow_message()//借阅系统函数
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



void borrow()//借书函数
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
		printf("\n 图书馆无库存!按任意键退出!");
		getch();
		exit(0);
	}
	else
	{
		printf("\n请输入借阅书名:\n请输入:");
		scanf("%s", znamee);
		k = statistic_book();//统计图书馆文件个数

		for (i = 0; i < k; i++)//先将图书信息建立链表，更改库存
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
			strcpy(p1->num, tshuhao);//复制书号
			strcpy(p1->name, tnamee);//复制书名
			strcpy(p1->aut, tauthor);//复制作者
			strcpy(p1->pub, tpublisher);//复制出版社
			strcpy(p1->cat, tkind);//复制类别
			p1->count = count;//复制现存量
			p1->price = tprice;//复制单价
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
		if (!(strcmp(p->name, znamee)))//判断要借书的是否存在，标记等于1，存在库存减一
		{

			flag = 1;
			loop = p->count;
			(p->count)--;
		}
		p = p->next;
	}
	if (flag && (loop > 0))//存在被借的图书且现存量大于0，把库存量变化后的链表存入文件
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

		if ((fp3 = fopen("reader.txt", "r")) == NULL)//建读者文件夹存入借书信息
		{
			fp3 = fopen("reader.txt", "w");//打开只读文件
			fclose(fp3);
		}
		fp3 = fopen("reader.txt", "a");

		printf("\n请按以下格式输入读者信息:\n 证号 姓名 借书日期 借书书名\n请输入:");//录入读者信息
		scanf("%d %s %s %s", &ID_card, name, time, znamee);
		fprintf(fp3, "\n%-8d%-23s%-18s%-10s\n", ID_card, name, time, znamee);
		fclose(fp3);
		printf("借书成功!请两个月内归还！！！按任意键返回\n");
		getch();//返回
		borrow_message();//调用借阅系统
	}
	else
	{
		if (flag != 0)
			printf("此书已被借完!按任意键返回!");//否则输出此书已被借完
		else
			printf("查找无此书!按任意键返回");
	}
	getch();//返回
	borrow_message();//调用借阅系统

}


void returnbook()//还书函数
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
		if (fp == NULL)//不存在读者文件，则输出不能还书
		{
			system("cls");
			printf("\n 不存在借书者!按任意键退出!");
			getch();
			system("cls");
			borrow_message();
		}

		else
		{
			{
				printf("\n请输入读者证号和书名:\n请输入:");
				scanf("%d %s", &ttzh, ttznamee);//输入还书证号和书名
				k = statistic_reader();//获取读者文件夹信息个数
				for (i = 0; i <= k; i++)//读取读者文件夹信息
				{
					fscanf(fp, "%d%s%s%s\n ", &tzhenghao, tname, ttime, tznamee);
					if ((ttzh == tzhenghao) && !strcmp(ttznamee, tznamee))//如果证号书名存在，则标记为1
						flag = 1;
				}
				fclose(fp);
				fp = fopen("reader.txt", "r");//打开读者文件，删除借书信息
				if (flag)
				{
					for (i = 0; i < k; i++)//将读者文件复制到链表
					{
						fscanf(fp, "%d%s%s%s\n ", &tzhenghao, tname, ttime, tznamee);//读取文件信息
						if (!((ttzh == tzhenghao) && !strcmp(ttznamee, tznamee)))
						{
							n++;
							if (n == 1)
							{
								p1 = p2 = (struct reader*)malloc(LEN1);//新建链表
								head = p1;
							}
							else
							{
								p2->next = p1;
								p2 = p1;
								p1 = (struct reader*)malloc(LEN1);//新建链表
							}
							p1->ID_card = tzhenghao;//复制证号
							strcpy(p1->borrow_name, tname);//复制读者名字
							strcpy(p1->time, ttime);//复制日
							strcpy(p1->return_name, tznamee);//复制书名
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
					fp = fopen("reader.txt", "w");//清空读者文件
					fclose(fp);
					fp = fopen("reader.txt", "a");//追加信息
					p = head;
					for (; p != NULL;)//把链表内容覆盖读者文件
					{
						fprintf(fp, "\n%-8d%-23s%-18s%-10s\n", p->ID_card, p->borrow_name, p->time, p->return_name);
						p = p->next;
					}
					free(p);
					fclose(fp);
				}}
		}}

	if (flag)//标记为1，即还书时更改库存
	{
		{
			{
				printf("确认还书请按回车!");
				for (; hitkey != 13 && hitkey != 27;)
					hitkey = getch();
				if (hitkey == 13)
					printf("成功!按任意键返回!");
				n = 0; flag = 0;
				fp3 = fopen("library.txt", "r");//打开图书馆文件
				k = statistic_book();//获取图书馆文件个数
				for (i = 0; i < k; i++)//将图书馆文件复制到链表
				{
					fscanf(fp3, "%s%s%s%s%s%d%f", tshuhao, tnamee, tauthor, tchuban, tkind, &txcl, &tprice);//读取信息
					n++;
					if (n == 1)
					{
						lp1 = lp2 = (struct book*)malloc(LEN);//新建链表
						lhead1 = lp1;
					}
					else
					{
						lp2->next = lp1;
						lp2 = lp1;
						lp1 = (struct book*)malloc(LEN);//新建链表
					}
					strcpy(lp1->num, tshuhao);//复制书号
					strcpy(lp1->name, tnamee);//复制书名
					strcpy(lp1->aut, tauthor);//复制作者
					strcpy(lp1->pub, tchuban);//复制出版社
					strcpy(lp1->cat, tkind);//复制类别
					lp1->count = txcl; //复制现存量
					lp1->price = tprice;//复制单价
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
			if (!(strcmp(zp1->name, ttznamee)))//寻找书名相同
				++(zp1->count);//现存量加1
			zp1 = zp1->next;
		}
		fp3 = fopen("library.txt", "w");//清空图书馆文件
		fclose(fp);
		fp3 = fopen("library.txt", "a");//追加信息
		zp1 = lhead1;
		for (; zp1 != NULL;)//把链表内容覆盖图书馆文件
		{
			fprintf(fp3, "%-8s%-9s%-14s%-16s%-18s%-7d%-8.2f\n",
				zp1->num, zp1->name, zp1->aut, zp1->pub, zp1->cat, zp1->count, zp1->price);
			zp1 = zp1->next;
		}
		fclose(fp3);
		getch();//返回
		borrow_message();//调用借阅系统
	}
	else
		printf("不存在此信息!按任意键返回!");
	getch();//返回
	borrow_message();//调用借阅系统
}


void visit_borrow()//显示借书情况函数

{
	FILE* fp;
	int ID = 0, xcl = 0, n = 0, i = 0, j = 0;
	char name[100] = { '\0' }, time[100] = { '\0' }, znamee[100] = { '\0' };
	if ((fp = fopen("reader.txt", "r")) == NULL)//打开读者文件夹
	{
		system("cls");
		printf("\n记录文件不存在!按任意键返回");
		getch();
		borrow_message();
	}
	n = statistic_reader();
	if (n == 0)
	{
		system("cls");
		printf("\n无任何记录!");
	}
	fp = fopen("reader.txt", "r");
	system("cls");
	printf("\n证号\t读者姓名\t\t借书日期\t书名\n");
	for (; !feof(fp);)//输出文件信息
	{
		fscanf(fp, "%d%s%s%s\n ", &ID, name, time, znamee);
		printf("\n%-8d%-23s%-18s%-10s\n", ID, name, time, znamee);
	}
	fclose(fp);
	printf("\n按任意键返回\n");
	getch();//返回
	borrow_message();//调用借阅系统
}

int borrow_humnum()
{

	FILE* fp;
	int t = 0;
	float price = 0;
	int borrownum = 0, k = 0, count = 0, m = 0, n = 0;

	char  borrowname[100] = { '\0' }, borrowtime[100] = { '\0' }, return_name[100] = { '\0' };
	char i;
	fp = fopen("reader.txt", "r");//打开文件
	for (n = 0; !feof(fp); n++)//逐个读文件
		fscanf(fp, "%d%s%s%s", &borrownum, borrowname, borrowtime, return_name);
	n--;
	fclose(fp);//关闭文件
	return (n);//返回个数
}
void inquire()//查询借书
{
	FILE* fp;
	int borrownum = 0, k = 0, count = 0, m = 0, n = 0;

	char  borrowname[100] = { '\0' }, borrowtime[100] = { '\0' }, return_name[100] = { '\0' };
	char i;
	char cz[100] = { '\0' };
	if ((fp = fopen("reader.txt", "r")) == NULL)//打开文件
	{
		system("cls");
		printf("\n记录文件不存在!按任意键返回");
		getch();
		borrow_message();
	}
	system("cls");
	printf("请输入证号或姓名查询：\n");
	scanf("%s", cz);
	system("cls");
	m = borrow_humnum();
	for (n = 0; n < m; n++)
	{
		fscanf(fp, "%d%s%s%s", &borrownum, borrowname, borrowtime, return_name);
		if ((!strcmp(cz, borrowname)) || (atoi(cz) == borrownum))
		{
			printf("查询结果:\n\n");
			printf("\n证号\t读者姓名\t\t借书日期\t书名\n");
			printf("\n%-8d%-23s%-18s%-10s\n", borrownum, borrowname, borrowtime, return_name);
			k++;

		}
	}
	if (k == 0)//文件夹为空则输出无记录并返回上一层
	{
		system("cls");
		printf("\n无符合记录!\n");
		getch();
		borrow_message();
	}
	fclose(fp);//查询结束
	getch();
	borrow_message();
}



//模糊查询
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
	if ((fp = fopen("library.txt", "r")) == NULL)//打开文件
	{
		system("cls");
		printf("\n记录文件不存在!按任意键返回");
		getch();
		libfunction();
	}
	system("cls");
	printf("请输入你想要查询的书中含有的字：");
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

				printf("书号\t书名\t作者\t\t出版社\t\t类别\t\t现存量\t单价\n");
			}
			printf("%-8s%-9s%-14s%-16s%-18s%-7d%-8.2f\n", num, name, aut, pub, cat, count, price);
			k++;
		}

	}
	if (k == 0)//文件夹为空则输出无记录并返回上一层
	{
		system("cls");
		printf("\n无符合记录!\n");
		getch();
		libfunction();
	}
	fclose(fp);//查询结束
	getch();
	libfunction();
}
