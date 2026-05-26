#include<bits/stdc++.h>
#include<time.h>
#include <windows.h>
#include <unistd.h>//获取文件地址 
#include "operate1.h" 
#include "operate2.h" 
#include "Data.h"
extern Operate1 Use1;

namespace {
const char kDataDirectory[] = "Datas";
const char kDefaultSaveFile[] = "data.yue";
const char kVersionedSaveMagic[] = "YUEYING_SAVE_V2";
const char kVersionLine[] = "version=2";
const char kScalarsSection[] = "[Scalars]";
const char kMapStringsSection[] = "[MapStrings]";
const char kMapTilesSection[] = "[MapTiles]";
const char kBagSection[] = "[Bag]";
const char kMapFindV2Section[] = "[MapFind]";
const char kMapStringSection[] = "NowisMapstring:";
const char kMapDataSection[] = "NowisMapdata:";
const char kBagDataSection[] = "NowisBagdata:";
const char kMapFindSection[] = "NowisMapFind:";
const char kPathSeparator = '\\';
const int kFloydMapLimit = 40;
const int kSaveScalarFieldCount = 30;
const int kSavedMapMaxIndex = 30;
const int kSavedMapRowMax = 20;
const int kSavedMapColMax = 60;
const int kSavedMapRowCount = kSavedMapRowMax + 1;
const int kSavedBagMaxIndex = 200;
const int kReadIntBufferSize = 100;

enum SaveSection {
	SAVE_SECTION_SCALAR = 0,
	SAVE_SECTION_MAP_STRING = 1,
	SAVE_SECTION_MAP_DATA = 2,
	SAVE_SECTION_BAG_DATA = 3,
	SAVE_SECTION_MAP_FIND = 4
};

string BuildDataPath(const string &fileName) {
	char cwd[256] = "";
	getcwd(cwd, 256);
	string path = cwd;
	path += kPathSeparator;
	path += kDataDirectory;
	path += kPathSeparator;
	path += fileName;
	return path;
}
}
void Data::GetMap_dis(){//Floyed最短路 

	memset(Map_dis,127/3,sizeof(Map_dis));
	
	Map_dis[1][5]=Map_dis[5][1]=1;Map_dis[5][2]=Map_dis[2][5]=1;Map_dis[2][3]=Map_dis[3][2]=1;Map_dis[2][6]=Map_dis[6][2]=1;
	Map_dis[2][7]=Map_dis[7][2]=1;Map_dis[2][9]=Map_dis[9][2]=1;Map_dis[9][4]=Map_dis[4][9]=1;Map_dis[4][20]=Map_dis[20][4]=1;
	Map_dis[11][13]=Map_dis[13][11]=1;Map_dis[13][17]=Map_dis[17][13]=1;Map_dis[11][14]=Map_dis[14][11]=1;Map_dis[14][15]=Map_dis[15][14]=1;
	Map_dis[15][16]=Map_dis[16][15]=1;Map_dis[11][18]=Map_dis[18][11]=1;Map_dis[18][19]=Map_dis[19][18]=1;
	//需要继续添加，地图之间的关系 
	for(int i=1;i<=Map_allnum;i++)Map_dis[i][i]=0;
	for(int k=1;k<=kFloydMapLimit;k++)
		for(int i=1;i<=kFloydMapLimit;i++)
			for(int j=1;j<=kFloydMapLimit;j++)
				Map_dis[i][j]=min(Map_dis[i][j],Map_dis[i][k]+Map_dis[k][j]);
}

void Data::Data_init(){//初始化，初始化数据，将地图存入数组(★)

	
	for(int i=0;i<=90;i++)for(int j=0;j<=90;j++)Map[i][j]="",wupin[i]="",Map_name[i]="";
	
	Map_name[1]="卧室";Map_name[2]="街道";Map_name[3]="商场"; Map_name[4]="小溪边"; Map_name[5]="小区";
	Map_name[6]="学校";Map_name[7]="公交车站";Map_name[9]="花园";Map_name[11]="万道城"; Map_name[12]="梦境"; 
	Map_name[13]="元府"; Map_name[14]="孤霞山脉"; Map_name[15]="孤山野村";Map_name[16]="远古森林";
	Map_name[17]="魂殿";Map_name[18]="残幽冥河";Map_name[19]="荒野之地"; Map_name[20]="亻[数据删除]也";
	
	GetMap_dis();
	
	//继续添加	单个变量
	
	/*下面是地图 Map 初始化*/
	/*物品*/
	wupin[1]="卧室钥匙";wupin[2]="矿泉水";wupin[3]="奇怪的书";
	wupin[4]="五彩斑斓的水晶";
	wupin[5]="小泡芙",wupin[6]="击伟酒",wupin[7]="面包";
	wupin[8]="逗猫棒"; wupin[9]="鱼饵";wupin[10]="绳子";
	wupin[11]="树枝";wupin[12]="软妹币";
	wupin[13]="状态良好的船桨";wupin[14]="损坏大半的船桨";
	wupin[15]="混混";
	wupin[16]="沉睡的七彩神玉";
	wupin[17]="《月影之眠》";//继续添加 
	/*卧室*/      
	//    十位:0         1         2         3         4         5
	//         012345678901234567890123456789012345678901234567890123       //方便计算坐标  
	Map[1][1]="▕▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▏";
	Map[1][2]="▕ 墙墙墙墙墙墙墙墙墙墙墙墙墙墙墙墙墙墙墙墙墙墙墙墙 ▏";
	Map[1][3]="▕ 墙                                          门 墙▏";
	Map[1][4]="▕ 墙  书柜  书柜  书柜  书柜                  门 墙▏";
	Map[1][5]="▕ 墙  书柜  书柜  书柜  书柜                  门 墙▏";
	Map[1][6]="▕ 墙  书柜  书柜  书柜  书柜                     墙▏";
	Map[1][7]="▕ 墙                                        盆栽 墙▏";
	Map[1][8]="▕ 墙  书桌                                  盆栽 墙▏";
	Map[1][9]="▕ 墙  书桌 椅子                                  墙▏";
   Map[1][10]="▕ 墙  书桌                                       墙▏";//对齐后方便计算坐标 
   Map[1][11]="▕ 墙                                             墙▏";
   Map[1][12]="▕ 墙 储物柜                                      墙▏";
   Map[1][13]="▕ 墙 储物柜                                      墙▏";
   Map[1][14]="▕ 墙                                        衣柜 墙▏";
   Map[1][15]="▕ 墙                                        衣柜 墙▏";
   Map[1][16]="▕ 墙  灯  床床床                            衣柜 墙▏";
   Map[1][17]="▕ 墙墙墙墙窗窗墙墙墙墙墙墙墙墙窗窗墙墙墙墙窗窗墙墙 ▏";
   Map[1][18]="▕__________________________________________________▏";//地图框架模板 
   
	for(int i=0;i<Map[1][2].size();i++)Mapx[1][2][i]=Mapx[1][17][i]=1;
	for(int i=2;i<=17;i++)Mapx[1][i][4]=Mapx[1][i][50]=1; //墙 
	Mapx[1][16][7]=Mapx[1][16][8]=9;//灯 
	for(int i=11;i<=16;i++)Mapx[1][16][i]=10;//床 
	for(int i=4;i<=6;i++)
	{
		Mapx[1][i][10]=Mapx[1][i][7]=Mapx[1][i][8]=Mapx[1][i][9]=4;
		Mapx[1][i][13]=Mapx[1][i][14]=Mapx[1][i][15]=Mapx[1][i][16]=4;
		Mapx[1][i][19]=Mapx[1][i][20]=Mapx[1][i][21]=Mapx[1][i][22]=4;
		Mapx[1][i][25]=Mapx[1][i][26]=Mapx[1][i][27]=Mapx[1][i][28]=4;
	}//书柜 
	for(int i=3;i<=5;i++)Mapx[1][i][47]=Mapx[1][i][48]=2;//门 
	for(int i=7;i<=8;i++)Mapx[1][i][45]=Mapx[1][i][46]=Mapx[1][i][47]=Mapx[1][i][48]=3;//盆栽 
	for(int i=8;i<=10;i++)Mapx[1][i][7]=Mapx[1][i][8]=Mapx[1][i][9]=Mapx[1][i][10]=5;//书桌 
	for(int i=12;i<=15;i++)Mapx[1][9][i]=6;//椅子
	for(int i=12;i<=13;i++)for(int j=6;j<=11;j++)Mapx[1][i][j]=7;//储物柜
	for(int i=43;i<=46;i++)Mapx[1][17][i]=11;for(int i=31;i<=34;i++)Mapx[1][17][i]=11;//窗 
	for(int i=14;i<=16;i++)Mapx[1][i][45]=Mapx[1][i][46]=Mapx[1][i][47]=Mapx[1][i][48]=8;//衣柜 
	
	/*小区*/ 
	//   十位: 0         1         2         3         4         5
	//         012345678901234567890123456789012345678901234567890123       //方便计算坐标 
	Map[5][1]="▕▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▏";
	Map[5][2]="▕ 树树树树花树门门门门树树树树树草树树花树树树树树 ▏";
	Map[5][3]="▕ 树      保安        保安               娱乐区  树▏";
	Map[5][4]="▕ 树                                     娱乐区  树▏";
	Map[5][5]="▕ 屋                                             树▏";
	Map[5][6]="▕ 屋屋                                           草▏";
	Map[5][7]="▕ 屋屋屋                                         树▏";
	Map[5][8]="▕ 屋屋             人                人          树▏";
	Map[5][9]="▕ 屋               广场   广场   超商            树▏";
   Map[5][10]="▕ 树      人       广场   广场   超商            屋▏";//对齐后方便计算坐标 
   Map[5][11]="▕ 花               广场   广场                 屋屋▏";
   Map[5][12]="▕ 树                                         屋屋屋▏";
   Map[5][13]="▕ 草 池塘                         怪人         屋屋▏";
   Map[5][14]="▕ 草 池塘          人                            屋▏";
   Map[5][15]="▕ 树                                     健身区  树▏";
   Map[5][16]="▕ 树                                     健身区  树▏";
   Map[5][17]="▕ 树树树树树树树家家家家树树树树草树树树树树树树树 ▏";
   Map[5][18]="▕__________________________________________________▏";
   
	for(int i=0;i<Map[5][2].size();i++)Mapx[5][2][i]=Mapx[5][17][i]=11;
	for(int i=2;i<=17;i++)Mapx[5][i][4]=Mapx[5][i][50]=11; //树
	Mapx[5][2][12]=Mapx[5][11][4]=Mapx[5][2][40]=Mapx[5][2][11]=Mapx[5][11][3]=Mapx[5][2][39]=12;//花 
	Mapx[5][2][34]=Mapx[5][13][4]=Mapx[5][14][4]=Mapx[5][17][34]=Mapx[5][6][50]=13;//草 
	Mapx[5][2][33]=Mapx[5][13][3]=Mapx[5][14][3]=Mapx[5][17][33]=Mapx[5][2][50]=13;//草
	Mapx[5][3][11]=Mapx[5][3][12]=Mapx[5][3][13]=Mapx[5][3][14]=14;//保安1
	Mapx[5][3][23]=Mapx[5][3][24]=Mapx[5][3][25]=Mapx[5][3][26]=15;//保安2
	for(int i=3;i<=4;i++)for(int j=42;j<=47;j++)Mapx[5][i][j]=16;//娱乐区
	for(int i=15;i<=16;i++)for(int j=42;j<=47;j++)Mapx[5][i][j]=17;//健身区 
	Mapx[5][10][11]=Mapx[5][10][12]=Mapx[5][8][38]=Mapx[5][8][39]=18;//人1 
	Mapx[5][14][20]=Mapx[5][14][21]=Mapx[5][8][20]=Mapx[5][8][21]=19;//人2 
	Mapx[5][13][35]=Mapx[5][13][36]=Mapx[5][13][37]=Mapx[5][13][38]=20;//人3
	for(int i=13;i<=14;i++)for(int j=6;j<=9;j++)Mapx[5][i][j]=21;//池塘 
	for(int i=9;i<=10;i++)for(int j=34;j<=37;j++)Mapx[5][i][j]=22;//超商 
	for(int i=9;i<=11;i++)for(int j=20;j<=23;j++)Mapx[5][i][j]=23;//广场
	for(int i=9;i<=11;i++)for(int j=27;j<=30;j++)Mapx[5][i][j]=23;//广场
	for(int i=17;i<=24;i++)Mapx[5][17][i]=24;//家 
	for(int i=5;i<=9;i++)Mapx[5][i][3]=Mapx[5][i][4]=25;
	for(int i=6;i<=8;i++)Mapx[5][i][5]=Mapx[5][i][6]=25;
	for(int i=10;i<=14;i++)Mapx[5][i][50]=Mapx[5][i][51]=25;
	for(int i=11;i<=13;i++)Mapx[5][i][48]=Mapx[5][i][49]=25;
	Mapx[5][7][7]=Mapx[5][7][8]=Mapx[5][12][46]=Mapx[5][12][47]=25;//屋 
	for(int i=15;i<=22;i++)Mapx[5][2][i]=26;//门 
	
	/*街道*/ 
	//   十位: 0         1         2         3         4         5
	//         012345678901234567890123456789012345678901234567890123       //方便计算坐标 
	Map[2][1]="▕▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▏";
	Map[2][2]="▕ 树树树树树树学校大门树树树树树树树树树树树树树树 ▏";
	Map[2][3]="▕ 树                                             树▏";
	Map[2][4]="▕ 树                                             树▏";
	Map[2][5]="▕ 树                  道         道   车         树▏";
	Map[2][6]="▕ 树          人      道 车      道   站         树▏";
	Map[2][7]="▕ 商                  道       车道              树▏";
	Map[2][8]="▕ 场                  道         道              花▏";
	Map[2][9]="▕ 大                  道         道              园▏";
   Map[2][10]="▕ 门                  道 车      道              大▏";//对齐后方便计算坐标 
   Map[2][11]="▕ 树                  道       车道              门▏";
   Map[2][12]="▕ 树     人           道         道              花▏";//(花1)
   Map[2][13]="▕ 树                  道         道         人   花▏";//(花2)
   Map[2][14]="▕ 树                  道 车      道              树▏";
   Map[2][15]="▕ 树                  道         道              树▏";
   Map[2][16]="▕ 树                                             树▏";
   Map[2][17]="▕ 树树树树树树门门门门树树树树树树树树树树树树树树 ▏";
   Map[2][18]="▕__________________________________________________▏";
   	for(int i=0;i<Map[5][2].size();i++)Mapx[2][2][i]=Mapx[2][17][i]=38;
	for(int i=2;i<=17;i++)Mapx[2][i][4]=Mapx[2][i][50]=38; //树
   Mapx[2][12][50]=27;Mapx[2][13][50]=28; //两朵花 
   for(int i=15;i<=22;i++)Mapx[2][17][i]=30;//小区门 
   for(int i=7;i<=10;i++)Mapx[2][i][4]=31;//商场门 
   for(int i=15;i<=22;i++)Mapx[2][2][i]=33;//学校门
   for(int i=8;i<=11;i++)Mapx[2][i][50]=32;//花园门 
   for(int i=5;i<=15;i++)
   	for(int j=23;j<=35;j++)
   		Mapx[2][i][j]=37;//车路
	Mapx[2][6][15]=Mapx[2][6][16]=34;//人1
	Mapx[2][12][10]=Mapx[2][12][11]=35;//人2
	Mapx[2][13][45]=Mapx[2][13][46]=36;//人3 
	for(int i=5;i<=6;i++)
		for(int j=39;j<=40;j++)
			Mapx[2][i][j]=39;//车站 
   	/*学校*/ 
	//   十位: 0         1         2         3         4         5
	//         012345678901234567890123456789012345678901234567890123       //方便计算坐标 
	Map[6][1]="▕▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▏";
	Map[6][2]="▕ 墙墙墙墙墙墙墙墙墙墙墙墙墙墙墙墙墙墙墙墙墙墙墙墙 ▏";
	Map[6][3]="▕ 墙                                 中二少年  楼楼▏";
	Map[6][4]="▕ 墙   操操操操操操操操    树树树树树        楼楼楼▏";
	Map[6][5]="▕ 墙   操     门     场   树 小情侣 树树树 楼楼楼楼▏";
	Map[6][6]="▕ 墙   操   学       场     树树树树树 学  楼楼楼楼▏";
	Map[6][7]="▕ 墙   操            场                      楼楼楼▏";
	Map[6][8]="▕ 墙   学     学     场                        楼楼▏";
	Map[6][9]="▕ 墙   操        球  场                          通▏";
   Map[6][10]="▕ 墙   操        学  场                          道▏";//对齐后方便计算坐标 
   Map[6][11]="▕ 墙   操            场                        楼楼▏";
   Map[6][12]="▕ 墙   操  学        场                 师   楼楼楼▏";
   Map[6][13]="▕ 墙   操     门     学                    楼楼楼楼▏";
   Map[6][14]="▕ 墙   场场场场场场场场       学           楼楼楼楼▏";
   Map[6][15]="▕ 墙                                         楼楼楼▏";
   Map[6][16]="▕ 墙                                焦急の同学 楼楼▏";
   Map[6][17]="▕ 树树树树树树学校大门树树树树树树树树树树树树树树 ▏";
   Map[6][18]="▕__________________________________________________▏";
   //40.墙 41.操场 42.学生1 43.学生2 44.学生3 45.老师 46.学校大门 47.中二少年 48.教学楼 49.通道 50.树1 51.树2(学校)
   for(int i=0;i<Map[5][2].size();i++)Mapx[6][2][i]=40,Mapx[6][17][i]=50;//墙 & 树1 
   for(int i=2;i<=16;i++)Mapx[6][i][4]=40;
   Mapx[6][12][41]=Mapx[6][12][42]=45;//老师 
   Mapx[6][14][31]=Mapx[6][14][32]=44;//学生3
   for(int i=38;i<=45;i++)Mapx[6][3][i]=47;//中二 
   for(int i=28;i<=37;i++)Mapx[6][4][i]=51;//树2 
   Mapx[6][5][27]=Mapx[6][5][28]=51;
   for(int i=37;i<=42;i++)Mapx[6][5][i]=51;
   for(int i=29;i<=38;i++)Mapx[6][6][i]=51;
   Mapx[6][9][50]=Mapx[6][10][50]=49;//通道
   Mapx[6][6][40]=Mapx[6][6][41]=43;//学生2
	for(int i=4;i<=14;i++)
		for(int j=8;j<=23;j++)
   			Mapx[6][i][j]=41;//操场 
   	Mapx[6][13][22]=Mapx[6][13][23]=42;//学生1 
   for(int i=15;i<=22;i++)Mapx[6][17][i]=46;//学校大门 
   for(int j=3;j<=16;j++)
	for(int i=51;i>=44;i--)
   	{
		if((j==3||j==8||j==11||j==16)&&i==47)break;
		if((j==4||j==7||j==12||j==15)&&i==45)break;
		//if((j==5||j==6||j==13||j==14)&&i==43)break;
		Mapx[6][j][i]=48;//教学楼 
	  }
   for(int i=37;i<=46;i++)Mapx[6][16][i]=105;//焦急的同学 
   
   
    /*花园*/ 
	//   十位: 0         1         2         3         4         5
	//         012345678901234567890123456789012345678901234567890123       //方便计算坐标 
	Map[9][1]="▕▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▏";
	Map[9][2]="▕ 墙花花花花花花花花花花花花花花花花花花花花花花花 ▏";
	Map[9][3]="▕ 墙花花花花花        花花花          花花花花花花 ▏";
	Map[9][4]="▕ 墙花花花花    花花  花花花  花花    花花花花花花 ▏";
	Map[9][5]="▕ 墙花花花    花花花    花    花花花    花花花花花 ▏";
	Map[9][6]="▕ 墙花花    花花花花花      花花花花花    花花花花 ▏";
	Map[9][7]="▕ 墙  花  花花花花花花花花花花花花花花花  花花花花 ▏";
	Map[9][8]="▕ 花      花花花花花花花花花花花花花花花        小 ▏";
	Map[9][9]="▕ 园        花花花花花花花花花花花花花          溪 ▏";
   Map[9][10]="▕ 大          花花花花花花花花花花花    花花花花花 ▏";//对齐后方便计算坐标 
   Map[9][11]="▕ 门            花花花花花花花花花    花花花花花花 ▏";
   Map[9][12]="▕ 墙  花花花花    花花花花花花花    花花花花花花花 ▏";
   Map[9][13]="▕ 墙花花花花花花    花花花花花    花花花花花花花花 ▏";
   Map[9][14]="▕ 墙花花花花花花花    花花花    花花花花花花花花花 ▏";
   Map[9][15]="▕ 墙花花花花花花花花          花花花花花花花花花花 ▏";
   Map[9][16]="▕ 墙花花花花花花花花花花花花花花花花花花花花花花花 ▏";
   Map[9][17]="▕ 花花花花花花花花花花花花花花花花花花花花花花花花 ▏";
   Map[9][18]="▕__________________________________________________▏";
   //52.小溪边入口 53.花 54.墙 104.花园大门(花园)
   for(int i=2;i<=17;i++)
   	for(int j=0;j<Map[9][2].size();j++)
   		Mapx[9][i][j]=53;
   Mapx[9][7][4]=Mapx[9][12][4]=54;
   Mapx[9][8][49]=Mapx[9][9][49]=52;
   for(int i=8;i<=11;i++)Mapx[9][i][4]=104;
   for(int i=15;i<=22;i++)Mapx[9][3][i]=0;
   for(int i=29;i<=38;i++)Mapx[9][3][i]=0;
   for(int i=13;i<=16;i++)Mapx[9][4][i]=0;Mapx[9][4][21]=Mapx[9][4][22]=Mapx[9][4][29]=Mapx[9][4][30]=Mapx[9][4][35]=Mapx[9][4][36]=Mapx[9][4][37]=Mapx[9][4][38]=0;
    for(int i=11;i<=14;i++)Mapx[9][5][i]=0;
    for(int i=21;i<=24;i++)Mapx[9][5][i]=0;
    for(int i=27;i<=30;i++)Mapx[9][5][i]=0;
    for(int i=37;i<=40;i++)Mapx[9][5][i]=0;
	for(int i=9;i<=12;i++)Mapx[9][6][i]=0;
	for(int i=23;i<=28;i++)Mapx[9][6][i]=0;
	for(int i=39;i<=42;i++)Mapx[9][6][i]=0;
	Mapx[9][7][5]=Mapx[9][7][6]=Mapx[9][12][5]=Mapx[9][12][6]=Mapx[9][7][9]=Mapx[9][7][10]=Mapx[9][7][41]=Mapx[9][7][42]=0;
	for(int i=5;i<=10;i++)Mapx[9][8][i]=0;
	for(int i=41;i<=48;i++)Mapx[9][8][i]=0;
	for(int i=5;i<=12;i++)Mapx[9][9][i]=0;
	for(int i=39;i<=48;i++)Mapx[9][9][i]=0;
	for(int i=5;i<=14;i++)Mapx[9][10][i]=0;
	for(int i=37;i<=40;i++)Mapx[9][10][i]=0;
	for(int i=5;i<=16;i++)Mapx[9][11][i]=0;
	for(int i=35;i<=38;i++)Mapx[9][11][i]=0;
	for(int i=15;i<=18;i++)Mapx[9][12][i]=0;
	for(int i=17;i<=20;i++)Mapx[9][13][i]=0;
	for(int i=19;i<=22;i++)Mapx[9][14][i]=0;
	for(int i=33;i<=36;i++)Mapx[9][12][i]=0;
	for(int i=31;i<=34;i++)Mapx[9][13][i]=0;
	for(int i=29;i<=32;i++)Mapx[9][14][i]=0;
	for(int i=21;i<=30;i++)Mapx[9][15][i]=0;

    /*商场*/ 
	//   十位: 0         1         2         3         4         5
	//         012345678901234567890123456789012345678901234567890123       //方便计算坐标 
	Map[3][1]="▕▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▏";
	Map[3][2]="▕ 墙墙墙墙墙墙墙墙墙墙墙墙墙墙墙墙墙墙墙墙墙墙墙墙 ▏";
	Map[3][3]="▕ 墙  导      墙      导  墙  导      墙  导     墙▏";
	Map[3][4]="▕ 墙          墙          墙          墙         墙▏";
	Map[3][5]="▕ 墙          墙          墙          墙         墙▏";
	Map[3][6]="▕ 墙          墙        人墙          墙墙墙  杂 墙▏";
	Map[3][7]="▕ 墙墙  衣服  墙  包包  墙墙墙  果蔬  墙         商▏";
	Map[3][8]="▕ 墙                      同学                   场▏";
	Map[3][9]="▕ 墙                                             大▏";
   Map[3][10]="▕ 墙墙墙墙墙       人                            门▏";//对齐后方便计算坐标 
   Map[3][11]="▕ 墙人    墙                                     墙▏";
   Map[3][12]="▕ 墙    导墙   墙  玩具  墙  日常  墙            墙▏";
   Map[3][13]="▕ 墙      墙   墙        墙        墙墙♂  WC  ♀墙▏";
   Map[3][14]="▕ 墙           墙        墙导      墙墙    |     墙▏";
   Map[3][15]="▕ 墙      器   墙        墙        墙墙    |     墙▏";
   Map[3][16]="▕ 墙           墙      导墙        墙墙  人|   人墙▏";
   Map[3][17]="▕ 墙墙墙墙墙墙墙墙墙墙墙墙墙墙墙墙墙墙墙墙墙墙墙墙 ▏";
   Map[3][18]="▕__________________________________________________▏";
   //55.商场大门 56.墙 57.WC 58.衣 59.包 60.果 61.杂 62.日常 63.器 64.玩具 65.导(衣) 66.导(包) 67.导(果) 68.导(杂) 69.导(日常) 70.导(器) 71.导(玩具)
   //72.人1(器) 73.人2(包) 74.人3 75.人(♂) 76.人4(♀) 77.同学 78.♂ 79.♀ 80.‘|’(分割线) 
   for(int i=0;i<Map[3][2].size();i++)Mapx[3][2][i]=Mapx[3][17][i]=56;
   for(int i=2;i<=17;i++)Mapx[3][i][4]=Mapx[3][i][50]=56;
   for(int i=7;i<=10;i++)Mapx[3][i][50]=55;//门 
   for(int i=3;i<=7;i++)Mapx[3][i][15]=Mapx[3][i][16]=56;
   for(int i=3;i<=7;i++)Mapx[3][i][27]=Mapx[3][i][28]=56;
   for(int i=3;i<=7;i++)Mapx[3][i][39]=Mapx[3][i][40]=56;
   for(int i=41;i<=44;i++)Mapx[3][6][i]=56;Mapx[3][7][5]=Mapx[3][7][6]=56;
   Mapx[3][7][25]=Mapx[3][7][26]=Mapx[3][7][29]=Mapx[3][7][30]=56;
   for(int i=5;i<=12;i++)Mapx[3][10][i]=56;
   for(int i=11;i<=13;i++)for(int j=11;j<=12;j++)Mapx[3][i][j]=56;
   for(int i=12;i<=16;i++)Mapx[3][i][16]=Mapx[3][i][17]=56;
   for(int i=12;i<=16;i++)Mapx[3][i][26]=Mapx[3][i][27]=56;
   for(int i=12;i<=16;i++)Mapx[3][i][36]=Mapx[3][i][37]=56;
   for(int i=13;i<=16;i++)Mapx[3][i][38]=Mapx[3][i][39]=56;
   for(int i=9;i<=12;i++)Mapx[3][7][i]=58;
   for(int i=19;i<=22;i++)Mapx[3][7][i]=59;
   for(int i=33;i<=36;i++)Mapx[3][7][i]=60;
   Mapx[3][6][47]=Mapx[3][6][48]=61;
   for(int i=30;i<=33;i++)Mapx[3][12][i]=62;
   for(int i=20;i<=23;i++)Mapx[3][12][i]=64;
   Mapx[3][15][11]=Mapx[3][15][12]=63;
   Mapx[3][3][7]=Mapx[3][3][8]=65;
   Mapx[3][3][23]=Mapx[3][3][24]=66;
   Mapx[3][3][31]=Mapx[3][3][32]=67;
   Mapx[3][3][43]=Mapx[3][3][44]=68;
   Mapx[3][12][9]=Mapx[3][12][10]=70;
   Mapx[3][16][24]=Mapx[3][16][25]=71;
   Mapx[3][14][28]=Mapx[3][14][29]=69;
   Mapx[3][11][5]=Mapx[3][11][6]=72;
   Mapx[3][6][25]=Mapx[3][6][26]=73;
   Mapx[3][10][20]=Mapx[3][10][21]=74;
   Mapx[3][16][42]=Mapx[3][16][43]=75;
   Mapx[3][16][48]=Mapx[3][16][49]=76;
   for(int i=27;i<=30;i++)Mapx[3][8][i]=77;
   Mapx[3][13][40]=Mapx[3][13][41]=78;   
   Mapx[3][13][48]=Mapx[3][13][49]=79;
   for(int i=14;i<=16;i++)Mapx[3][i][44]=80;
   Mapx[3][13][44]=Mapx[3][13][45]=57;
    /*公交车站*/ 
	//   十位: 0         1         2         3         4         5
	//         012345678901234567890123456789012345678901234567890123       //方便计算坐标 
	Map[7][1]="▕▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▏";
	Map[7][2]="▕ 形の墙 无形の墙 无形の墙 无形の墙 无形の墙 无形の▏";
	Map[7][3]="▕ の                                             墙▏";
	Map[7][4]="▕ 墙                              报纸区         无▏";//放些关于主线的（小溪）消息 
	Map[7][5]="▕ 无           |                                 形▏";
	Map[7][6]="▕ 形       公  |                  车牌[1]        の▏";
	Map[7][7]="▕ の       交  |      客          车牌[2]        墙▏";
	Map[7][8]="▕ 墙       车  |             休   车牌[3]        无▏";
	Map[7][9]="▕ 无           |             息   [广 告]        形▏";
   Map[7][10]="▕ 形           |        客   区   车牌[4]        の▏";//对齐后方便计算坐标 
   Map[7][11]="▕ の       公  |                  车牌[5]        墙▏";
   Map[7][12]="▕ 墙       交  | 客               车牌[6]        无▏";
   Map[7][13]="▕ 无       车  |                                 形▏";
   Map[7][14]="▕ 形           |                                 の▏";
   Map[7][15]="▕ の                                             墙▏";
   Map[7][16]="▕ 墙                出口[exit]                   无▏";
   Map[7][17]="▕ 无形の墙 无形の墙 无形の墙 无形の墙 无形の墙 无形▏";
   Map[7][18]="▕__________________________________________________▏";
   //81.无形の墙 82.出口[exit] 83.‘|’(分割线) 84.公交车1 85.公交车2 86.客1 87.客2 88.客3 89.休息区 90.报纸区
   //91.车牌[1] 92.车牌[2] 93.车牌[3] 94.车牌[4] 95.车牌[5] 96.车牌[6] 97.广告 
   for(int i=0;i<Map[7][2].size();i++)Mapx[7][2][i]=Mapx[7][17][i]=81;
   for(int i=2;i<=17;i++)Mapx[7][i][4]=Mapx[7][i][50]=81;
   for(int i=21;i<=30;i++)Mapx[7][16][i]=82;
   for(int i=5;i<=14;i++)Mapx[7][i][16]=83;
   for(int i=6;i<=8;i++)for(int j=12;j<=13;j++)Mapx[7][i][j]=84;
   for(int i=11;i<=13;i++)for(int j=12;j<=13;j++)Mapx[7][i][j]=85;
   Mapx[7][12][18]=Mapx[7][12][19]=88;
   Mapx[7][7][23]=Mapx[7][7][24]=87;
   Mapx[7][10][25]=Mapx[7][10][26]=86;
   for(int i=8;i<=10;i++)for(int j=30;j<=31;j++)Mapx[7][i][j]=89;
   for(int i=35;i<=40;i++)Mapx[7][4][i]=90;
   for(int i=35;i<=41;i++)Mapx[7][6][i]=91;
   for(int i=35;i<=41;i++)Mapx[7][7][i]=92;
   for(int i=35;i<=41;i++)Mapx[7][8][i]=93;
   for(int i=35;i<=41;i++)Mapx[7][10][i]=94;
   for(int i=35;i<=41;i++)Mapx[7][11][i]=95;
   for(int i=35;i<=41;i++)Mapx[7][12][i]=96;
   for(int i=35;i<=41;i++)Mapx[7][9][i]=97;
   
    /*小溪边*/ 
	//   十位: 0         1         2         3         4         5
	//         012345678901234567890123456789012345678901234567890123       //方便计算坐标 
	Map[4][1]="▕▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▏";
	Map[4][2]="▕ 花花花花花花花路路路路路溪溪溪溪溪溪溪 石        ▏";
	Map[4][3]="▕ 花花花花花花              溪溪溪溪溪溪溪   柳  柳▏";
	Map[4][4]="▕ 花花花花花                  溪溪溪溪石溪溪    石 ▏";
	Map[4][5]="▕ 花花花花                      溪溪溪溪溪溪溪     ▏";
	Map[4][6]="▕ 花花花                  渔      溪溪溪溪溪溪溪   ▏";
	Map[4][7]="▕ 草花                    者    溪溪溪溪溪溪溪  柳 ▏";
	Map[4][8]="▕ 花                          溪溪石石溪溪溪       ▏";
	Map[4][9]="▕ 园                        溪溪溪溪溪溪溪   柳    ▏";
   Map[4][10]="▕ 草花                    溪溪溪溪溪溪溪        柳 ▏";//对齐后方便计算坐标 
   Map[4][11]="▕ 花花花     石         溪溪溪溪溪溪溪  柳    柳   ▏";
   Map[4][12]="▕ 花花花花 石石石     溪溪溪溪石溪溪   石          ▏";
   Map[4][13]="▕ 花花花花花 石         溪溪溪溪溪溪溪   柳  柳    ▏";
   Map[4][14]="▕ 花花花花花花            溪溪溪溪溪溪溪  石       ▏";
   Map[4][15]="▕ 花花花花花花花            溪溪溪溪溪溪溪   柳    ▏";
   Map[4][16]="▕ 花花花花花花花花            溪溪溪石溪溪溪       ▏";
   Map[4][17]="▕ 花花花花花花花花花路路路路路路溪溪溪溪溪溪溪溪 柳▏";
   Map[4][18]="▕__________________________________________________▏";
   //98.花园入口 99.花 100.渔者 101.石头 102.溪 103.路
	Mapx[4][8][4]=Mapx[4][9][4]=98;
	int dfgtre=6;
    for(int i=10;i<=17;i++)
    {
    	for(int j=3;j<=dfgtre;j++)
    		Mapx[4][i][j]=99;
		dfgtre+=2;
	}
    dfgtre=6;
    for(int i=7;i>=2;i--)
    {
    	for(int j=3;j<=dfgtre;j++)
    		Mapx[4][i][j]=99;
    	dfgtre+=2;
	}
   for(int i=12;i<=17;i++)Mapx[4][12][i]=101;
   Mapx[4][11][14]=Mapx[4][11][15]=Mapx[4][13][14]=Mapx[4][13][15]=101;
   for(int i=6;i<=7;i++)for(int j=27;j<=28;j++)Mapx[4][i][j]=100;
   for(int i=21;i<=34;i++)Mapx[4][17][i]=103;
   for(int i=17;i<=26;i++)Mapx[4][2][i]=103;
   int pplo=27;
   for(int i=2;i<=6;i++){Mapx[4][i][pplo]=Mapx[4][i][pplo+1]=102;pplo+=2;}
   pplo-=2;
   for(int i=6;i<=12;i++){Mapx[4][i][pplo]=Mapx[4][i][pplo+1]=102;pplo-=2;}
   pplo+=2;
   for(int i=12;i<=16;i++){Mapx[4][i][pplo]=Mapx[4][i][pplo+1]=102;pplo+=2;}

    /*传送之地*/ 
	//    十位: 0         1         2         3         4         5
	//          012345678901234567890123456789012345678901234567890123       //方便计算坐标 
	Map[20][1]="▕▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▏";
	Map[20][2]="▕ 树树树树树树树树树树树树树树树树树树树树树树树树 ▏";
	Map[20][3]="▕ 灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰 树▏";
	Map[20][4]="▕ 灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰 树▏";
	Map[20][5]="▕ 灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰 树▏";
	Map[20][6]="▕ 灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰 树▏";
	Map[20][7]="▕ 灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰 树▏";
	Map[20][8]="▕ 小灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰 树▏";
	Map[20][9]="▕ 溪  灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰 树▏";
   Map[20][10]="▕ 边灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰 树▏";//对齐后方便计算坐标 
   Map[20][11]="▕ 灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰 树▏";
   Map[20][12]="▕ 灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰 树▏";
   Map[20][13]="▕ 灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰 树▏";
   Map[20][14]="▕ 灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰 树▏";
   Map[20][15]="▕ 灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰 树▏";
   Map[20][16]="▕ 灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰灰 树▏";
   Map[20][17]="▕ 树树树树树树树树树树树树树树树树树树树树树树树树 ▏";
   Map[20][18]="▕__________________________________________________▏";
   //107.灰 108.林中小湖 109.树 110.林 111.小溪边入口 
   for(int i=3;i<=16;i++)
   	for(int j=3;j<=48;j++)
	   Mapx[20][i][j]=107;
	Mapx[20][9][3]=Mapx[20][9][4]=111;Mapx[20][9][5]=Mapx[20][9][6]=0;
	Mapx[20][8][4]=Mapx[20][8][3]=Mapx[20][10][4]=Mapx[20][10][3]=111; 
	for(int i=3;i<=50;i++)Mapx[20][2][i]=Mapx[20][17][i]=109;
	for(int i=3;i<=16;i++)Mapx[20][i][50]=Mapx[20][i][51]=109;
	
	//万道城
	//    十位: 0         1         2         3         4         5
	     //     012345678901234567890123456789012345678901234567890123       //方便计算坐标 
	Map[11][1]="▕▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▏";
	Map[11][2]="▕ 墙墙墙墙墙墙墙墙门门门门门门门门墙墙墙墙墙墙墙墙 ▏";
	Map[11][3]="▕ 墙          守卫                守卫           墙▏";
	Map[11][4]="▕ 墙                                             墙▏";
	Map[11][5]="▕ 墙                                          守 墙▏";
	Map[11][6]="▕ 墙                                          卫 墙▏";//一定要建墙！！(第一列的墙要空一格，后面的墙才能贴紧) 
	Map[11][7]="▕ 墙 传        铁匠铺         拍卖行             门▏";
	Map[11][8]="▕ 墙 送                                          门▏";
	Map[11][9]="▕ 墙 门                                          门▏";
   Map[11][10]="▕ 墙           清风酒楼       交易所             门▏";//对齐后方便计算坐标 
   Map[11][11]="▕ 墙 守                                          门▏";
   Map[11][12]="▕ 墙 护                                       守 墙▏";
   Map[11][13]="▕ 墙 者                                       卫 墙▏";
   Map[11][14]="▕ 墙                                             墙▏";
   Map[11][15]="▕ 墙                                             墙▏";
   Map[11][16]="▕ 墙          守卫                守卫           墙▏";
   Map[11][17]="▕ 墙墙墙墙墙墙墙墙门门门门门门门门墙墙墙墙墙墙墙墙 ▏";
   Map[11][18]="▕__________________________________________________▏"; 
   //115.传送门 116.守护者 117.守卫1(上) 118.守卫2(下) 119.守卫3(右) 120.门(上) 121.门(下) 122.门(右) 123.铁匠铺 124.清风酒楼 125.拍卖行 126.交易所 127.墙 
   for(int i=3;i<=50;i++)Mapx[11][2][i]=Mapx[11][17][i]=127;
   for(int i=2;i<=17;i++)Mapx[11][i][4]=Mapx[11][i][50]=127;
   for(int i=7;i<=9;i++)for(int j=6;j<=7;j++)Mapx[11][i][j]=115;
   for(int i=11;i<=13;i++)for(int j=6;j<=7;j++)Mapx[11][i][j]=116;
   for(int i=15;i<=18;i++)Mapx[11][3][i]=117;
   for(int i=35;i<=38;i++)Mapx[11][3][i]=117;
   for(int i=15;i<=18;i++)Mapx[11][16][i]=118;
   for(int i=35;i<=38;i++)Mapx[11][16][i]=118;
   for(int i=5;i<=6;i++)for(int j=47;j<=48;j++)Mapx[11][i][j]=119;
   for(int i=12;i<=13;i++)for(int j=47;j<=48;j++)Mapx[11][i][j]=119;
   for(int i=19;i<=34;i++)Mapx[11][2][i]=120;
   for(int i=19;i<=34;i++)Mapx[11][17][i]=121;
   for(int i=7;i<=11;i++)Mapx[11][i][50]=122;
   for(int i=16;i<=21;i++)Mapx[11][7][i]=123;
   for(int i=31;i<=36;i++)Mapx[11][7][i]=125;
   for(int i=16;i<=23;i++)Mapx[11][10][i]=124;
   for(int i=31;i<=36;i++)Mapx[11][10][i]=126;

   //★：注意简化的坐标要对齐！！！  
}
//记得所有变量都要初始化 

#define YUEYING_SCALAR_FIELDS(X) \
	X(xwsf) \
	X(xwz) \
	X(diyicichuansongmen) \
	X(xw) \
	X(timey) \
	X(timem) \
	X(timed) \
	X(jlz) \
	X(dx) \
	X(dy1) \
	X(dy2) \
	X(xiaomaomihaogandu) \
	X(mijingshifou) \
	X(ddd) \
	X(sfgmye) \
	X(sfjq) \
	X(jqdf) \
	X(yzsf) \
	X(sfdh) \
	X(cmsdcs) \
	X(zxtsf) \
	X(HP) \
	X(DE) \
	X(MA) \
	X(AT) \
	X(caoweishifou) \
	X(youxibeijingshifou) \
	X(first_xiaoqu) \
	X(first_sb) \
	X(NowMap)

void Data::WriteScalarFields(ostream &out){
#define WRITE_SCALAR_FIELD(field) out<<#field<<"="<<(int)(field)<<"\n";
	YUEYING_SCALAR_FIELDS(WRITE_SCALAR_FIELD)
#undef WRITE_SCALAR_FIELD
}

bool Data::ApplyScalarField(const string &name,int value){
#define APPLY_SCALAR_FIELD(field) if(name==#field){field=value;return true;}
	YUEYING_SCALAR_FIELDS(APPLY_SCALAR_FIELD)
#undef APPLY_SCALAR_FIELD
	return false;
}

void Data::WriteVersionedData(const string &savePath){
	ofstream outFile(savePath.c_str());
	outFile<<kVersionedSaveMagic<<"\n";
	outFile<<kVersionLine<<"\n";
	outFile<<kScalarsSection<<"\n";
	WriteScalarFields(outFile);

	outFile<<kMapStringsSection<<"\n";
	for(int map=0;map<=kSavedMapMaxIndex;map++)
		for(int row=0;row<=kSavedMapRowMax;row++)
			outFile<<map<<" "<<row<<" "<<Map[map][row]<<"\n";

	outFile<<kMapTilesSection<<"\n";
	for(int map=0;map<=kSavedMapMaxIndex;map++)
		for(int row=0;row<=kSavedMapRowMax;row++){
			outFile<<map<<" "<<row;
			for(int col=0;col<=kSavedMapColMax;col++)outFile<<" "<<Mapx[map][row][col];
			outFile<<"\n";
		}

	outFile<<kBagSection<<"\n";
	outFile<<"numt="<<numt<<"\n";
	for(int i=0;i<=kSavedBagMaxIndex;i++)
		outFile<<"item "<<i<<" "<<things[i]<<" "<<thing_num[i]<<" "<<pd_thing[i]<<"\n";

	outFile<<kMapFindV2Section<<"\n";
	outFile<<"Map_allnum="<<Map_allnum<<"\n";
	for(int i=1;i<=Map_allnum;i++)outFile<<i<<"="<<Map_Find[i]<<"\n";
}

void Data::SaveDatax(){
	WriteVersionedData(BuildDataPath(kDefaultSaveFile));
	Use1.LowPrint("存档完成！！");
	Sleep(1000); 
}

namespace {
int ToInt(const string &value){
	return atoi(value.c_str());
}

bool SplitKeyValue(const string &line,string &key,string &value){
	int pos=line.find('=');
	if(pos<0)return false;
	key=line.substr(0,pos);
	value=line.substr(pos+1);
	return true;
}

void DropSingleLeadingSpace(string &value){
	if(!value.empty()&&value[0]==' ')value.erase(0,1);
}
}

bool Data::LoadVersionedData(const string &savePath){
	ifstream inputFile(savePath.c_str());
	if(!inputFile.is_open())return false;

	string line,section;
	getline(inputFile,line);// magic
	while(getline(inputFile,line)){
		if(line.empty())continue;
		if(line[0]=='['){section=line;continue;}

		if(section==kScalarsSection){
			string key,value;
			if(SplitKeyValue(line,key,value))ApplyScalarField(key,ToInt(value));
			continue;
		}

		if(section==kMapStringsSection){
			istringstream in(line);
			int map=0,row=0;
			if(in>>map>>row){
				string value;
				getline(in,value);
				DropSingleLeadingSpace(value);
				if(map>=0&&map<=kSavedMapMaxIndex&&row>=0&&row<=kSavedMapRowMax)Map[map][row]=value;
			}
			continue;
		}

		if(section==kMapTilesSection){
			istringstream in(line);
			int map=0,row=0;
			if(in>>map>>row&&map>=0&&map<=kSavedMapMaxIndex&&row>=0&&row<=kSavedMapRowMax)
				for(int col=0;col<=kSavedMapColMax;col++)in>>Mapx[map][row][col];
			continue;
		}

		if(section==kBagSection){
			string key,value;
			if(SplitKeyValue(line,key,value)&&key=="numt"){
				numt=ToInt(value);
				continue;
			}
			istringstream in(line);
			string tag;
			int index=0;
			if(in>>tag>>index&&tag=="item"&&index>=0&&index<=kSavedBagMaxIndex)
				in>>things[index]>>thing_num[index]>>pd_thing[index];
			continue;
		}

		if(section==kMapFindV2Section){
			string key,value;
			if(!SplitKeyValue(line,key,value))continue;
			if(key=="Map_allnum")Map_allnum=ToInt(value);
			else {
				int map=ToInt(key);
				if(map>=1&&map<Data_Array::MAX_MAP_COUNT)Map_Find[map]=ToInt(value);
			}
			continue;
		}
	}
	return true;
}

int change_string_to_int(string ss){//把一串数字字符变成数字，旧存档兼容读取专用 
	int ssint=0,Lss=ss.size();
	for(int i=0;i<=Lss-1;i++)ssint=ssint*10+ss[i]-'0';
	return ssint;
}

void change_string_to_ints(int * ssint,string ss){//把n个数字字符变成int数组，旧存档兼容读取专用 
	int ssx=0,Lss=ss.size(),ttx=-1;
	for(int i=0;i<=Lss-1;i++){
		if(ss[i]!=' ')ssx=ssx*10+ss[i]-'0';
		else ssint[++ttx]=ssx,ssx=0;
	}
	ssint[++ttx]=ssx;
}

bool Data::LoadLegacyData(const string &savePath){
	ifstream inputFile(savePath.c_str());
	if(!inputFile.is_open())return false;

	string line="";
	int saveid=0,savei=0,savesec=SAVE_SECTION_SCALAR; 
	while (getline(inputFile,line)) {
		if(line==kMapStringSection){savesec=SAVE_SECTION_MAP_STRING,saveid=0,savei=0;continue;}
		if(line==kMapDataSection){savesec=SAVE_SECTION_MAP_DATA,saveid=0,savei=0;continue;}
		if(line==kBagDataSection){savesec=SAVE_SECTION_BAG_DATA,saveid=0,savei=0;continue;}
		if(line==kMapFindSection){savesec=SAVE_SECTION_MAP_FIND,saveid=0,savei=1;continue;}
		if(savesec==SAVE_SECTION_SCALAR){
			static const char *legacyFields[kSaveScalarFieldCount]={
				"xwsf","xwz","diyicichuansongmen","xw","timey",
				"timem","timed","jlz","dx","dy1",
				"dy2","xiaomaomihaogandu","mijingshifou","ddd","sfgmye",
				"sfjq","jqdf","yzsf","sfdh","cmsdcs",
				"zxtsf","HP","DE","MA","AT",
				"caoweishifou","youxibeijingshifou","first_xiaoqu","first_sb","NowMap"
			};
			if(saveid<kSaveScalarFieldCount)ApplyScalarField(legacyFields[saveid],change_string_to_int(line));
			saveid++;
			continue;
		}
		if(savesec==SAVE_SECTION_MAP_STRING){
			Map[saveid][savei]=line;
			savei++;
			if(savei==kSavedMapRowCount)saveid++,savei=0;
		}
		if(savesec==SAVE_SECTION_MAP_DATA){
			int i=savei,ssint[kReadIntBufferSize];
			for(int j=0;j<kReadIntBufferSize;j++)ssint[j]=0;
			change_string_to_ints(ssint,line);
			for(int j=0;j<=kSavedMapColMax;j++)Mapx[saveid][i][j]=ssint[j];
			savei++;
			if(savei==kSavedMapRowCount)savei=0,saveid++;
		}
		if(savesec==SAVE_SECTION_BAG_DATA){
			int i=savei,ssint[kReadIntBufferSize]={};
			change_string_to_ints(ssint,line);
			if(saveid==0)numt=change_string_to_int(line);
			if(saveid==1)things[i]=ssint[0],thing_num[i]=ssint[1],pd_thing[i]=ssint[2];
			if(!saveid)saveid++;
			else savei++;
		}
		if(savesec==SAVE_SECTION_MAP_FIND){
			if(!saveid){Map_allnum=change_string_to_int(line);saveid=1;}
			else {Map_Find[savei]=change_string_to_int(line);savei++;}
		}
	}
	return true;
}

bool Data::GetData(string s){//s为需要从哪个文件获取数据 
	string savePath = BuildDataPath(s);
	ifstream probe(savePath.c_str());
	if(!probe.is_open()){
		cout<<"打开存档失败！[Error: Not Exist]\n\n";
		system("pause");
		return false;
	}
	string firstLine;
	getline(probe,firstLine);
	probe.close();

	if(firstLine==kVersionedSaveMagic)return LoadVersionedData(savePath);
	return LoadLegacyData(savePath);
}

#undef YUEYING_SCALAR_FIELDS



