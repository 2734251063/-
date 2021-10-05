#pragma once

#include"loadResources.h"

#define LBorder -120
#define RBorder  1024
#define UpBorder  150
#define DownBorder 450
class Role
{
	int x; //x����
	int y; //y����
	int postion;  //��ǰλ��
	int fullHP;   //Ѫ��
	int myself; //1��ʾ�Լ� 0��ʾ����
	int HP;     //����Ѫ��

public:
	//���캯��
	Role() {
		x = 50;
		y = 300;
		postion = 1;
		fullHP = 100;
		myself = 1;
		HP = 100;
	}
	~Role() {};

	//��ʼ��
	void init(int X, int Y, int pos, int fullBlood, int Myself, int blood);

	//�߽��ж���λ�øı�
	void XMove();
	void YMove();
	//λ�����ƶ��ƶ�
	void moveRight()
	{
		x += 30;
	}
	//λ�����ƶ�
	void moveLeft()
	{
		x -= 30;
	}
	//λ��
	int Pos()
	{
		return postion;
	}
	//λ������
	void Up() {
		y -= 30;
	}
	//λ������
	void Down() {
		y += 30;
	}
	//����X����
	int X() {
		return x;
	}
	int Y() {
		return y;
	}
	//�ı�x��ֵ
	void ChangeX(int value)
	{
		x = value;
	}
	//�ı�y��ֵ
	void ChangeY(int value)
	{
		y = value;
	}
	//�ı�λ��
	void ChangePos(int pos) {
		postion = pos;
	}
	//���ض���
	int Object()
	{
		return myself;
	}
	//����Ѫ��
	void changeHP(int peopleHP)
	{
		HP -= peopleHP;

	}
	//����Ѫ��
	int NowHP()
	{
		return HP;
	}
	

	//����Ѫ��
	//Ѫ��ͼ
	void showHP(int X, int Y, int xx, int yy, int dir) {

		if (dir == 1)
		{
			char HPtext[100]; //MPtext[20];
			sprintf(HPtext, "��ɫ   %d/%d", HP, fullHP);
			//sprintf(MPtext, "MP       %d/%d", MP, fullMP);
			rectangle(X, 1 + Y, 110 + xx, 20 + yy);
			//rectangle(20, 22, 116, 42);
			setfillcolor(RED);
			solidrectangle(1 + X, 2 + Y,10+HP + xx, 19 + yy);
			setbkmode(TRANSPARENT);
			outtextxy(0,3,HPtext);
			//setfillcolor(BLUE);
			//solidrectangle(21, 23, 15 + MP, 41);
			//outtextxy(0, 3, HPtext);
			//outtextxy(0, 25, MPtext);
		}

		if (dir == 0)
		{
			char HPtext_opp[100];
			sprintf(HPtext_opp, "����   %d/%d", HP, fullHP);
			rectangle(X, 30 + Y, 110 + xx, 50 + yy);
			
			setfillcolor(RED);
			solidrectangle(1 + X, 31 + Y, 10+HP + xx, 49 + yy);
			setbkmode(TRANSPARENT);
			outtextxy(0, 32, HPtext_opp);

		}

	}
};


//�߽��ж��������ƶ�λ�øı�
//x
void Role::XMove() {
	switch (postion) {
	case 0:
		if (x < LBorder) {
			x = LBorder;
			break;
		}
		moveLeft();

		break;
	case 1:
		if (x > RBorder-230) {
			x = RBorder - 230;
			break;
		}
		moveRight();
			break;
	}
}
//y
void Role::YMove() {
	switch (postion) {
	case 0:
       
		if (y > DownBorder) {
			y = DownBorder;
			break;
		}
         Down();
		break;
	case 1:
          
		if (y < UpBorder) {
			y = UpBorder;
			break;
		}
		Up();
		break;
	}
}
//��ʼ��
void Role::init(int X, int Y, int pos, int fullBlood,int Myself,int blood) {
	x = X;
	y = Y;
	postion = pos;
	fullHP = fullBlood;
	myself = Myself;
	HP = blood;
}

