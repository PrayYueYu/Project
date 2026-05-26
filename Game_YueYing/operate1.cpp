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
using namespace std;
extern Data A;
extern Operate1 Use1;
extern Operate2 Use2;

void Operate1::kbread(char * ss){
	while(!_kbhit()){}
	*ss=_getch();
}

void Operate1::LowPrint(string ss)//缓慢输出(收起)
{
	int PrintLenth=ss.size();
	for(int i=0;i<PrintLenth;i++){
		cout<<ss[i];
		Sleep(70);
	}
}

void Operate1::Print(string ss)//普通输出(收起)
{
	int PrintLenth=ss.size();
	for(int i=0;i<PrintLenth;i++)
		cout<<ss[i];
}

void Operate1::xiugaibeibao(int id,int idx,int numberx)//修改背包类容(移除)(背包中编号 & 根编号 & 消耗的数量) 
{
	if(!A.thing_num[idx])return;
	if(A.thing_num[idx]-numberx==0)
	{
		for(int i=id+1;i<=A.numt;i++)
			A.pd_thing[A.things[i]]=i-1,A.things[i-1]=A.things[i];
		A.numt--;
	}
	A.thing_num[idx]-=numberx;
}

bool Operate1::pdrn(int x)//判断闰年
{
	
	if((x%4==0&&x%100!=0)||x%400==0)return true;
	
	return false;
	
} 

bool Operate1::pdzq()//判断是否是中秋 
{
	
	if(A.timey==2004&&A.timem==9&&A.timed==28)return true;
	if(A.timey==2005&&A.timem==9&&A.timed==18)return true;
	if(A.timey==2006&&A.timem==10&&A.timed==6)return true;
	if(A.timey==2007&&A.timem==9&&A.timed==25)return true;
	if(A.timey==2008&&A.timem==9&&A.timed==14)return true;
	if(A.timey==2009&&A.timem==10&&A.timed==3)return true;
	if(A.timey==2010&&A.timem==9&&A.timed==22)return true;
	if(A.timey==2011&&A.timem==9&&A.timed==12)return true;
	if(A.timey==2012&&A.timem==9&&A.timed==30)return true;
	if(A.timey==2013&&A.timem==9&&A.timed==19)return true;
	if(A.timey==2014&&A.timem==9&&A.timed==8)return true;
	if(A.timey==2015&&A.timem==9&&A.timed==27)return true;
	if(A.timey==2016&&A.timem==9&&A.timed==15)return true;
	if(A.timey==2017&&A.timem==10&&A.timed==4)return true;
	if(A.timey==2018&&A.timem==9&&A.timed==24)return true;
	if(A.timey==2019&&A.timem==9&&A.timed==13)return true;
	if(A.timey==2020&&A.timem==10&&A.timed==1)return true;
	if(A.timey==2021&&A.timem==9&&A.timed==21)return true;
	if(A.timey==2022&&A.timem==9&&A.timed==10)return true;
	if(A.timey==2023&&A.timem==9&&A.timed==29)return true;
	if(A.timey==2024&&A.timem==9&&A.timed==17)return true;
	if(A.timey==2025&&A.timem==10&&A.timed==6)return true;//
	return false;
	
}

void Operate1::qiguaideshu(int id,int idx,int op,int now)//奇怪的书 の 查看 
{
	HANDLE hout=GetStdHandle(STD_OUTPUT_HANDLE);
	int ysx=1;//共7页 
	while(1)
	{
		system("cls");
		SetConsoleTextAttribute(hout,6);
		cout<<"                                            ["<<A.wupin[A.things[id]]<<"]"<<endl; 
		SetConsoleTextAttribute(hout,7);
		cout<<"____________________________________________________________________________________________________"<<endl<<endl;
		if(ysx==0){cout<<"已是第一页！";Sleep(1500);ysx++;continue;}
		if(ysx==1)cout<<"这真是个奇怪的世界...";
		if(ysx==2)cout<<"两条手臂、两条腿和一个头的奇怪物种竟然称霸了世界！";
		if(ysx==3)cout<<"我又是谁呢？？";
		if(ysx==4)cout<<"[空白页]";
		if(ysx==5)cout<<"[空白页]";
		if(ysx==6)cout<<"[空白页]";
		if(ysx==8){cout<<"已是最后一页！";Sleep(1500);ysx--;continue;}
		if(ysx==7)cout<<"满月之夜，梦神现世；携万年灵泉，即可招之";
		for(int i=1;i<=21-4;i++)cout<<endl;
		cout<<"_______________________\n\n";
		cout<<"[1] 上一页\n[2] 下一页\n[3] 返回\n请选择: ";
		char qqsd;cin>>qqsd;
		system("cls");
		if(qqsd=='1')ysx--;
		if(qqsd=='2')ysx++;
		if(qqsd=='3')break;
	}
	Use1.beibao(idx,op,now);
}

void Operate1::chakanwupin(int id,int idx,int op,int now)//查看物品 
{
	/*
	wupin[1]="卧室钥匙";wupin[2]="矿泉水";wupin[3]="奇怪的书";
	wupin[4]="五彩斑斓的水晶";
	wupin[5]="小泡芙",wupin[6]="啤酒",wupin[7]="面包";
	wupin[8]="逗猫棒"; wupin[9]="鱼饵";wupin[10]="绳子";
	wupin[11]="树枝";wupin[12]="软妹币";
	wupin[13]="状态良好的船桨";wupin[14]="损坏大半的船桨";
	wupin[16]="沉睡的七彩神玉";
	wupin[17]="《月影之眠》";
	*/
	if(id>A.numt){cout<<"编号错误！";Sleep(2500);return;}
	HANDLE hout=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hout,6);
	cout<<"                                            ["<<A.wupin[A.things[id]]<<"]"<<endl; 
	SetConsoleTextAttribute(hout,7);
	cout<<"____________________________________________________________________________________________________"<<endl<<endl;
	int count=4;
	if(A.things[id]==1)
		Print("“为什么我的钥匙会在盆栽里？”");
	if(A.things[id]==2)
	{
		Print("珍藏多年的矿泉水，闻上去有一股淡淡的清香，令人深陷其中，难以自拔(上面似乎写着……？**？=CE 7978？)");
	}
	if(A.things[id]==3)
	{
		count++;
		Print("一本奇怪的书...似乎以前没见过");
		cout<<endl;
		LowPrint("是否仔细察看? (1 for yes)");
		char dfghjk;cin>>dfghjk;
		if(dfghjk=='1')
		{
			system("cls");
			qiguaideshu(id,idx,op,now);
			system("cls");
		}
	}
	if(A.things[id]==4)
	{
		if(A.xwsf==0)Print("散发着彩光的晶石，不知道有什么用。（至少现在没用吧？）");
		if(A.xwsf)Print("似乎是神域中用来修炼的晶石？");
	}
	if(A.things[id]==6)Print("杰哥圣物：击伟酒，传说喝下后可以登dua郎了哦~~~");
	if(A.things[id]==7)
	{
		Print("那一天，阿伟想起了被杰哥玩弄的恐惧……");
		cout<<endl<<endl;
		Print("面包里传来了杰哥的声音：我还不饿，请你们吃！！（狞笑）");
	}
	if(A.things[id]==8)
	{
		Print("好想用长长的大棒子逗逗可耐的小猫咪~");
	}
	if(A.things[id]==9)
	{
		Print("总所周知，生物都是从鱼儿进化而来……（你似乎有了些想法萌生……）");
		cout<<endl<<endl;
		Print("那，人类，会不会也会被 [鱼饵] 钓起呢？……");
		cout<<endl<<endl;
		Print("还是说，人类本身就是池中之鱼呢？呵呵……………………");
	}
	if(A.things[id]==10)
	{
		Print("这是一根十分结实的绳子！！");
		cout<<endl<<endl;
		Print("可能也是sm必备之物！！");
	}
	if(A.things[id]==11)
	{
		Print("这个游戏的树怎么这么不牢固啊！！");
		cout<<endl<<endl;
		Print("才摇两下就断了！真的太逊了！！！");
		cout<<endl<<endl;
		Print("树：你有没有树枝啊！！油饼食不食？香精煎鱼食不食？"); 
	}
	if(A.things[id]==12)
	{
		Print("软软糯糯的妹妹baby~诶嘿嘿嘿……好可爱！");
		cout<<endl<<endl;
		Print("（这个游戏作者可能出什么问题了）");
	}
	if(A.things[id]==13)
	{
		Print("应该……会很结实吧？"); 
	}
	if(A.things[id]==14)
	{
		Print("看起来一碰就会断掉的船桨，希望不要出问题！！");
	}
	if(A.things[id]==16)
	{
		Print("发着圣光的石头……好像陷入了睡眠一般……一呼一吸之间，流光婉转……");
	}
	if(A.things[id]==17)
	{
		Print("书中第一页写着：思君心切，故作此篇，待来日，君临天下……");
		cout<<endl<<endl;
		Print("书中第二页写着：《月影之眠》，万年而著成，唯月族、影族之人可修习之，神界三大功法之一");
		cout<<endl<<endl;
		Print("书中第三页为修炼之法（在地图中每走一步修为增加1，境界提升修为增长也会提升）");
		cout<<endl<<endl;
		Print("书中第四页写着《月影之眠》专属法诀，为神界九大法诀之一");
	}
	for(int i=1;i<=21-count;i++)cout<<endl;
	cout<<"_______________________\n\n";
	cout<<"[0]:返回"<<endl;
	char sert;cin>>sert; 
	Use1.beibao(idx,op,now);
}

void Operate1::beibao(int id,int op,int now)//背包界面(返回时需要的场景编号 和 场景本身就有的 op & now)
{
	HANDLE hout=GetStdHandle(STD_OUTPUT_HANDLE);
	system("cls");
	char ydf;int asd=0;
	while(true)
	{
		SetConsoleTextAttribute(hout,6);
		cout<<"                                            [背包]"<<endl; 
		SetConsoleTextAttribute(hout,7);
		cout<<"____________________________________________________________________________________________________"<<endl<<endl;
		int i=1,count=3;
		while(1)
		{
			if(i>A.numt)break;
			printf("%d: ",i);
			cout<<A.wupin[A.things[i]];
			cout<<"  ×"<<A.thing_num[A.things[i]]<<endl;
			count++;i++;
		}
		if(!A.thing_num[A.things[1]]){count++;cout<<"背包空空如也呢！";}
		for(int i=1;i<=21-count;i++)cout<<endl;
		cout<<"_______________________\n\n";
		if(!asd)cout<<"[1] 使用物品\n[2] 查看物品\n[3] 返回\n请选择: ";
		if(!asd)
		{
			char xxx;cin>>xxx;//cout<<"YES!"<<endl;
			if(xxx=='1'){system("cls");asd=3;continue;}
			if(xxx=='2'){system("cls");asd=2;continue;}
			else break;
		}
		else if(asd==2)
		{
			cout<<"请选择查看的物品编号(0为退出): ";
			int xxx;cin>>xxx;
			system("cls");asd=0;
			if(xxx==0)continue; 
			Use1.chakanwupin(xxx,id,op,now);
			system("cls");
		}
		else if(asd==3)
		{
			cout<<"请选择使用的物品编号(0为退出)：";
			int xxx;cin>>xxx;
			system("cls");asd=0;
			if(xxx==0)continue;
			Use1.shiyongwupin(xxx,op,id,now);
			system("cls");
		}
	}	
	Use2.toMap(op);
}

void Operate1::shiyongwupin(int id,int idx,int op,int now)//使用物品 (★：id只是背包中物品的位置序号！！e.g.:背包中矿泉水从上往下数是第5个，而设定值矿泉水是第2个，所以id=5，things[id]=2)
{ 
	if(A.thing_num[A.things[id]]==0)
	{
		LowPrint("你暂时还没有这件物品哦~");
		Sleep(1000);
	}
	
	else if(A.things[id]==4&&A.dx==6&&A.dy1==48&&A.caoweishifou==0)
	{
		LowPrint("是否将晶石放入槽内？(1 for yes)：");
		char xxx;cin>>xxx;	
		if(xxx=='1')
		{
			cout<<endl;
			LowPrint("叮~~");cout<<endl<<endl;
			LowPrint("你听见奇怪的声音自远处传来，不知发生了什么");
			A.caoweishifou=1;
		//	Iden newI={};
		//	A=A|newI;
			Use1.xiugaibeibao(A.pd_thing[4],4,5);
			Sleep(1000);
		}
		else LowPrint("你觉得有些不妥，随即又将晶石放回了背包");
	} 
	
	else if(A.things[id]==2&&A.thing_num[2]!=0&&((A.dx==13&&A.dy1==33)||(A.dx==14&&A.dy1==33))&&A.caoweishifou==2)
	{
		LowPrint("是否将水倒入湖中？（1 for yes）：");
		int xxx;cin>>xxx;
		if(xxx==1&&A.thing_num[2]>=2) 
		{
			cout<<endl;
		//	Iden newI={};
		//	A=A|newI;
			//Use1.xiugaibeibao();
			Use1.xiugaibeibao(A.pd_thing[2],2,1);
			LowPrint("你将矿泉水倒入了干涸的湖内");
			cout<<endl<<endl;
			Sleep(500);
			system("cls");
		}
		else if(xxx==1&&A.thing_num[2]==1)
		{
			cout<<endl;
		//	Iden newI={};
		//	A=A|newI;
			Use1.xiugaibeibao(A.pd_thing[2],2,1);
			LowPrint("你将最后一瓶矿泉水倒入干涸的湖内");
			cout<<endl<<endl;
			LowPrint("……"); 
			cout<<endl<<endl;
			LowPrint("…………"); 
			cout<<endl<<endl;
			LowPrint("………………"); 
			Sleep(2000);
			cout<<endl<<endl;
			LowPrint("突然，人影猛地一滞，转过身来。");
			cout<<endl<<endl;
			LowPrint("在略显苍白而又娇艳无比的脸上，两只黑洞洞的眼睛死死地盯着你，似乎……渗出了丝丝粘稠的黑色液滴……");
			cout<<endl<<endl;
			LowPrint("你想逃跑，可发现身体已然动弹不得，只能睁大眼睛恐惧地盯着那道绝美的身影");
			cout<<endl<<endl;
			LowPrint("那道身影缓缓地向你飘来，她的红唇贴紧了你的耳垂，似乎想要说些什么……");
			cout<<endl<<endl;
			LowPrint("“月，我终于，找到你了……”");
			cout<<endl<<endl;
			LowPrint("“我会永远等着你……哪怕万年不曾相见……”");
			cout<<endl<<endl;
			LowPrint("身影的话如同魔音，让你感到头晕目眩，好像脑子里有什么东西裂开了……（解锁游戏背景，可在重入轮回时查看）");
			cout<<endl<<endl;
			LowPrint("你苦苦支撑着不让自己晕倒，而随着一股暖流流入体内，庞大的信息瞬间冲入脑内，令你无法抵抗，彻底晕倒过去……(可在醒来后去背包查看)");
			A.youxibeijingshifou=1;
			cout<<endl<<endl;
			A.things[++A.numt]=17,A.pd_thing[17]=A.numt,A.thing_num[17]+=1;
			//           十位: 0         1         2         3         4         5
			//                 012345678901234567890123456789012345678901234567890123       //方便计算坐标 
			A.Map[20][3]="▕ 树                                             树▏";
			A.Map[20][4]="▕ 树            亻？                             树▏";
			A.Map[20][5]="▕ 树            ？门                             树▏";
			A.Map[20][6]="▕ 树                                             对▏";
			A.Map[20][7]="▕ 树                                             树▏";
			A.Map[20][8]="▕ 小                                             树▏";
			for(int i=4;i<=5;i++)
				for(int j=17;j<=20;j++)
					A.Mapx[20][i][j]=114; 
			A.xwsf=1;A.timey=2022,A.timem=3,A.timed=20;A.xwz=0;
			system("pause");
			Use2.toMap(20); 
		}
		else if(xxx==0) LowPrint("你觉得此事过于诡异，还是不要乱动的好");	
	}
	
	else 
	{
		LowPrint("最好还是不要乱用东西！！重开多麻烦吖，你说是吧！");
		Sleep(1500);
	}

} 

void Operate1::change_date()
{
	int monthDays[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
	if(pdrn(A.timey))monthDays[2]=29;
	A.timed++;
	if(A.timed>monthDays[A.timem])
	{
		A.timed=1;
		A.timem++;
		if(A.timem>12)
		{
			A.timem=1;
			A.timey++;
		}
	}
} 

void Operate1::Return(int op){
	int Where=Use2.GetWhere(op);
	if(Where==1){
		Use1.LowPrint("精力耗尽，即将自动回家！（休息可恢复精力）");
		A.dx=15,A.dy1=13,A.dy2=14;
		Use1.change_date();
		A.jlz=500;Use2.toMap(1);
	}
	if(Where==2){
		Use1.LowPrint("精力耗尽，即将自动返回万道城！（休息可恢复精力）");
		A.dx=8,A.dy1=8,A.dy2=9;change_date();A.jlz=500;Use2.toMap(11);		
	} 
}

void Operate1::Returnx(int op){
	int Where=Use2.GetWhere(op);
	if(Where==1){
		Use1.LowPrint("是否要回家？\n");
		Use1.LowPrint("[1]是 [2]否\n");
		cout<<"请选择：";
		char huijiaflag;cin>>huijiaflag;
		if(huijiaflag!='1')return;
		A.dx=15,A.dy1=13,A.dy2=14;Use2.toMap(1);
	}
	if(Where==2){
		Use1.LowPrint("是否要回万道城？\n");
		Use1.LowPrint("[1]是 [2]否\n");
		cout<<"请选择："; 
		char huichengflag;cin>>huichengflag;
		if(huichengflag!='1')return;
		A.dx=8,A.dy1=8,A.dy2=9;Use2.toMap(11);
	}
} 

void Operate1::SaveData(){
	Use1.LowPrint("[1]存档 [2]读档 [3]返回\n");
	cout<<"请选择：";
	char SaveorGet;cin>>SaveorGet;
	if(SaveorGet=='1'){
		Use1.LowPrint("确定要存档？（会覆盖上一次存档）\n");
		Use1.LowPrint("[1]是 [2]否\n");
		cout<<"请选择：";
		char Saveflag;cin>>Saveflag;
		if(Saveflag!='1')return;
		A.SaveDatax();
	}
	else if(SaveorGet=='2'){
		Use1.LowPrint("确定要读档？\n");
		Use1.LowPrint("[1]是 [2]否\n");
		cout<<"请选择：";
		char Getflag;cin>>Getflag;
		if(Getflag!='1')return;
		A.GetData();Use2.toMap(A.NowMap);
	}
	else if(SaveorGet=='3'){return;} 
	else {Use1.LowPrint("无效输入！");Sleep(700);}
	/*存档代码*/
}

void Operate1::Exit(){
	HANDLE hout=GetStdHandle(STD_OUTPUT_HANDLE); 
	system("cls");
	Use1.LowPrint("真的要退出游戏吗？");
	cout<<endl<<"[1]确定 [2]还是算了\n";
	cout<<"请选择：";
	cin>>A.yd;
	if(A.yd[0]!='1')return;
	system("cls");
	for(int i=1;i<=6;i++)
	{
		SetConsoleTextAttribute(hout,4);
		if(i%2)Use1.Print("即将退出游戏！");
		else Sleep(300);
		Sleep(200);
		system("cls");
	}
	SetConsoleTextAttribute(hout,7);
	exit(0); 
}
