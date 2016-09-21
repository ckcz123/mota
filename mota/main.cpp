#include "stdafx.h"

// 地图信息
c_map_floor map_floor[50];

// 勇士信息
c_hero hero;

// 常量信息
constants consts;

void loadsave()
{
	FILE *savefile;
	constants tmpcon;
	c_hero tmphero;
	for (int i=0;i<10;i++) {
		char s[100]="";
		sprintf_s(s,"Save/save%d.dat",i);
		int err=fopen_s(&savefile,s,"r");
		if (err!=0)
			consts.sd[i].hp=-1;
		else {
			tmpcon.load(savefile);
			tmphero.load(savefile);
			consts.sd[i].init(tmphero.getHP(), tmphero.getAtk(), tmphero.getDef(), tmphero.getNowFloor());
			fclose(savefile);
		}
	}
	consts.lasttime=clock();
}

void save(int id)
{
	FILE *savefile;
	char s[100]="";
	sprintf_s(s,"Save/save%d.dat",id);
	fopen_s(&savefile,s,"w");
	consts.save(savefile);
	hero.save(savefile);
	for(int i=0;i<consts.map_floornum;i++)map_floor[i].save(savefile);
	for(int i=31;i<=consts.special_floornum;i++)map_floor[i].save(savefile);
	fclose(savefile);
	consts.setMsg("存档成功！");
}
void load(int id)
{
	FILE *loadfile;
	char s[100]="";
	sprintf_s(s,"Save/save%d.dat",id);
	fopen_s(&loadfile,s,"r");
	consts.load(loadfile);
	hero.load(loadfile);
	for(int i=0;i<consts.map_floornum;i++)map_floor[i].load(loadfile);
	for(int i=31;i<=consts.special_floornum;i++)map_floor[i].load(loadfile);
	fclose(loadfile);
	consts.setMsg("读档成功！");
}
void showMessage(const char *s) // 显示提示
{
	hgeSprite *s_temp;
	s_temp=new hgeSprite(consts.ht_skin,0,0,128,128);
	s_temp->SetColor(0x88FFFFFF);
	s_temp->RenderStretch(16+consts.ScreenLeft,consts.map_height*32-160,consts.map_width*32+consts.ScreenLeft-16,consts.map_height*32-8);
	GfxFont *f=new GfxFont("楷体",23);
	f->Print(16+consts.ScreenLeft+8,consts.map_height*32-160+8,"%s",s);
	delete f;
	delete s_temp;
}
void init(bool restart=false)
{
	// 初始化
	consts.init();
	hero.init();
	// 读入地图
	FILE *map_infile;
	fopen_s(&map_infile,"Res/map.dat","r");
	for(int i=0;i<consts.map_floornum;i++)
	{
		int ch[30][30];
		for(int j=0;j<consts.map_height;j++)for(int k=0;k<consts.map_width;k++)fscanf_s(map_infile,"%d",&ch[j][k]);
		map_floor[i].init(i,ch);
	}
	for(int i=31;i<=consts.special_floornum;i++)
	{
		int ch[30][30];
		for(int j=0;j<consts.map_height;j++)for(int k=0;k<consts.map_width;k++)fscanf_s(map_infile,"%d",&ch[j][k]);
		map_floor[i].init(i,ch);
	}
	fclose(map_infile);
	if (restart)
		consts.setMsg("游戏已重新开始！");
}
bool frameFunc()
{
	float dt=consts.hge->Timer_GetDelta();

	if(consts.isFree() && consts.hge->Input_GetKeyState(HGEK_DOWN) && hero.canMove(0))consts.moving=true;
	if(consts.isFree() && consts.hge->Input_GetKeyState(HGEK_LEFT) && hero.canMove(1))consts.moving=true;
	if(consts.isFree() && consts.hge->Input_GetKeyState(HGEK_RIGHT) && hero.canMove(2))consts.moving=true;
	if(consts.isFree() && consts.hge->Input_GetKeyState(HGEK_UP) && hero.canMove(3))consts.moving=true;
	if(consts.hge->Input_GetKeyState(HGEK_H) && consts.isFree()) {
		const char* help_hint[50]={
			"这是一款固定数值的RPG型小游\n戏，你的目标是冲上顶楼救下\n被抓住的XX。\n\n[按回车键继续]", 
			"地图中分布着一定数量的门、\n道具、怪物和NPC等。\n\n不同颜色的门需要对应颜色的\n钥匙才能开启，特殊门需要特\n殊方式才能开启。",
			"与怪物的战斗方式是回合制，\n每次用你的攻击减怪物的防御\n扣除其生命值，然后用其攻击\n减你的防御扣除你的生命值，\n直到怪物的生命值为0。打\n败怪物后可获取金币和经验。",
			"金币和经验值可以用来在商店\n提升自己的能力，同时你也可\n以通过逝去地图上的道具进行\n提升，例如宝石和剑盾可以提\n升你的攻击防御，血瓶可以\n提升你的生命值，等等。",
			"S/L: 存档/读档\nF: 楼层飞行（需飞行器）\nR: 重新开始\nM: 音乐开关\nH: 查看帮助\nQ: 退出游戏"
		};
		consts.setMsg(help_hint);
	}
	if(consts.hge->Input_GetKeyState(HGEK_Q) && consts.isFree()) consts.msg=consts.MESSAGE_QUIT;
	if(consts.hge->Input_GetKeyState(HGEK_R) && consts.isFree()) consts.msg=consts.MESSAGE_RESTART;
	if(consts.hge->Input_GetKeyState(HGEK_S) && consts.isFree()) {
		if (hero.getNowFloor()>=30 && !hero.nearStair()) {
			consts.setMsg("只有在楼梯边才能存档！");
		}
		else {
			loadsave();
			consts.msg=consts.MESSAGE_SAVE;
		}
	}
	if(consts.hge->Input_GetKeyState(HGEK_L) && consts.isFree()) {
		loadsave();
		consts.msg=consts.MESSAGE_LOAD;
	}
	if(consts.hge->Input_GetKeyState(HGEK_F) && consts.isFree()) {
		if (hero.getNowFloor()>=30) consts.setMsg("这里不能使用飞行器！");
		else if (consts.canfly) { 
			if (hero.getNowFloor()==21) consts.setMsg("飞行器好像在这层楼失效了！");
			else consts.msg=consts.MESSAGE_FLYING;
		}
		else if (consts.lefttime<80) consts.setMsg("飞行器好像遗失了！");
		else consts.setMsg("你需要先获得飞行器！");
	}
	if(consts.hge->Input_GetKeyState(HGEK_M) && consts.isFree()) {
		consts.music=!consts.music;
		consts.setMsg(consts.music?"音乐已开启":"音乐已关闭");
		if (consts.music) consts.hge->Channel_SetVolume(consts.hc_Music, consts.bgmvolume);
		else consts.hge->Channel_SetVolume(consts.hc_Music, 0);
	}

	// 提示消息
	if (consts.msg==consts.MESSAGE_HINT)
	{
		if(consts.hge->Input_GetKeyState(HGEK_ENTER) && clock()-consts.lasttime>200) {
			consts.nowcnt++;
			consts.lasttime=clock();
		}
		if (consts.nowcnt>=consts.hint.size())
			consts.msg=consts.MESSAGE_NONE;
	}

	// 存档
	if(consts.msg==consts.MESSAGE_SAVE)
	{
		if(consts.hge->Input_GetKeyState(HGEK_DOWN) && clock()-consts.lasttime>200) {
			consts.wanttosave++;
			if (consts.wanttosave>=10) consts.wanttosave=9;
			consts.lasttime=clock();
		}
		else if(consts.hge->Input_GetKeyState(HGEK_UP) && clock()-consts.lasttime>200) {
			consts.wanttosave--;
			if (consts.wanttosave<0) consts.wanttosave=0;
			consts.lasttime=clock();
		}
		else if(consts.hge->Input_GetKeyState(HGEK_ESCAPE))
			consts.msg=consts.MESSAGE_NONE;
		else if(consts.hge->Input_GetKeyState(HGEK_ENTER))
			save(consts.wanttosave);
	}

	// 读档
	if(consts.msg==consts.MESSAGE_LOAD)
	{
		if(consts.hge->Input_GetKeyState(HGEK_DOWN) && clock()-consts.lasttime>200) {
			consts.wanttosave++;
			if (consts.wanttosave>=10) consts.wanttosave=9;
			consts.lasttime=clock();
		}
		else if(consts.hge->Input_GetKeyState(HGEK_UP) && clock()-consts.lasttime>200) {
			consts.wanttosave--;
			if (consts.wanttosave<0) consts.wanttosave=0;
			consts.lasttime=clock();
		}
		else if(consts.hge->Input_GetKeyState(HGEK_ESCAPE))
			consts.msg=consts.MESSAGE_NONE;
		else if(consts.hge->Input_GetKeyState(HGEK_ENTER)) {
			if (consts.sd[consts.wanttosave].hp<0)
				consts.setMsg("无效的存档。");
			else load(consts.wanttosave);
		}
	}

	// 胜利or失败
	if ((consts.msg==consts.MESSAGE_WIN || consts.msg==consts.MESSAGE_LOSE) && consts.hge->Input_GetKeyState(HGEK_ENTER)) return true;
	// 退出
	if (consts.msg==consts.MESSAGE_QUIT && consts.hge->Input_GetKeyState(HGEK_SPACE)) return true;
	// 重新开始
	if (consts.msg==consts.MESSAGE_RESTART && consts.hge->Input_GetKeyState(HGEK_SPACE)) init(true);

	// 正在飞行
	if(consts.msg==consts.MESSAGE_FLYING)
	{
		if(consts.hge->Input_GetKeyState(HGEK_UP) && clock()-consts.lasttime>100)
		{
			hero.setFlyFloor(1);
			consts.lasttime=clock();
		}
		if(consts.hge->Input_GetKeyState(HGEK_DOWN) && clock()-consts.lasttime>100)
		{
			hero.setFlyFloor(-1);
			consts.lasttime=clock();
		}
		if(consts.hge->Input_GetKeyState(HGEK_ESCAPE))
		{
			consts.msg=consts.MESSAGE_NONE;
		}
		if(consts.hge->Input_GetKeyState(HGEK_ENTER))
		{
			hero.fly();
			consts.msg=consts.MESSAGE_NONE;
		}
	}

	if(consts.msg==consts.MESSAGE_NPC)
	{
		int npcid=map_floor[hero.getNowFloor()].getinfo(hero.nextY(),hero.nextX())->getNpcID();

		if (npcid>=40 && npcid<=44)
			hero.npc();

		if (npcid>=45 && npcid<=50)
		{
			if(consts.hge->Input_GetKeyState(HGEK_1) && clock()-consts.lasttime>200) {
				hero.npc(1);consts.lasttime=clock();
			}
			else if(consts.hge->Input_GetKeyState(HGEK_2) && clock()-consts.lasttime>200) {
				hero.npc(2);consts.lasttime=clock();
			}
			else if(consts.hge->Input_GetKeyState(HGEK_3) && clock()-consts.lasttime>200) {
				hero.npc(3);consts.lasttime=clock();
			}
		}

		if (npcid==51 || npcid==52 || npcid>=55)
			hero.npc();

		if(npcid==53 || npcid==54)
		{
			if(consts.hge->Input_GetKeyState(HGEK_1)) hero.npc(1);
			else hero.npc();
		}
	}

	if ((consts.msg==consts.MESSAGE_FLYING || consts.msg==consts.MESSAGE_NPC
			|| consts.msg==consts.MESSAGE_QUIT || consts.msg==consts.MESSAGE_RESTART) && consts.hge->Input_GetKeyState(HGEK_ENTER))
		consts.msg=consts.MESSAGE_NONE;

	consts.goOn(&hero, &map_floor[hero.getNowFloor()], dt);
	return false;
}
bool renderFunc()
{
	consts.hge->Gfx_BeginScene();
	consts.hge->Gfx_Clear(0);
	map_floor[hero.getNowFloor()].show();
	hero.setMaxFloor();
	hero.show();
	hero.printInfo();
	consts.printInfo();

	float mx,my; // 鼠标位置
	consts.hge->Input_GetMousePos(&mx,&my);
	int x=(mx-consts.ScreenLeft)/32,y=my/32;
	if(consts.battling)consts.monster_battling->printInfo();
	else if (consts.book && x>=0 && x<consts.map_width)map_floor[hero.getNowFloor()].printMonsterInfo(x,y);


	switch (consts.msg)
	{
	case consts.MESSAGE_QUIT:
		showMessage("你想退出游戏吗？\n\n[ENTER] 继续游戏\n[SPACE] 退出游戏");
		break;
	case consts.MESSAGE_RESTART:
		showMessage("你想重新开始吗？\n\n[ENTER] 继续游戏\n[SPACE] 重新开始");
		break;;
	case consts.MESSAGE_WIN:
		if (consts.trueend) 
			showMessage("在仙子的祝福下，YY和XX\n同学顺利地从塔中逃生。从此\n，两人相亲相爱，度过了幸福\n的一生。\n\nTRUE END.");
		else 
			showMessage("YY和XX同学顺利地从塔中\n逃生，从此过上了快乐幸福的\n生活。\n\nHAPPY END.");
		break;
	case consts.MESSAGE_LOSE:
		showMessage("塔倒了，YY和XX同学最终\n还是没有冲出来；但是直到最\n后他们的手还是拉在一起的，\n紧紧也没分开。\n\nNORMAL END.");
		break;
	case consts.MESSAGE_HINT:
		showMessage(consts.hint.at(consts.nowcnt).c_str());
		break;
	case consts.MESSAGE_SAVE:
		{
			char ss[200];
			if (consts.sd[consts.wanttosave].hp<0)
				sprintf_s(ss,"存档到文件 %d\n(空白)\n\n[↑] [↓] 更改存档位置\n[ENTER] 确认存档\n[ESC] 取消", consts.wanttosave+1);
			else
				if (consts.sd[consts.wanttosave].now_floor<30)
					sprintf_s(ss,"存档到文件 %d\n(F%d/HP%d/A%d/D%d)\n\n[↑] [↓] 更改存档位置\n[ENTER] 确认存档\n[ESC] 取消",
						consts.wanttosave+1, consts.sd[consts.wanttosave].now_floor, consts.sd[consts.wanttosave].hp,
						consts.sd[consts.wanttosave].atk, consts.sd[consts.wanttosave].def);
				else
					sprintf_s(ss,"存档到文件 %d\n(F???/HP%d/A%d/D%d)\n\n[↑] [↓] 更改存档位置\n[ENTER] 确认存档\n[ESC] 取消",
					consts.wanttosave+1, consts.sd[consts.wanttosave].hp,
					consts.sd[consts.wanttosave].atk, consts.sd[consts.wanttosave].def);
			showMessage(ss);
			break;
		}
	case consts.MESSAGE_LOAD:
		{
			char ss[200];
			if (consts.sd[consts.wanttosave].hp<0)
				sprintf_s(ss,"读取存档 %d\n(无效的存档)\n\n[↑] [↓] 更改读档位置\n[ENTER] 确认读档\n[ESC] 取消", consts.wanttosave+1);
			else
				if (consts.sd[consts.wanttosave].now_floor<30)
					sprintf_s(ss,"读取存档 %d\n(F%d/HP%d/A%d/D%d)\n\n[↑] [↓] 更改读档位置\n[ENTER] 确认读档\n[ESC] 取消",
						consts.wanttosave+1, consts.sd[consts.wanttosave].now_floor, consts.sd[consts.wanttosave].hp,
						consts.sd[consts.wanttosave].atk, consts.sd[consts.wanttosave].def);
				else
					sprintf_s(ss,"读取存档 %d\n(F???/HP%d/A%d/D%d)\n\n[↑] [↓] 更改读档位置\n[ENTER] 确认读档\n[ESC] 取消",
						consts.wanttosave+1, consts.sd[consts.wanttosave].hp,
						consts.sd[consts.wanttosave].atk, consts.sd[consts.wanttosave].def);
			showMessage(ss);
			break;
		}
	case consts.MESSAGE_FLYING:
		{
			char ss[100];
			sprintf_s(ss,"我要飞往 %d 楼\n[↑] [↓] 更改楼号\n[ENTER] 确认飞行\n[ESC] 取消",hero.getFlyFloor());
			showMessage(ss);
			break;
		}
	default:
		break;
	}
	if (consts.msg==consts.MESSAGE_NPC) {
		int npcid=map_floor[hero.getNowFloor()].getinfo(hero.nextY(),hero.nextX())->getNpcID();
		int npctime=map_floor[hero.getNowFloor()].getinfo(hero.nextY(),hero.nextX())->getNpcVisit();
		if (npcid==45)
			showMessage("你想用经验提升你的能力吗？\n[1] 提升一级 （100经验）\n[2] 攻击+5 （30经验）\n[3] 防御+5 （30经验）\n[ENTER] 退出");
		if (npcid==46)
			showMessage("你想购买钥匙吗？\n[1] 黄钥匙 （10金币）\n[2] 蓝钥匙 （50金币）\n[3] 红钥匙 （100金币）\n[ENTER] 退出");
		if (npcid==47)
			showMessage("你可以用25金币：\n[1] 生命+400\n[2] 攻击+4\n[3] 防御+4\n[ENTER] 退出");
		if (npcid==48)
			showMessage("你可以用100金币：\n[1] 生命+2000\n[2] 攻击+20\n[3] 防御+20\n[ENTER] 退出");
		if (npcid==49)
			showMessage("你想用经验提升你的能力吗？\n[1] 提升三级 （270经验）\n[2] 攻击+17 （95经验）\n[3] 防御+17 （95经验）\n[ENTER] 退出");
		if (npcid==50)
			showMessage("你有多余的钥匙要出售吗？\n[1] 黄钥匙 （7金币）\n[2] 蓝钥匙 （35金币）\n[3] 红钥匙 （70金币）\n[ENTER] 退出");
		if (npcid==53 && npctime==0)
			showMessage("500点经验换取120点攻击力，\n换吗？\n[1] 换\n[ENTER] 不要");
		if (npcid==54 && npctime==0)
			showMessage("500点金币换取120点防御力，\n换吗？\n[1] 换\n[ENTER] 不要");
	}
	consts.hge->Gfx_EndScene();
	return false;
}
int WINAPI WinMain(HINSTANCE,HINSTANCE,LPSTR,int)
{
	
	//hge初始化
	consts.hge=hgeCreate(HGE_VERSION);
	consts.hge->System_SetState(HGE_FRAMEFUNC,frameFunc);
	consts.hge->System_SetState(HGE_RENDERFUNC,renderFunc);
	consts.hge->System_SetState(HGE_USESOUND,true);
	consts.hge->System_SetState(HGE_TITLE,"魔塔");
	consts.hge->System_SetState(HGE_WINDOWED,true);
	consts.hge->System_SetState(HGE_HIDEMOUSE,false);
	consts.hge->System_SetState(HGE_SCREENHEIGHT,32*consts.map_height);
	consts.hge->System_SetState(HGE_SCREENWIDTH,32*consts.map_width+2*consts.ScreenLeft);
	if(consts.hge->System_Initiate())
	{
		consts.loadResources();
		init();
		consts.hge->System_Start();
		consts.destroy();
	}
	consts.hge->System_Shutdown();
	consts.hge->Release();
	return 0;
}
