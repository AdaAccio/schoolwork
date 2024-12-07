#include <stdio.h>
#include <stdlib.h>//其中包含system函数
#include <conio.h>//定义了通过控制台进行 数据输入 和数据输出的函数，如getch函数。
#include <string.h>//定义字符数组
#include <math.h>
#include <assert.h>

#define LEN sizeof(struct book)//有关图书信息的结构体
#include "test.h"

int statistic_book()//统计图书文本个数
{
	FILE* fp;
	int t = 0, n;
	float price = 0;
	char name[100] = { '\0' }, author[100] = { '\0' }, publisher[100] = { '\0' }, kind[100] = { '\0' }, number[100] = { '\0' };
	fp = fopen("library.txt", "r");//打开文件
	for (n = 0; !feof(fp); n++)//逐个读文件
		fscanf(fp, "%s%s%s%s%s%d%f", number, name, author, publisher, kind, &t, &price);
	n--;
	fclose(fp);//关闭文件
	return (n);//返回个数
}


int statistic_reader()//统计文读者本个数函数

{
	FILE* fp;
	int ID_card = 0, n;
	char name1[100] = { '\0' }, time[100] = { '\0' }, name2[100] = { '\0' };
	fp = fopen("reader.txt", "r");//打开文件
	for (n = 0; !feof(fp); n++)//逐个读文件
		fscanf(fp, "%d%s%s%s ", &ID_card, &name1, &time, &name2);
	n--;
	fclose(fp);//关闭文件
	return (n);//返回个数
}


int statistic_book3()//统计账号密码文本个数
{
	FILE* fp;
	int ID = 0, n;
	char code[100] = { '\0' };
	fp = fopen("land.txt", "r");//打开文件
	for (n = 0; !feof(fp); n++)//逐个读文件
		fscanf(fp, "%d %s", &ID, code);
	n--;
	fclose(fp);//关闭文件
	return (n);//返回个数
}



void adds()//增加图书
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

	if ((fp = fopen("library.txt", "r+")) == NULL)//if语句：打开图书馆文件，不存在此文件则新建
	{
		//fp = fopen("library.txt", "r+");
		fclose(fp);
	}
	//fp = fopen("library.txt", "r+");

	printf("\n请按以下格式输入图书信息:\n书号 书名 作者 出版社 类别 进库量 单价");

	for (; i != 27;)//为了实现输入一次后按esc退出
	{
		printf("请输入:\n");
		scanf("%s%s%s%s%s%d%f", num, nam, aut, pub, cat, &many, &price);
		int flag = 0;
		fp = fopen("library.txt", "r+");
		for (int n = 0; !feof(fp); n++)//逐个读文件
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
			printf("该序号已存在，重新输入请按回车，结束输入请按Esc\n");
			i = getch();//暂停程序当i接收后继续下一条指令
			for (; i != 13 && i != 27;)//保证只能是CR和ESC才能退出循环,输入其他字符无用，暂停程序，按'CR'继续。
				i = getch();
			fclose(fp);
			continue;
		}

		fprintf(fp, "%-20s%-20s%-20s%-20s%-20s%-7d%-8.2f\n", num, nam, aut, pub, cat, many, price);
		fclose(fp);
		printf("继续输入请按回车，结束输入请按Esc\n");
		i = getch();//暂停程序当i接收后继续下一条指令
		for (; i != 13 && i != 27;)//保证只能是CR和ESC才能退出循环,输入其他字符无用，暂停程序，按'CR'继续。
			i = getch();
	}

	fclose(fp);
	printf("\n保存成功，按任意键返回上一层!");
	getch();
	libfunction();//返回上一层
}

void removes()//删除图书
{
	int flag = 1;//判断记录
	struct book* head = NULL;
	struct book* p, * p1 = NULL, * p2 = NULL;
	int tcount = 0, n = 0, j, k;
	float tprice = 0;
	char  tname[100] = { '\0' }, taut[100] = { '\0' }, tcat[100] = { '\0' }, tpub[100] = { '\0' }, tnum[100] = { '\0' };
	char jborrow_name[100] = { '\0' };
	char i;
	FILE* fp;
	if ((fp = fopen("library.txt", "r")) == NULL)//打开文件
	{
		system("cls");
		printf("\n记录文件不存在!按任意键返回");
		getch();
		libfunction();
	}

	else//实现删除的功能
	{
		system("cls");
		printf("\n请输入你要删除的书名:");//输入删除图书书名
		scanf("%s", jborrow_name);
		printf("\n确认删除请回车，取消请按Esc\n");
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
			if (strcmp(jborrow_name, tname))//比较名字，将不同名字的信息复制到链表
			{
				n++;//相同返回值为0不执行if语句继续循环，不同则执行直到将所有不同的书名建立成链表
				if (n == 1)//建立链表
				{
					p1 = p2 = (struct book*)malloc(LEN);
					head = p1;
				}
				else
				{
					p2->next = p1;
					p2 = p1;
					p1 = (struct book*)malloc(LEN);//新建链表
				}

				strcpy(p1->num, tnum);//复制书号
				strcpy(p1->name, tname);//复制书名
				strcpy(p1->aut, taut);//复制作者名字
				strcpy(p1->pub, tpub);//复制出版社
				strcpy(p1->cat, tcat);//复制类别
				p1->count = tcount;//复制个数
				p1->price = tprice;//复制单价
			}
		}
		if (n == 0)//如果图书只有一项且这一项刚好和要删除的相同
		{
			head = NULL;
		}
		else//建立链表的最后剩余一个储存空间，所以封底
		{
			p2->next = p1;
			p1->next = NULL;
			fclose(fp);
		}
		if (n == j)
			flag = 0;
	}

	fp = fopen("library.txt", "w");//清空文件，只写打开，然后关闭
	fclose(fp);
	fp = fopen("library.txt", "a");//追加文件
	p = head;

	for (; p != NULL;)//把链表内容覆盖到文件
	{
		fprintf(fp, "%-30s%-30s%-30s%-30s%-30s%-7d%-8.2f\n", p->num, p->name, p->aut, p->pub, p->cat, p->count, p->price);
		p = p->next;
	}
	fclose(fp);
	system("cls");
	if (flag)
		printf("\n删除成功 \n按任意键返回上一层\n");
	else
		printf("\n该书不存在，无法删除！\n");
	getch();//返回上一层
	libfunction();
}


void search()//查询图书
{
	FILE* fp;
	int k = 0, count = 0, m = 0, n = 0;
	float price = 0;
	char  name[100] = { '\0' }, aut[100] = { '\0' }, cat[100] = { '\0' }, pub[100] = { '\0' }, num[100] = { '\0' };
	char i;
	char arr[100] = { '\0' };
	if ((fp = fopen("library.txt", "r")) == NULL)//打开文件
	{
		system("cls");
		printf("\n记录文件不存在!按任意键返回");
		getch();
		libfunction();
	}
	system("cls");
	printf("请输入书号,书名,作者或类别查询：\n");
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
				printf("查询结果:\n\n");
				printf("书号\t书名\t作者\t\t出版社\t\t类别\t\t现存量\t单价\n");
			}
			printf("%-8s%-30s%-30s%-30s%-30s%-7d%-8.2f\n", num, name, aut, pub, cat, count, price);
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


void visit()//浏览图书
{
	FILE* fp;
	int n = 0;
	int k = 0, m = 0, count = 0;
	float price = 0;
	char  name[100] = { '\0' }, aut[100] = { '\0' }, cat[100] = { '\0' }, pub[100] = { '\0' }, num[100] = { '\0' };
	char i;
	if ((fp = fopen("library.txt", "r")) == NULL)//打开文件
	{
		system("cls");
		printf("\n记录文件不存在!按任意键返回");
		getch();//返回
		libfunction();
	}
	n = statistic_book();
	if (n == 0)
	{
		system("cls");
		printf("\n无任何记录!");
	}

	fp = fopen("library.txt", "r");//打开只读文件
	system("cls");
	printf("书号\t书名\t作者\t\t出版社\t\t类别\t\t库存量\t单价\n");

	for (m = 0; m < n; m++)//输出数据
	{
		fscanf(fp, "%s%s%s%s%s%d%f", num, name, aut, pub, cat, &count, &price);
		printf("%-8s%-30s%-30s%-30s%-30s%-7d%-8.2f\n", num, name, aut, pub, cat, count, price);
	}
	fclose(fp);
	printf("\n按任意键返回\n");
	getch();
	libfunction();
}



