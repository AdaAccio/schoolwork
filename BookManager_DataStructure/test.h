#ifndef TEST_H_INCLUDED
#define TEST_H_INCLUDED


#define LEN sizeof(struct book)//�й�ͼ����Ϣ�Ľṹ��
#define LEN1 sizeof(struct reader)//�йض�����Ϣ�Ľṹ��
#define LEN2 sizeof(struct land)//�йص�¼ϵͳ�Ľṹ��


struct book//ͼ����Ϣ
{
	char num[100], name[100], aut[100], pub[100], cat[100];     //pub-������     cat-Ŀ¼
	int  count;
	float price;
	struct book* next;
};

struct reader//���߽�����Ϣ
{
	int ID_card;
	char borrow_name[100], time[100], return_name[100];
	struct reader* next;
};
struct land//��¼��Ϣ
{
	int ID_card;
	char password[100];
	struct land* next;
};

int statistic_book();//ͳ��library�ı���������
void alter(int, char[]);  //�޸ĺ���
void mainmenu();//��ʾ���˵�
void bookmenu();//��ʾͼ����Ϣ�˵�
void borrowmenu();//��ʾ������Ϣ�˵�
void landingmenu();//��ʾ��¼�˵�

void mainfunction();// ���˵�����
void libfunction();//ͼ��˵�����
void search();//��ѯͼ��
void adds();//����ͼ��
void removes();//ɾ��ͼ��
void visit();//���ͼ��

void borrow_message();//���߽�����Ϣ
void borrow();//����
void returnbook();//����
void inquire();//��ѯ����
void visit_borrow();// ����������
void vague();

void land();//��¼����ϵͳ
void create();//�����˺�����
void altercode();//�޸�����
void landingmain();//��¼���溯��
void change();//�޸�ͼ����Ϣ
#endif // TEST_H_INCLUDED
#pragma once
