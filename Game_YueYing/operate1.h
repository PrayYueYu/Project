#ifndef OPERATE1_H
#define OPERATE1_H
#include<bits/stdc++.h>
using namespace std;
class Operate1{//简单的比较杂的操作 
	protected:
		void chakanwupin(int id,int idx,int op,int now);//查看物品 
		void qiguaideshu(int id,int idx,int op,int now);
		void beibao(int id,int op,int now);//把物品存入背包 
		void shiyongwupin(int id,int idx,int op,int now);//使用物品 
		void xiugaibeibao(int id,int idx,int numberx);//修改背包数据 
		bool pdrn(int x);//判断润年 
		bool pdzq();//判断中秋 
		void Exit();
		void change_date();//修改日期，日期+1 
		void Return(int op);//回+恢复精力+改变日期 
		void Returnx(int op);//回到恢复精力的地方 
		void SaveData();//存档
		void kbread(char * ss);//_kbhit读入，判断有没有输入 		
		void LowPrint(string ss);//缓慢输出 
		void Print(string ss);//普通输出 
	public:	
		friend class Operate2;
		friend class Data;
		friend class MAIN;
};

#endif
