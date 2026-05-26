#ifndef MAINX_H
#define MAINX_H
#include<bits/stdc++.h>
using namespace std;
class MAIN{//简单的比较杂的操作 
	public:
		void Slowx();
		void Died();
		void kongbai(int op,int now);
		void Mapx_kongbai(int op1,int op2);//空白地图 
		void First(int op);//首次进入 
		void Openy();//开始-2 
		void jieshaogame(int op);//介绍 
		void OpEnx(int SkipFlag,int op);//开始-1 
		void Mengjing();//梦境 
		bool GetSkip();//跳过开头 
		void Start();//开始 
};

#endif
