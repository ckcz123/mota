#pragma once
#include <hge.h>
#include <hgefont.h>
#include <hgesprite.h>
#include "gfxfont.h"
using namespace std;

class c_monster
{
public:
	void init(int);//初始化
	void show(GfxFont*,int,int);//渲染
	void printInfo();//输出信息
	void changeState();//怪物动画
	int getId() {return id;}
	int getHp() {return hp;}
	bool beAttacked(int hero_atk) {hp-=special==2?1:hero_atk-def;return hp<=0;}
	int getAtk() {return atk;}
	int getDef() {return def;}
	int getMoney() {return money;}
	int getExperience() {return experience;}
	int getSpecial() {return special;}
private:
	char name[30];
	int id,hp,atk,def,money,experience,special;
	int state,position;
	hgeSprite *monster[4];
};