#ifndef TEST_H_INCLUDED
#define TEST_H_INCLUDED


#define LEN sizeof(struct book)//有关图书信息的结构体
#define LEN1 sizeof(struct reader)//有关读者信息的结构体
#define LEN2 sizeof(struct land)//有关登录系统的结构体


struct book//图书信息
{
	char num[100], name[100], aut[100], pub[100], cat[100];     //pub-出版社     cat-目录
	int  count;
	float price;
	struct book* next;
};

struct reader//读者借阅信息
{
	int ID_card;
	char borrow_name[100], time[100], return_name[100];
	struct reader* next;
};
struct land//登录信息
{
	int ID_card;
	char password[100];
	struct land* next;
};

int statistic_book();//统计library文本个数函数
void alter(int, char[]);  //修改函数
void mainmenu();//显示主菜单
void bookmenu();//显示图书信息菜单
void borrowmenu();//显示借阅信息菜单
void landingmenu();//显示登录菜单

void mainfunction();// 主菜单功能
void libfunction();//图书菜单功能
void search();//查询图书
void adds();//增加图书
void removes();//删除图书
void visit();//浏览图书

void borrow_message();//读者借阅信息
void borrow();//借书
void returnbook();//还书
void inquire();//查询借书
void visit_borrow();// 浏览借书情况
void vague();

void land();//登录功能系统
void create();//创建账号密码
void altercode();//修改密码
void landingmain();//登录界面函数
void change();//修改图书信息
#endif // TEST_H_INCLUDED
#pragma once
