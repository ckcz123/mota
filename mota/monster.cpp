#include "stdafx.h"

extern c_hero hero;
extern constants consts;
void c_monster::init(int t)
{
	id=t;
	state=0;
	switch(t)
	{
	case 1:strcpy_s(name,"绿色史莱姆");position=0;hp=50;atk=20;def=1;money=1;experience=1;special=0;break;
	case 2:strcpy_s(name,"红色史莱姆");position=1;hp=70;atk=15;def=2;money=2;experience=2;special=0;break;
	case 3:strcpy_s(name,"青头怪");position=2;hp=200;atk=35;def=10;money=5;experience=5;special=0;break;
	case 4:strcpy_s(name,"史莱姆王");position=3;hp=700;atk=250;def=125;money=32;experience=30;special=0;break;
	case 5:strcpy_s(name,"小蝙蝠");position=4;hp=100;atk=20;def=5;money=3;experience=3;special=0;break;
	case 6:strcpy_s(name,"大蝙蝠");position=5;hp=150;atk=65;def=30;money=10;experience=8;special=0;break;
	case 7:strcpy_s(name,"红蝙蝠");position=6;hp=550;atk=160;def=95;money=25;experience=20;special=0;break;
	case 8:strcpy_s(name,"冥灵魔王");position=7;hp=30000;atk=2100;def=1700;money=250;experience=220;special=0;break;
	case 9:strcpy_s(name,"初级法师");position=8;hp=125;atk=50;def=25;money=10;experience=7;special=0;break;
	case 10:strcpy_s(name,"高级法师");position=9;hp=1000;atk=200;def=110;money=30;experience=25;special=0;break;
	case 11:strcpy_s(name,"初级巫师");position=10;hp=500;atk=120;def=70;money=20;experience=17;special=3;break;
	case 12:strcpy_s(name,"高级巫师");position=11;hp=1234;atk=400;def=260;money=47;experience=45;special=3;break;
	case 13:strcpy_s(name,"骷髅人");position=12;hp=110;atk=25;def=5;money=5;experience=4;special=0;break;
	case 14:strcpy_s(name,"骷髅士兵");position=13;hp=150;atk=40;def=20;money=8;experience=6;special=0;break;
	case 15:strcpy_s(name,"骷髅队长");position=14;hp=400;atk=90;def=50;money=15;experience=12;special=0;break;
	case 16:strcpy_s(name,"冥队长");position=15;hp=3000;atk=880;def=790;money=80;experience=72;special=0;break;
	case 17:strcpy_s(name,"兽人");position=16;hp=300;atk=75;def=45;money=13;experience=10;special=0;break;
	case 18:strcpy_s(name,"兽面武士");position=17;hp=900;atk=450;def=330;money=50;experience=50;special=0;break;
	case 19:strcpy_s(name,"石头人");position=18;hp=30;atk=95;def=0;money=15;experience=15;special=2;break;
	case 20:strcpy_s(name,"影子战士");position=19;hp=3100;atk=1250;def=1050;money=105;experience=95;special=0;break;
	case 21:strcpy_s(name,"初级卫兵");position=20;hp=450;atk=150;def=90;money=22;experience=19;special=0;break;
	case 22:strcpy_s(name,"中级卫兵");position=21;hp=1250;atk=500;def=400;money=55;experience=55;special=0;break;
	case 23:strcpy_s(name,"高级卫兵");position=22;hp=1500;atk=560;def=460;money=60;experience=60;special=0;break;
	case 24:strcpy_s(name,"双手剑士");position=23;hp=1200;atk=620;def=520;money=65;experience=75;special=0;break;
	case 25:strcpy_s(name,"冥战士");position=24;hp=2000;atk=680;def=590;money=70;experience=65;special=0;break;
	case 26:strcpy_s(name,"初级骑士");position=25;hp=850;atk=350;def=200;money=45;experience=40;special=0;break;
	case 27:strcpy_s(name,"高级骑士");position=26;hp=900;atk=750;def=650;money=77;experience=70;special=0;break;
	case 28:strcpy_s(name,"灵武士");position=27;hp=3000;atk=980;def=900;money=88;experience=75;special=0;break;
	case 29:strcpy_s(name,"红衣魔王");position=28;hp=15000;atk=1000;def=1000;money=100;experience=100;special=0;break;
	case 30:strcpy_s(name,"魔法警卫");position=29;hp=1300;atk=300;def=150;money=40;experience=35;special=1;break;
	case 31:strcpy_s(name,"灵法师");position=30;hp=1500;atk=830;def=730;money=80;experience=70;special=1;break;
	case 36:strcpy_s(name,"冥队长");position=15;hp=3333;atk=1200;def=1133;money=112;experience=100;special=0;break;
	case 38:strcpy_s(name,"黑衣魔王");position=36;hp=50000;atk=3300;def=2600;money=0;experience=0;special=0;break;
	case 39:strcpy_s(name,"铁面人");position=34;hp=50;atk=1221;def=0;money=127;experience=111;special=2;break;
	case 46:strcpy_s(name,"高级巫师");position=11;hp=5000;atk=2500;def=1500;money=0;experience=0;special=3;break;
	case 47:strcpy_s(name,"铁面人");position=34;hp=100;atk=2333;def=0;money=0;experience=0;special=2;break;
	case 48:strcpy_s(name,"灵武士");position=27;hp=1600;atk=1306;def=1200;money=117;experience=100;special=0;break;
	case 49:strcpy_s(name,"红衣魔王");position=28;hp=20000;atk=1777;def=1444;money=133;experience=133;special=0;break;
	default:position=-1;
	}
	if (position!=-1)
		for(int i=0;i<4;i++)
			monster[i]=new hgeSprite(consts.ht_monster,32*i,32*position,32,32);
}
void c_monster::show(GfxFont* f,int i,int j)
{
	if(id!=0)
	{
		monster[state]->Render(j*32+consts.ScreenLeft,i*32);
		if (consts.book && f!=NULL && !(consts.battling && consts.monster_battling==this)) {
			int damage=hero.getDamage(*this);
			int hp=hero.getHP();
			if (damage<hp) damage-=hero.getSpeLife(this->hp);
			if (damage>=hp)
				f->SetColor(4294901760ul);
			else if (damage<=hp/16)
				f->SetColor(4278255360ul);
			else if (damage<=hp/8)
				f->SetColor(4290047668ul);
			else if (damage<=hp/4)
				f->SetColor(4291677440ul);
			else if (damage<=hp/2)
				f->SetColor(4293844098ul);
			else if (damage<=hp*2/3)
				f->SetColor(4294951361ul);
			else f->SetColor(4294942842ul);
			if (damage>=c_hero::MAX_DAMAGE)
				f->Print(j*32+consts.ScreenLeft,i*32+20,"???");
			else if (damage<100000)
				f->Print(j*32+consts.ScreenLeft,i*32+20,"%d",damage);
			else
				f->Print(j*32+consts.ScreenLeft,i*32+20,"%dw",damage/10000);
		}
	}
}
void c_monster::printInfo()
{
	if(id!=0)
	{
		int py=16;
		GfxFont *f=new GfxFont("楷体",24);
		char s0[100]="";
		if (special==1) strcpy_s(s0, "（吸血）");
		else if (special==2) strcpy_s(s0, "（坚固）");
		else if (special==3) strcpy_s(s0, "（魔攻）");
		f->Print(consts.ScreenLeft+consts.map_width*32+16,py,"%s%s",name,s0);
		delete f;
		py+=32;
		consts.s_heart->Render(consts.ScreenLeft+consts.map_width*32+16,py);
		consts.hgef->printf(consts.ScreenLeft+consts.map_width*32+60,py,HGETEXT_LEFT,"%d",hp);
		py+=32;
		consts.s_sword1->Render(consts.ScreenLeft+consts.map_width*32+16,py);
		consts.hgef->printf(consts.ScreenLeft+consts.map_width*32+60,py,HGETEXT_LEFT,"%d",atk);
		py+=32;
		consts.s_shield1->Render(consts.ScreenLeft+consts.map_width*32+16,py);
		consts.hgef->printf(consts.ScreenLeft+consts.map_width*32+60,py,HGETEXT_LEFT,"%d",special==2?hero.getAtk()-1:def);
		py+=32;
		consts.s_coin->Render(consts.ScreenLeft+consts.map_width*32+16,py);
		consts.hgef->printf(consts.ScreenLeft+consts.map_width*32+60,py,HGETEXT_LEFT,"%d",money);
		py+=32;
		consts.s_expr->Render(consts.ScreenLeft+consts.map_width*32+16,py);
		consts.hgef->printf(consts.ScreenLeft+consts.map_width*32+60,py,HGETEXT_LEFT,"%d",experience);
		if(!consts.battling)
		{
			py+=32;
			consts.s_damage->Render(consts.ScreenLeft+consts.map_width*32+16,py);
			int damage=hero.getDamage(*this);
			if (damage<hero.getHP()) damage-=hero.getSpeLife(hp);
			if (damage==c_hero::MAX_DAMAGE)
				consts.hgef->printf(consts.ScreenLeft+consts.map_width*32+60,py,HGETEXT_LEFT,"???");
			else
				consts.hgef->printf(consts.ScreenLeft+consts.map_width*32+60,py,HGETEXT_LEFT,"%d",damage);
		}
	}
}
void c_monster::changeState()
{
	state++;
	state%=4;
}