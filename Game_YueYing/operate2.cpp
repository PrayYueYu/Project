#include <windows.h>
#include <conio.h>
#include<string.h>
#include<time.h>
#include <unistd.h>//获取文件地址 
#include<bits/stdc++.h>
#define ll long long
#define random(x) (rand()%x)
#include "operate1.h" 
#include "operate2.h" 
#include "Data.h"
#include "mainx.h"
using namespace std;
extern Data A;
extern Operate1 Use1;
extern Operate2 Use2;

const char *Operate2::GetMapTitle(int op)
{
	switch(op)
	{
		case 1:return "卧室";
		case 2:return "街道";
		case 3:return "商场";
		case 4:return "小溪边";
		case 5:return "小区";
		case 6:return "学校";
		case 7:return "公交车站";
		case 9:return "花园";
		case 11:return "神域·万道城";
		case 12:return "梦境";
		case 13:return "神域·元府";
		case 14:return "神域·孤霞山脉";
		case 15:return "神域·孤山野村";
		case 16:return "神域·远古森林";
		case 17:return "神域·魂殿";
		case 18:return "神域·残幽冥河";
		case 19:return "神域·荒野之地";
		case 20:return "亻[数据删除]也";
	}
	return "未知地点";
}

const char *Operate2::GetCultivationStage(int xwz)
{
	struct StageLimit
	{
		int maxValue;
		const char *name;
	};
	static const StageLimit stages[]={
		{99,"凡人之躯）"},
		{199,"炼气一层)"},
		{299,"炼气二层)"},
		{399,"炼气三层)"},
		{499,"炼气四层)"},
		{599,"炼气五层)"},
		{699,"炼气六层)"},
		{799,"炼气七层)"},
		{899,"炼气八层)"},
		{999,"炼气九层)"},
		{1199,"炼气圆满)"},
		{2500,"筑基初期)"},
		{5000,"筑基中期)"},
		{7500,"筑基后期)"},
		{9999,"筑基圆满)"},
		{19999,"金丹初期)"},
		{29999,"金丹中期)"},
		{39999,"金丹后期)"},
		{49999,"金丹圆满)"},
		{99999,"元婴初期)"},
		{499999,"元婴中期)"},
		{999999,"元婴后期)"},
		{1499999,"元婴圆满)"},
		{2999999,"化神初期)"},
		{4999999,"化神中期)"},
		{7499999,"化神后期)"},
		{9999999,"化神圆满)"}
	};
	for(int i=0;i<(int)(sizeof(stages)/sizeof(stages[0]));i++)
		if(xwz<=stages[i].maxValue)return stages[i].name;
	return "无我（月影之巅）)";
}

char Operate2::ReadInputKey()
{
	while(!_kbhit()){}
	return _getch();
}

bool Operate2::IsKey(char key,char expected)
{
	return key==expected||key==expected-'a'+'A';
}

void Operate2::AddWalkingCultivation()
{
	if(A.xwsf!=1)return;
	if(A.xwz<=1119)A.xwz+=1;
	else if(A.xwz<=9999)A.xwz+=2;
	else if(A.xwz<=49999)A.xwz+=3;
	else if(A.xwz<=1499999)A.xwz+=4;
	else if(A.xwz<=9999999)A.xwz+=5;
}

void Operate2::DrawPlayerMapRows(int op,bool showTransmit,const char *guidePrefix)
{
	HANDLE hout=GetStdHandle(STD_OUTPUT_HANDLE);
	int count=0;
	for(int i=1;i<=18;i++)
	{
		for(int j=0;j<A.Map[op][i].size();j++)
		{
			if(i==A.dx&&j==A.dy1){count++,SetConsoleTextAttribute(hout,12);cout<<"我";SetConsoleTextAttribute(hout,7);}
			if(!count)cout<<A.Map[op][i][j];
			if(count)count++;
			if(count==3)count=0;
		}
		if(showTransmit&&i==4)cout<<"                          传送[T]";
		if(i==6)cout<<"                          背包[B]";
		if(i==8)cout<<"                          存/读档[C]";
		if(i==10)cout<<"                          退出[R]";
		if(i==12)cout<<"                          回家[H]";
		if(A.xwsf==1&&i==14)cout<<"                          修炼[P]";
		if(i==16)cout<<guidePrefix<<"游戏指南：通过触碰来触发剧情";
		cout<<endl;
	}
}

int Operate2::ActualMapIdFromChoice(int choice)
{
	if(choice>=8)choice++;
	if(choice>=10)choice++;
	if(choice>=12)choice++;
	return choice;
}

void Operate2::SetPlayerPosition(int x,int y1)
{
	A.dx=x;
	A.dy1=y1;
	A.dy2=y1+1;
}

void Operate2::Place(int op)
{
	HANDLE hout=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hout,13);
	cout<<"   ["<<GetMapTitle(op)<<"]";
	SetConsoleTextAttribute(hout,7);
	printf("     时间: %d年 %d月%d日",A.timey,A.timem,A.timed);
	SetConsoleTextAttribute(hout,3);
	printf("  精力：%d",A.jlz);
	if(A.xwsf==1)
	{
		SetConsoleTextAttribute(hout,2);
		printf("  修为值：%d（",A.xwz);
		cout<<GetCultivationStage(A.xwz);
	}
	SetConsoleTextAttribute(hout,7);
	cout<<endl<<endl;
} 

void Operate2::zhandoujiemian(int HP_x,int MA_x,int DE_x,int AT_x,int idxx)
{
	system("cls");
	HANDLE hout=GetStdHandle(STD_OUTPUT_HANDLE);
	while(1)
	{ 
		char t;t=92;
		SetConsoleTextAttribute(hout,7);
		cout<<"                "<<A.wupin[idxx];
		int ggghhf=A.wupin[idxx].size();
		for(int i=22-ggghhf;i>=1;i--)cout<<" ";cout<<"|                                         |"      <<"             月雩           "<<endl;
		cout<<"                                      |                                         |"      <<"                            "<<endl;
		cout<<"                                      |                                         |"      <<"                            "<<endl;
		cout<<"                                      |       "  <<"                   _______        |"<<"                            "<<endl;
		cout<<"                                      |        "<<t<<"      /         /               |"<<"                            "<<endl;
		cout<<"      HP:"<<HP_x<<"          MA:"<<MA_x<<"             |         "<<t<<"    /         /______          |"<<"      HP:"<<A.HP<<"          MA:"<<A.MA<<"   "<<endl;
		cout<<"                                      |          "<<t<<"  /                /          |"<<"                            "<<endl;
		cout<<"                                      |           "<<t<<"/      .   ______/           |"<<"                            "<<endl;
		cout<<"                                      |                                         |"      <<"                            "<<endl;
		cout<<"      AT:"<<AT_x<<"           DE:"<<DE_x<<"             |                                         |"      <<"      AT:"<<A.AT<<"         DE:"<<A.DE<<"   "<<endl;
		cout<<"                                      |                                         |"      <<"                            "<<endl;
		cout<<"______________________________________|                                         |______________________________________"<<endl<<endl;
		if(A.HP<=1){Use1.LowPrint("你失败了！！");break;} 
		if(HP_x<=1){Use1.LowPrint("你赢了！！");break;} 
		
		cout<<endl<<"[1].普通攻击"<<endl;
		cout<<"[2].释放技能(暂未开启)"<<endl;
		Use1.LowPrint("请选择：");  
		char attcc[1000];cin>>attcc;
		if(attcc[0]=='1')
		{
			cout<<endl;Use1.LowPrint("你向对方发起了攻击！！");cout<<endl<<endl;
			if(A.AT<=DE_x)Use1.LowPrint("但是由于敌人防御力太高，你无法对其造成伤害！！");
			else {Use1.LowPrint("你对敌人造成了 ");cout<<A.AT-DE_x;Use1.LowPrint(" 点伤害！！");HP_x-=(A.AT-DE_x);}
		}   
		else continue;
		cout<<endl<<endl;
		if(AT_x>A.DE){Use1.LowPrint("敌方对你造成了 ");cout<<AT_x-A.DE;Use1.LowPrint(" 点伤害！！");A.HP-=(AT_x-A.DE);}
		else Use1.LowPrint("你像钢板一样坚硬！");
		Sleep(500);
		system("cls");
	}           
	A.HP=50;                                                              
}


void Operate2::chuli(int op,int x,int y)
{
	
	int now=op;
	
	HANDLE hout=GetStdHandle(STD_OUTPUT_HANDLE);
//注意，如果因为要切换屏幕，有了system("pause")，那么最后一行的system("pause")是不用的，用 PauseFlag 变量记录 	
	int PauseFlag=0;
	
	if(now==1)//卧室 
	{
		
		if(A.Mapx[1][x][y]==1)Use1.LowPrint("朴实无华的墙");
		if(A.Mapx[1][x][y]==7)Use1.LowPrint("储物柜里空空如也");
		if(A.Mapx[1][x][y]==6)Use1.LowPrint("从某宝上淘来的便宜木制椅");
		if(A.Mapx[1][x][y]==5&&x==10&&!A.pd_thing[3])
		{A.things[++A.numt]=3,A.pd_thing[3]=A.numt,A.thing_num[3]++;Use1.LowPrint("一本奇怪的书，似乎以前没见过");cout<<endl;Use1.LowPrint("获得 [奇怪的书]");}
		else if(A.Mapx[1][x][y]==5)Use1.LowPrint("简单的书桌");
		if(A.Mapx[1][x][y]==3&&x==7&&!A.pd_thing[1]){A.things[++A.numt]=1,A.pd_thing[1]=A.numt,A.thing_num[1]++;Use1.LowPrint("获得 [卧室钥匙]");}
		else if(A.Mapx[1][x][y]==3)Use1.LowPrint("绿色的枝叶随风飘摆，散发出迷人的幽香");
		if(A.Mapx[1][x][y]==2&&!A.pd_thing[1])Use1.LowPrint("门似乎被锁住了，真是太奇怪了");
		if(A.Mapx[1][x][y]==2&&A.pd_thing[1])
		{
			
			Use1.LowPrint("门开了");
			Sleep(500);
			//Use1.xiugaibeibao(A.pd_thing[1],1,1);
			A.dx=16,A.dy1=19,A.dy2=20;
			if(!A.first_xiaoqu)
			{
				system("cls");
				Sleep(500);
				Use1.LowPrint("一开门，强烈的阳光瞬间刺入眼睛，你感到极为不适");
				Sleep(800);
				cout<<endl<<endl;
				Use1.LowPrint("已经有多久没出来了呢？");
				Sleep(800);
				system("cls");
				Use1.LowPrint("先去转转吧");
				cout<<endl<<endl;system("pause");
				system("cls");
				A.first_xiaoqu=true;
				PauseFlag=1;
			}
			toMap(5);
		}
		if(A.Mapx[1][x][y]==8&&x==15&&!A.pd_thing[2])
		{A.things[++A.numt]=2,A.pd_thing[2]=A.numt,A.thing_num[2]+=3;Use1.LowPrint("几瓶珍藏多年的矿泉水");cout<<endl;Use1.LowPrint("获得 [矿泉水] ×3");}
		else if(A.Mapx[1][x][y]==8)Use1.LowPrint("一些自己用的衣物");
		if(A.Mapx[1][x][y]==10)
		{
			Use1.LowPrint("是否睡觉？(进入下一天)");
			cout<<"\n1.睡觉\n2.再等会儿吧\n请选择:";
			char oopppq;cin>>oopppq;
			if(oopppq=='1')
			{
				A.jlz=500;
				system("cls");Use1.LowPrint("这亦真亦幻的世界...");cout<<endl<<endl;Sleep(200);Use1.LowPrint("呵呵");cout<<endl<<endl;Sleep(200);Use1.LowPrint("迷糊间，你沉沉地睡了过去...");
				Use1.change_date();

			}
			else {}
		} 
		if(A.Mapx[1][x][y]==9)Use1.LowPrint("一盏朴实无华的灯");
		if(A.Mapx[1][x][y]==11)Use1.LowPrint("一扇破旧的窗，透过它可以看到窗外繁华的城市");
		if(A.Mapx[1][x][y]==4)Use1.LowPrint("一些珍藏多年的书籍");
		
	}
	/*	
	1:卧室 
	2:街道 
	3:商场 
	4:小溪边 
	5:小区
	6.学校
	7.公交车站
	9.花园
	11.万道城 
	12.梦境 
	13.元府 
	14.孤霞山脉 
	15.孤山野村
	16.远古森林
	17.魂殿
	18.残幽冥河
	19.荒野之地 
	20.亻[数据删除]也（传送之地）
	*/
	
	else if(now==11)
	{
		//115.传送门 116.守护者 117.守卫1(上) 118.守卫2(下) 119.守卫3(右) 120.门(上) 121.门(下) 122.门(右) 123.铁匠铺 124.清风酒楼 125.拍卖行 126.交易所 127.墙 
		if(A.Mapx[11][x][y]==115)
		{
			
			Use1.LowPrint("连通人界的传送门，但已有万年未曾开启过了（除了你小子）");
			char errorr;
			cout<<endl<<endl;
			Use1.LowPrint("是否返回人界？(1 for yes):");
			cin>>errorr; 
			if(errorr=='1')
			{
				A.dx=6,A.dy1=17,A.dy2=18;
				toMap(20);
			} 
			else 
			{
				cout<<endl;
				Use1.LowPrint("你还不想返回人界");
			}
		}
		else if(A.Mapx[11][x][y]==116)
		{
			Use1.LowPrint("（眼睛猛地睁开）竟然是从人界来的小子……真是奇了怪了……");
			cout<<endl;
			Use1.LowPrint("(小声嘀咕)不是说从 元帝 和 月帝 之战后传送门就被封印了吗……");
			cout<<endl;
			Use1.LowPrint("小子，神界可不同于人界，在神界要处处小心，以免陨落！(体力用完之后会回到这里自动恢复)");
		}
		else if(A.Mapx[11][x][y]==117)
		{
			if(A.xwz<1000000)Use1.LowPrint("元府仅对 元婴圆满及以上 或元府之人开放！！");
			
			else Use1.LowPrint("欢迎参观元府~");
		}
		else if(A.Mapx[11][x][y]==118)Use1.LowPrint("想去残幽冥河吗？要小心哦，那里有许多高阶魔族！");
		else if(A.Mapx[11][x][y]==119)Use1.LowPrint("想去孤霞山脉吗？据说那里藏着巨大的机缘呢！");
		
		else if(A.Mapx[11][x][y]==120)
		{
			//元府 
		}
		else if(A.Mapx[11][x][y]==121)
		{
			//残幽冥河 
		}
		else if(A.Mapx[11][x][y]==122)
		{
			//孤霞山脉 
		}
		else if(A.Mapx[11][x][y]==123)
		{
			
			//集齐 混沌+五行神晶可打造
			Use1.LowPrint("“想要更精良的装备吗？(开发中)”"); 
			
		}
		else if(A.Mapx[11][x][y]==124)Use1.LowPrint("清风酒楼，神界最大的酒楼，热闹非凡，人满为患");
		else if(A.Mapx[11][x][y]==125)Use1.LowPrint("拍卖行开发中~");
		else if(A.Mapx[11][x][y]==126)Use1.LowPrint("交易所开发中~");
		else if(A.Mapx[11][x][y]==127)Use1.LowPrint("神界的城墙，据说是用深渊陨石制成的，可以轻松抵挡元婴后期的全力一击");
		
		
	}
	
	else if(now==20)//传送之地
	{
	//107.灰 108.林中小湖 109.树 110.林 111.小溪边入口 112.槽位 113.诡湖 
		if(A.Mapx[20][x][y]==107)
		{
			
			Use1.LowPrint("啊啊啊啊啊啊啊！！这张地图好脏脏！");
			cout<<endl;
			Use1.LowPrint("今天开始我要自己做卫生~~(温馨提示：打扫卫生会花掉10天哦~)");
			int hygtfr=0;
			cout<<endl<<"是否打扫地图？（1 for yes）:";
			cin>>hygtfr;
			if(hygtfr==1)
			{
				system("cls");
				Use1.LowPrint("嘿咻嘿咻嘿咻咻～～");
				cout<<endl<<endl;
				Use1.LowPrint("(十天之后……)");
				cout<<endl<<endl;A.jlz=500;
				Use1.LowPrint("我滴任务，终于完成啦！！！！");
				for(int i=1;i<=10;i++)Use1.change_date();
				cout<<endl<<endl;
			   for(int i=3;i<=16;i++)
				   	for(int j=3;j<=48;j++)
					   A.Mapx[20][i][j]=0;
					A.Mapx[20][9][3]=A.Mapx[20][9][4]=111;A.Mapx[20][9][5]=A.Mapx[20][9][6]=0;
					A.Mapx[20][8][4]=A.Mapx[20][8][3]=A.Mapx[20][10][4]=A.Mapx[20][10][3]=111; 
					//             十位: 0         1         2         3         4         5
					//                   012345678901234567890123456789012345678901234567890123       //方便计算坐标 
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
				system("pause"); 
				PauseFlag=1;
			}
			else Use1.LowPrint("但是我好懒~");
			
		}
		
		else if(A.Mapx[20][x][y]==111){A.dx=6,A.dy1=33,A.dy2=34;toMap(4);}
		
		else if(A.Mapx[20][x][y]==110)
		{	
			Use1.LowPrint("一片小型树林，清新的空气弥漫其中");
			cout<<endl<<endl;
			Use1.LowPrint("我深吸一口气，五脏六腑如同被洗刷着，好爽啊！");
			cout<<endl<<endl;
			Use1.LowPrint("但……总感觉哪里怪怪的……");
		}
		
		else if(A.Mapx[20][x][y]==109){Use1.LowPrint("参天古木，仿佛要把天撕裂出一个大口");}
		
		else if(A.Mapx[20][x][y]==108)
		{
		
			if(A.caoweishifou!=2)Use1.LowPrint("湖中……倒映着一个世界呐……月影闪动，流光隐现，宛若仙境……"); 
			
			if(Use1.pdzq()&&A.caoweishifou==1)
			{
				Sleep(3000);system("cls");
				Use1.LowPrint("……"); 
				cout<<endl<<endl;
				Use1.LowPrint("…………"); 
				cout<<endl<<endl;
				Use1.LowPrint("………………"); 
				cout<<endl<<endl;
				Use1.LowPrint("你望着小湖，阵阵发神，不知不觉天已经黑了");
				cout<<endl<<endl;
				Use1.LowPrint("忽然，一道灵光自湖底冲出，一道人影现于湖面之上，你不禁一怔");
				cout<<endl<<endl;
				Use1.LowPrint("在你失神之际，湖水竟不知不觉消散了");
				A.Map[20][13]="▕ 树                              诡湖林林林     树▏";
				A.Map[20][14]="▕ 树                              诡湖林林林     树▏";
				for(int i=13;i<=14;i++)
				for(int j=35;j<=38;j++)A.Mapx[20][i][j]=113;
				A.caoweishifou=2;				
			}
		
		} 
		
		else if(A.Mapx[20][x][y]==113)Use1.LowPrint("人影在空中静静地漂浮着，她背对着你，窈窕多姿，恍若仙子下凡，美轮美奂");
		
		else if(A.Mapx[20][x][y]==112)Use1.LowPrint("奇怪，这棵树怎么怪怪的？总感觉少了点东西……（树上发现了五个小槽，不知道是用来做什么的）"); 
		
		else if(A.Mapx[20][x][y]==114)
		{
			
			Use1.LowPrint("一扇奇怪的门……好像之前从没见过");
			
			cout<<endl<<endl;
			
			if(A.xwz>=10000)
			{
				
				Use1.LowPrint("是否进入？（1 for yes）");
				int tgtgyh=0;
				cin>>tgtgyh;
				
				if(A.diyicichuansongmen==0)
				{
					A.diyicichuansongmen=1;
					system("cls");
					Use1.LowPrint("……");
					cout<<endl<<endl;
					Use1.LowPrint("…………");
					cout<<endl<<endl;
					Sleep(1000);
					Use1.LowPrint("我……这是死了吗……");
					cout<<endl<<endl;
					Use1.LowPrint("前路迷茫，我身在何方……");
					cout<<endl<<endl;
					Use1.LowPrint("迷迷糊糊中，你向下坠去……");
					cout<<endl<<endl;
					Sleep(2000);
					Use1.LowPrint("不知过了多久，你终于醒了过来(可以去找守护者要提示)");
					cout<<endl<<endl;
					system("pause");
					PauseFlag=1;
					
				}
				A.dx=8,A.dy1=8,A.dy2=9;
				toMap(11);
			}
			
			else Use1.LowPrint("冥冥之中，一股力量拒绝你进入（似乎是修为不足？去提升提升修为再来试试吧！）");
			
		}
	 
	} 
	
	else if(now==5)//小区
	{
		if(A.Mapx[5][x][y]==24)//家
		{
			A.dx=4,A.dy1=45,A.dy2=46;
			toMap(1);
		}
		if(A.Mapx[5][x][y]==11)
		{
			A.cmsdcs++;Use1.LowPrint("一棵参天古树");
			if(A.cmsdcs==7)
			{
				Sleep(1000);
				system("cls"); 
				Use1.LowPrint("你使劲的摇了摇大树，只听见树枝哗啦哗啦的声音，甚是悦耳！！");
				cout<<endl<<endl;
				Use1.LowPrint("突然！！一条巨大无比的树枝掉了下来！！");
				cout<<endl<<endl;
				Use1.LowPrint("获得 [树枝] ");
				A.things[++A.numt]=11,A.pd_thing[11]=A.numt,A.thing_num[11]++;
				cout<<endl<<endl;system("pause");PauseFlag=1;
			}
		}
		if(A.Mapx[5][x][y]==12){Use1.LowPrint("一些花，在风中传来阵阵幽香");}
		if(A.Mapx[5][x][y]==13){Use1.LowPrint("几棵正翩翩起舞的小草");}
		if(A.Mapx[5][x][y]==14){Use1.LowPrint("小子，疫情期间注意带好口罩！");}
		if(A.Mapx[5][x][y]==15){Use1.LowPrint("天天上班好累啊，小伙子，要不陪我开两把？");}
		if(A.Mapx[5][x][y]==16){Use1.LowPrint("小区筹建的游乐园，现在有很多人在里面");}
		if(A.Mapx[5][x][y]==17){Use1.LowPrint("小区筹建的健身区，有许多人正在运动");}
		if(A.Mapx[5][x][y]==18){Use1.LowPrint("来来来，大伙向我看齐，我宣布个事，我LYJ，就是个SB!!!");}
		if(A.Mapx[5][x][y]==19){Use1.LowPrint("我叫马牛逼！你知道我有多牛逼吗？我敢吃屎！……");}
		if(A.Mapx[5][x][y]==20&&A.first_sb==0)
		{Use1.LowPrint("龟野先生，天皇，陛下!我的任务，完成啦！！！");cout<<endl;Use1.LowPrint("（多点几次试试？）");Sleep(500);A.first_sb++;}
		else if(A.Mapx[5][x][y]==20&&A.first_sb==1)
		{Use1.LowPrint("龟野先生，天皇，陛下!我的任务，完成啦！！！");cout<<endl;A.first_sb++;}
		else if(A.Mapx[5][x][y]==20&&A.first_sb>=2&&A.first_sb!=5)
		{Use1.LowPrint("龟野先生，天皇，陛下!我的任务，完成啦！！！");cout<<endl;A.first_sb++;}
		else if(A.Mapx[5][x][y]==20&&A.first_sb==5)
		{Use1.LowPrint("这晶石十分的珍贵！你且拿下！");cout<<endl;Use1.LowPrint("获得 [五彩斑斓的水晶] ×5");A.things[++A.numt]=4,A.pd_thing[4]=A.numt,A.thing_num[4]+=5;A.first_sb++;}
		if(A.Mapx[5][x][y]==21){Use1.LowPrint("幽幽的荷叶正淡淡地飘着，柔和的清香随风而至");}
		if(A.Mapx[5][x][y]==22)
		{
			Use1.LowPrint("杰哥(阿杰):");
			Use1.LowPrint("请问……你要一些好康的嘛？(0为离开)");
			cout<<endl;
			Use1.Print("[1]小泡芙     2元/袋(不建议购买)");
			cout<<endl;
			Use1.Print("[2]击伟酒       30元/瓶(不建议购买)");
			cout<<endl;
			if(A.sfgmye==0)Use1.Print("[3]鱼饵       1000元/包");
			else Use1.Print("[3]面包       999元/片");
			cout<<endl;
			char ssdd;cin>>ssdd;
			if(ssdd=='1'&&A.thing_num[12]>=2)
			{
				A.things[++A.numt]=5,A.pd_thing[5]=A.numt,A.thing_num[5]++;
				A.thing_num[12]-=2;;Use1.LowPrint("获得 [小泡芙] ×1");Sleep(1000);
			}
			else if(ssdd=='2'&&A.thing_num[12]>=30)
			{
				A.things[++A.numt]=6,A.pd_thing[6]=A.numt,A.thing_num[6]++;
				A.thing_num[12]-=30;Use1.LowPrint("获得 [啤酒] ×1");Sleep(1000);
			}
			else if(ssdd=='3'&&((A.thing_num[12]>=1000&&A.sfgmye==0)||(A.sfgmye==1&&A.thing_num[12]>=999)))
			{
				if(A.sfgmye==0)
				{ 
					A.things[++A.numt]=9,A.pd_thing[9]=A.numt,A.thing_num[9]++;
					A.thing_num[12]-=1000;Use1.LowPrint("获得 [鱼饵] ×1");Sleep(1000);
					A.sfgmye=1;
				}
				else
				{
					A.things[++A.numt]=7,A.pd_thing[7]=A.numt,A.thing_num[7]++;
					A.thing_num[12]-=999;
					system("cls");
					Use1.LowPrint("突然，杰哥走向了你");cout<<endl<<endl;
					Use1.LowPrint("[杰哥]：嘿，俏佳人，你要不要一些好van♂的？");cout<<endl;cout<<endl;
					Use1.LowPrint("[我]：杰、杰哥，你要干嘛！");cout<<endl;cout<<endl;
					Use1.LowPrint("突然，杰哥掏出了一个很长很长的棒子");cout<<endl;cout<<endl;Sleep(2000); 
					Use1.LowPrint("[杰哥]：这逗猫棒你要不要？只要1元就可以得到了哦~(1 for yes)");cout<<endl;
					char dddffg;cin>>dddffg;
					if(dddffg=='1'&&A.thing_num[12]>=1)
					{
						A.things[++A.numt]=8,A.pd_thing[8]=A.numt,A.thing_num[8]++;
						A.thing_num[12]-=1;Use1.LowPrint("获得 [逗猫棒] ×1");
					}
					else if(dddffg!='1')
					{
						Use1.LowPrint("[杰哥(撅嘴)]：你不要的话，那也没关系");
					}
					else Use1.LowPrint("[杰哥]：没钱来乱搞什么！！！");
				}
			}
			else Use1.LowPrint("[杰哥]：没钱来乱搞什么！！！");
		}
		if(A.Mapx[5][x][y]==23){Use1.LowPrint("两群大妈正在比赛跳辣舞,诶嘿嘿 （流鼻血）！");}
		if(A.Mapx[5][x][y]==25){Use1.LowPrint("朴素而精致的小屋，最好还是不要进去打扰了");}
		if(A.Mapx[5][x][y]==26){A.dx=16,A.dy1=17,A.dy2=18;toMap(2);}
		
	}
	
	else if(now==2)//街道 
	{
		if(A.Mapx[2][x][y]==27)
		{
			Use1.LowPrint("你走近花丛旁，正准备摘一些花，突然，从花丛里钻出来一只可爱的的狸花猫");
			cout<<endl;Use1.LowPrint("喵~~");cout<<endl;A.dx=12,A.dy1=46,A.dy2=47;A.Mapx[2][12][48]=A.Mapx[2][12][49]=29;
			A.Map[2][12]="▕ 树     人           道         道            猫花▏";
			Use1.LowPrint("小猫咪轻轻地叫了一声，两只眼睛直勾勾地盯着你，似乎对你很感兴趣");
			cout<<endl;Use1.LowPrint("是否要和小猫咪玩耍呢？(消耗200点精力)(1 for yes)");
			cout<<endl;char ddffgghh;cin>>ddffgghh;
			if(ddffgghh=='1'&&A.jlz>=200)
			{
				A.jlz-=200;
				Use1.LowPrint("你要怎么和小猫咪玩耍呢？");cout<<endl;
				Use1.Print("1.将小猫咪举起来");cout<<endl;
				Use1.Print("2.揉揉小猫咪的小脑壳");cout<<endl;
				if(A.thing_num[8]){Use1.Print("3.用逗猫棒逗逗小猫咪(小猫咪好感度+100%)");cout<<endl;} 
				char eerrtt;cin>>eerrtt;
				if(eerrtt=='1')Use1.LowPrint("你将小猫咪抱了起来，嗯，小猫咪真可爱！"); 
				else if(eerrtt=='2')Use1.LowPrint("你揉了揉小猫咪的脑袋，嗯，软软的！");
				else if(A.thing_num[8]&&eerrtt=='3'){
					Use1.LowPrint("你用逗猫棒和小猫咪玩得不亦乐乎！");
					A.xiaomaomihaogandu+=100;
				//	Iden newI={};
				//	A=A+newI;
					Use1.xiugaibeibao(A.pd_thing[8],8,1);
				}
				else Use1.LowPrint("你站在原地看着小猫咪，小猫咪也盯着你");
			}
			else if(ddffgghh=='1'&&A.jlz<200)Use1.LowPrint("你没有精力啦！");
			else Use1.LowPrint("喵~~。小猫咪又叫了一声，便看向了别处");
		}
		else if(A.Mapx[2][x][y]==29)
		{
			Use1.LowPrint("喵~~");cout<<endl;
			Use1.LowPrint("小猫咪轻轻地叫了一声，两只眼睛直勾勾地盯着你，似乎对你很感兴趣");
			cout<<endl;Use1.LowPrint("是否要和小猫咪玩耍呢？(消耗200点精力)(1 for yes)");
			cout<<endl;char ddffgghh;cin>>ddffgghh;
			if(ddffgghh=='1'&&A.jlz>=200)
			{
				A.jlz-=200;
				Use1.LowPrint("你要怎么和小猫咪玩耍呢？");cout<<endl;
				Use1.Print("1.将小猫咪举起来");cout<<endl;
				Use1.Print("2.揉揉小猫咪的小脑壳");cout<<endl;
				if(A.thing_num[8]){Use1.Print("3.用逗猫棒逗逗小猫咪(小猫咪好感度+100%)");cout<<endl;} 
				char eerrtt;cin>>eerrtt;
				if(eerrtt=='1')Use1.LowPrint("你将小猫咪抱了起来，嗯，小猫咪真可爱！"); 
				else if(eerrtt=='2')Use1.LowPrint("你揉了揉小猫咪的脑袋，嗯，软软的！");
				else if(A.thing_num[8]&&eerrtt=='3'){
					Use1.LowPrint("你用逗猫棒和小猫咪玩得不亦乐乎！");
					A.xiaomaomihaogandu+=100;
			//		Iden newI={};
			//		A=A+newI;
					Use1.xiugaibeibao(A.pd_thing[8],8,1);
				}
				else Use1.LowPrint("你站在原地看着小猫咪，小猫咪也盯着你");
			}
			else if(ddffgghh=='1'&&A.jlz<200)Use1.LowPrint("你没有精力啦！");
			else Use1.LowPrint("喵~~。小猫咪又叫了一声，便看向了别处");
		}
		else if(A.Mapx[2][x][y]==28)Use1.LowPrint("一些不知名的小花花，正在莫名其妙地晃动着");
		
		else if(A.Mapx[2][x][y]==30){A.dx=3,A.dy1=17,A.dy2=18;toMap(5);}
		
		else if(A.Mapx[2][x][y]==31){A.dx=8,A.dy1=48,A.dy2=49;toMap(3);} 
		else if(A.Mapx[2][x][y]==32){A.dx=8,A.dy1=5,A.dy2=6;toMap(9);} 
		else if(A.Mapx[2][x][y]==33){A.dx=16,A.dy1=17,A.dy2=18;toMap(6);} 
		else if(A.Mapx[2][x][y]==34){Use1.LowPrint("哥们儿，你这瓜多少钱一斤啊……");} 
		else if(A.Mapx[2][x][y]==35){Use1.LowPrint("giegie~~~");} 
		else if(A.Mapx[2][x][y]==36){Use1.LowPrint("我们联合！形成两面包夹芝士！");} 
		else if(A.Mapx[2][x][y]==37){Use1.LowPrint("好快的车车们在车路上疾驰，最好还是不要去了辣，免得被撞飞！");} 
		else if(A.Mapx[2][x][y]==38)
		{
			A.cmsdcs++;
			Use1.LowPrint("前几年种下的小树，说是为了绿化，但做成这个样子(把四周都包围住)真的好吗？");
			if(A.cmsdcs==7)
			{
				Sleep(1000);
				system("cls"); 
				Use1.LowPrint("你使劲的摇了摇大树，只听见树枝哗啦哗啦的声音，甚是悦耳！！");
				cout<<endl<<endl;
				Use1.LowPrint("突然！！一条巨大无比的树枝掉了下来！！");
				cout<<endl<<endl;
				Use1.LowPrint("获得 [树枝] ");
				A.things[++A.numt]=11,A.pd_thing[11]=A.numt,A.thing_num[11]++;
				cout<<endl<<endl;system("pause");PauseFlag=1;
			}
		} 
		else if(A.Mapx[2][x][y]==39){A.dx=15,A.dy1=23,A.dy2=24;toMap(7);} 
	}
	
	/*1:卧室 
	2:街道 
	3:商场 
	4:小溪边 
	5:小区
	6.学校
	7.公交车站
	              //8.火车站(取消)
	9.花园*/
	
	else if(now==9)//花园 
	{
	//52.小溪边入口 53.花 54.墙 (花园)	
		if(A.Mapx[9][x][y]==52){A.dx=8,A.dy1=5,A.dy2=6;toMap(4);}
		if(A.Mapx[9][x][y]==53){Use1.LowPrint("淡淡的清香弥漫在花园中，似乎……有一种悲伤的感觉？一种说不出的感觉在心底蔓延");cout<<endl;Use1.LowPrint("为什么会这样啊！？！");}
		if(A.Mapx[9][x][y]==54)Use1.LowPrint("这是来自于街道的墙呢！！");
		if(A.Mapx[9][x][y]==104){A.dx=8,A.dy1=48,A.dy2=49;toMap(2);}
	}

	else if(now==7)//公交车站
	{
		
   //81.无形の墙 82.出口[exit] 83.‘|’(分割线) 84.公交车1 85.公交车2 86.客1 87.客2 88.客3 89.休息区 90.报纸区
   //91.车牌[1] 92.车牌[2] 93.车牌[3] 94.车牌[4] 95.车牌[5] 96.车牌[6] 97.广告 		
   		if(A.Mapx[7][x][y]==81)Use1.LowPrint("一股神秘的力量挡住了你的去路？真是好生奇怪！！"); 
   		if(A.Mapx[7][x][y]==82){A.dx=6,A.dy1=41,A.dy2=42;toMap(2);}
   		if(A.Mapx[7][x][y]==83){Use1.LowPrint("前面就是马路辣，千万不要过去啊啊啊啊！");}
   		if(A.Mapx[7][x][y]==84){Use1.LowPrint("公交车司机：你有毛病吗啊啊！");}
   		if(A.Mapx[7][x][y]==85){Use1.LowPrint("想被撞死倒是可以一逝！！");}
   		if(A.Mapx[7][x][y]==86){Use1.LowPrint("正在播放 [卡农]！！！感觉有点危险（？");}
   		if(A.Mapx[7][x][y]==87){Use1.LowPrint("啊哈哈哈哈哈哈哈哈！（突发恶疾）");}
   		if(A.Mapx[7][x][y]==88){Use1.LowPrint("我好想做嘉然小姐的狗啊嘿嘿嘿~~");} 
   		if(A.Mapx[7][x][y]==89){Use1.LowPrint("一些乘客正在休息ZZZz~~");}
   		if(A.Mapx[7][x][y]==90)
   		{
			Use1.LowPrint("有亿些报纸，你要看那个捏？");
			cout<<endl;
			Use1.Print("[1]生活");
			cout<<endl;
			Use1.Print("[2]情感");
			cout<<endl;
			Use1.Print("[3]都市(★★★)");
			cout<<endl;char ghghgh;
			Use1.LowPrint("请选择：");cin>>ghghgh;
			if(ghghgh=='1')Use1.LowPrint("缺货中！！");
			if(ghghgh=='2')
			{
				
				Use1.LowPrint("怎样快速把妹？怎么戒色？输入下方网站并点击关注就能知道啦！");
				cout<<endl;
				Use1.Print("https://space.bilibili.com/367230056");Sleep(3000);
				
			}
			if(ghghgh=='3')
			{
				
				system("cls");
				Use1.LowPrint("相传，在远古时代，曾有天神降临于我市");SetConsoleTextAttribute(hout,12);
				Use1.LowPrint("树林");SetConsoleTextAttribute(hout,7);
				cout<<endl<<endl;
				Use1.LowPrint("而如今，仍然能有人看见");
				SetConsoleTextAttribute(hout,12);
				Use1.LowPrint("林中小湖");SetConsoleTextAttribute(hout,7);
				Use1.LowPrint("中投射出 [神] 的身影……");
				cout<<endl<<endl;
				Use1.LowPrint("最神奇的是，据说，这些人都是在");SetConsoleTextAttribute(hout,12);
				Use1.LowPrint(" 中秋节 ");SetConsoleTextAttribute(hout,7);
				Use1.LowPrint("这天看见的！！");
				cout<<endl<<endl;
				Use1.LowPrint("或许有机会，或者说是契机，你，也能");
				SetConsoleTextAttribute(hout,12);
				Use1.LowPrint("召唤");SetConsoleTextAttribute(hout,7);
				Use1.LowPrint("出 ");
				SetConsoleTextAttribute(hout,12);
				Use1.LowPrint("[神]");SetConsoleTextAttribute(hout,7);
				Use1.LowPrint(" ！");
				cout<<endl;system("pause");PauseFlag=1;
				
			}
			
		}
   		if(A.Mapx[7][x][y]==91){Use1.LowPrint("这是356公交车");}
   		if(A.Mapx[7][x][y]==92){Use1.LowPrint("这是357公交车");}
   		if(A.Mapx[7][x][y]==93){Use1.LowPrint("这是365公交车");}
   		if(A.Mapx[7][x][y]==94){Use1.LowPrint("这是353公交车");}
   		if(A.Mapx[7][x][y]==95){Use1.LowPrint("这是592公交车");}
   		if(A.Mapx[7][x][y]==96){Use1.LowPrint("这是583公交车");}
   		if(A.Mapx[7][x][y]==97)
{Use1.LowPrint("欢迎关注世纪名人 [月雩·薇嫭] 的B站账号！");cout<<endl;Use1.LowPrint("快输入下方链接关注吧！！");cout<<endl;Use1.Print("https://space.bilibili.com/367230056");cout<<endl;system("pause");PauseFlag=1;}
		
	}

	else if(now==6)//学校
	{
//40.墙 41.操场 42.学生1 43.学生2 44.学生3 45.老师 46.学校大门 47.中二少年 48.教学楼 49.通道 50.树 51.树2 105.焦急的同学(学校)		
		if(A.Mapx[6][x][y]==40)Use1.LowPrint("如果没有它，你小子就可以飞出地图了吧？（恼）");
		if(A.Mapx[6][x][y]==41)Use1.LowPrint("万米巨型操场！这是哪个人才想出来的！！");
		if(A.Mapx[6][x][y]==42){Use1.LowPrint("我好不容易比一次跑步，你却让我输的这么彻底……呵呵呵呵……焯！！！");}
		if(A.Mapx[6][x][y]==43){Use1.LowPrint("嗯……，啊——好刺激啊，要受不了啦，脑袋要坏惹~嘿嘿");}
		if(A.Mapx[6][x][y]==44){Use1.LowPrint("要迟到啦！！！！");}
		if(A.Mapx[6][x][y]==45){Use1.LowPrint("让我康康！是谁没到！！");}
		if(A.Mapx[6][x][y]==46){A.dx=3,A.dy1=17,A.dy2=18;toMap(2);}
		if(A.Mapx[6][x][y]==47)
		{
			Use1.LowPrint("诶嘿嘿，我舅四天下最强贱客！欧不对，是剑！！欧不对，我不剑！不，我最剑……emm，反正我最强！！");
			
			if(A.xwz>=1000000)
			{
				
			}
			
		}
		if(A.Mapx[6][x][y]==48){Use1.LowPrint("教学楼里传来一阵阵读书声，“秦孝公据崤函之固，拥雍州之地，君臣固守以窥周室，……” 真怀念啊!" );}
		if(A.Mapx[6][x][y]==49){Use1.LowPrint("通往地狱の路~~！");}
		if(A.Mapx[6][x][y]==50)
		{
			A.cmsdcs++;
			Use1.LowPrint("这是来自于街道的树呢！");
			if(A.cmsdcs==7)
			{
				Sleep(1000);
				system("cls"); 
				Use1.LowPrint("你使劲的摇了摇大树，只听见树枝哗啦哗啦的声音，甚是悦耳！！");
				cout<<endl<<endl;
				Use1.LowPrint("突然！！一条巨大无比的树枝掉了下来！！");
				cout<<endl<<endl;
				Use1.LowPrint("获得 [树枝] ");
				A.things[++A.numt]=11,A.pd_thing[11]=A.numt,A.thing_num[11]++;
				cout<<endl<<endl;system("pause");PauseFlag=1;
			}
		}
		if(A.Mapx[6][x][y]==51)Use1.LowPrint("啊，哥哥不要啦，那里不行的啦！啊啊~！好大！……我，我要*了！！啊！！");
		if(A.Mapx[6][x][y]==105)
		{
			if(A.zxtsf==0)game_zhuaxiaotou(A.dx,A.dy1),PauseFlag=1;
			else Use1.LowPrint("真的太感谢你上次帮助我啦！！mua~ mua~");
		}
		
	}
	
	else if(now==4)//小溪边
	{
	//98.花园入口 99.花 100.渔者 101.石头 102.溪 103.路	
		if(A.Mapx[4][x][y]==98){A.dx=9,A.dy1=47,A.dy2=48;toMap(9);}
		if(A.Mapx[4][x][y]==99)Use1.LowPrint("从花园蔓延过来的花，似乎越靠近小溪，那股令人窒息的香味便越来越浓……");
		if(A.Mapx[4][x][y]==100)
		{//sfdh=1;
			if(A.sfdh==0)
			{
				int numkkf=0;
				if(A.thing_num[10])numkkf+=1;
				if(A.thing_num[11])numkkf+=1;
				if(A.yzsf==0)
				{ 
					system("cls");Sleep(200);
					Use1.LowPrint("你走向钓鱼的老爷爷，想得到点帮助来「渡河」 ");
					cout<<endl<<endl; 
					Use1.LowPrint("老爷爷盯着你看了一会，突然笑着说：小娃娃，想过去吗？");
					cout<<endl<<endl; 
					Use1.LowPrint("你使劲的点点头，看来有方法了呢！");
					cout<<endl<<endl; 
					Use1.LowPrint("突然，老爷爷的表情冷了下来，道：渡河需要3件物品");
					cout<<endl<<endl; 
					if(A.thing_num[10])SetConsoleTextAttribute(hout,12);
					else SetConsoleTextAttribute(hout,7);
					Use1.LowPrint("[1].绳子  ");SetConsoleTextAttribute(hout,7);
					if(A.thing_num[11])SetConsoleTextAttribute(hout,12);
					else SetConsoleTextAttribute(hout,7);
					Use1.LowPrint("[2].树枝  ");SetConsoleTextAttribute(hout,7);
					Use1.LowPrint("[3].船桨");
					cout<<endl<<endl; 
					Use1.LowPrint("等你找到这三件物品再来找我！老爷爷呢喃着：");
					SetConsoleTextAttribute(hout,12);
					Use1.LowPrint("如果实在无法找到就回来来找我帮忙吧！");
					SetConsoleTextAttribute(hout,7);
					cout<<endl<<endl;system("pause"); A.yzsf=1;PauseFlag=1;
				}
				else if(numkkf==2)
				{
					
					system("cls");
					Use1.LowPrint("看来你已经尽力了！老爷爷笑眯眯的看着你");
					cout<<endl<<endl;
					Use1.LowPrint("没错，船桨在这个游戏世界是没法寻到的！只有通过我这里换取才可得！");
					cout<<endl<<endl;
					Use1.LowPrint("换取需要 [鱼饵] ×1，你有吗？");
					cout<<endl<<endl;
					if(A.thing_num[9]) 
					{
						Sleep(1000);
						Use1.LowPrint("看来你已经找到鱼饵了！(自动进行交易)");
					//	Iden newI={};
					//	A=A+newI;
						Use1.xiugaibeibao(A.pd_thing[9],9,1);
						cout<<endl<<endl;
						Use1.LowPrint("请选择一个船桨：");
						cout<<endl;
						Use1.LowPrint("[1].状态良好的船桨(小概率断掉)");
						cout<<endl;
						Use1.LowPrint("[2].损坏大半的船桨(大概率断掉)");
						cout<<endl<<endl;
						Use1.LowPrint("哦，对了，如果你选择 损坏的船桨 ，我会奖励你 2RMB 的哦！老爷爷笑眯眯的说");
						cout<<endl<<endl;
						Use1.LowPrint("请选择：");char ddrrttyy;cin>>ddrrttyy;
						if(ddrrttyy=='1'){A.things[++A.numt]=13,A.pd_thing[13]=A.numt,A.thing_num[13]++;Use1.LowPrint("你获得了 [状态良好的船桨]");}
						else {A.things[++A.numt]=14,A.pd_thing[14]=A.numt,A.thing_num[14]++;A.thing_num[12]+=2;Use1.LowPrint("你获得了 [损坏大半的船桨] 和 [软妹币] ×2");}
						cout<<endl<<endl;system("pause"); A.sfdh=1;PauseFlag=1;
					}
					else
					{
						Sleep(300);
						Use1.LowPrint("你在身上到处摸索，直到把自己摸得红潮一片也没找到");
						cout<<endl<<endl;
						Use1.LowPrint("老爷爷见状，不禁叹了一口气：再去地图里转转吧！");
						cout<<endl<<endl;
						SetConsoleTextAttribute(hout,12);
						Use1.LowPrint("(PS:如果钱不够，建议重开！)");
						SetConsoleTextAttribute(hout,7);
						system("pause");PauseFlag=1;
					}
					
				}
				else 
				{
			
					Use1.LowPrint("东西找到了吗？(红色为已找到)");
					cout<<endl<<endl;
					if(A.thing_num[10])SetConsoleTextAttribute(hout,12);
					else SetConsoleTextAttribute(hout,7);
					Use1.LowPrint("[1].绳子  ");SetConsoleTextAttribute(hout,7);
					if(A.thing_num[11])SetConsoleTextAttribute(hout,12);
					else SetConsoleTextAttribute(hout,7);
					Use1.LowPrint("[2].树枝  ");SetConsoleTextAttribute(hout,7);
					Use1.LowPrint("[3].船桨");Sleep(1000);
				
				} 
			}
			else
			{
				
				Use1.LowPrint("小伙子，想要现在渡河吗？（1 for yes）");
				char ddffrrttgghh;cin>>ddffrrttgghh;
				if(ddffrrttgghh=='1')
				{
					Use1.LowPrint("好吧，船就在前方！出发吧少年！");
					A.Map[4][6]="▕ 花花花                  渔      船溪溪溪溪溪溪   ▏";
					A.Mapx[4][6][35]=A.Mapx[4][6][36]=106;
				}
				else {Use1.LowPrint("你还有些事吗？那先去忙吧，什么时候想渡河就来告诉我");}
			}
			
		}
		if(A.Mapx[4][x][y]==101)Use1.LowPrint("溪边的小石子儿~嘿嘿，真好玩！");
		if(A.Mapx[4][x][y]==102)Use1.LowPrint("一条汹涌的……小溪？奇怪的设定……似乎不能硬闯过去呢");
		if(A.Mapx[4][x][y]==103)Use1.LowPrint("通往外界的小路，现在不是过去的时候！！");
		if(A.Mapx[4][x][y]==106)
		{
			system("cls");
			Use1.LowPrint("小船在汹涌的小河上飘荡着……");
			cout<<endl<<endl;
			if(A.thing_num[13]==true&&A.thing_num[16]==false)
			{
				Sleep(2000);
				Use1.LowPrint("突然！一阵狂风卷过，惊涛骇浪，万雷齐鸣，恐怖如斯！");
				cout<<endl<<endl;
				Use1.LowPrint("而就在这时，你手中的坚实的船桨……");
				cout<<endl<<endl;
				Use1.LowPrint("咔嚓……");
				cout<<endl<<endl;
				Use1.LowPrint("断了……");
				cout<<endl<<endl;
				Use1.LowPrint("你的船和你沉入了船底……");
				cout<<endl<<endl;
				system("pause");
				system("cls");
				Use1.LowPrint("就在你陷入绝望之际，一道七彩霞光笼罩了你……");
				cout<<endl<<endl;
				Sleep(1000);
				Use1.LowPrint("当你醒来之后，已是几天之后");
				cout<<endl<<endl;Use1.change_date();Use1.change_date();
				Use1.LowPrint("你的脑中晕乎乎，但船桨似乎已经恢复，并且手中似乎多了一样东西……");
				cout<<endl<<endl;
				Use1.LowPrint("你获得了 [沉睡的七彩神玉] ×1");
				A.things[++A.numt]=16,A.pd_thing[16]=A.numt,A.thing_num[16]++;
				cout<<endl<<endl;
				system("pause");PauseFlag=1;
				system("cls");
				
			}
			else
			{
				Sleep(2000);
				Use1.LowPrint("有惊无险地通过……");
				cout<<endl<<endl;
				system("pause");PauseFlag=1;
				system("cls");
				
			}
			A.dx=9,A.dy1=5,A.dy2=6;toMap(20);
		}
		
	}
	
	else if(now==3)//商场
	{
		
   //55.商场大门 56.墙 57.WC 58.衣 59.包 60.果 61.杂 62.日常 63.器 64.玩具 65.导(衣) 66.导(包) 67.导(果) 68.导(杂) 69.导(日常) 70.导(器) 71.导(玩具)
   //72.人1(器) 73.人2(包) 74.人3 75.人(♂) 76.人4(♀) 77.同学 78.♂ 79.♀ 80.‘|’(分割线) 
   	if(A.Mapx[3][x][y]==55)
	{
	
		A.dx=8,A.dy1=5,A.dy2=6;
		
		if(A.sfjq&&!A.jqdf)
		{
			
			A.jqdf=1;
			
			system("cls");
			
			Use1.LowPrint("正当你准备走出商场，突然眼前出现了几条人影");
			cout<<endl<<endl;
			Use1.LowPrint("小子，听说你得到了很多钱？其中一个人走上前来，扛着一根大棒子对着你说");
			cout<<endl<<endl;
			Use1.LowPrint("你、你们要干什么！！不要过来啊！！");
			cout<<endl<<endl;
			Use1.LowPrint("哼，只要你乖乖的把钱交出来，就可以免去一顿皮肉之苦了！啊哈哈哈哈！");
			cout<<endl<<endl;
			Use1.LowPrint("几个混混大笑开来");
			cout<<endl<<endl;
			Use1.LowPrint("你面红耳赤，怒目圆睁地道：死也不给！！");
			Sleep(1000);
			zhandoujiemian(50,0,5,7,15);
			system("cls");
			Use1.LowPrint("哼！算你小子走运！老子今天不想打人了！！赶紧给我滚！！");
			cout<<endl<<endl;
			Use1.LowPrint("混混冷冷的盯着你，直到你走出商场");
			cout<<endl<<endl;
			system("pause");PauseFlag=1;
			 
			
		}
		
		toMap(2);
	
	}
   	if(A.Mapx[3][x][y]==56){Use1.LowPrint("只是朴实无华的墙呢~");}
   	if(A.Mapx[3][x][y]==57)Use1.LowPrint("休息一下吧~！");
   	if(A.Mapx[3][x][y]==58)Use1.LowPrint("Balenciaga(巴黎世家)专卖店");
   	if(A.Mapx[3][x][y]==59)Use1.LowPrint("Lv(路易威登)专卖店");
   	if(A.Mapx[3][x][y]==60)Use1.LowPrint("Dole(都乐)");
   	if(A.Mapx[3][x][y]==61)Use1.LowPrint("Pray(月雩)の杂货铺");
   	if(A.Mapx[3][x][y]==62)Use1.LowPrint("广告上写着：“各种生活用品，只要你想的，都有哦~~！”");
   	if(A.Mapx[3][x][y]==63)Use1.LowPrint("Midea(美的)专卖店");
   	if(A.Mapx[3][x][y]==64)Use1.LowPrint("Lego(乐高)专卖店");
   	if(A.Mapx[3][x][y]==65)Use1.LowPrint("导购只是冷冷的看了你一眼，便说：没钱来干什么！快滚！你暗暗骂着：狗眼看人低的狗东西！");
   	if(A.Mapx[3][x][y]==66)Use1.LowPrint("导购只是冷冷的看了你一眼，便说：没钱来干什么！快滚！你暗暗骂着：狗眼看人低的狗东西！");
   	if(A.Mapx[3][x][y]==67)Use1.LowPrint("导购只是冷冷的看了你一眼，便说：没钱来干什么！快滚！你暗暗骂着：狗眼看人低的狗东西！");
   	if(A.Mapx[3][x][y]==68)Use1.LowPrint("导购只是冷冷的看了你一眼，便说：没钱来干什么！快滚！你暗暗骂着：狗眼看人低的狗东西！");
   	if(A.Mapx[3][x][y]==69)Use1.LowPrint("导购只是冷冷的看了你一眼，便说：没钱来干什么！快滚！你暗暗骂着：狗眼看人低的狗东西！");
   	if(A.Mapx[3][x][y]==70)Use1.LowPrint("导购只是冷冷的看了你一眼，便说：没钱来干什么！快滚！你暗暗骂着：狗眼看人低的狗东西！");
   	if(A.Mapx[3][x][y]==71)Use1.LowPrint("导购只是冷冷的看了你一眼，便说：没钱来干什么！快滚！你暗暗骂着：狗眼看人低的狗东西！");
   	if(A.Mapx[3][x][y]==72)Use1.LowPrint("这天气太热了！我要买十万个空调把整个地球冻住！！");
   	if(A.Mapx[3][x][y]==73)Use1.LowPrint("什么品牌啊！这么便宜！哈哈哈老子要全买下来！");
   	if(A.Mapx[3][x][y]==74)Use1.LowPrint("商场打卡~~");
   	if(A.Mapx[3][x][y]==75)Use1.LowPrint("诶嘿嘿，你想看的我的吗？哈哈哈！");
   	if(A.Mapx[3][x][y]==76)Use1.LowPrint("啊啊啊啊！有变态啊！！");
   	if(A.Mapx[3][x][y]==77)
   	{
   		if(A.sfjq==0)
		{ 
			system("cls");
			Use1.LowPrint("Hello,月雩");
			cout<<endl<<endl;
			Use1.LowPrint("突然，一阵声音传入了你的耳朵");
			cout<<endl<<endl;
			Use1.LowPrint("你转头一看，竟是自己5年未曾相见的小学同学！");
			cout<<endl<<endl;
			Use1.LowPrint("好久不见啊兄嘚，你怎么会在这里？");
			cout<<endl<<endl;
			Use1.LowPrint("哈哈哈，这不来逛逛商场吗");
			cout<<endl<<endl;
			Use1.LowPrint("真是听君一席话如听一席话啊！你暗自腹诽");
			cout<<endl<<endl;
			Use1.LowPrint("突然，你想到一个严肃的问题……");
			cout<<endl<<endl;
			Use1.LowPrint("自己身上没钱了！！这可怎么在社会上厮混啊！");
			cout<<endl<<endl;
			Use1.LowPrint("“那个，好兄弟”，你扭扭捏捏，面露害羞之色（雾），“最近你朋友我囊中羞涩，您看能否……？”");
			cout<<endl<<endl;
			Use1.LowPrint("行啦，爸爸答应了！说吧，要多少？");
			cout<<endl<<endl;
			Use1.LowPrint("你想了想，认为还是多要一点为妙（游戏设定 嘿嘿）");
			cout<<endl<<endl;
			Use1.LowPrint("2000怎么样？你兴奋地捏着衣角，差点吼了出来");
			cout<<endl<<endl;
			Use1.LowPrint("啊这……我只有 1998 RMB了……就只有先借你这些了……对不住了啊兄弟！（微笑emoji）");
			cout<<endl<<endl;
			Use1.LowPrint("行行行，有钱就行！你笑呵呵地接过了钱，转身便离去");
			cout<<endl<<endl;Use1.LowPrint("喂，月雩，小心啊！这里很危险的！同学在后面大声叫着,还有！");
			SetConsoleTextAttribute(hout,12);
			Use1.LowPrint("不要乱花钱！不然你过不了关！！");
			SetConsoleTextAttribute(hout,7);
			Use1.LowPrint("哈哈");
			cout<<endl<<endl;system("pause");PauseFlag=1;A.things[++A.numt]=12,A.pd_thing[12]=A.numt,A.thing_num[12]+=1998;A.sfjq=1;
		}
		else Use1.LowPrint("我没钱！！死开！！哈哈哈。。。");
	} 
   	if(A.Mapx[3][x][y]==78)Use1.LowPrint("可能是男厕所");
   	if(A.Mapx[3][x][y]==79)Use1.LowPrint("可能是女厕所");
   	if(A.Mapx[3][x][y]==80)Use1.LowPrint("把头贴近墙面，你能听见对面传来的嘘嘘声……我为什么要这样做？？！！！");
		
	}

	else Use1.LowPrint("无效的移动！");
	
	Sleep(250);cout<<"\n";
	if(!PauseFlag)system("pause"); 
}//注意，如果因为要切换屏幕，有了system("pause")，那么最后一行的system("pause")是不用的，用 PauseFlag 变量记录 

void Operate2::game_zhuaxiaotou(int dd_x,int dd_y)
{ 
	system("cls");
	Use1.LowPrint("那个……同学，你能帮我找回钱包吗？我的钱包刚被偷了！那名学生说着就要哭出声来");
	cout<<endl<<endl;
	Use1.LowPrint("行啦别哭啦，你安慰着");
	cout<<endl<<endl;
	Use1.LowPrint("“那，你愿意帮助我吗？”（1 for yes）");
	cout<<endl<<endl;Use1.LowPrint("是否接受（建议在 精力值>100时接受任务，当前精力值：");
	cout<<A.jlz;Use1.LowPrint("）"); 
	char asdfqwer;
	asdfqwer=ReadInputKey();
	if(asdfqwer=='1')
	{
		cout<<endl<<endl;
		Use1.LowPrint("我答应啦！");
		cout<<endl<<endl;
		Use1.LowPrint("耶！那狗贼就在 [街道] 上闲逛，快去吧！mua~(将自动传送至街道)");
		cout<<endl<<endl;
		system("pause");
	}
	else
	{
		cout<<endl;
		Use1.LowPrint("你看了看正午的烈阳，道：对不起啊，我妈妈叫我回家吃晚饭了！");
		cout<<endl<<endl;
		Use1.LowPrint("呜呜呜呜……你听着哭声，有种说不出的难过");
		cout<<endl<<endl;system("pause"); 
		return;
	}
	system("cls");
	A.dx=3,A.dy1=17,A.dy2=18;
	HANDLE hout=GetStdHandle(STD_OUTPUT_HANDLE);
	int dx_xiaotou=14,dy1_xiaotou=21,dy2_xiaotou=22;
	while(1)
	{
		Place(2);
		int count=0; 
		for(int i=1;i<=18;i++)
		{
			for(int j=0;j<A.Map[2][i].size();j++)
			{
				if(i==A.dx&&j==A.dy1){count++,SetConsoleTextAttribute(hout,12);cout<<"我";SetConsoleTextAttribute(hout,7);}
				if(i==dx_xiaotou&&j==dy1_xiaotou){count++,SetConsoleTextAttribute(hout,10);cout<<"贼";SetConsoleTextAttribute(hout,7);}
				if(!count)cout<<A.Map[2][i][j];
				if(count)count++;
				if(count==3)count=0;
			}
			if(i==6)cout<<"                          背包[B]";
			if(i==8)cout<<"                          存/读档[C]";
			if(i==10)cout<<"                          退出[R]";
			if(i==12)cout<<"                          回家[H]";
			if(A.xwsf==1&&i==14)cout<<"                          修炼[P]"; 
			if(i==16) cout<<"              游戏指南：通过触碰来触发剧情";
			cout<<endl;
		}
		cout<<"\n_______________________\n\n";
		if(A.jlz<=1){Use1.Return(2);} 
		else
		{
			A.yd[0]=ReadInputKey();
			if(IsKey(A.yd[0],'w'))
			{
				if(A.Mapx[2][A.dx-1][A.dy1]!=0||A.Mapx[2][A.dx-1][A.dy2]!=0)Use1.LowPrint("还搁这闲逛呢！快去抓贼！！");
				else A.dx--,A.jlz--;
				
			}
			else if(IsKey(A.yd[0],'s'))
			{
				if(A.Mapx[2][A.dx+1][A.dy1]!=0||A.Mapx[2][A.dx+1][A.dy2]!=0)Use1.LowPrint("还搁这闲逛呢！快去抓贼！！");
				else A.dx++,A.jlz--;
			}
			else if(IsKey(A.yd[0],'a'))
			{
				if(A.Mapx[2][A.dx][A.dy1-1]!=0||A.Mapx[2][A.dx][A.dy2-1]!=0)Use1.LowPrint("还搁这闲逛呢！快去抓贼！！");
				else A.dy1--,A.dy2--,A.jlz--;
			}			
			else if(IsKey(A.yd[0],'d'))
			{//cout<<A.dy2<<endl;
				if(A.Mapx[2][A.dx][A.dy1+1]!=0||A.Mapx[2][A.dx][A.dy2+1]!=0)Use1.LowPrint("还搁这闲逛呢！快去抓贼！！");
				else A.dy1++,A.dy2++,A.jlz--;
			}
			else if(IsKey(A.yd[0],'b'))Use1.beibao(2,2,2);
			else if(IsKey(A.yd[0],'r'))exit(0);
			else if(IsKey(A.yd[0],'h')){Use1.Returnx(2);}
			else if(IsKey(A.yd[0],'c'))Use1.SaveData();
		}//cout<<dx_xiaotou<<"  "<<dy1_xiaotou<<endl;system("pause");
		int hhjj=abs(dx_xiaotou-A.dx)+abs(dy1_xiaotou-A.dy1); 
		if((A.dx==dx_xiaotou&&A.dy2+1==dy1_xiaotou)||(A.dx==dx_xiaotou&&A.dy1-1==dy2_xiaotou)||(abs(A.dx-dx_xiaotou)==1&&A.dy1==dy1_xiaotou)||(abs(A.dx-dx_xiaotou)==1&&A.dy1==dy2_xiaotou)||(abs(A.dx-dx_xiaotou)==1&&A.dy2==dy1_xiaotou))
		break;
		int num_jishu=0,pd_oop=0;
		//cout<<fwww<<" "<<dfwf<<endl;system("pause");
		if(A.Mapx[2][dx_xiaotou+1][dy2_xiaotou]==0&&A.Mapx[2][dx_xiaotou+1][dy1_xiaotou]==0&&(abs(dx_xiaotou+1-A.dx)+abs(dy2_xiaotou-A.dy2))>hhjj){dx_xiaotou++;pd_oop=1;}
		else if(A.Mapx[2][dx_xiaotou-1][dy2_xiaotou]==0&&A.Mapx[2][dx_xiaotou-1][dy1_xiaotou]==0&&(abs(dx_xiaotou-1-A.dx)+abs(dy2_xiaotou-A.dy2))>hhjj){dx_xiaotou--;pd_oop=1;}
		else if(A.Mapx[2][dx_xiaotou][dy2_xiaotou+1]==0&&(abs(dx_xiaotou-A.dx)+abs(dy2_xiaotou+1-A.dy2))>hhjj){dy1_xiaotou++,dy2_xiaotou++;pd_oop=1;}
		else if(A.Mapx[2][dx_xiaotou][dy2_xiaotou-1]==0&&(abs(dx_xiaotou-A.dx)+abs(dy2_xiaotou-1-A.dy2))>hhjj){dy1_xiaotou--,dy2_xiaotou--;pd_oop=1;}
		
		if(pd_oop==0)
		{
			if(A.Mapx[2][dx_xiaotou+1][dy2_xiaotou]==0&&A.Mapx[2][dx_xiaotou+1][dy1_xiaotou]==0&&(abs(dx_xiaotou+1-A.dx)+abs(dy2_xiaotou-A.dy2))==hhjj){dx_xiaotou++;pd_oop=1;}
			else if(A.Mapx[2][dx_xiaotou-1][dy2_xiaotou]==0&&A.Mapx[2][dx_xiaotou-1][dy1_xiaotou]==0&&(abs(dx_xiaotou-1-A.dx)+abs(dy2_xiaotou-A.dy2))==hhjj){dx_xiaotou--;pd_oop=1;}				
			else if(A.Mapx[2][dx_xiaotou][dy2_xiaotou+1]==0&&(abs(dx_xiaotou-A.dx)+abs(dy2_xiaotou+1-A.dy2))==hhjj){dy1_xiaotou++,dy2_xiaotou++;pd_oop=1;}
			else if(A.Mapx[2][dx_xiaotou][dy2_xiaotou-1]==0&&(abs(dx_xiaotou-A.dx)+abs(dy2_xiaotou-1-A.dy2))==hhjj){dy1_xiaotou--,dy2_xiaotou--;pd_oop=1;}
		}
		if(pd_oop==0)
		{
			if(A.Mapx[2][dx_xiaotou+1][dy2_xiaotou]==0&&A.Mapx[2][dx_xiaotou+1][dy1_xiaotou]==0&&(abs(dx_xiaotou+1-A.dx)+abs(dy2_xiaotou-A.dy2))==hhjj-1){dx_xiaotou++;pd_oop=1;}
			else if(A.Mapx[2][dx_xiaotou-1][dy2_xiaotou]==0&&A.Mapx[2][dx_xiaotou-1][dy1_xiaotou]==0&&(abs(dx_xiaotou-1-A.dx)+abs(dy2_xiaotou-A.dy2))==hhjj-1){dx_xiaotou--;pd_oop=1;}			
			else if(A.Mapx[2][dx_xiaotou][dy2_xiaotou+1]==0&&(abs(dx_xiaotou-A.dx)+abs(dy2_xiaotou+1-A.dy2))==hhjj-1){dy1_xiaotou++,dy2_xiaotou++;pd_oop=1;}
			else if(A.Mapx[2][dx_xiaotou][dy2_xiaotou-1]==0&&(abs(dx_xiaotou-A.dx)+abs(dy2_xiaotou-1-A.dy2))==hhjj-1){dy1_xiaotou--,dy2_xiaotou--;pd_oop=1;}
	
			
		}
		system("cls");
	}
	system("cls");
	Sleep(1000);
	Use1.LowPrint("你把从贼身上抢回来的钱包还给那同学");
	cout<<endl<<endl; 
	Use1.LowPrint("太感谢啦！！我也没什么拿的出手的，唔，就送你根绳子吧（脸红）");
	cout<<endl<<endl;
	Use1.LowPrint("获得 [绳子]");A.things[++A.numt]=10,A.pd_thing[10]=A.numt,A.thing_num[10]++;
	cout<<endl<<endl;system("pause");
	A.dx=dd_x,A.dy1=dd_y,A.dy2=A.dy1+1;A.zxtsf=1;
} 

void Operate2::mijing()
{
	system("cls");
	
	Use1.Print("[提示]：快速修炼是用精力值换取修为，比例为1:1");
	int xiuweizhihuanqu=0;
	cout<<endl<<endl;
	Use1.Print("请问需要多少修为呢（当前精力值 ");
	cout<<A.jlz;Use1.Print("）：");
	cin>>xiuweizhihuanqu;
	cout<<endl;
	if(xiuweizhihuanqu<=0) Use1.LowPrint("转化失败！！");
	else if(xiuweizhihuanqu>A.jlz)Use1.LowPrint("精力不足！！");
	else 
	{
		A.jlz-=xiuweizhihuanqu;
		A.xwz+=xiuweizhihuanqu;
		Use1.LowPrint("转化成功！！");
	}
	cout<<endl<<endl;
	system("pause");
	 
} 

void Operate2::toMap(int op){
	if(op==1&&!A.ddd){
		Place(op);
		DrawPlayerMapRows(op,false,"              ");
		cout<<"\n_______________________\n\n";
		HANDLE hout=GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hout,3);
		Use1.LowPrint("通过[WSAD]移动");cout<<endl;
		SetConsoleTextAttribute(hout,7);
		system("pause");A.ddd=1;	
	}
	Draw_Map(op,op);
}

void Operate2::Changexy(int op){

	switch(op)
	{
		case 1:SetPlayerPosition(10,27);break;
		case 2:SetPlayerPosition(9,20);break;
		case 3:SetPlayerPosition(10,27);break;
		case 4:SetPlayerPosition(10,20);break;
		case 5:SetPlayerPosition(7,27);break;
		case 6:SetPlayerPosition(10,27);break;
		case 7:SetPlayerPosition(9,20);break;
		case 9:SetPlayerPosition(6,24);break;
		case 11:SetPlayerPosition(10,27);break;
		case 20:SetPlayerPosition(12,12);break;
	}
/*
	if(op==13)A.dx=,A.dy1=,A.dy2=;
	if(op==14)A.dx=,A.dy1=,A.dy2=;
	if(op==15)A.dx=,A.dy1=,A.dy2=;
	if(op==16)A.dx=,A.dy1=,A.dy2=;
	if(op==17)A.dx=,A.dy1=,A.dy2=;
	if(op==18)A.dx=,A.dy1=,A.dy2=;
	if(op==19)A.dx=,A.dy1=,A.dy2=;
	未开启 
*/
	//需要继续添加 
}

void Operate2::Transmit(int op){
	HANDLE hout=GetStdHandle(STD_OUTPUT_HANDLE);
	system("cls");
	Use1.LowPrint("请问您想传送到什么地方？\n");
	int tx=0;
	for(int i=1;i<=20;i++){
		if(i==8||i==10||i==12)continue;
		SetConsoleTextAttribute(hout,7);
		tx++;cout<<"["<<tx<<"] "; 
		if(A.Map_Find[i]){
			SetConsoleTextAttribute(hout,7);
			cout<<A.Map_name[i]<<endl;
		}
		else {
			SetConsoleTextAttribute(hout,4);
			cout<<"暂未解锁\n";
		}
	}
	SetConsoleTextAttribute(hout,7);
	Use1.LowPrint("请选择：");
	int Moveto;
	cin>>Moveto;
	Moveto=ActualMapIdFromChoice(Moveto);
	if(Moveto>=1&&Moveto<=A.Map_allnum){
		if(!A.Map_Find[Moveto]){
			Use1.LowPrint("地图暂未解锁！！\n");
			system("pause");
			return;
		}
		if(GetWhere(Moveto)!=GetWhere(op)){
			Use1.LowPrint("似乎……有一股神秘的力量阻挡了这次传送……\n");
			Sleep(500);
			Use1.LowPrint("传送失败\n");
			system("pause");
			return;
		}
		Use1.LowPrint("这将会消耗您 ");
		cout<<A.Map_dis[op][Moveto]*75;
		Use1.LowPrint(" 点体力\n");
		Use1.LowPrint("确定吗？");
		cout<<"（当前精力值为 "<<A.jlz<<"）\n";
		cout<<"[1] 确定 [2] 返回\n";
		cout<<"请输入：";
		char opxx[1000];
		cin>>opxx;
		if(opxx[0]=='1'){
			if(A.jlz>=A.Map_dis[op][Moveto]*75+2){
				A.jlz-=A.Map_dis[op][Moveto]*75;
				Changexy(Moveto);
				toMap(Moveto);
			}
			else {
				Use1.LowPrint("您的精力值不足！");
				return;
			}
		}
	}
	else {
		Use1.LowPrint("编号错误！\n");
		system("pause");
		return;
	}
} 

void Operate2::Move(int op,int now){
	A.yd[0]=ReadInputKey();
	AddWalkingCultivation();
	auto moveVertical=[&](int delta){
		int nextX=A.dx+delta;
		if(A.Mapx[op][nextX][A.dy1]!=0||A.Mapx[op][nextX][A.dy2]!=0){
			if(A.Mapx[op][nextX][A.dy1]!=0)chuli(now,nextX,A.dy1); 
			else chuli(now,nextX,A.dy2); 
		}
		else A.dx+=delta,A.jlz--;
	};
	auto moveHorizontal=[&](int delta){
		int leftY=A.dy1+delta;
		int rightY=A.dy2+delta;
		if(A.Mapx[op][A.dx][leftY]!=0||A.Mapx[op][A.dx][rightY]!=0){
			if(delta<0)chuli(now,A.dx,leftY);
			else chuli(now,A.dx,rightY);
		}
		else A.dy1+=delta,A.dy2+=delta,A.jlz--;
	};
	if(IsKey(A.yd[0],'w'))moveVertical(-1);
	else if(IsKey(A.yd[0],'s'))moveVertical(1);
	else if(IsKey(A.yd[0],'a'))moveHorizontal(-1);
	else if(IsKey(A.yd[0],'d'))moveHorizontal(1);
	else if(IsKey(A.yd[0],'b'))Use1.beibao(op,op,now);
	else if(IsKey(A.yd[0],'r'))Use1.Exit();
	else if(IsKey(A.yd[0],'h')){Use1.Returnx(op);}
	else if(A.xwsf==1&&IsKey(A.yd[0],'p'))Use2.mijing();
	else if(IsKey(A.yd[0],'c'))Use1.SaveData();
	else if(IsKey(A.yd[0],'t'))Transmit(op);
}

void Operate2::Draw_Map(int op,int now){
	system("cls");A.NowMap=op;
	A.Map_Find[op]=true;
	while(1)
	{
		Place(op);
		DrawPlayerMapRows(op,true,"                 ");
		cout<<"\n_______________________\n\n";
		if(A.jlz<=1){Use1.Return(op);} 
		else Move(op,op);
		system("cls");
	}	
}

int Operate2::GetWhere(int op){
	if(op<=9||op==20)return 1;//人界 
	if(op==12)return 3;//梦境 
	return 2;//神界 
	//继续添加 
}

