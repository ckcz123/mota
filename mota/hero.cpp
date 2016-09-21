#include "stdafx.h"

extern c_map_floor map_floor[50];
extern constants consts;

c_hero::c_hero()
{
	dir[0][0]=dir[0][3]=dir[1][1]=dir[1][2]=0;
	dir[0][1]=dir[1][3]=-1;
	dir[0][2]=dir[1][0]=1;
};
void c_hero::init()
{
	lv=1;
	hp=1000;
	atk=10;
	def=10;
	money=0;
	experience=0;
	redkey=0;
	bluekey=0;
	yellowkey=0;
	special=0;
	x=5;
	y=9;
	face=3;
	move=0;
	now_floor=0;
	max_floor=0;
	fly_floor=0;
}
float c_hero::nextX()
{
	return x+dir[0][face];
}
float c_hero::nextY()
{
	return y+dir[1][face];
}
bool c_hero::canMove(int f)
{
	face=f;
	int special=map_floor[now_floor].getSpecial(x,y);
	if (special==203 && f!=3) return false;
	if (special==204 && f!=1) return false;
	if (special==205 && f!=2) return false;
	if (special==206 && f!=0) return false;
	return map_floor[now_floor].canMove(nextX(),nextY(),f);
}
void c_hero::show()
{
	(new hgeSprite(consts.ht_hero,move*32,face*33,32,33))
		->Render(x*32+8*move*dir[0][face]+consts.ScreenLeft, y*32+8*move*dir[1][face]);
}
bool c_hero::nearStair()
{
	if (map_floor[now_floor].getinfo(y,x)->nearStair()) return true;
	if (x>0 && map_floor[now_floor].getinfo(y,x-1)->nearStair()) return true;
	if (y>0 && map_floor[now_floor].getinfo(y-1,x)->nearStair()) return true;
	if (x<consts.map_width-1 && map_floor[now_floor].getinfo(y,x+1)->nearStair()) return true;
	if (y<consts.map_width-1 && map_floor[now_floor].getinfo(y+1,x)->nearStair()) return true;
	return false;
}
bool c_hero::moveComplete()
{
	bool c=false;
	if(move==3)
	{
		c=true;
		x+=dir[0][face];
		y+=dir[1][face];
	}
	if (c)
	{
		char item=map_floor[now_floor].getItem(x,y);
		if(item>=11 && consts.music)
			consts.hge->Effect_PlayEx(consts.he_GetItem,consts.volume);
		switch(item)
		{
		case 10:
			hp-=100;
			if (hp<=0) hp=1;
			break;
		case 11:atk+=3;
			if (!consts.attack_flag) {
				consts.attack_flag=true;
				consts.setMsg("获取红宝石，攻击力+3");
			}
			break;
		case 12:def+=3;
			if (!consts.defence_flag) {
				consts.defence_flag=true;
				consts.setMsg("获取蓝宝石，防御力+3");
			}
			break;
		case 13:
			consts.book=true;
			consts.setMsg("获得怪物手册。\n你可以将鼠标放置在怪物上查\n看怪物的基本信息。从上到下\n依次为怪物的名称、血量、攻\n击、防御、打掉后获得的金币\n、经验，对你造成的伤害。");
			break;
		case 14:
			yellowkey++;bluekey++;redkey++;
			consts.setMsg("获取钥匙盒，全钥匙数量+1");
			break;
		case 15:yellowkey++;
			if (!consts.yellow_flag) {
				consts.yellow_flag=true;
				consts.setMsg("获得黄钥匙");
			}
			break;
		case 16:bluekey++;
			if (!consts.blue_flag) {
				consts.blue_flag=true;
				consts.setMsg("获得蓝钥匙");
			}
			break;
		case 17:redkey++;
			if (!consts.red_flag) {
				consts.red_flag=true;
				consts.setMsg("获得红钥匙");
			}
			break;
		case 18:hp+=200;
			if (!consts.small_flag) {
				consts.small_flag=true;
				consts.setMsg("获得小血瓶，生命+200");
			}
			break;
		case 19:hp+=500;
			if (!consts.big_flag) {
				consts.big_flag=true;
				consts.setMsg("获得大血瓶，生命+500");
			}
			break;
		case 20:atk+=10;consts.setMsg("获得铁剑，攻击力+10");break;
		case 21:def+=10;consts.setMsg("获得铁盾，防御力+10");break;
		case 22:money+=300;consts.setMsg("获得大金币，金币+300");break;
		case 23:lv++;hp+=700;atk+=7;def+=7;
			consts.setMsg("获得小飞羽，提升一级\n生命+700，攻击+7，防御+7");break;
		case 24:consts.cross=true;
			consts.setMsg("获得十字架，交给0楼的仙子\n可以大幅提升自身能力！");break;
		case 25:atk+=70;consts.setMsg("获得银剑，攻击力+70");break;
		case 26:def+=70;consts.setMsg("获得银盾，防御力+70");break;
		case 30:hp*=2;consts.setMsg("获得圣水，生命值翻倍。");break;
		case 27:consts.canfly=true;consts.setMsg("获得楼层飞行器，按F键使用");break;
		case 28:consts.stick=true;consts.setMsg("获得锄头，需要把它交给杰克。");break;
		case 29:lv+=3;hp+=2100;atk+=21;def+=21;consts.setMsg("获得大飞羽，提升三级\n生命+2100，攻击+21，防御+21");break;
		case 31:atk+=150;consts.setMsg("获得神圣剑，攻击力+150");break;
		case 32:def+=150;consts.setMsg("获得神圣盾，防御力+150");break;
		case 33:special=1;consts.setMsg("我：\n这是啥？要是能找人鉴定一下\n就好了。");break;
		case 34:special=2;consts.setMsg("我：\n这是啥？要是能找人鉴定一下\n就好了。");break;
		case 35:special=3;consts.setMsg("我：\n这是啥？要是能找人鉴定一下\n就好了。");break;
		}
		int special=map_floor[now_floor].getSpecial(x,y);
		if (special!=0) {
			if (special==201) {
				map_floor[now_floor].setSpecial(x,y,202);
			}
			if (special==209) {
				map_floor[now_floor].changeLight(x,y);
			}
			if (special==210 || special==211) {
				map_floor[now_floor].setSpecial(x,y,special==210?0:209);
				if (map_floor[now_floor].getSpecial(x+dir[0][face],y+dir[1][face])==0) {
					map_floor[now_floor].setSpecial(x+dir[0][face],y+dir[1][face],210);
				}
				else if (map_floor[now_floor].getSpecial(x+dir[0][face],y+dir[1][face])==209) {
					map_floor[now_floor].setSpecial(x+dir[0][face],y+dir[1][face],211);
				}
			}
		}
		if (map_floor[now_floor].checkChallenge())
			map_floor[now_floor].finishChallenge();
		consts.step++;
		if (now_floor==0 && x==5 && y==10) consts.msg=consts.MESSAGE_WIN;
	}
	move++;
	move%=4;
	return c;
}
bool c_hero::openRedDoor()
{
	if(redkey>0)
	{
		redkey--;
		return true;
	}
	return false;
}
bool c_hero::openBlueDoor()
{
	if(bluekey>0)
	{
		bluekey--;
		return true;
	}
	return false;
}
bool c_hero::openYellowDoor()
{
	if(yellowkey>0)
	{
		yellowkey--;
		return true;
	}
	return false;
}
bool c_hero::openSpecialDoor()
{
	if(map_floor[now_floor].getinfo(nextY(),nextX())->canOpen())
		return true;
	return false;
}
void c_hero::upstair()
{
	now_floor++;
	setFlyFloor();
	map_floor[now_floor].getDownPosition(x,y);
	consts.flooring=true;
	consts.step++;
}
void c_hero::downstair()
{
	now_floor--;
	setFlyFloor();
	map_floor[now_floor].getUpPosition(x,y);
	consts.flooring=true;
	consts.step++;
}
void c_hero::specialMove()
{
	consts.flooring=true;
	consts.step++;
	if (now_floor<30) {
		now_floor=31;
		x=10;y=0;
	}
	else {
		now_floor=10;
		x=10;y=0;
	}
}
void c_hero::fly()
{
	if(now_floor<=fly_floor && fly_floor!=0)map_floor[fly_floor].getDownPosition(x,y);
	else map_floor[fly_floor].getUpPosition(x,y);
	now_floor=fly_floor;
	consts.flooring=true;
}
int c_hero::getSpecialLv()
{
	if (lv<=10) return 1;
	if (lv<=20) return 2;
	if (lv<=45) return 3;
	if (lv<=80) return 4;
	return 5;
}
int c_hero::getSpeDef()
{
	int slv=getSpecialLv();
	if (special!=2 || slv==1) return 0;
	if (slv==2) return def*0.03;
	if (slv==3) return def*0.06;
	if (slv==4) return def*0.1;
	return def*0.15;
}
int c_hero::getSpeLife(int lf)
{
	int slv=getSpecialLv();
	if (special!=3 || slv==1) return 0;
	if (slv==2) return lf*0.2;
	else if (slv==3) return lf*0.33;
	else if (slv==4) return lf*0.5;
	return lf;
}
int c_hero::getSpeAtkTimes()
{
	if (special!=1) return 1;
	return getSpecialLv();
}
void c_hero::printInfo()
{
	int py=16;
	consts.s_storey->Render(16,py);
	if (now_floor<30)
		consts.hgef->printf(60,py,HGETEXT_LEFT,"%d",now_floor);
	else consts.hgef->printf(60,py,HGETEXT_LEFT,"???");
	py+=32;
	consts.s_level->Render(16,py);
	consts.hgef->printf(60,py,HGETEXT_LEFT,"%d",lv);
	if (special!=0) {
		if (special==1)
			consts.s_atk->Render(160,py);
		if (special==2)
			consts.s_def->Render(160,py);
		if (special==3)
			consts.s_life->Render(160,py);
		consts.hgef->printf(204,py,HGETEXT_LEFT,"%d",getSpecialLv());
	}
	py+=32;
	consts.s_heart->Render(16,py);
	consts.hgef->printf(60,py,HGETEXT_LEFT,"%d",hp);
	py+=32;
	consts.s_sword1->Render(16,py);
	consts.hgef->printf(60,py,HGETEXT_LEFT,"%d",atk);
	py+=32;
	consts.s_shield1->Render(16,py);
	if (special!=2)
		consts.hgef->printf(60,py,HGETEXT_LEFT,"%d",def);
	else
		consts.hgef->printf(60,py,HGETEXT_LEFT,"%d (+%d)",def,getSpeDef());
	py+=32;
	consts.s_yellowkey->Render(16,py);
	consts.hgef->printf(60,py,HGETEXT_LEFT,"%d",yellowkey);
	py+=32;
	consts.s_bluekey->Render(16,py);
	consts.hgef->printf(60,py,HGETEXT_LEFT,"%d",bluekey);
	py+=32;
	consts.s_redkey->Render(16,py);
	consts.hgef->printf(60,py,HGETEXT_LEFT,"%d",redkey);
	py+=32;
	consts.s_coin->Render(16,py);
	consts.hgef->printf(60,py,HGETEXT_LEFT,"%d",money);
	py+=32;
	consts.s_expr->Render(16,py);
	consts.hgef->printf(60,py,HGETEXT_LEFT,"%d",experience);

}
bool c_hero::canBeat(c_monster monster) // 判断能否打败
{
	return hp>getDamage(monster);
}
int c_hero::getDamage(c_monster monster) // 打败怪物，返回hp
{
	int monster_def=monster.getSpecial()==2?atk-1:monster.getDef();
	if (atk<=monster_def) return MAX_DAMAGE;
	int val=monster.getSpecial()==1?hp/3:0;
	if (monster.getSpecial()!=3 && getDef()>=monster.getAtk()) return val;
	return val+(monster.getHp()-1)/((atk-monster_def)*getSpeAtkTimes())*(monster.getAtk()-(monster.getSpecial()==3?0:getDef()));
}
bool c_hero::attack(c_monster &monster)
{
	if (consts.music)
		consts.hge->Effect_PlayEx(consts.he_Attack,consts.volume);
	int times=getSpeAtkTimes();
	for (int i=1;i<=times;i++) {
		if (monster.beAttacked(atk))
		{
			money+=monster.getMoney();
			experience+=monster.getExperience();
			return false;
		}
	}
	return true;
}
void c_hero::beAttacked(c_monster monster)
{
	if (monster.getSpecial()==3) hp-=monster.getAtk();
	else if (getDef()<monster.getAtk())
		hp-=monster.getAtk()-getDef();
}
void c_hero::npc(int select)
{
	int npcid=map_floor[now_floor].getinfo(nextY(),nextX())->getNpcID();
	int npctime=map_floor[now_floor].getinfo(nextY(),nextX())->getNpcVisit();
	switch (npcid)
	{
	case 40:
		if (npctime==0)
		{
			const char* npc_hint[50] = {
				"老人：\n孩子，这座塔很危险，你怎么\n进来了？",
				"我：\n我女朋友在里面，我要冲进去\n救她！",
				"老人：\n勇气可嘉！我有本书遗失在了\n三楼，如果你能获得它，或许\n能对你有所帮助。",
				"我：\n谢谢您！",
				"老人：\n另外，多和塔里的老人们进行\n对话，会得到很多有用的情报\n的。",
				"老人：\n还有，一定要注意随时存档！"
			};
			consts.setMsg(npc_hint);
			map_floor[now_floor].getinfo(nextY(),nextX())->visitNpc();
		}
		else
			consts.setMsg("老人：\n多和塔里的老人们进行对话，\n会得到很多有用的情报的。\n同时，一定要注意随时存档！");
		break;
	case 41:
		if (npctime==0)
		{
			atk+=30;
			map_floor[now_floor].getinfo(nextY(),nextX())->visitNpc();
			consts.setMsg("老人：\n孩子，感谢你救了我。\n这30点攻击就是我送你的！");
		}
		else
			consts.setMsg("老人：\n经过熔岩地面会扣除你100生命\n值，最低将你的生命值扣到1。");
		break;
	case 42:
		if (npctime==0)
		{
			def+=30;
			map_floor[now_floor].getinfo(nextY(),nextX())->visitNpc();
			consts.setMsg("老人：\n孩子，感谢你救了我。\n这30点防御就是我送你的！");
		}
		else
			consts.setMsg("老人：\n遇到圣水不要急着去取，它会\n将你的生命值翻倍。");
		break;
	case 43:
		if (npctime==0)
		{
			map_floor[2].getinfo(6,1)->setOpened();
			map_floor[now_floor].getinfo(nextY(),nextX())->visitNpc();
			const char* thief_hint[50] = {
				"我：\n你是谁？怎么被关押在这里？",
				"杰克：\n我叫杰克；是住在附近的一个\n居民。听说这个塔里有宝藏，\n我就进来了，结果刚进来就被\n抓了。",
				"我：\n宝藏？什么宝藏？",
				"杰克：\n我也只是听说... \n不过谢谢你救了我！",
				"我：\n你会开门吗？",
				"杰克：\n会啊，怎么了？",
				"我：\n那你能把二楼的门打开吗？",
				"杰克：\n好的，我这就去帮你打开；另\n外，如果你能找到我遗失的锄\n头，我也能帮你把18楼的门给\n打开。",
				"我：\n谢谢，我这就去帮你找你的锄\n头。"
			};
			consts.setMsg(thief_hint);
		}
		else if (npctime==1)
		{
			if (consts.stick) {
				map_floor[18].getinfo(5,5)->setOpened();
				map_floor[now_floor].getinfo(nextY(),nextX())->visitNpc();
				consts.setMsg("杰克：\n你找到了我的锄头啊！\n18楼的门已经为你打开。");
			}
			else {
				consts.setMsg("杰克：\n锄头找到了吗？");
			}
		}
		else
			consts.setMsg("杰克：\n还有什么事吗？");
		break;

	case 44:
		if (npctime==0)
		{
			const char* fairy_hint[50]={
				"我：\n（这是什么鬼地方，阴森森的）\n\n[按回车键继续]",
				"我：\n（今天和女朋友结对编程时，\n就因为大括号是否应该换行的\n问题，一言不合，她竟然就跑\n出来了...）",
				"我：\n（结果我追着她到了这个鬼地\n方，这是哪啊.....）\n......\n（大声喊）XX！XX！！",
				"仙子：\n哎你是谁，为什么跑到这来了？",
				"我：\n这里是哪？怎么这么阴森？\n你又是谁？",
				"仙子：\n这是镇妖塔，镇压着一方魔物。\n我是这里的守塔仙子。\n这不是你该来的地方，快点回\n去吧。",
				"我：\n仙子你好，你看到了一个小女\n孩吗？\n......\n（比划）大概这么高，齐刘海",
				"仙子：\n啊看到了，她刚刚冲进了塔里！\n我都没来得及拦住她哎。",
				"我：\n她进去了？那我也要进去找她！\n",
				"仙子：\n她这时候恐怕已经被魔物抓起\n来了，凶多吉少，你进去也没\n用的。",
				"我：\n她是我的女朋友！\n我一定要把她安全带出来！\n",
				"仙子：\n但是这里面魔物很凶猛的，特\n别是顶楼的boss更是厉害得很\n啊。",
				"我：\n那该怎么办？怎么才能救出她\n呢？",
				"仙子：\n如果你能把七楼的十字架交给\n我，我就能大幅提高你的能力\n，这样或许你就能救出她了。",
				"我：\n好！我这就去替你找回你的十\n字架！而且我一定能把她给救\n出来！",
				"仙子：\n去吧，我相信你！祝你好运！",
				"S/L: 存档/读档\nF: 楼层飞行（需飞行器）\nR: 重新开始\nM: 音乐开关\nH: 查看帮助\nQ: 退出游戏",
				"仙子：\n（痴情的孩子啊......）"
			};
			consts.setMsg(fairy_hint);
			map_floor[0].getinfo(7,5)->setOpened();
			map_floor[now_floor].getinfo(nextY(),nextX())->visitNpc();
		}
		else if(npctime==1)
		{
			if (consts.cross) {
				consts.setMsg("仙子：\n对，就是这个十字架！\n巴拉巴拉...轰！\n......\n全属性提高25%！\n去吧，我只能帮你到这里了！");
				hp=hp*1.25;
				atk=atk*1.25;
				def=def*1.25;
				map_floor[20].getinfo(6,5)->setOpened();
				map_floor[20].getinfo(7,4)->setOpened();
				map_floor[20].getinfo(7,6)->setOpened();
				map_floor[20].getinfo(8,5)->setOpened();
				map_floor[now_floor].getinfo(nextY(),nextX())->visitNpc();
			}
			else {
				consts.setMsg("仙子：\n找到十字架了吗？");
			}
		}
		else if (consts.lefttime<80) {
			if (consts.trueend) {
				consts.setMsg("仙子：\n快走吧孩子，再不走就来不及\n了！");
			}
			else {
				consts.trueend=true;
				const char* princess_hint[50]={
					"仙子：\n你真的把她救出来了！",
					"我：\n谢谢仙子！不过这座塔就要倒\n了，你不赶快撤离吗？",
					"仙子（悲伤）：\n我早已深根于这座塔中，能去\n哪。塔就要倒了，我也就要去\n了。这样吧，我用我剩余的修\n为，祝福你们一生幸福美满。",
					"我：\n仙子......",
					"仙子：\n快走吧，你们的一生还很长的\n，祝福你们！"
				};
				consts.setMsg(princess_hint);
			}
		}
		else consts.setMsg("仙子：\n我只能帮你到这里了，加油把\n你女朋友救出来吧！");
		break;

	case 45: // The first exp store
		if (select==1 && experience>=100)
		{
			lv++;
			hp+=700;
			atk+=7;
			def+=7;
			experience-=100;
		}
		if (select==2 && experience>=30)
		{
			atk+=5;
			experience-=30;
		}
		if (select==3 && experience>=30)
		{
			def+=5;
			experience-=30;
		}
		break;
	case 46: // The key store
		if (select==1 && money>=10)
		{
			yellowkey++;
			money-=10;
		}
		if (select==2 && money>=50)
		{
			bluekey++;
			money-=50;
		}
		if (select==3 && money>=100)
		{
			redkey++;
			money-=100;
		}
		break;
	case 47: // The first store
		if (select==1 && money>=25)
		{
			hp+=400;
			money-=25;
		}
		if (select==2 && money>=25)
		{
			atk+=4;
			money-=25;
		}
		if (select==3 && money>=25)
		{
			def+=4;
			money-=25;
		}
		break;
	case 48: // The second store
		if (select==1 && money>=100)
		{
			hp+=2000;
			money-=100;
		}
		if (select==2 && money>=100)
		{
			atk+=20;
			money-=100;
		}
		if (select==3 && money>=100)
		{
			def+=20;
			money-=100;
		}
		break;
	case 49: // The second exp store
		if (select==1 && experience>=270)
		{
			experience-=270;
			lv+=3;
			hp+=2100;
			atk+=21;
			def+=21;
		}
		if (select==2 && experience>=95)
		{
			experience-=95;
			atk+=17;
		}
		if (select==3 && experience>=95)
		{
			experience-=95;
			def+=17;
		}
		break;
	case 50: // sell keys store
		if (select==1 && yellowkey>=1)
		{
			yellowkey--;
			money+=7;
		}
		if (select==2 && bluekey>=1)
		{
			bluekey--;
			money+=35;
		}
		if (select==3 && redkey>=1)
		{
			redkey--;
			money+=70;
		}
		break;
	case 51:
		if(npctime==0)
		{
			const char *princess_hint[50]={
				"我：\nXX，终于找到你了！\n这里危险，快和我回去！",
				"我：\n。。。？\n...XX。。。？",
				"？？？（男声）：\n哈哈哈，你在找谁啊？\n",
				"我：\n你是谁！她呢？",
				"？？？：\n她？已经被大王抓到顶层去了\n，这时候恐怕已经...",
				"我：\n你！！！你们！！！",
				"？？？：\n想见她的话就冲到顶楼来吧！\n我们在这里决一死战！",
				"我：\n好！要战便战！\n（低声）等着我，我很快就来..."
			};
			consts.setMsg(princess_hint);
			map_floor[now_floor].getinfo(nextY(),nextX())->visitNpc();
			map_floor[18].getinfo(10,9)->setOpened();
		}
		else {
			if (consts.lefttime<80)
				consts.setMsg("？？？：\n和我们一起陪葬吧，哈哈哈！");
			else 
				consts.setMsg("？？？：\n不敢来了？那你就别想见到她\n了！");
		}
		break;
	case 52:
		if(npctime==0)
		{
			const char *princess_hint[50]={
				"我：\nXX，是你吗？真的是你吗？",
				"XX（虚弱）：\n。。。YY，你，你终于来了",
				"我：\n我来了，我来救你了！\n这些魔物们没对你怎么样吧！",
				"XX：\n还没有... 我还好....",
				"我（抽泣）：\n都是我不好，不该和你争吵的\n以后一切事情都依你的，我不\n想再和你分开了！",
				"XX：\n宝宝你真好...",
				"我：\n嗯！话说这座塔要倒了，此地\n不宜久留，我们赶快走吧！",
				"我：\n跟我来！"
			};
			consts.setMsg(princess_hint);
			map_floor[now_floor].getinfo(nextY(),nextX())->visitNpc();
			map_floor[21].getinfo(7,4)->setOpened();
			map_floor[21].getinfo(7,6)->setOpened();
			map_floor[0].getinfo(10,5)->setOpened();
		}
		else consts.setMsg("XX：\n塔要倒了，快走吧！我随后就\n跟来！");
		break;
	case 53:
		if(npctime==0)
		{
			if (select==1 && experience>=500)
			{
				experience-=500;
				atk+=120;
				map_floor[now_floor].getinfo(nextY(),nextX())->visitNpc();
			}
		}
		else
			consts.setMsg("老人：\n注意备足钥匙，小心不够。");
		break;
	case 54:
		if(npctime==0)
		{
			if (select==1 && money>=500)
			{
				money-=500;
				def+=120;
				map_floor[now_floor].getinfo(nextY(),nextX())->visitNpc();
			}
		}
		else
			consts.setMsg("老人：\n十字架最好冲到17楼时再给仙\n子，太早的话是没办法过的。\n当然，如果能在最终决战前再\n把十字架给仙子，那就更没有\n压力了。");
		break;
	case 55:
		{
			const char* npc_hint[50]= {
				"老人：\n吸血怪物将首先扣除你1/3的\n血量再与你战斗；坚固怪物的\n防御力永远比你的攻击力少1；\n魔攻怪物将无视你的防御值。",
				"老人：\n对于吸血怪物，血越少杀它的\n效果越好，因此可以尽量留下\n血瓶不急于去吃，等血很少时\n再去杀它。",
				"老人：\n对于坚固怪物，最好的方式就\n是“防杀”它，也就是将你的\n防御力加到不小于其攻击力，\n这样可以无伤杀它。",
				"老人：\n对于魔攻怪物，找到其“临界\n点”，将你的攻击加到怪物的\n“临界点”之上，就可以以最\n小的生命值代价杀掉它。"
			};
			consts.setMsg(npc_hint);
		}
		break;
	case 56:
		{
			const char* npc_hint[50]= {
				"老人：\n这座塔共有21层，实际上分为\n了三个部分：1到7层为第一部\n分，以能战胜红蝙蝠为界；8\n到16层为第二部分，以能战胜\n红衣魔王为界。",
				"老人：\n17到21层为第三部分，以能战\n胜最终boss为界。\n\n加油！"
			};
			consts.setMsg(npc_hint);
		}
		break;
	case 57:
		{
			const char* npc_hint[50]= {
				"老人：\n上面就是顶楼了，也是boss的\n所在地，上去后就下不来了。\n建议先存个档上去看看怪物的\n各个属性，以方便最终决战。"
			};
			consts.setMsg(npc_hint);
		}
		break;
	case 58:
		consts.setMsg("老人：\n8到12层中存在一个机关，找到它！");
		break;
	case 61:
		{
			if(npctime==0) {
				const char* npc_hint[50]= {
					"老人：\n你竟然找到了这个地方！",
					"我：\n您好，请问这是哪？",
					"老人：\n这是一个神秘莫测的地方，充\n满了各种机关。如果你能闯过\n每一层的试炼，也许会有很大\n的好处在等着你哦！",
					"我：\n真的吗？那我要去试试了！",
					"老人：\n请注意，在这些机关层，将无\n法使用飞行器，楼梯边才能存\n档；一旦参与将没有回头路可\n走，所以请慎重进行每一步。",
					"老人：\n这里不能使用飞行器！楼梯边\n才能存档！",
					"老人：\n这里不能使用飞行器！楼梯边\n才能存档！\n（重要的事情说三遍）",
					"我：\n（汗..）我知道了..谢谢您！",
					"老人：\n在这一层中，找到所有暗墙即\n可通过！"
				};
				consts.setMsg(npc_hint);
				map_floor[now_floor].getinfo(nextY(),nextX())->visitNpc();
				map_floor[now_floor].getinfo(1,10)->setOpened();
			}
			else consts.setMsg("老人：\n在这一层中，找到所有暗墙即\n可通过！");
			break;
		}
	case 62:
		consts.setMsg("老人：\n每个灯只准通过一次，踩灭所\n有灯即可通过！");
		break;
	case 63:
		consts.setMsg("老人：\n点灯游戏，3*3版。");
		break;
	case 64:
		consts.setMsg("老人：\n点灯游戏，4*4版。");
		break;
	case 65:
		consts.setMsg("老人：\n我相信你能找到正确的路的。");
		break;
	case 66:
		consts.setMsg("老人：\n将楼上的图案左右反转过来。");
		break;
	case 67:
		consts.setMsg("老人：\n这层楼和楼上有一些关联。");
		break;
	case 68:
		consts.setMsg("老人：\n不要觉得我丧心病狂，推箱子\n真的不好写的。。。。");
		break;
	case 69:
		consts.setMsg("老人：\n来试试5*5的吧。\n\n提示一下：第一行11000。");
		break;
	case 70:
		consts.setMsg("老人：\n在楼上的图案中，如果从左上\n进，右下出，且每次仅允许向\n右或者向下行走，那么共有多\n少种不同的走法？");
		break;
	case 71:
		consts.setMsg("老人：\n这是最后一关了，我保证。");
		break;
	case 72:
		if (special==0)
		{
			consts.setMsg("老人：\n你没有拿到楼上的“章”吗？");
			break;
		}
		else
		{
			if (npctime==0) {
				if (special==1) {
					const char* npc_hint[50]= {
						"老人：\n你终于走到了我的面前，不错\n，真不错。",
						"我：\n您帮我看看我在楼上得到的这\n个是什么？",
						"老人：\n这个啊，这是“勇者之章”。",
						"我：\n勇者之章？",
						"老人：\n勇者之章可以增加你每回合的\n攻击次数的，也就是连击数。\n比如说二级的勇者之章，你每\n回合打怪物两次，怪物才会打\n你一次。",
						"我：\n这么好？那章的等级是可以提\n升的吗？",
						"老人：\n当然可以，章的等级与你的等\n级有关。当你1-10级时章为1\n级，11-20级时章为2级，21-\n45级时章为3级，46-80级时章\n为4级，81级以上时章为5级。",
						"老人：\n勇者之章是几级，你每回合就\n可以连击几次。",
						"我：\n好的，谢谢您！我对救出心爱\n的人又有着更多的把握了呢。",
						"老人：\n去吧，你还有更重要的事要做\n，赶快去把你心爱的人救出来\n吧。"
					};
					consts.setMsg(npc_hint);
				}
				else if (special==2) {
					const char* npc_hint[50]= {
						"老人：\n你终于走到了我的面前，不错\n，真不错。",
						"我：\n您帮我看看我在楼上得到的这\n个是什么？",
						"老人：\n这个啊，这是“霸者之章”。",
						"我：\n霸者之章？",
						"老人：\n霸者之章是可以按比例提升你\n的防御力的。例如二级的霸者\n之章，就可以提升你3%的防御\n力。",
						"我：\n这么好？那章的等级是可以提\n升的吗？",
						"老人：\n当然可以，章的等级与你的等\n级有关。当你1-10级时章为1\n级，11-20级时章为2级，21-\n45级时章为3级，46-80级时章\n为4级，81级以上时章为5级。",
						"老人：\n一级的霸者之章是没有增幅效\n果的，二级的霸者之章提升3%\n防御力，三级的提升6%防御力\n，四级的提升10%防御力，五\n级的提升15%防御力。",
						"我：\n好的，谢谢您！我对救出心爱\n的人又有着更多的把握了呢。",
						"老人：\n去吧，你还有更重要的事要做\n，赶快去把你心爱的人救出来\n吧。"
					};
					consts.setMsg(npc_hint);
				}
				else if (special==3) {
					const char* npc_hint[50]= {
						"老人：\n你终于走到了我的面前，不错\n，真不错。",
						"我：\n您帮我看看我在楼上得到的这\n个是什么？",
						"老人：\n这个啊，这是“贤者之章”。",
						"我：\n贤者之章？",
						"老人：\n贤者之章是可以在战斗后按比\n例吸收怪物的生命值的。例如\n二级的贤者之章可以在战斗后\n吸收20%的怪物原始生命值。",
						"我：\n这么好？那章的等级是可以提\n升的吗？",
						"老人：\n当然可以，章的等级与你的等\n级有关。当你1-10级时章为1\n级，11-20级时章为2级，21-\n45级时章为3级，46-80级时章\n为4级，81级以上时章为5级。",
						"老人：\n一级的贤者之章是没有增幅效\n果的，二级的贤者之章吸收20\n%生命值，三级的吸收33%生命\n值，四级的吸收50%生命值，\n五级的吸收100%生命值。",
						"我：\n好的，谢谢您！我对救出心爱\n的人又有着更多的把握了呢。",
						"老人：\n去吧，你还有更重要的事要做\n，赶快去把你心爱的人救出来\n吧。"
					};
					consts.setMsg(npc_hint);
				}
				map_floor[now_floor].getinfo(nextY(),nextX())->visitNpc();
			}
			else consts.setMsg("老人：\n去吧，你还有更重要的事要做\n，别在这里再停留了。");
		}
		break;
	default:
		consts.setMsg("我：\n这是啥？");
		break;
	}
}
void c_hero::save(FILE* f)
{
	fprintf_s(f,"%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n",
		lv,hp,atk,def,money,experience,redkey,bluekey,yellowkey,special,x,y,face,now_floor,max_floor,fly_floor);
}
void c_hero::load(FILE* f)
{
	fscanf_s(f,"%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n",
		&lv,&hp,&atk,&def,&money,&experience,&redkey,&bluekey,&yellowkey,&special,&x,&y,&face,&now_floor,&max_floor,&fly_floor);
}
void c_hero::setFlyFloor(int delta)
{
	if (delta==0 && now_floor<30) 
		fly_floor=now_floor;
	else
	{
		int tmpfloor=fly_floor+delta;
		if (tmpfloor<=max_floor && tmpfloor>=0 && tmpfloor<=20) fly_floor=tmpfloor;
	}
}