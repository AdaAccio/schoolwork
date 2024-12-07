#include <stdio.h>
#include <stdlib.h>//其中包含system函数
#include <conio.h>//定义了通过控制台进行 数据输入 和数据输出的函数，如getch函数。
#include <string.h>//定义字符数组
#include <math.h>

#define LEN2 sizeof(struct land)//有关登录系统的结构体
#include "test.h"
void landingmenu()//显示登录菜单
{


	printf("\n\n\t    欢迎使用会员登录系统\n\n");
	printf("**********************************************");
	printf("\n\n\t\t1.登录系统\n\n");
	printf("\n\n\t\t2.创建账号\n\n");
	printf("\n\n\t\t3.修改密码\n\n");
	printf("\n\n\t\t4.退出系统\n\n");
	printf("\n\n\t    请按键选择，回车确定\n");
	printf("**********************************************");
	return;
}


void landingmain()//登录功能函数
{
	void land();
	void create();
	char choose;
	landingmenu();
	scanf(" %c", &choose);
	switch (choose)//功能函数
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



void create()//新建账户密码
{
	FILE* fp;
	int ID_card;
	char password[100], password1[100];
	char hit = 0;
	if ((fp = fopen("land.txt", "r")) == NULL)//if语句：打开图书馆文件，不存在此文件则新建
	{
		fp = fopen("land.txt", "w");
		fclose(fp);
	}
	system("cls");
	fp = fopen("land.txt", "a");
	for (;;)//输入两次密码确认，两次相同才能确认
	{
		printf("\n请按以下格式输入账户:\n学号 密码\n");
		printf("请输入:");
		scanf("%d %s", &ID_card, password);
		printf("再次输入密码:\n");
		scanf("%s", password1);
		if (strcmp(password, password1) == 0)
		{
			fprintf(fp, "%d %s\n", ID_card, password);
			break;
		}
		else
		{
			printf("两次输入密码不一致，继续创建按回车，退出按ESC");
			hit = getch();
			if (hit = 27)
				system("cls");
			landingmain();
		}
	}
	fclose(fp);
	printf("创建成功，按任意键返回");
	getch();
	system("cls");
	landingmain();
}



int match(int m, char a[100])//匹配数据库中的账号密码
{
	FILE* fp;
	int n = 0, i = 0;
	int ID_card;
	char password[100];

	if ((fp = fopen("land.txt", "r")) == NULL)//不存在读者文件
	{
		system("cls");
		printf("\n 还未存在用户!请新建账户");
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

void land()//输入账户密码的登录函数
{
	int ID_card;
	char password[100];
	int i = 2, j, k, n;
	char hit = 0;
	system("cls");
	do
	{
		printf("\n请输入账号:\n");
		scanf("%d", &ID_card);
		printf("确认输入请安回车，重新输入请按ECS");
		hit = getch();//暂停程序当i接收后继续下一条指令
		for (; hit != 13 && hit != 27;)//保证只能是CR和ESC才能退出循环,输入其他字符无用，暂停程序，按'CR'继续。
		{
			hit = getch();
		}
	} while (hit == 27);
	printf("\n请输入密码:\n");
	scanf("%s", password);
	i = match(ID_card, password);
	if (i == 1)
	{
		printf("登陆成功!按任意键继续");
		getch();
		mainfunction();
	}
	else
	{
		if (i == -1)
		{
			printf("密码错误!");
			getch();
			land();
		}
		if (i == 0)
			printf("不存在此用户");
		getch();
		system("cls");
		landingmain();
	}
}

void alter(int z, char m[100])//修改函数
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
		if (z != ID_card1)//比较名字，将不同名字的信息复制到链表
		{
			n++;//相同返回值为0不执行if语句继续循环，不同则执行直到将所有不同的书名建立成链表
			if (n == 1)//建立链表
			{
				p1 = p2 = (struct land*)malloc(LEN2);
				head = p1;
			}
			else
			{
				p2->next = p1;
				p2 = p1;
				p1 = (struct land*)malloc(LEN2);//新建链表
			}
			p1->ID_card = ID_card1;
			strcpy(p1->password, mima1);//复制账号密码
		}
	}
	if (n == 0)
	{
		head = NULL;
	}
	else//建立链表的最后剩余一个储存空间，所以封底
	{
		p2->next = p1;
		p1->next = NULL;
		fclose(fp);
	}
	fp = fopen("land.txt", "w");//清空文件，只写打开，然后关闭
	fclose(fp);
	fp = fopen("land.txt", "a");//追加文件
	p = head;
	for (; p != NULL;)//把链表内容覆盖到文件
	{
		fprintf(fp, "%d %s%\n", p->ID_card, p->password);
		p = p->next;
	}
	fprintf(fp, "%d %s\n", z, m);
	fclose(fp);
	system("cls");

}



void altercode()//修改密码
{

	FILE* fp;
	int zh = 0, k = 0, count = 0, m = 0, n = 0;
	int chazhao, hit;
	char mima[100] = { '\0' }, password1[100] = { '\0' };
	char  mm[100] = { '\0' };
	char i;

	if ((fp = fopen("land.txt", "r")) == NULL)//打开文件
	{
		system("cls");
		printf("\n记录文件不存在!按任意键返回");
		getch();
		system("cls");
		landingmain();
	}
	system("cls");
	printf("请输入你的帐号和旧密码：\n");
	scanf("%d %s", &chazhao, mima);
	m = statistic_book3();
	for (n = 0; n <= m; n++)
	{
		fscanf(fp, "%d %s", &zh, mm);
		if (zh == chazhao)
		{
			if (!strcmp(mm, mima))
			{
				printf("请输入新的密码");
				scanf("%s", mima);
				printf("再次输入密码:\n");
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
					printf("两次输入密码不一致,按任意键退出");
					hit = getch();
					system("cls");
					landingmain();

				}
			}
			else
			{
				printf("旧密码错误，按任意键返回！");
				getch();
				system("cls");
				landingmain();

			}

		}
	}
	printf("不存在此账号，按任意键返回");
	fclose(fp);//修改结束
	getch();
	system("cls");
	landingmain();
}
