#include "stdafx.h"

constants::constants()
{
	yellow_flag=blue_flag=red_flag=attack_flag=defence_flag=big_flag=small_flag=false;
	hge=NULL;
	volume=30;
	bgmvolume=100;
	ScreenLeft=240;
	music=true;
	map_width=11;map_height=11;
	map_floornum=22;
	special_floornum=45;
}

void constants::init()
{
	canfly=book=stick=cross=trueend=moving=opening=battling=flooring=false;
	lefttime=100.0;
	playtime=0.0;
	step=0;
	time_move=time_open=time_animation=time_battle=time_floor=0;
	isMyTurn=true;
	beatStarted=false;
	for (int i=0;i<10;i++) sd[i].hp=0;
}
void constants::loadResources()
{
	ht_map=hge->Texture_Load("Res/map.png");
	ht_icon=hge->Texture_Load("Res/icon.png");
	ht_hero=hge->Texture_Load("Res/hero.png");
	ht_monster=hge->Texture_Load("Res/monster.png");
	ht_skin=hge->Texture_Load("Res/skin.png");
	ht_npc=hge->Texture_Load("Res/npc.png");
	ht_special=hge->Texture_Load("Res/special.png");
	he_GetItem=hge->Effect_Load("Res/item.ogg");
	he_OpenDoor=hge->Effect_Load("Res/door.ogg");
	he_Attack=hge->Effect_Load("Res/attack.ogg");
	he_Music=hge->Effect_Load("Res/bgm.mp3");
	hgef=new hgeFont("Res/font.fnt");
	//ht_map
	s_ground=new hgeSprite(ht_map,0,0,32,32);
	s_wall=new hgeSprite(ht_map,32,0,32,32);
	s_water=new hgeSprite(ht_map,32,32,32,32);
	s_sky=new hgeSprite(ht_map,0,32,32,32);
	s_lightning=new hgeSprite(ht_npc,0,128,32,32);
	s_barrier=new hgeSprite(ht_special,128,960,32,32);
	//ht_door
	s_yellowdoor=new hgeSprite(ht_map,0,64,32,32);
	s_bluedoor=new hgeSprite(ht_map,32,64,32,32);
	s_reddoor=new hgeSprite(ht_map,64,64,32,32);
	s_specialdoor=new hgeSprite(ht_map,96,64,32,32);
	s_downstair=new hgeSprite(ht_map,0,192,32,32);
	s_upstair=new hgeSprite(ht_map,32,192,32,32);
	s_shopleft=new hgeSprite(ht_map,0,224,32,32);
	s_shopright=new hgeSprite(ht_map,64,224,32,32);
	//ht_item
	s_yellowkey=new hgeSprite(ht_icon,0,0,32,32);
	s_bluekey=new hgeSprite(ht_icon,32,0,32,32);
	s_redkey=new hgeSprite(ht_icon,64,0,32,32);
	s_allkey=new hgeSprite(ht_icon,96,0,32,32);
	s_coin=new hgeSprite(ht_icon,0,64,32,32);
	s_fly=new hgeSprite(ht_icon,0,192,32,32);
	s_fly2=new hgeSprite(ht_icon,0,192,32,32);
	s_floor=new hgeSprite(ht_icon,32,160,32,32);
	s_level=new hgeSprite(ht_icon,64,128,32,32);
	s_storey=new hgeSprite(ht_icon,64,96,32,32);
	s_cross=new hgeSprite(ht_icon,96,160,32,32);
	s_stick=new hgeSprite(ht_icon,0,160,32,32);
	s_drink=new hgeSprite(ht_icon,32,192,32,32);
	s_heart=new hgeSprite(ht_icon,64,192,32,32);
	s_expr=new hgeSprite(ht_icon,96,192,32,32);
	s_time=new hgeSprite(ht_icon,32,96,32,32);
	s_step=new hgeSprite(ht_icon,32,128,32,32);
	s_damage=new hgeSprite(ht_icon,64,160,32,32);
	s_enemyinfo=new hgeSprite(ht_icon,32,64,32,32);
	s_bluejewel=new hgeSprite(ht_icon,64,32,32,32);
	s_redjewel=new hgeSprite(ht_icon,96,32,32,32);
	s_redpotion=new hgeSprite(ht_icon,64,64,32,32);
	s_bluepotion=new hgeSprite(ht_icon,96,64,32,32);
	s_sword1=new hgeSprite(ht_icon,0,32,32,32);
	s_shield1=new hgeSprite(ht_icon,32,32,32,32);
	s_sword2=new hgeSprite(ht_icon,0,96,32,32);
	s_shield2=new hgeSprite(ht_icon,0,128,32,32);
	s_sword3=new hgeSprite(ht_icon,96,96,32,32);
	s_shield3=new hgeSprite(ht_icon,96,128,32,32);
	//special
	s_sigh=new hgeSprite(ht_special,192,800,32,32);
	s_sighed=new hgeSprite(ht_special,192,832,32,32);
	s_up=new hgeSprite(ht_special,0,928,32,32);
	s_down=new hgeSprite(ht_special,32,928,32,32);
	s_left=new hgeSprite(ht_special,64,928,32,32);
	s_right=new hgeSprite(ht_special,96,928,32,32);
	s_portal=new hgeSprite(ht_special,192,928,32,32);
	s_flower=new hgeSprite(ht_special,224,736,32,32);
	s_box=new hgeSprite(ht_special,192,768,32,32);
	s_boxed=new hgeSprite(ht_special,224,768,32,32);
	s_atk=new hgeSprite(ht_special,224,832,32,32);
	s_def=new hgeSprite(ht_special,224,864,32,32);
	s_life=new hgeSprite(ht_special,224,896,32,32);
	hc_Music=hge->Effect_PlayEx(he_Music,bgmvolume,0,1,true);
}

void constants::destroy()
{
	hge->Texture_Free(ht_map);
	hge->Texture_Free(ht_icon);
	hge->Texture_Free(ht_hero);
	hge->Texture_Free(ht_skin);
	hge->Texture_Free(ht_monster);
	hge->Texture_Free(ht_npc);
	hge->Effect_Free(he_GetItem);
	hge->Effect_Free(he_Music);
	hge->Effect_Free(he_OpenDoor);
	hge->Effect_Free(he_Attack);
	delete hgef;
}

void constants::setMsg(const char* s[50])
{
	hint.clear();
	for (int i=0;i<50;i++) {
		if (s[i]==NULL) break;
		hint.push_back(string(s[i]));
	}
	lasttime=clock();
	nowcnt=0;
	msg=MESSAGE_HINT;
}

void constants::setMsg(const char* s) 
{
	hint.clear();
	hint.push_back(string(s));
	lasttime=clock();
	nowcnt=0;
	msg=MESSAGE_HINT;
}

void constants::goOn(c_hero* hero, c_map_floor* currFloor, float dt)
{
	playtime+=dt;
	if(moving) // 移动
	{
		time_move+=dt;
		if(time_move>=0.03)
		{
			time_move-=0.03;
			if(hero->moveComplete())
				moving=false;
		}		
	}
	if(flooring) // 上下楼
	{
		time_floor+=dt;
		if(time_floor>=0.4)
		{
			time_floor=0;
			flooring=false;
		}
	}
	if(opening) // 开门
	{
		time_open+=dt;
		if(time_open>=0.05)
		{
			time_open-=0.05;
			if(map_openingdoor->open())
				opening=false;
		}		
	}

	time_animation+=dt;
	if(time_animation>=0.1) // 四次后又回到自身状态
	{
		time_animation-=0.1;
		currFloor->animation();
	}

	if(battling) // 战斗
	{
		if (!beatStarted)
		{
			monster_life=monster_battling->getHp();
			if(monster_battling->getSpecial()==1)
				hero->specialDamage();
		}
		beatStarted=true;
		time_battle+=dt;
		if(time_battle>=0.05)
		{
			time_battle-=0.05;
			if(isMyTurn)
			{
				if(!hero->attack(*monster_battling))
				{
					battling=false;
					beatStarted=false;
					if (monster_battling->getId()==38) {
						setMsg("？？？：\n你...竟然赢了我！\n不过，这座塔马上就要倒了，\n你们都和我一起陪葬吧！");
						lefttime=70.00;
						canfly=false;
					}
					hero->addHp(hero->getSpeLife(monster_life));
					monster_battling->init(0);
				}
				else isMyTurn=false;
			}
			else 
			{
				hero->beAttacked(*monster_battling);
				isMyTurn=true;
			}
		}
	}

	if (msg!=MESSAGE_WIN && lefttime<80 && lefttime>=0) lefttime-=dt;
	if (lefttime<0) {
		msg=MESSAGE_LOSE;
		lefttime=0;
	}
}

void constants::printInfo()
{
	if (lefttime<80)
		hgef->printf(ScreenLeft+16,16,HGETEXT_LEFT,"%.2f",lefttime);
	s_step->Render(ScreenLeft+map_width*32+16, 308);
	hgef->printf(ScreenLeft+map_width*32+60, 310, HGETEXT_LEFT, "%d", step);
	int ptm=playtime;
	s_time->Render(ScreenLeft+map_width*32+16,264);
	if (ptm>=3600)
		hgef->printf(ScreenLeft+map_width*32+60,268,HGETEXT_LEFT,"%02d : %02d : %02d",ptm/3600, (ptm/60)%60, ptm%60);
	else hgef->printf(ScreenLeft+map_width*32+60,268,HGETEXT_LEFT,"%02d : %02d", ptm/60, ptm%60);
}

void constants::save(FILE* f) 
{
	fprintf_s(f, "%d %d %d %d %d %d %d %d %.2f %.2f\n", map_floornum, map_width, map_height, canfly?1:0, book?1:0, stick?1:0, cross?1:0, step, lefttime, playtime);
}

void constants::load(FILE* f)
{
	int _fly, _book, _stick, _cross;
	fscanf_s(f, "%d %d %d %d %d %d %d %d %f %f", &map_floornum, &map_width, &map_height, &_fly, &_book, &_stick, &_cross, &step, &lefttime, &playtime);
	canfly=_fly==1;
	book=_book==1;
	stick=_stick==1;
	cross=_cross==1;
	trueend=moving=opening=battling=flooring=false;
}