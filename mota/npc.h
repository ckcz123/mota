#pragma once
#include "monster.h"

class c_map_npc
{
public:
	void init(int);//初始化
	void show(int,int);//渲染
	int getId();//返回npc的id
	void changeState();//改变状态
	int getVisit() {return visit;}
	void setVisit(int t) {visit=t;}
private:
	int id;
	int state;
	int visit;
	hgeSprite *npc[4];
};