#include "stdafx.h"

extern c_map_floor map_floor[50];
extern c_hero hero;
extern constants consts;

void c_map_door::init(int t)
{
	type=t;
	if(t<=3)for(int i=0;i<4;i++) door[i]=new hgeSprite(consts.ht_map,32*(t-1),32*(i+2),32,32);
	if(t==4)for(int i=0;i<4;i++) door[i]=consts.s_upstair;
	if(t==5)for(int i=0;i<4;i++) door[i]=consts.s_downstair;
	if(t==6)for(int i=0;i<4;i++) door[i]=consts.s_shopleft;
	if(t==7)for(int i=0;i<4;i++) door[i]=consts.s_shopright;
	if(t==8){for(int i=0;i<4;i++) door[i]=new hgeSprite(consts.ht_map,96,32*(i+2),32,32);opened=false;}
	if(t==9){for(int i=0;i<4;i++) door[i]=new hgeSprite(consts.ht_map,96,32*(i+2),32,32);opened=true;}
	state=0;
}
void c_map_door::show(int i,int j)
{
	if(type!=0 && type<=10)door[state]->Render(j*32+consts.ScreenLeft,i*32);
}
bool c_map_door::open()
{
	state++;
	if(state==3)
	{
		this->init(0);
		return true;
	}
	return false;
}
void c_map_point::init(hgeSprite *s_type,hgeSprite *s_item,int s_monster,int s_door, int s_spe)
{
	if (s_type==NULL) type=consts.s_ground;
	else type=s_type;
	item=s_item;
	monster.init(s_monster);
	door.init(s_door);
	npc.init(s_door);
	special=s_spe;
}
void c_map_point::show(GfxFont* f,int i,int j)
{
	if(type==consts.s_barrier)
		consts.s_ground->Render(j*32+consts.ScreenLeft,i*32);
	type->Render(j*32+consts.ScreenLeft,i*32);
	if(item!=NULL) item->Render(j*32+consts.ScreenLeft,i*32);
	monster.show(f,i,j);
	door.show(i,j);
	npc.show(i,j);
	if(special!=0) {
		switch (special)
		{
		case 201:
			consts.s_sigh->Render(j*32+consts.ScreenLeft,i*32);
			break;
		case 202:
			consts.s_sighed->Render(j*32+consts.ScreenLeft,i*32);
			break;
		case 203:
			consts.s_up->Render(j*32+consts.ScreenLeft,i*32);
			break;
		case 204:
			consts.s_left->Render(j*32+consts.ScreenLeft,i*32);
			break;
		case 205:
			consts.s_right->Render(j*32+consts.ScreenLeft,i*32);
			break;
		case 206:
			consts.s_down->Render(j*32+consts.ScreenLeft,i*32);
			break;
		case 207:
			consts.s_wall->Render(j*32+consts.ScreenLeft,i*32);
			break;
		case 208:
			consts.s_portal->Render(j*32+consts.ScreenLeft,i*32);
			break;
		case 209:
			consts.s_flower->Render(j*32+consts.ScreenLeft,i*32);
			break;
		case 210:
			consts.s_box->Render(j*32+consts.ScreenLeft,i*32);
			break;
		case 211:
			consts.s_flower->Render(j*32+consts.ScreenLeft,i*32);
			consts.s_boxed->Render(j*32+consts.ScreenLeft,i*32);
			break;
		default:
			break;
		}

	}
}
bool c_map_point::isGround()
{
	return type==consts.s_ground;
}
bool c_map_point::canMove(int f)
{
	if(type==consts.s_ground)
	{
		if(door.getType()!=0)
		{
			bool c=false;
			switch(door.getType())
			{
			case 1:c=hero.openYellowDoor();break;
			case 2:c=hero.openBlueDoor();break;
			case 3:c=hero.openRedDoor();break;
			case 8:case 9:c=hero.openSpecialDoor();break;
			case 4:hero.upstair();break;
			case 5:hero.downstair();break;
			}
			if (door.getType()>=40 && door.getType()<=80) {
				consts.msg=consts.MESSAGE_NPC;
				return false;
			}
			if(c)
			{
				consts.opening=true;
				consts.map_openingdoor=&door;
				if (consts.music)
					consts.hge->Effect_PlayEx(consts.he_OpenDoor,consts.volume);
			}
			return c;
		}
		if(monster.getId()!=0)
		{
			if(hero.canBeat(monster))
			{
				consts.battling=true;
				consts.monster_battling=&monster;
			}
			return false;
		}
		if(special!=0)
		{
			if(special==207) {
				if (hero.getNowFloor()<30) {
					special=208;
					consts.setMsg("我：\n这里竟然有个暗墙？后面还有\n个暗道？走，进去看看！");
					return false;
				}
				else {
					special=0;
					return true;
				}
			}
			if(special==208) {
				hero.specialMove();
				return false;
			}
			if(special==202) return false;
			if(special==203 && f==0) return false;
			if(special==204 && f==2) return false;
			if(special==205 && f==1) return false;
			if(special==206 && f==3) return false;
		}
		return true;
	}
	else return false;
}
bool c_map_point::openSpecial()
{
	if (door.getType()!=8) return false;
	door.setOpened();
	consts.opening=true;
	consts.map_openingdoor=&door;
	if (consts.music)
		consts.hge->Effect_PlayEx(consts.he_OpenDoor,consts.volume);
	return true;
}
void c_map_point::changeLight()
{
	if (special!=201 && special!=202) return;
	special=403-special;
}
int c_map_point::getItemID()
{
	int c=0;
	if(item==consts.s_lightning)c=10;
	if(item==consts.s_redjewel)c=11;
	if(item==consts.s_bluejewel)c=12;
	if(item==consts.s_enemyinfo)c=13;
	if(item==consts.s_allkey)c=14;
	if(item==consts.s_yellowkey)c=15;
	if(item==consts.s_bluekey)c=16;
	if(item==consts.s_redkey)c=17;
	if(item==consts.s_redpotion)c=18;
	if(item==consts.s_bluepotion)c=19;
	if(item==consts.s_sword1)c=20;
	if(item==consts.s_shield1)c=21;
	if(item==consts.s_coin)c=22;
	if(item==consts.s_fly)c=23;
	if(item==consts.s_cross)c=24;
	if(item==consts.s_sword2)c=25;
	if(item==consts.s_shield2)c=26;
	if(item==consts.s_floor)c=27;
	if(item==consts.s_stick)c=28;
	if(item==consts.s_fly2)c=29;
	if(item==consts.s_drink)c=30;
	if(item==consts.s_sword3)c=31;
	if(item==consts.s_shield3)c=32;
	if(item==consts.s_atk)c=33;
	if(item==consts.s_def)c=34;
	if(item==consts.s_life)c=35;
	return c;
}
void c_map_point::save(FILE* f)
{
	int g=0;
	if(type==consts.s_ground)g=0;
	if(type==consts.s_wall)g=1;
	if(type==consts.s_water)g=2;
	if(type==consts.s_sky)g=3;
	if(type==consts.s_barrier)g=4;
	int doortype=door.getType();
	if (doortype==8 && door.isOpened()) doortype=9;
	fprintf_s(f,"%d %d %d %d %d %d %d\n",g, getItemID(),monster.getId(),doortype,npc.getId(),npc.getVisit(),special);
}
void c_map_point::load(FILE* f)
{
	int g,i,m,d,n,t;
	fscanf_s(f,"%d %d %d %d %d %d %d\n",&g,&i,&m,&d,&n,&t,&special);
	if(g==0)type=consts.s_ground;
	if(g==1)type=consts.s_wall;
	if(g==2)type=consts.s_water;
	if(g==3)type=consts.s_sky;
	if(g==4)type=consts.s_barrier;
	item=NULL;
	switch(i)
	{
	case 10:item=consts.s_lightning;break;
	case 11:item=consts.s_redjewel;break;
	case 12:item=consts.s_bluejewel;break;
	case 13:item=consts.s_enemyinfo;break;
	case 14:item=consts.s_allkey;break;
	case 15:item=consts.s_yellowkey;break;
	case 16:item=consts.s_bluekey;break;
	case 17:item=consts.s_redkey;break;
	case 18:item=consts.s_redpotion;break;
	case 19:item=consts.s_bluepotion;break;
	case 20:item=consts.s_sword1;break;
	case 21:item=consts.s_shield1;break;
	case 22:item=consts.s_coin;break;
	case 23:item=consts.s_fly;break;
	case 24:item=consts.s_cross;break;
	case 25:item=consts.s_sword2;break;
	case 26:item=consts.s_shield2;break;
	case 27:item=consts.s_floor;break;
	case 28:item=consts.s_stick;break;
	case 29:item=consts.s_fly2;break;
	case 30:item=consts.s_drink;break;
	case 31:item=consts.s_sword3;break;
	case 32:item=consts.s_shield3;break;
	case 33:item=consts.s_atk;break;
	case 34:item=consts.s_def;break;
	case 35:item=consts.s_life;break;
	}
	monster.init(m);
	door.init(d);
	npc.init(n);
	npc.setVisit(t);
}
void c_map_floor::init(int d,int ch[30][30])
{
	id=d;
	ux=-100;uy=-100;dx=-100;dy=-100;
	for(int i=0;i<consts.map_height;i++)
	{
		for(int j=0;j<consts.map_width;j++)
		{
			if(ch[i][j]==0)info[i][j].init(consts.s_ground,NULL,0,0);
			if(ch[i][j]==1)info[i][j].init(consts.s_wall,NULL,0,0);
			if(ch[i][j]==2)info[i][j].init(consts.s_water,NULL,0,0);
			if(ch[i][j]==3)info[i][j].init(consts.s_sky,NULL,0,0);
			if(ch[i][j]==4)info[i][j].init(consts.s_barrier,NULL,0,0);
			if(ch[i][j]==10)info[i][j].init(NULL,consts.s_lightning,0,0);
			if(ch[i][j]==11)info[i][j].init(NULL,consts.s_redjewel,0,0);
			if(ch[i][j]==12)info[i][j].init(NULL,consts.s_bluejewel,0,0);
			if(ch[i][j]==13)info[i][j].init(NULL,consts.s_enemyinfo,0,0);
			if(ch[i][j]==14)info[i][j].init(NULL,consts.s_allkey,0,0);
			if(ch[i][j]==15)info[i][j].init(NULL,consts.s_yellowkey,0,0);
			if(ch[i][j]==16)info[i][j].init(NULL,consts.s_bluekey,0,0);
			if(ch[i][j]==17)info[i][j].init(NULL,consts.s_redkey,0,0);
			if(ch[i][j]==18)info[i][j].init(NULL,consts.s_redpotion,0,0);
			if(ch[i][j]==19)info[i][j].init(NULL,consts.s_bluepotion,0,0);
			if(ch[i][j]==20)info[i][j].init(NULL,consts.s_sword1,0,0);
			if(ch[i][j]==21)info[i][j].init(NULL,consts.s_shield1,0,0);
			if(ch[i][j]==22)info[i][j].init(NULL,consts.s_coin,0,0);
			if(ch[i][j]==23)info[i][j].init(NULL,consts.s_fly,0,0);
			if(ch[i][j]==24)info[i][j].init(NULL,consts.s_cross,0,0);
			if(ch[i][j]==25)info[i][j].init(NULL,consts.s_sword2,0,0);
			if(ch[i][j]==26)info[i][j].init(NULL,consts.s_shield2,0,0);
			if(ch[i][j]==27)info[i][j].init(NULL,consts.s_floor,0,0);
			if(ch[i][j]==28)info[i][j].init(NULL,consts.s_stick,0,0);
			if(ch[i][j]==29)info[i][j].init(NULL,consts.s_fly2,0,0);
			if(ch[i][j]==30)info[i][j].init(NULL,consts.s_drink,0,0);
			if(ch[i][j]==31)info[i][j].init(NULL,consts.s_sword3,0,0);
			if(ch[i][j]==32)info[i][j].init(NULL,consts.s_shield3,0,0);
			if(ch[i][j]==33)info[i][j].init(NULL,consts.s_atk,0,0);
			if(ch[i][j]==34)info[i][j].init(NULL,consts.s_def,0,0);
			if(ch[i][j]==35)info[i][j].init(NULL,consts.s_life,0,0);
			if(ch[i][j]==81)info[i][j].init(NULL,NULL,0,6);
			if(ch[i][j]==83)info[i][j].init(NULL,NULL,0,7);
			if(ch[i][j]==91)info[i][j].init(NULL,NULL,0,1);
			if(ch[i][j]==92)info[i][j].init(NULL,NULL,0,2);
			if(ch[i][j]==93)info[i][j].init(NULL,NULL,0,3);
			if(ch[i][j]==96)info[i][j].init(NULL,NULL,0,8);
			if(ch[i][j]==97)info[i][j].init(NULL,NULL,0,9);
			if (ch[i][j]>=40 && ch[i][j]<=80)
				info[i][j].init(NULL,NULL,0,ch[i][j]);
			if(ch[i][j]==94)
			{
				info[i][j].init(NULL,NULL,0,4);
				ux=j;
				uy=i;
			}
			if(ch[i][j]==95)
			{
				info[i][j].init(NULL,NULL,0,5);
				dx=j;
				dy=i;
			}
			if(ch[i][j]>=101 && ch[i][j]<=200)info[i][j].init(NULL,NULL,ch[i][j]-100,0);
			if(ch[i][j]>=201 && ch[i][j]<=300) {
				info[i][j].init(NULL,NULL,0,0,ch[i][j]);
			}
		}
	}
}
void c_map_floor::show()
{
	GfxFont *f=new GfxFont("楷体",12,true);
	for(int i=0;i<consts.map_height;i++)
	{
		for(int j=0;j<consts.map_width;j++)
		{
			info[i][j].show(f,i,j);
		}
	}
	delete f;
}
void c_map_floor::animation()
{	
	for(int i=0;i<consts.map_height;i++)
		for(int j=0;j<consts.map_width;j++)
			info[i][j].animation();
}
void c_map_floor::printMonsterInfo(int i,int j)
{
	info[j][i].printMonsterInfo();
}
bool c_map_floor::canMove(int x,int y,int f)
{
	if (info[y][x].canMove(f)) {
		int spe=info[y][x].getSpecial();
		if (spe!=210 && spe!=211) return true;
		int sx=x+hero.dir[0][f],sy=y+hero.dir[1][f];
		if (!info[sy][sx].isGround()) return false;
		if (info[sy][sx].getSpecial()==0 || info[sy][sx].getSpecial()==209) return true;
		return false;
	}
	return false;
}
int c_map_floor::getItem(int x,int y)
{
	int c=info[y][x].getItemID();
	if (c!=10)
		info[y][x].distroyItem();
	return c;
}
int c_map_floor::getSpecial(int x, int y)
{
	return info[y][x].getSpecial();
}
void c_map_floor::setSpecial(int x, int y, int _spe)
{
	info[y][x].setSpecial(_spe);
}
void c_map_floor::getDownPosition(int &x,int &y)
{
	x=dx;
	y=dy;
	if (hero.getNowFloor()==21)
		y-=2;
}
void c_map_floor::getUpPosition(int &x,int &y)
{
	x=ux;
	y=uy;
}
bool c_map_floor::checkChallenge()
{
	if (id<30 || finished) return false;
	if (id==31) {
		for (int i=0;i<consts.map_width;i++) {
			for (int j=0;j<consts.map_width;j++) {
				if (info[i][j].getSpecial()==207)
					return false;
			}
		}
		return true;
	}
	if (id==32) {
		for (int i=0;i<consts.map_width;i++) {
			for (int j=0;j<consts.map_width;j++) {
				if (info[i][j].getSpecial()==201)
					return false;
			}
		}
		return true;
	}
	if (id==33 || id==34 || id==35) {
		for (int i=0;i<consts.map_width;i++) {
			for (int j=0;j<consts.map_width;j++) {
				if (info[i][j].getSpecial()==202)
					return false;
			}
		}
		return true;
	}
	if (id==37) {
		int darkcnt=0;
		for (int i=0;i<11;i++)
			for (int j=0;j<11;j++)
				if (info[i][j].getSpecial()==202)
					darkcnt++;
		if (darkcnt!=8) return false;
		int res[8][2]={{4,2},{5,2},{5,3},{6,2},{7,2},{7,3},{4,8},{6,6}};
		for (int i=0;i<8;i++)
			if (info[res[i][0]][res[i][1]].getSpecial()!=202) return false;
		return true;
	}
	if (id==40) {
		for (int i=0;i<9;i++)
			for (int j=0;j<9;j++)
				if (info[i+2][j].getSpecial()!=map_floor[id-1].getinfo(i+2,8-j)->getSpecial())
					return false;
		return true;
	}
	if (id==41) {
		int darkcnt=0;
		for (int i=0;i<11;i++)
			for (int j=0;j<11;j++)
				if (info[i][j].getSpecial()==202)
					darkcnt++;
		if (darkcnt!=3) return false;
		if (info[4][2].getSpecial()!=202 || info[6][4].getSpecial()!=202 || info[6][6].getSpecial()!=202) return false;
		return true;
	}
	if (id==42 || id==43) {
		for (int i=0;i<consts.map_width;i++) {
			for (int j=0;j<consts.map_width;j++) {
				if (info[i][j].getSpecial()==209 || info[i][j].getSpecial()==210)
					return false;
			}
		}
		return true;
	}
	return false;
}
void c_map_floor::finishChallenge()
{
	finished=true;
	if (ux>=1 && info[uy][ux-1].openSpecial()) return;
	if (uy>=1 && info[uy-1][ux].openSpecial()) return;
	if (ux<consts.map_width-1 && info[uy][ux+1].openSpecial()) return;
	if (uy<consts.map_width-1 && info[uy+1][ux].openSpecial()) return;
}
void c_map_floor::changeLight(int x, int y)
{
	if (id==33) {
		x-=6;y-=4;
		if (x<0 || x>2 || y<0 || y>2) return;
		info[y+4][x+2].changeLight();
		if (x>0) info[y+4][x+1].changeLight();
		if (y>0) info[y+3][x+2].changeLight();
		if (x<2) info[y+4][x+3].changeLight();
		if (y<2) info[y+5][x+2].changeLight();
	}
	else if (id==34) {
		x-=1;y-=4;
		if (x<0 || x>3 || y<0 || y>3) return;
		info[y+4][x+6].changeLight();
		if (x>0) info[y+4][x+5].changeLight();
		if (y>0) info[y+3][x+6].changeLight();
		if (x<3) info[y+4][x+7].changeLight();
		if (y<3) info[y+5][x+6].changeLight();
	}
	else if (id==35) {
		x-=6;y-=3;
		if (x<0 || x>4 || y<0 || y>4) return;
		info[y+3][x].changeLight();
		if (x>0) info[y+3][x-1].changeLight();
		if (y>0) info[y+2][x].changeLight();
		if (x<4) info[y+3][x+1].changeLight();
		if (y<4) info[y+4][x].changeLight();
	}
}
void c_map_floor::save(FILE* f)
{
	fprintf_s(f,"%d %d %d %d\n",dx,dy,ux,uy);
	for(int i=0;i<consts.map_height;i++)
	{
		for(int j=0;j<consts.map_width;j++)
		{
			info[i][j].save(f);
		}
	}
}
void c_map_floor::load(FILE* f)
{
	fscanf_s(f,"%d %d %d %d\n",&dx,&dy,&ux,&uy);
	for(int i=0;i<consts.map_height;i++)
	{
		for(int j=0;j<consts.map_width;j++)
		{
			info[i][j].load(f);
		}
	}
	finished=false;
}