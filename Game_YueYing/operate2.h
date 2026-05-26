#ifndef OPERATE2_H
#define OPERATE2_H
class Operate2{//地图以及互动 
	protected:
		void Place(int op);//地点
		const char *GetMapTitle(int op);//地图标题
		const char *GetCultivationStage(int xwz);//修为阶段显示
		char ReadInputKey();//等待并读取按键
		bool IsKey(char key,char expected);//按键大小写判断
		void AddWalkingCultivation();//移动时增长修为
		void DrawPlayerMapRows(int op,bool showTransmit,const char *guidePrefix);//绘制地图主体与侧边提示
		int ActualMapIdFromChoice(int choice);//传送菜单编号转地图编号
		void SetPlayerPosition(int x,int y1);//设置玩家坐标
		void chuli(int op,int x,int y);//处理移动过程中遇到的物品
		void game_zhuaxiaotou(int dd_x,int dd_y);//抓小偷游戏，获得绳子
		void zhandoujiemian(int HP_x,int MA_x,int DE_x,int AT_x,int idxx);//战斗界面 (生命、法力、防御、攻击（敌人的）以及 敌人名字 编号)
		void Move(int op,int now);//自动移动到其他地图 
		void Draw_Map(int op/*实际在的地点(地点)*/,int now/*应该输出的地点(地图)*/);//输出地图界面 
		void mijing();//转化修为 
		void toMap(int op/*要去哪个地图*/);//切换地图快捷函数	
		//以下函数在新的变量加入后需要继续添加 
		int GetWhere(int op);//判断在 人界 还是 神界 还是 梦境 
		void Transmit(int op);//选择传送到哪个地图并进行传送 
		void Changexy(int op);//更改传送之后的坐标 
	public:
		friend class MAIN;
		friend class Operate1;
		friend class Data;
};

#endif
