#include <stdio.h>
#include <stdlib.h>//其中包含system函数
#include <conio.h>//定义了通过控制台进行 数据输入 和数据输出的函数，如getch函数。
#include <string.h>//定义字符数组
#include <math.h>
#define LEN sizeof(struct book)//有关图书信息的结构体
#define LEN1 sizeof(struct reader)//有关读者信息的结构体
#define LEN2 sizeof(struct land)//有关登录系统的结构体
#pragma warning(disable:4996);
#include <assert.h>

#include "test.h"


void mainmenu()//主菜单
{
	system("cls");

	printf("**************************************************");

	printf("\n\n 1.图书系统\n\n");

	printf("\n\n 2.借阅系统\n\n");

	printf("\n\n 3.退出系统\n\n");

	printf("\n\n 请按键选择，回车确定\n");

	printf("*************************************************\n");

	return;
}


void bookmenu() //图书馆信息菜单
{
	system("cls");

	printf("****************************************************");

	printf("\n 1.增加图书\n\n");

	printf("\n 2.删除图书\n\n");

	printf("\n 3.查询图书\n\n");

	printf("\n 4.库存浏览\n\n");

	printf("\n 5.模糊查询\n\n");

	printf("\n 6.返回上一层\n\n");

	printf("\n 请按键选择，回车确定\n");

	printf("***************************************************\n");

	return;

}


void mainfunction()
{
	void borrow_message();
	char choose;
	mainmenu();
	scanf(" %c", &choose);
	switch (choose)//功能函数
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

