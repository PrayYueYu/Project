#ifndef DATA_H
#define DATA_H
#include <iostream>
#include <string>

using std::cout;
using std::string;

class Data_Single{
	protected:
		enum { DEFAULT_MAP_ALLNUM = 20 };
		int xwsf,xwz;//是否开启修为  /  修为值 
		int diyicichuansongmen;//是否第一次进入传送门 
		int xw,timey,timem,timed,jlz;//修为值 、年、月、日、精力值 
		int dx,dy1,dy2;//当前坐标(dx->多少行 ; dy->多少列   dy上会占两格,dy1在左 ,dy2在右)
		int xiaomaomihaogandu;//剩余 钱 数改为物品（wupin）数组！！！、小猫咪好感度（判断大结局是否帮助主角） 

		int mijingshifou;//是否开启秘境（自动刷经验） 
		bool ddd;//是否跳过教程 
		int sfgmye;//是否购买鱼饵（道具） 
		int sfjq,jqdf;//是否借了钱（只能借1次）  /   借钱被打了没 
		int yzsf,sfdh;//渔者对话是否结束（仅一次对话（关于渡河））    /    是否能渡河（集齐材料否？） 
		int cmsdcs;//触摸树的次数（3次获得树枝，且仅能获得一次） 
		int zxtsf;//抓小偷游戏是否完成 
		int HP,DE,MA,AT;//生命、防御、法力、攻击 の值 
		int caoweishifou;//传送阵启动的槽位是否安放晶石 
		int youxibeijingshifou;//是否解锁游戏背景
		int first_xiaoqu,first_sb;//第一次走入小区 否？ /  第几次触碰 人3？(剧情不同)  
		int NowMap;//上次存档在哪一张地图，存档专用 
		int Map_allnum;//当前拥有的地图总数 
	public:
		friend class Operate2;
		friend class Operate1;
		friend class MAIN;
		virtual void Prints(string s){
			cout<<s;
		}
		Data_Single(int I=DEFAULT_MAP_ALLNUM):Map_allnum(I){}// I 记得改一下 

};

class Data_Array{
	protected:
		enum {
			MAX_MAP_COUNT = 100,
			MAX_MAP_ROWS = 100,
			MAX_MAP_COLS = 100,
			MAX_COMMAND_COUNT = 10000,
			MAX_THING_COUNT = 10000
		};
		int Map_Find[MAX_MAP_COUNT];//是否开启地图
		string Map_name[MAX_MAP_COUNT];//地图地点名字
		int Map_dis[MAX_MAP_COUNT][MAX_MAP_COUNT];//两个地图间隔了几个地图 
		string Map[MAX_MAP_COUNT][MAX_MAP_ROWS];//地图数组，同下 
		int Mapx[MAX_MAP_COUNT][MAX_MAP_ROWS][MAX_MAP_COLS];//地图物品存储：地图编号，坐标x，坐标y 
		char yd[MAX_COMMAND_COUNT];//移动指令
		
		int things[MAX_THING_COUNT],thing_num[MAX_THING_COUNT],numt;//背包物品(链接 & 数量(每种) & 当前拥有不同种类物品的数量)
		string wupin[MAX_THING_COUNT];//背包物品(名称)
		int pd_thing[MAX_THING_COUNT];//判断物品是否被拿(储存数据为放入背包的编号(链接))	
		friend class Operate2;
		friend class Operate1;
		friend class MAIN;
}; 

class Data:public Data_Single,public Data_Array{
	public:
		void GetMap_dis();
		//以下变量暂未加入储存与获取函数，完成后将本句话移至后面 
		//以下函数在新的变量加入后需要继续添加 
		void Data_init();//初始化  需继续添加 
		void SaveDatax();//存档 需继续添加 
		bool GetData(string s="data.yue");//读档  需继续添加 
			private:
		bool LoadVersionedData(const string &savePath);
		bool LoadLegacyData(const string &savePath);
		void WriteVersionedData(const string &savePath);
		void WriteScalarFields(std::ostream &out);
		bool ApplyScalarField(const string &name,int value);
	public:
void Prints(string s)override{
			cout<<s;
		}
		Data(){
			Data_init();//地图/物品 初始化 
			GetData("newdata.yue");//从文档初始化其他数据 
			Data_Single();//构造函数初始化 Data_Single类 
		}
		//构造函数 初始化 
};



#endif



