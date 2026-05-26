#include<bits/stdc++.h>
#include <windows.h>
#include <conio.h>
#include<time.h>//Sleep函数 
#include <unistd.h>//获取文件地址 
#define ll long long
#define random(x) (rand()%x)//随机数 
#include <thread>//多线程
#define _CRT_SECURE_NO_WARNINGS//播放音乐 
#pragma comment(lib,"winmm.lib")//播放音乐 
#include<mmsystem.h>//播放音乐 
#include "operate1.h"//多文件 
#include "operate2.h"//多文件 
#include "Data.h"//多文件 
#include "mainx.h"//多文件 
using namespace std;
Data A; 
Operate1 Use1;
Operate2 Use2;
MAIN E;

ll read()//快读(数字)(收起)
{
	ll x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
void PlayMusicx()
{
	while(true){
		
		char Placeelse[30]={'\\','B','G','M','\\',' ','.','m','p','3',' ','a','l','i','a','s',' ','s','1','o','p','e','n',' '};
		char GetPlace[256]="",GetPlacex[256]="";
		getcwd(GetPlace,256);//获取当前地址 
		Placeelse[5]=random(1)+'1';//目前有 1 首歌，随机选一首 
		int LP=strlen(GetPlace);
		for(int i=0;i<=18;i++)GetPlace[i+LP]=Placeelse[i]; 
		for(int i=19;i<=23;i++)GetPlacex[i-19]+=Placeelse[i];
		LP=strlen(GetPlace);
		for(int i=0;i<LP;i++)GetPlacex[i+5]+=GetPlace[i];
		
		mciSendString(TEXT(GetPlacex),NULL,0,NULL);
		mciSendString(TEXT("play s1"),NULL,0,NULL);
		Sleep(126000);//听歌时长 
		mciSendString(TEXT("close s1"),NULL,0,NULL);
	}
}
void MAIN::Slowx()//加载动画(收起)
{
	HANDLE hout=GetStdHandle(STD_OUTPUT_HANDLE);
	cout<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<"                                    ";
	Use1.LowPrint("我们最终会相知 ");
	Sleep(300);
	Use1.LowPrint("在那遥远的苍穹");
	Sleep(200);
	system("cls");
	for(int i=2;i<=100;i+=2)
	{	
		cout<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<"                                    ";
		Use1.Print("我们最终会相知 在那遥远的苍穹");
		cout<<endl<<endl<<endl;
		SetConsoleTextAttribute(hout,7);
		cout<<"                游戏加载中 "; 
		int nowspace=(i/2);
		for(int j=1;j<=i/2;j++)cout<<"▉";
		if(i&1)cout<<"▏",nowspace++;
		if(i<=9)for(int j=1;j<=55-nowspace;j++)cout<<" ";
		else if(i!=100)for(int j=1;j<=54-nowspace;j++)cout<<" ";
		else for(int j=1;j<=53-nowspace;j++)cout<<" ";
		cout<<i<<"%"; //cout<<nowspace<<endl;system("pause");
		if(i!=100)Sleep(1);
		else Sleep(100);
		system("cls");
	}
}

void MAIN::Died()//死亡效果(收起)
{
	HANDLE hout=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hout,4);
	system("cls");
	Use1.Print("你死了");
	Sleep(1000);
	SetConsoleTextAttribute(hout,7);
	exit(0);
}

void MAIN::kongbai(int op,int now)//地图:[空白](收起)
{
	Use2.Place(op);
	for(int i=1;i<=19;i++)cout<<endl;
	cout<<"_______________________\n\n";
} 

void MAIN::Mapx_kongbai(int op1,int op2)//地图+对话框 [op1:地点，op2:地图](收起)
{
	system("cls");
	HANDLE hout=GetStdHandle(STD_OUTPUT_HANDLE);
	if(op2==0)kongbai(op1,op2);
	if(op2==1)Use2.toMap(op1);
	SetConsoleTextAttribute(hout,7);
}

void MAIN::First(int op)//第一天(收起)
{
	A.Map_Find[0]=A.Map_Find[1]=1;
	HANDLE hout=GetStdHandle(STD_OUTPUT_HANDLE);
	if(op)Slowx();A.dx=15,A.dy1=13,A.dy2=14;
	for(int j=1;j<=13;j++)cout<<endl;
	printf("                                          ");Use1.LowPrint("一切的伊始");
	Sleep(2000);
	SetConsoleTextAttribute(hout,7);
	system("cls");
	Mapx_kongbai(1,0);	
	cout<<"我：";SetConsoleTextAttribute(hout,3);
	Use1.LowPrint("真是奇怪的梦呢！");SetConsoleTextAttribute(hout,7);cout<<endl;
	system("pause");
	Mapx_kongbai(1,0);
	cout<<"我：";SetConsoleTextAttribute(hout,3);
	Use1.LowPrint("现在太黑了，我需要开灯");SetConsoleTextAttribute(hout,7);
	cout<<endl<<"是否开灯(1 for yes):";char chx;chx=getchar();
	system("cls");
	if(chx!='1')
	{
		Mapx_kongbai(1,0);	
		SetConsoleTextAttribute(hout,3);
		Use1.LowPrint("一团轻烟笼罩了你，在黑暗与迷茫中，你逐渐死去...");
		Sleep(2000);
		Died(); 
	}
	Mapx_kongbai(1,0);SetConsoleTextAttribute(hout,3);
	Use1.LowPrint("灯逐渐亮了\n");SetConsoleTextAttribute(hout,7);
	system("pause");
	Mapx_kongbai(1,1); 
	SetConsoleTextAttribute(hout,3);
	Use1.LowPrint("通过WSAD移动");
} 

void MAIN::Openy()//(收起)
{
	HANDLE hout=GetStdHandle(STD_OUTPUT_HANDLE);	
	for(int i=1;i<=10;i++)cout<<endl;
	cout<<"                                   ";
	SetConsoleTextAttribute(hout,6);Use1.Print("神域");
	cout<<endl<<"                                       ";
	SetConsoleTextAttribute(hout,2);Use1.Print("の");
	SetConsoleTextAttribute(hout,12);Use1.Print("大冒险");
	Sleep(500);system("cls");
	for(int i=1;i<=10;i++)cout<<endl;
	cout<<"                                   ";
	SetConsoleTextAttribute(hout,6);Use1.Print("神域");
	SetConsoleTextAttribute(hout,2);Use1.Print("の");
	SetConsoleTextAttribute(hout,12);Use1.Print("大冒险");
	Sleep(200);system("cls");
	for(int i=1;i<=9;i++)cout<<endl;
	cout<<"                                   ";
	SetConsoleTextAttribute(hout,6);Use1.Print("神域");
	cout<<endl<<"                                       ";
	SetConsoleTextAttribute(hout,2);Use1.Print("の");
	SetConsoleTextAttribute(hout,12);Use1.Print("大冒险");
	Sleep(500);system("cls");
	for(int i=1;i<=9;i++)cout<<endl;
	cout<<"                                   ";
	SetConsoleTextAttribute(hout,6);Use1.Print("神域");
	SetConsoleTextAttribute(hout,2);Use1.Print("の");
	SetConsoleTextAttribute(hout,12);Use1.Print("大冒险");
	Sleep(300);
	for(int i=1;i<=6;i++)
		putchar('\b'),putchar('\b'),putchar(' '),putchar(' '),putchar('\b'),putchar('\b'),Sleep(100);
	system("cls");
	for(int i=1;i<=6;i++)cout<<endl;
	cout<<"                                   ";
	SetConsoleTextAttribute(hout,6);Use1.LowPrint("神域");
	SetConsoleTextAttribute(hout,2);Use1.LowPrint("の");
	SetConsoleTextAttribute(hout,12);Use1.LowPrint("大冒险");
	cout<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<"                            ";
	Sleep(1000);SetConsoleTextAttribute(hout,7);
	Use1.LowPrint("谨此，");Sleep(500);
	Use1.LowPrint("纪");Sleep(75);
	Use1.LowPrint("念");Sleep(75);
	Use1.LowPrint("那");Sleep(75);
	Use1.LowPrint("些");Sleep(75);
	Use1.LowPrint("即");Sleep(75);
	Use1.LowPrint("被");Sleep(75);
	Use1.LowPrint("遗");Sleep(75);
	Use1.LowPrint("忘");Sleep(75);
	Use1.LowPrint("的");Sleep(75);
	Use1.LowPrint("岁");Sleep(75);
	Use1.LowPrint("月");Sleep(75);
	Sleep(1000);
	for(int i=1;i<=14;i++)putchar('\b'),putchar('\b'),putchar(' '),putchar(' '),putchar('\b'),putchar('\b'),Sleep(75);
}

void MAIN::jieshaogame(int op)//介绍游戏
{
	system("cls");	
	Use1.LowPrint("背景制作：月雩");cout<<endl<<endl;
	Use1.LowPrint("剧情：月雩");cout<<endl<<endl;
	Use1.LowPrint("游戏开发：月雩");cout<<endl<<endl;
	Use1.LowPrint("B站账号：月雩薇嫭");cout<<endl<<endl;
	Use1.LowPrint("广告：prayyueyu.github.io");cout<<endl<<endl;
	Use1.LowPrint("联系方式：1944215344（QQ）");cout<<endl<<endl; 
	system("pause");
	system("cls");
	Use1.LowPrint("本游戏由月雩一人开发制作，历经无数岁月终得以问世，喜欢的话请多多支持哦~");
	cout<<endl<<endl;
	if(A.youxibeijingshifou==1)
	{
		Use1.LowPrint("是否进入游戏背景介绍？（1 for yes）");
		int qwerfghj=0;
		cin>>qwerfghj;
		if(qwerfghj==1)
		{
			/*
				此处为游戏背景 
			*/
			system("cls");
			Use1.LowPrint("游戏背景开发中~");
			cout<<endl<<endl;
			system("pause");
			OpEnx(1,op);
		}
		else cout<<endl<<endl;	
	}
	else {Use1.LowPrint("(快去游戏里寻找解锁游戏背景的方法吧~)");cout<<endl<<endl;} 
	system("pause");
	system("cls");
	OpEnx(1,op);
} 

void MAIN::OpEnx(int SkipFlag,int op)//开始界面(标题)(收起)
{
	HANDLE hout=GetStdHandle(STD_OUTPUT_HANDLE);
	if(!SkipFlag){
		SetConsoleTextAttribute(hout,6);
		cout<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl;	
		cout<<"                                   ";	
		cout<<"神";Sleep(180); 	
		cout<<"域";Sleep(180); 	
		system("cls");	
		for(int i=5;i<=12;i++)
		{		
			if(i!=12)
			{			
				SetConsoleTextAttribute(hout,2);	
				for(int j=1;j<=i-1;j++)cout<<endl;		
				cout<<"                                       の";			
				SetConsoleTextAttribute(hout,6);		
				for(int j=12-i;j>=1;j--)cout<<endl;			
				cout<<"                                   ";cout<<"神域";Sleep(70);system("cls");			
			}		
			else
			{			
				SetConsoleTextAttribute(hout,6);			
				cout<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl;		
				cout<<"                                   ";Use1.Print("神域");		
				SetConsoleTextAttribute(hout,2);Use1.Print("の");	
				SetConsoleTextAttribute(hout,12); 		
				Use1.LowPrint("大冒险"); 		
			}	
		}
		Sleep(1000);system("cls");	
		cout<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<"                                   ";
		SetConsoleTextAttribute(hout,6); 
		Use1.Print("神域");		
		SetConsoleTextAttribute(hout,2);Use1.Print("の");		
		SetConsoleTextAttribute(hout,12); 		
		Use1.Print("大冒险"); 	
		Sleep(100);
		system("cls");
		Openy();
	}
	system("cls");
	for(int i=1;i<=6;i++)cout<<endl;
	cout<<"                                   ";
	SetConsoleTextAttribute(hout,6);Use1.LowPrint("神域");
	SetConsoleTextAttribute(hout,2);Use1.LowPrint("の");
	SetConsoleTextAttribute(hout,12);Use1.LowPrint("大冒险");Sleep(100);	
	SetConsoleTextAttribute(hout,7); 
	cout<<endl<<endl<<endl<<endl;
	cout<<"                                    ";
	if(op==1)Use1.Print("1.新游戏");
	if(op==2)Use1.Print("1.继续游戏");
	cout<<endl<<endl;
	cout<<"                                    ";Use1.Print("2.打开存档");cout<<endl<<endl;
	cout<<"                                    ";Use1.Print("3.关于游戏");cout<<endl<<endl;
	cout<<"                                    ";Use1.Print("4.退出游戏");cout<<endl<<endl<<endl<<endl<<endl;
	cout<<"_______________________\n\n请选择:";
	int num=0;num=read();
	if(num==4){system("cls");exit(0);}
	if(num==1)
	{
		system("cls");
		if(op==1)First(1);
		if(op==2)Use2.toMap(A.NowMap);
	}
	if(num==2)
	{
		system("cls");bool OpenFlag=A.GetData();
		if(OpenFlag==true){
			Use1.LowPrint("存档加载中……");Sleep(1500);
			Use1.LowPrint("加载成功！");Sleep(1000);
			OpEnx(1,2);
		}
		else OpEnx(1,1);
		
	}
	if(num==3)jieshaogame(op); 
}

void MAIN::Mengjing()//剧情的伊始(收起)
{
	HANDLE hout=GetStdHandle(STD_OUTPUT_HANDLE);
	for(int all=1;all<=3;all++)
	{	
		if(all==1)
		{
			for(int i=1;i<=21;i++)
			{	
				if(i!=21)
				{
					SetConsoleTextAttribute(hout,13);
					cout<<"   [梦境]";			
					SetConsoleTextAttribute(hout,7);
					for(int j=1;j<=i;j++)cout<<endl;		
					cout<<"                                             我";		
					for(int j=1;j<=21-i;j++)cout<<endl;					
					cout<<"__________________________________________         _____________________________________________\n";				
					SetConsoleTextAttribute(hout,3);			
					if(i==1||i==2)Use1.Print("我");
					if(i==3||i==4)Use1.Print("我不");
					if(i==5||i==6)Use1.Print("我不停");	
					if(i==7||i==8)Use1.Print("我不停地");	
					if(i==9||i==10)Use1.Print("我不停地坠");
					if(i==11||i==12)Use1.Print("我不停地坠落");
					if(i==13||i==14||i==15)Use1.Print("我不停地坠落着");
					if(i>=16)Use1.Print("我不停地坠落着...");
					SetConsoleTextAttribute(hout,7);
					Sleep(50);system("cls");
				}
				else
				{					
					SetConsoleTextAttribute(hout,13);					
					cout<<"   [梦境]";					
					SetConsoleTextAttribute(hout,7);					
					for(int j=1;j<=21;j++)cout<<endl;				
					cout<<"__________________________________________   我    _____________________________________________\n";					
					SetConsoleTextAttribute(hout,3);					
					Use1.Print("我不停地坠落着...");				
					SetConsoleTextAttribute(hout,7);					
					system("cls");				
				}			
			}		
			for(int i=1;i<=5;i++)
			{				
				SetConsoleTextAttribute(hout,13);		
				cout<<"   [梦境]";			
				SetConsoleTextAttribute(hout,7);		
				for(int j=1;j<=21;j++)cout<<endl;		
				cout<<"__________________________________________         _____________________________________________\n";			
				if(i>=2)
				{				
					SetConsoleTextAttribute(hout,3);		
					Use1.Print("我不停地坠落着...");					
					SetConsoleTextAttribute(hout,7);				
				}				
				else 
				{					
					SetConsoleTextAttribute(hout,3);			
					Use1.Print("我不停地坠落着...                            ");				
					SetConsoleTextAttribute(hout,7);				
					Use1.Print("我"); 				
				}				
				for(int j=2;j<=i;j++)cout<<endl;				
				if(i>=2)cout<<"                                             我";			
				Sleep(100);system("cls");			
			}		
		}		
		else if(all==2)
		{		
			for(int i=1;i<=21;i++)
			{ 
				if(i!=21)
				{		
					SetConsoleTextAttribute(hout,13);				
					cout<<"   [梦境]";			
					SetConsoleTextAttribute(hout,7);		
					for(int j=1;j<=i;j++)cout<<endl;				
					cout<<"                                             我";			
					for(int j=1;j<=21-i;j++)cout<<endl;				
					cout<<"__________________________________________         _____________________________________________\n";				
					SetConsoleTextAttribute(hout,3);				
					if(i==1||i==2)Use1.Print("直");				
					if(i==3||i==4)Use1.Print("直到");
					if(i==5||i==6)Use1.Print("直到永");
					if(i==7||i==8)Use1.Print("直到永远");
					if(i>=9)Use1.Print("直到永远...");
					SetConsoleTextAttribute(hout,7);
					Sleep(50);system("cls");
				}
				else
				{
					SetConsoleTextAttribute(hout,13);
					cout<<"   [梦境]";
					SetConsoleTextAttribute(hout,7);
					for(int j=1;j<=21;j++)cout<<endl;
					cout<<"__________________________________________   我    _____________________________________________\n";
					SetConsoleTextAttribute(hout,3);
					Use1.Print("直到永远...");
					SetConsoleTextAttribute(hout,7);
					system("cls");
				}
			}
			for(int i=1;i<=5;i++)
			{
				SetConsoleTextAttribute(hout,13);
				cout<<"   [梦境]";
				SetConsoleTextAttribute(hout,7);
				for(int j=1;j<=21;j++)cout<<endl;
				cout<<"__________________________________________         _____________________________________________\n";
				if(i>=2)
				{				
					SetConsoleTextAttribute(hout,3);			
					Use1.Print("直到永远...");				
					SetConsoleTextAttribute(hout,7);				
				} 			
				else
				{
					SetConsoleTextAttribute(hout,3);	
					 Use1.Print("直到永远...                                  ");		 
					 SetConsoleTextAttribute(hout,7);			 
					 Use1.Print("我");			 
				} 		
				for(int j=2;j<=i;j++)cout<<endl;		
				if(i>=2)cout<<"                                             我";		
				Sleep(100);system("cls");		
			}			
		}
		else
		{
			for(int i=1;i<=21;i++)
			{ 
				if(i!=21)
				{		
					SetConsoleTextAttribute(hout,13);	
					cout<<"   [梦境]";	
					SetConsoleTextAttribute(hout,7);
					for(int j=1;j<=i;j++)cout<<endl;			
					cout<<"                                             我";		
					for(int j=1;j<=21-i;j++)cout<<endl;		
					cout<<"__________________________________________         _____________________________________________\n";		
					Sleep(50);system("cls");		
				}	
				else
				{			
					SetConsoleTextAttribute(hout,13);	
					cout<<"   [梦境]";	
					SetConsoleTextAttribute(hout,7);	
					for(int j=1;j<=21;j++)cout<<endl;
					cout<<"__________________________________________   我    _____________________________________________\n";	
					system("cls");	
				}
			}	
			for(int i=1;i<=5;i++)
			{
				SetConsoleTextAttribute(hout,13);
				cout<<"   [梦境]";
				SetConsoleTextAttribute(hout,7);
				for(int j=1;j<=21;j++)cout<<endl;
				cout<<"__________________________________________         _____________________________________________";
				for(int j=1;j<=i;j++)cout<<endl;
				cout<<"                                             我";
				Sleep(100);system("cls");
			}				
		}	
	}	
}

bool MAIN::GetSkip()
{
	cout<<"是否跳过开头？\n";
	cout<<"[1]是 [2]否\n";
	cout<<"请输入：";
	char SkipFlag[1000];
	cin>>SkipFlag;system("cls");
	if(SkipFlag[0]=='1')return 1;
	return 0;
}



void AllStartx()
{
	int SkipFlag=E.GetSkip();
	if(!SkipFlag){E.Mengjing();Sleep(1000);}
	E.OpEnx(SkipFlag,1);//youxibeijingshifou=1; 
}

void MAIN::Start()
{
	thread t2(AllStartx),t1(PlayMusicx);
	t2.join();t1.join();
}

int main() {
	E.Start();
	//A.GetData();Use2.toMap(A.NowMap);//测试读档 
	//First(0);//从头开始测试专用 
	//A.dx=16,A.dy1=19,A.dy2=20;Use2.xiaoquMap(5,5);//小区测试专用 
	//dx=16,dy1=17,dy2=18;jiedaoMap(2,2);//街道测试专用 
	//dx=8,dy1=48,dy2=49;shangchangMap(3,3);//商场专测试用 
	//dx=15,dy1=23,dy2=24;gongjiaochezhanMap(7,7);//公交车站测试专用
	//dx=16,dy1=17,dy2=18;xuexiaoMap(6,6); //学校测试专用 
	//dx=8,dy1=5,dy2=6;huayuanMap(9,9);//花园测试专用 
	//A.Map[4][6]="▕ 花花花                  渔      船溪溪溪溪溪溪   ▏";A.Mapx[4][6][35]=A.Mapx[4][6][36]=106;A.dx=8,A.dy1=5,A.dy2=6;Use2.xiaoxibianMap(4,4);//小溪边测试专用 
/*传送之地测试专用*/
/*	cout<<endl<<endl;
	A.Map[4][6]="▕ 花花花                  渔      船溪溪溪溪溪溪   ▏";A.Mapx[4][6][35]=A.Mapx[4][6][36]=106;
   for(int i=3;i<=16;i++)
	   	for(int j=3;j<=48;j++)
		   A.Mapx[20][i][j]=0;
		A.Mapx[20][9][3]=A.Mapx[20][9][4]=111;A.Mapx[20][9][5]=A.Mapx[20][9][6]=0;
		A.Mapx[20][8][4]=A.Mapx[20][8][3]=A.Mapx[20][10][4]=A.Mapx[20][10][3]=111; 
		//           十位: 0         1         2         3         4         5
		//                 012345678901234567890123456789012345678901234567890123       //方便计算坐标 
		A.Map[20][3]="▕ 树                                             树▏";
		A.Map[20][4]="▕ 树                                             树▏";
		A.Map[20][5]="▕ 树                                             树▏";
		A.Map[20][6]="▕ 树                                             对▏";
		A.Map[20][7]="▕ 树                                             树▏";
		A.Map[20][8]="▕ 小                                             树▏";
		A.Map[20][9]="▕ 溪                                             树▏";
	   A.Map[20][10]="▕ 边                                             树▏";//对齐后方便计算坐标 
	   A.Map[20][11]="▕ 树                          林林林林  林林     树▏";
	   A.Map[20][12]="▕ 树                          林林林林林林林     树▏";
	   A.Map[20][13]="▕ 树                              湖湖林林林     树▏";
	   A.Map[20][14]="▕ 树                              湖湖林林林     树▏";
	   A.Map[20][15]="▕ 树                            林林林林林林     树▏";
	   A.Map[20][16]="▕ 树                              林             树▏";
	   for(int i=11;i<=12;i++)
	   	for(int j=31;j<=44;j++)A.Mapx[20][i][j]=110;
		A.Mapx[20][11][39]=A.Mapx[20][11][40]=0;
	   for(int i=13;i<=15;i++)
	   	for(int j=39;j<=44;j++)A.Mapx[20][i][j]=110;
	   	A.Mapx[20][15][33]=A.Mapx[20][15][34]=A.Mapx[20][15][35]=A.Mapx[20][15][36]=A.Mapx[20][15][37]=A.Mapx[20][15][38]=110;
		A.Mapx[20][16][35]=A.Mapx[20][16][36]=110; 
	   for(int i=13;i<=14;i++)
	   	for(int j=35;j<=38;j++)A.Mapx[20][i][j]=108;
	   	A.Mapx[20][6][50]=A.Mapx[20][6][51]=112;
		for(int i=3;i<=7;i++)
			for(int j=3;j<=4;j++)
				A.Mapx[20][i][j]=109; 
		for(int i=11;i<=16;i++)
			for(int j=3;j<=4;j++)
				A.Mapx[20][i][j]=109; 
		A.Map[20][13]="▕ 树                              诡湖林林林     树▏";
		A.Map[20][14]="▕ 树                              诡湖林林林     树▏";
		for(int i=13;i<=14;i++)
		for(int j=35;j<=38;j++)A.Mapx[20][i][j]=113;
		caoweishifou=2;				
	timed=21;things[++numt]=2,pd_thing[2]=numt,thing_num[2]+=3;things[++numt]=4,pd_thing[4]=numt,thing_num[4]+=5;first_sb++;dx=9,dy1=5,dy2=6;chuansongzhidiMap(20,20);
*/


	return 0;
	
}
/**月雩薇嫭**/
/**
[注]：21~23行为对话框开始的地方，上面为游戏界面(21行是'___',22行是空行,23行是对话内容) 
	  21行标准长度 "_______________________" 
	  13行左右为屏幕中央 ,"                                           "后为屏幕中央 

 	
  //   十位: 0         1         2         3         4         5
  //         012345678901234567890123456789012345678901234567890123       //方便计算坐标 
	xxxx[1]="▕▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▏";
	xxxx[2]="▕                                                  ▏";
	xxxx[3]="▕                                                  ▏";
	xxxx[4]="▕                                                  ▏";
	xxxx[5]="▕                                                  ▏";
	xxxx[6]="▕                                                  ▏";//一定要建墙！！(第一列的墙要空一格，后面的墙才能贴紧) 
	xxxx[7]="▕                                                  ▏";
	xxxx[8]="▕                                                  ▏";
	xxxx[9]="▕                                                  ▏";
   xxxx[10]="▕                                                  ▏";//对齐后方便计算坐标 
   xxxx[11]="▕                                                  ▏";
   xxxx[12]="▕                                                  ▏";//(花1)
   xxxx[13]="▕                                                  ▏";//(花2)
   xxxx[14]="▕                                                  ▏";
   xxxx[15]="▕                                                  ▏";
   xxxx[16]="▕                                                  ▏";
   xxxx[17]="▕                                                  ▏";
   xxxx[18]="▕__________________________________________________▏"; (模板)

0->无色 
1->深蓝色 9
2->绿色   10
3->天蓝色 11(对话使用 3,旁白使用 3,人物(对话)使用 7)
4->红色   12(人物(地图中)使用12)
5->紫色   13(地点使用13,在第一行空三格处)
6->黄色   14
7->白色(原色) 
8->灰色 
9~15:即 1~7 颜色变浅一些(白色不变) 
**/
