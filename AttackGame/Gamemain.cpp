/*
�����ߣ�������
��Ŀ���ܣ���Ϸ

*/

#include<conio.h>
#include<iostream>
#include<stdio.h>
#include<time.h>
#include<graphics.h>       //ͼ�ο��ļ�
#include<mmsystem.h>
#include"Role.h"
#include"loadResources.h"
#pragma comment(lib,"Winmm.lib")   //�������ֵ�api


//����Ϸ����
void ShowUI();
//����Ϸ����
//��������
void keyDown();

//��������
void opp_Follow();
//AI����
void AI();
//���ݱ���
void SaveData();   //0���� 1��ʾ�Լ�
//���ݶ�ȡ
void ReadData();

//�ж��Ƿ���ʤ��
void Win();

int state = 0;  //����״̬
int state_opp = 0;  //�����������һ��״̬
int isRelease = 0;  //�Ƿ�ż���


//�������ﲢ��ʼ��
Role role;
//����з�����
Role opponent;




//��ʼ����
void startUI() {
	MOUSEMSG Msg;
	ReadData();
	FlushMouseMsgBuffer();
   //������Դ
    putimage(0, 0, &START[0]);
	putimage(415, 333, &START[1]);
	putimage(415, 400, &START[2]);

	EndBatchDraw();
	//��������
	mciSendString("open resources\\Music\\bkmusic.mp3 alias myMusic",NULL,0,NULL);
	mciSendString("play myMusic repeat", NULL, 0, NULL);
     //�����
	while (1) {
		
		 if(MouseHit()){
         Msg = GetMouseMsg();
		if (Msg.x >= 415 && Msg.x <= 415 + 160 && Msg.y >= 333 && Msg.y <= 333 + 44) {
			putimage(415, 333, &BUTTON[0]);
			Sleep(10);
			if (WM_LBUTTONDOWN == Msg.uMsg) {
				//mciSendString("stop myMusic",NULL,NULL,NULL);
				cleardevice();
				putimage(0, 0, &BKGRD);
				break;
			}
		}
		if (Msg.x >= 415 && Msg.x <= 415 + 160 && Msg.y >= 400 && Msg.y <= 400 + 44) {
			putimage(415, 400, &BUTTON[1]);
			Sleep(10);
			if (WM_LBUTTONDOWN == Msg.uMsg) {
				exit(0);
			}
			else
			putimage(415, 333, &START[1]);
			putimage(415, 400, &START[2]);
		}
		}
	}
}



//����Ϸ����
void ShowUI() {
	cleardevice();
	BeginBatchDraw();
	putimage(0, 0, &BKGRD);
	//�Լ�
	putimage(role.X(), role.Y(), 400, 300, &StandY[role.Pos()], 0, 0, SRCAND);
	putimage(role.X(), role.Y(), 400, 300, &Stand[role.Pos()], 0, 0, SRCPAINT);

	//����
	putimage(opponent.X(), opponent.Y(), 400, 300, &StandY_opp[opponent.Pos()], 0, 0, SRCAND);
	putimage(opponent.X(), opponent.Y(), 400, 300, &Stand_opp[opponent.Pos()], 0, 0, SRCPAINT);

	//Ѫ��
	role.showHP(0, 0, 0, 0, 1);
	opponent.showHP(0, 0, 0, 0, 0);
	EndBatchDraw();
	Sleep(50);
}



//��������
void keyDown()
{
	
	//�ж��Ƿ��¼���
	if (kbhit()) {
		if (GetAsyncKeyState('A') || GetAsyncKeyState('a'))   //������Ӧ�ļ�����ִ��
		{
		//���ƶ� 0
			isRelease = 1;
			role.ChangePos(0);
			state = 1;
			role.XMove();
		}
		//���ƶ� 1
		if (GetAsyncKeyState('D') || GetAsyncKeyState('d'))
		{
			isRelease = 1;
			role.ChangePos(1);
			state = 1;
			role.XMove();
		}
			//���ƶ�
		if (GetAsyncKeyState('W') || GetAsyncKeyState('w'))
		{
			isRelease = 1;
			role.ChangePos(1);
			role.YMove();
			
			state = 1;	
		}
			//���ƶ�
		if (GetAsyncKeyState('S') || GetAsyncKeyState('s'))
		{
			isRelease = 1;
			role.ChangePos(0);
			role.YMove();
			state = 1;
		}
			//��Ծ
		if (GetAsyncKeyState('J') || GetAsyncKeyState('j'))
		{
			isRelease = 1;
			state = 2;
			
		}
			//����cut
		if (GetAsyncKeyState('K') || GetAsyncKeyState('k'))
		{
			isRelease = 1;
			state = 3;	
			
		}
			//����
		if (GetAsyncKeyState('U') || GetAsyncKeyState('u'))
		{
			isRelease = 1;
			state = 4;

		}
		
	}
	
}
//�����ͷ�
	void killRelease()
{
		if (isRelease)
		{
			switch (state)
			{
				//վ��
			case 0:
			{
				BeginBatchDraw();
				putimage(role.X(), role.Y(), 400, 300, &StandY[role.Pos()], 0, 0, SRCAND);
				putimage(role.X(), role.Y(), 400, 300, &Stand[role.Pos()], 0, 0, SRCPAINT);
				//����
				putimage(opponent.X(), opponent.Y(), 400, 300, &StandY_opp[opponent.Pos()], 0, 0, SRCAND);
				putimage(opponent.X(), opponent.Y(), 400, 300, &Stand_opp[opponent.Pos()], 0, 0, SRCPAINT);
				//Ѫ��
				role.showHP(0, 0, 0, 0, 1);
				opponent.showHP(0, 0, 0, 0, 0);
				EndBatchDraw();
				break;
			}
			//����
			case 1:
			{

				for (int i = 0; i < 8; i++) {
					BeginBatchDraw();
					putimage(0, 0, &BKGRD);
					//����
					putimage(opponent.X(), opponent.Y(), 400, 300, &StandY_opp[opponent.Pos()], 0, 0, SRCAND);
					putimage(opponent.X(), opponent.Y(), 400, 300, &Stand_opp[opponent.Pos()], 0, 0, SRCPAINT);
					//�Լ�
					putimage(role.X(), role.Y(), 400, 300, &MoveY[role.Pos()], 400 * i, 0, SRCAND);
					putimage(role.X(), role.Y(), 400, 300, &Move[role.Pos()], 400 * i, 0, SRCPAINT);
					//Ѫ��
					role.showHP(0, 0, 0, 0, 1);
					opponent.showHP(0, 0, 0, 0, 0);
					EndBatchDraw();
					Sleep(50);
				}
				break;
			}
			//��
			case 2:
			{

				for (int i = 0; i < 8; i++) {
					BeginBatchDraw();
					putimage(0, 0, &BKGRD);
					//����
					putimage(opponent.X(), opponent.Y(), 400, 300, &StandY_opp[opponent.Pos()], 0, 0, SRCAND);
					putimage(opponent.X(), opponent.Y(), 400, 300, &Stand_opp[opponent.Pos()], 0, 0, SRCPAINT);
					//�Լ�
					putimage(role.X(), role.Y(), 400, 300, &JumpY[role.Pos()], 400 * i, 0, SRCAND);
					putimage(role.X(), role.Y(), 400, 300, &Jump[role.Pos()], 400 * i, 0, SRCPAINT);
					//Ѫ��
					role.showHP(0, 0, 0, 0, 1);
					opponent.showHP(0, 0, 0, 0, 0);
					EndBatchDraw();
					Sleep(50);
				}

				break;
			}
			//��
			case 3:
			{

				mciSendString("open resources\\Music\\cut.wav alias music", 0, 0, 0);
				mciSendString("play music from 0", 0, 0, 0);
				for (int i = 0; i < 7; i++) {
					BeginBatchDraw();
					putimage(0, 0, &BKGRD);
					//����
					putimage(opponent.X(), opponent.Y(), 400, 300, &StandY_opp[opponent.Pos()], 0, 0, SRCAND);
					putimage(opponent.X(), opponent.Y(), 400, 300, &Stand_opp[opponent.Pos()], 0, 0, SRCPAINT);
					//�Լ�
					putimage(role.X(), role.Y(), 400, 300, &RoleCutY[role.Pos()], 400 * i, 0, SRCAND);
					putimage(role.X(), role.Y(), 400, 300, &RoleCut[role.Pos()], 400 * i, 0, SRCPAINT);
					//Ѫ��
					role.showHP(0, 0, 0, 0, 1);
					opponent.showHP(0, 0, 0, 0, 0);
					EndBatchDraw();
					Sleep(50);
				}

				break;
			}
			//����
			case 4:
			{

				//��������
				mciSendString("open resources\\Music\\cut1.wav alias music", 0, 0, 0);
				mciSendString("play music from 0", 0, 0, 0);
				for (int i = 0; i < 6; i++) {
					BeginBatchDraw();
					putimage(0, 0, &BKGRD);
					//����
					putimage(opponent.X(), opponent.Y(), 400, 300, &StandY_opp[opponent.Pos()], 0, 0, SRCAND);
					putimage(opponent.X(), opponent.Y(), 400, 300, &Stand_opp[opponent.Pos()], 0, 0, SRCPAINT);
					//�Լ�
					putimage(role.X(), role.Y(), 400, 300, &JumpCutY[role.Pos()], 400 * i, 0, SRCAND);
					putimage(role.X(), role.Y(), 400, 300, &JumpCut[role.Pos()], 400 * i, 0, SRCPAINT);
					//Ѫ��
					role.showHP(0, 0, 0, 0, 1);
					opponent.showHP(0, 0, 0, 0, 0);
					EndBatchDraw();
					Sleep(50);
				}
				opponent.changeHP(10);
				//���漼��
				for (int i = 0; i < dgSkillFrames; i++) {
					BeginBatchDraw();
					putimage(opponent.X() + 100, opponent.Y(), &dragonSkillY[i], SRCAND);
					putimage(opponent.X() + 100, opponent.Y(), &dragonSkill[i], SRCPAINT);
					
					//Ѫ��
					role.showHP(0, 0, 0, 0, 1);
					opponent.showHP(0, 0, 0, 0, 0);
					EndBatchDraw();
					Sleep(20);
				}
				break;

			}
			
			}
          isRelease = 0;
		}

 }


//��������
	void opp_Follow()
	{
		
		switch (state_opp)
		{
			//վ��
		case 0:
		{
			BeginBatchDraw();
			//�Լ�
			putimage(role.X(), 300, 400, 300, &StandY[role.Pos()], 0, 0, SRCAND);
			putimage(role.X(), 300, 400, 300, &Stand[role.Pos()], 0, 0, SRCPAINT);
			//����
			putimage(600, opponent.Y(), 400, 300, &StandY_opp[opponent.Pos()], 0, 0, SRCAND);
			putimage(600, opponent.Y(), 400, 300, &Stand_opp[opponent.Pos()], 0, 0, SRCPAINT);
			//Ѫ��
			role.showHP(0, 0, 0, 0, 1);
			opponent.showHP(0, 0, 0, 0, 0);
			EndBatchDraw();
			break;
		}
		//����
		case 1:
		{

			for (int i = 0; i < 8; i++) {
				BeginBatchDraw();
				putimage(0, 0, &BKGRD);
				//�Լ�
				putimage(role.X(), role.Y(), 400, 300, &StandY[role.Pos()], 0, 0, SRCAND);
				putimage(role.X(), role.Y(), 400, 300, &Stand[role.Pos()], 0, 0, SRCPAINT);
				//����
				putimage(opponent.X(), opponent.Y(), 400, 300, &MoveY_opp[opponent.Pos()], 400 * i, 0, SRCAND);
				putimage(opponent.X(), opponent.Y(), 400, 300, &Move_opp[opponent.Pos()], 400 * i, 0, SRCPAINT);
				//Ѫ��
				role.showHP(0, 0, 0, 0, 1);
				opponent.showHP(0, 0, 0, 0, 0);
				EndBatchDraw();
				Sleep(50);

			}

			break;
		
		}
		//��
		case 2:
		{
			BeginBatchDraw();
			for (int i = 0; i < 8; i++) {
				putimage(0, 0, &BKGRD);
				//�Լ�
				putimage(role.X(), role.Y(), 400, 300, &StandY[role.Pos()], 0, 0, SRCAND);
				putimage(role.X(), role.Y(), 400, 300, &Stand[role.Pos()], 0, 0, SRCPAINT);
				//����
				putimage(opponent.X(), opponent.Y(), 400, 300, &JumpY_opp[opponent.Pos()], 400 * i, 0, SRCAND);
				putimage(opponent.X(), opponent.Y(), 400, 300, &Jump_opp[opponent.Pos()], 400 * i, 0, SRCPAINT);
				//Ѫ��
				role.showHP(0, 0, 0, 0, 1);
				opponent.showHP(0, 0, 0, 0, 0);
				EndBatchDraw();
			 Sleep(50);
               
			}
			
			break;
		}
		//��
		case 3:
		{
			
			mciSendString("open resources\\Music\\cut.wav alias music", 0, 0, 0);
			mciSendString("play music from 0", 0, 0, 0);
			role.changeHP(3);
			for (int i = 0; i < 7; i++) {
               BeginBatchDraw();
				putimage(0, 0, &BKGRD);
				//�Լ�
				putimage(role.X(), role.Y(), 400, 300, &StandY[role.Pos()], 0, 0, SRCAND);
				putimage(role.X(), role.Y(), 400, 300, &Stand[role.Pos()], 0, 0, SRCPAINT);
				//����
				putimage(opponent.X(), opponent.Y(), 400, 300, &RoleCutY_opp[opponent.Pos()], 400 * i, 0, SRCAND);
				putimage(opponent.X(), opponent.Y(), 400, 300, &RoleCut_opp[opponent.Pos()], 400 * i, 0, SRCPAINT);
				//Ѫ��
				role.showHP(0, 0, 0, 0, 1);
				opponent.showHP(0, 0, 0, 0, 0);
                EndBatchDraw();
				Sleep(50);
			}
			
			break;
		}
		//����
		case 4:
		{
			
			//��������
			mciSendString("open resources\\Music\\rain.wav alias music", 0, 0, 0);
			mciSendString("play music from 0", 0, 0, 0);
			for (int i = 0; i < 6; i++) {
              BeginBatchDraw();
				putimage(0, 0, &BKGRD);
				//�Լ�
				putimage(role.X(), role.Y(), 400, 300, &StandY[role.Pos()], 0, 0, SRCAND);
				putimage(role.X(), role.Y(), 400, 300, &Stand[role.Pos()], 0, 0, SRCPAINT);
				//����
				putimage(opponent.X(), opponent.Y(), 400, 300, &JumpCutY_opp[opponent.Pos()], 400 * i, 0, SRCAND);
				putimage(opponent.X(), opponent.Y(), 400, 300, &JumpCut_opp[opponent.Pos()], 400 * i, 0, SRCPAINT);
				//Ѫ��
				role.showHP(0, 0, 0, 0, 1);
				opponent.showHP(0, 0, 0, 0, 0);
                 EndBatchDraw();
				Sleep(50);
			}
			
			//���漼��
			if (opponent.Pos() == 1)
			{
				
				for (int i = 0; i < frameRain; i++) {
                     BeginBatchDraw();
					//putimage(opponent.X() + 200, opponent.Y(), &rainSkillY[i], SRCAND);
					putimage(role.X(), role.Y()-150, &rainSkill[i], SRCPAINT);
					//Ѫ��
					role.showHP(0, 0, 0, 0, 1);
					opponent.showHP(0, 0, 0, 0, 0);
					EndBatchDraw();
					Sleep(50);
				}
			}
			else
				{
				
					for (int i = 0; i < frameRain; i++) {
                     BeginBatchDraw();
						//putimage(opponent.X() - 200, opponent.Y(), &rainSkillY[i], SRCAND);
						putimage(role.X(), role.Y()-150, &rainSkill[i], SRCPAINT);
						//Ѫ��
						role.showHP(0, 0, 0, 0,1);
						opponent.showHP(0, 0, 0, 0,0);
                      EndBatchDraw();
					  Sleep(50);
					}
					
				}
				
			}
			break;
		
		}

		state_opp = 0;
	}
	//AI����
	void AI()
	{
		if ((role.X() - opponent.X()) >= 30 || (role.X() - opponent.X()) <= -30)
		{
			state_opp = 1;
			opponent.XMove();

		}
		
		else
		{
			state_opp = 3 + rand() % 6;
			role.changeHP(5);
		}
			

	}
	//���ݱ���
void SaveData()   //0���� 1��ʾ�Լ�
	{
	int HP = role.NowHP();
	int opp_HP = opponent.NowHP();
	FILE *fp_role;
	FILE*fp_opp;
	
	
	fp_role = fopen("Data\\RoleData.dat", "w+");
	 fp_opp =fopen("Data\\oppData.dat", "w+");
	 
	fprintf(fp_role,"%d",HP);	
			
	fprintf(fp_opp,"%d",opp_HP);
	fclose(fp_role);
	fclose(fp_opp);
	}


void ReadData() {

	FILE *fp_role, *fp_opp;
	int HP = role.NowHP();
	int opp_HP = opponent.NowHP();
	if ((fp_role = fopen("Data\\RoleData.dat", "rb")) == NULL)
	{
		MessageBox(NULL, _T("�ļ������ڣ��������¿�ʼ..."), _T("����ļ�"),MB_OK);
	}
	if ((fp_opp = fopen("Data\\oppData.dat", "rb+")) == NULL)
	{
		MessageBox(NULL, _T("�ļ������ڣ��������¿�ʼ..."), _T("����ļ�"), MB_OK);
	}

	fscanf(fp_role, "%d",&HP);

	fscanf(fp_opp, "%d",&opp_HP);
	fclose(fp_role);
	fclose(fp_opp);
		

	}

//�ж��Ƿ���ʤ��
void Win()
{
	if (opponent.NowHP() <= 0)
	{
		putimage(300, 200, &Victory);
		Sleep(500);
		MessageBox(NULL, _T("��Ϸ�����¿�ʼ..."), _T("ʤ��"), MB_OK);
		opponent.init(600, role.Y(), 0, 100, 0, 100);
		role.init(50,300,1,100,1,100);
		startUI();
		
	}
	if (role.NowHP() <= 0) {

		putimage(300, 200, &Fail);
		Sleep(500);
		MessageBox(NULL, _T("��Ϸ�����¿�ʼ..."), _T("ʧ��"), MB_OK);
		opponent.init(600, role.Y(), 0, 100, 0, 100);
		role.init(50, 300, 1, 100, 1, 100);
		startUI();
	}

}
int main(int argv, char*argc[])
{
	
	//���������
	srand((unsigned)time(NULL));
    //��������
	initgraph(WIDTH, HEIGHT);  //NOCLOSE���ܹرմ���
	loadResources();
    //�з������ʼ��
    opponent.init(600,role.Y(),0,100,0,100);
	//��ʼ����
	startUI();
	
	while (1) {
		//1 ��ʾ����������
		  ShowUI();
		//2 �������¸ı�����λ����Ϣ
		  keyDown();
		  killRelease();
		  AI();
		  opp_Follow();
		//3 ������ʾ������Ϣ
		  SaveData();
		  Win();
		
	}
	closegraph();
	return 0;
}
