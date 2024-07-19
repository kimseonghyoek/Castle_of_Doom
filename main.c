#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>
#include <conio.h>

// 酈爾萄 高
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define SPACE 4

// player 掘褻羹
struct player {
	// 霜機 ,唳я纂, 羹溘, 溯漣, ч遴溘, 奢問溘, 菟堅氈朝 嬴檜蠱(僥濠翮), 嬴檜蠱菟(僥濠翮 寡翮)
	int job;
	int level;
	int hp;
	float attack;
	float luck;
	double exp;
	char* item;
	char bags[1][10];
};

// 嬴檜蠱 掘褻羹
struct armor_item {
	// 羹溘 隸陛, ч遴溘 隸陛
	int increase_hp;
	double increase_luck;
};

struct attack_item {
	// 奢問溘隸陛
	double increase_attack;
};

// 瞳 掘褻羹
struct enemy {
	// 羹溘, 溯漣, 奢問溘, 跪檜 菟堅氈朝 嬴檜蠱(僥濠翮), 跪 嶸⑽(褸偃, 爾蝶)
	int hp;
	int level;
	int attack;
	char* mop_item;
	char* mop_category;
};

static void gotoxy(int x, int y) {
	COORD curserPostion = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), curserPostion);
}

// л熱 摹樹睡
int startLayout();
void showLayout();
int runAway();
void showingPlayerInfo(struct player *p);
int attack(struct plyaer *p, struct enemy *e, int damege, int hp);
char* selectItems(char *itmes);
int keyControl();
int selectMenu();
int selectPlayer(struct player *p);
void getBags(struct player *p);
void setEnemy(struct enemy *e);
struct enemy createEnemy(int hp, int level, int attack, const char* mop_item, const char* mop_category);
void printEnemy(struct enemy* e);
int enemyAttack(struct enemy* e, int player_hp);
void freeEnemy(struct enemy* e);
void Battle(struct player *p, struct player *e);


// 詭檣 л熱
int main(void) {
	// smenuCode = 1 or 2
	int smenuCode = startLayout();
	if (smenuCode == 2) {
		return 0;
	}
	else if(smenuCode == 1) {
		system("cls");
		showLayout();
		struct player(*players) = malloc(sizeof(struct player));
		struct enemy(*mop) = malloc(sizeof(struct enemy));
		setEnemy(mop);
		selectPlayer(players);
		showingPlayerInfo(players);
		Battle(players, mop);
	}
	return 0;
}

void setEnemy(struct enemy* e) {
	e->level = 1;
	e->hp = 2;
	e->attack = 1;
	e->mop_item = NULL;
	e->mop_category = "small";
}

int selectMenu() {
	int x, y = 0;
	x = 192;
	y = 53;
	gotoxy(x, y);
	printf("   1. 奢問ж晦.    \n");
	y = 54;
	gotoxy(x, y);
	printf("   2. 紫蜂除棻.    \n");
	gotoxy(x, y + 1);
	printf("   3. 陛寞翮晦.    \n");

	while (1) {
		int n = keyControl();
		switch (n) {
		case UP:
			if (y > 53) {
				gotoxy(x - 2, y);
				printf(" ");
				gotoxy(x - 2, --y);
				printf(">");
			}
			break;

		case DOWN:
			if (y < 55) {
				gotoxy(x - 2, y);
				printf(" ");
				gotoxy(x - 2, ++y);
				printf(">");
			}
			break;

		case SPACE:
			return y - 52;
		}
	}
}

void Battle(struct player *p, struct enemy *e) {
	int smenu = selectMenu();
	int x = 80;
	int y = 50;

	char vs = ' ';

	if (smenu == 1) {
		int result = attack(p, e, p->attack, e->hp);

		if (result == 0) {
			system("cls");
			printf("蝓葬!");
		}
		else if (result == 1) {
			system("cls");
			printf("ぬ寡");
		}
	}
	else if (smenu == 2) {
		int run = runAway();
		if (run == 0) {
			gotoxy(x, y);
			printf("鼠餌�� 紫蜂蟻蝗棲棻.");
		}
		else if (run == 1) {
			gotoxy(x, y);
			printf("紫蜂陛雖 跤ж艘蝗棲棻.");
			attack(p, e, e->attack, p->hp);
		}
	}
	else if (smenu == 3) {
		getBags(p);
	}

	// 檜啣擊 唳辦
	if (vs == 'W') {
		if (e->mop_category == "small") {
			system("cls");
			printf("瞪癱縑憮 蝓葬!\n");
			p->exp = p->exp + 1.7;
			if (p->exp >= 100) {
				printf("蹴жм棲棻. 溯漣檜 螢嫉蝗棲棻.");
				p->level = p->level + 1;
			}
		}
		else if (e->mop_category == "middle") {
			p->exp = p->exp + 5.4;
			if (p->exp >= 100) {
				printf("蹴жм棲棻. 溯漣檜 螢嫉蝗棲棻.");
				p->level = p->level + 1;
			}
		}
		else if (e->mop_category == "big") {
			p->exp = p->exp + 15;
			if (p->exp >= 100) {
				printf("蹴жм棲棻. 溯漣檜 螢嫉蝗棲棻.");
				p->level = p->level + 1;
			}
		}
	}
	else if (vs == 'L') {
		system("cls");
		printf("GAME OVER");
	}
}



// 議葛攪 嶸⑽ 摹鷗 -> 餌辨濠煎 殮溘嫡堅 爾檜朝 殮溘高 雖錶幗葬晦
int selectPlayer(struct player *p) {
	int x = 65;
	int y = 14;
	gotoxy(x, y);
	// 詭檣 �飛橦� 轎溘
	printf("========== 寢だ檜橫曖 撩щ擊 堅腦撮蹂. ==========\n");
	x = 45;
	y = 24;
	gotoxy(x, y );
	printf("1. 戀醴⑽ 寢だ檜橫\n");
	gotoxy(x, y + 1);
	printf("晦獄 羹溘: 35 弛 晦獄 奢問溘: 2.7\n");
	gotoxy(x, y + 10);
	printf("2. 裁楝⑽ 寢だ檜橫\n");
	gotoxy(x, y + 11);
	printf("晦獄 羹溘: 17 弛 晦獄 奢問溘: 5.0\n");
	// 餌檜萄 ж欽縑 殮溘й 熱 氈啪.
	x = 181;
	y = 52;
	gotoxy(x, y);
	scanf_s("%d", &p->job);
	gotoxy(x, y);
	printf(" ");
	if (p->job == 1) {
		p->hp = 35;
		p->attack = 2.7;
	}
	else if (p->job == 2) {
		p->hp = 17;
		p->attack = 5.0;
	}
	p->level = 1;
	p->exp = 0.0;
	p->luck = 1.1;
	p->item = "燮釭檜Щ";
	p->bags[0][0] = p->item;
	x = 45;
	y = 24;
	printf("\n");
	return 0;
}

struct enemy createEnemy(int hp, int level, int attack, const char* mop_item, const char* mop_category) {
	struct enemy (*e) = malloc(sizeof(struct enemy));
	e->hp = hp;
	e->level = level;
	e->attack = attack;
	size_t item_len = strlen(mop_item) + 1;
	size_t category_len = strlen(mop_category) + 1;
	e->mop_item = (char*)malloc(strlen(mop_item) + 1);
	if (e->mop_item != NULL) {
		strcpy_s(e->mop_item, item_len, mop_item);
	}
	e->mop_category = malloc(strlen(mop_category) + 1);
	if (e->mop_category != NULL) {
		strcpy_s(e->mop_category, category_len, mop_category);
	}
	return *e;
}
void getBags(struct player* p) {
	int x = 185;
	int y = 25;
	printf("\n");
	printf("\n");
	printf("\n");
	gotoxy(x, y);
	printf("嬴檜蠱 跡煙\n");
	for (int i = 0; i < sizeof(p->bags) / sizeof(char); i++) {
	//	printf("%d", i);
		printf("%s \n", &p->bags[0][i]);
	}
}

// ⑷營 棟溘纂 爾罹輿晦.
void showingPlayerInfo(struct player *p) {
	int x = 185;
	int y = 5;
	if (p->job == 1) {
		gotoxy(x, y);
		printf("Ы溯檜橫 顫殮: 戀醴⑽\n");
	}
	else {
		gotoxy(x, y);
		printf("Ы溯檜橫 顫殮: 裁楝⑽\n");
	}
	gotoxy(x, y+1);
	printf("⑷營 羹溘: %d\n", p->hp);
	gotoxy(x, y + 2);
	printf("⑷營 濰雜醞檣 濰綠: %s\n", p->item);
	gotoxy(x, y + 3);
	printf("奢問溘: %.2f\n", p->attack);
	gotoxy(x, y + 4);
	printf("ч遴溘: %.2f\n", p->luck);
	gotoxy(x, y + 5);
	printf("溯漣: %d.LV \n", p->level);
	gotoxy(x, y + 6);
	printf("唳я纂: %.5f\n", p->exp);
}

// 瞪癱衛 紫蜂(0~9醞縑憮 6梱雖朝 紫蜂檜 陛棟ж堅 6爾棻 觼賊 紫蜂縑 跤陛朝 �捕�)
int runAway() {
	srand(time(NULL));
	int random = 0;
	random = rand() % 9;
	if (random <= 6) {
		return 0;
	}
	else {
		return 1;
	}
};

// 瞪癱衛 奢問(parameter煎 ⑷營 奢問溘婁 奢問嫡朝 鼻渠曖 羹溘擊 嫡擠. �醴� 奢問擊 嫡擎 �釋� 羹溘擊 奩�納�.)
int attack(struct player *p, struct enemy *e, int damege, int hp) {
	damege = (int)p->attack;
	e->hp = e->hp - damege;
	damege = (int)e->attack;
	p->hp = p->hp - damege;
;
	if (e->hp == 0) {
		return 0;
	}
	else if (p->hp == 0) {
		return 1;
	}
}

// ⑷營 陛雖堅 氈朝 嬴檜蠱 醞 摹鷗
char* selectItems(char* items) {
	return "items";
}

// 酈爾萄 鐘お煤 л熱
int keyControl() {
	char temp = _getch();

	if (temp == 'w' || temp == 'W') {
		return UP;
	}
	else if (temp == 'a' || temp == 'A') {
		return LEFT;
	}
	else if (temp == 's' || temp == 'S') {
		return DOWN;
	}
	else if (temp == 'd' || temp == 'D') {
		return RIGHT;
	}
	else if (temp == ' ') {
		return SPACE;
	}
}

// 啪歜 褒ч衛 爾罹還 溯檜嬴醒
int startLayout() {
	int x = 190;
	int y = 54;

	SetConsoleTitle(TEXT("だ資曖 撩 - Castle of Doom"));
	printf("忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖\n");
	printf("弛                                                                                                                                                                                 弛                                           弛\n");
	printf("弛 \033[0;33m                                                                     ##                 ###                                                                                     \033[0;37m弛                                           弛\n");
	printf("弛 \033[0;33m                                                ####              ## ##                ##     ####                                                                              \033[0;37m弛                                           弛\n");
	printf("弛 \033[0;33m                                              ##     ###    ### #### ##  ###     ###  #####   ## ##   ###   ###  # ## #                                                         \033[0;37m弛                                           弛\n");
	printf("弛 \033[0;33m                                             ##        ##  ##    ##  ## ## ##   ## ##  ##     ##  ## ## ## ## ## ## ## ##                                                       \033[0;37m弛                                           弛\n");
	printf("弛 \033[0;33m                                             ##        ##  ##    ##  ## ## ##   ## ##  ##     ##  ## ## ## ## ## ## ## ##                                                       \033[0;37m弛                                           弛\n");
	printf("弛 \033[0;33m                                             ##      ####  ###   ##  ## ## ##   ## ##  ##     ##  ## ## ## ## ## ## ## ##                                                       \033[0;37m弛                                           弛\n");
	printf("弛 \033[0;33m                                             ##     ## ##   ###  ##  ## #####   ## ##  ##     ##  ## ## ## ## ## ## ## ##                                                       \033[0;37m弛                                           弛\n");
	printf("弛 \033[0;33m                                              ##    ## ##    ##  ##  ## ##      ## ##  ##     ## ##  ## ## ## ## ## ## ##                                                       \033[0;37m弛                                           弛\n");
	printf("弛 \033[0;33m                                               ####  ## ## ###    ## ##  ####    ###   ##     ####    ###   ###  ## ## ##                                                       \033[0;37m弛                                           弛\n");
	printf("弛                                                                                                                                                                                 \033[0;37m弛                                           弛\n");
	printf("弛                                                                                                                                                                                 弛                                           弛\n");
	printf("弛                                                                                                                                                                                 弛                                           弛\n");
	printf("弛                                                           \033[0;31m!!!!!!;;;;;;;;;;:::::::::::::;;;;;;;;!!!!!!!!!!!!!\033[0;37m                                                                    弛                                           弛\n");
	printf("弛                                                           \033[0;31m!!!!!!!;;;;;;;;;;;:::::::::::::;;;;;;;;;;!!!!!!!!!\033[0;37m                                                                    弛                                           弛\n");
	printf("弛                                                           \033[0;31m!!!!!!!!;;;;;;;;;;\033[0;30m***********!!\033[0;31m;;;;;;;;;;!!!!!!!!!\033[0;37m                                                                    弛                                           弛\n");
	printf("弛                                                           \033[0;31m!!!!!!;;;;;;;;;\033[0;30m!*$##@@@#######$==!\033[0;31m:;::;;;;!;!!!!!!\033[0;37m                                                                    弛                                           弛\n");
	printf("弛                                                           \033[0;31m!!!;;;;;;;;;;\033[0;30m!*##@@####@########@$!\033[0;31m:::::;;;;;;!!!!\033[0;37m                                                                    弛                                           弛\n");
	printf("弛                                                           \033[0;31m!!!!;;;;;;;;;\033[0;30m*#@@@@@#####$#####@@#$!\033[0;31m:::::;;;;;;;;;\033[0;37m                                                                    弛                                           弛\n");
	printf("弛                                                           \033[0;31m;;;;;;;;;;;;\033[0;30m*@@@@@###@##@#$$$###@@@$\033[0;31m;:::::;;;;;;;;\033[0;37m                                                                    弛                                           弛\n");
	printf("弛                                                           \033[0;31m;;;;;;;;;;;\033[0;30m*#@@@@###$#$##$#######@@@=\033[0;31m::::::;;;;;;;\033[0;37m                                                                    弛                                           弛\n");
	printf("弛                                                           \033[0;31m;;;;;;;;;;\033[0;30m!#@#@@@#################@#@*\033[0;31m::::::::::::\033[0;37m                                                                    弛                                           弛\n");
	printf("弛                                                           \033[0;31m;;;;;;;;;;\033[0;30m=#@@@#########@########@@@@#!\033[0;31m:::::::::~~\033[0;37m                                                                    弛                                           弛\n");
	printf("弛                                                           \033[0;31m;;;;;;;;;\033[0;30m*##@@@@########@########@@@@@$\033[0;31m:::::::~~~~\033[0;37m                                                                    弛                                           弛\n");
	printf("弛                                                           \033[0;31m;;;;;;;;\033[0;30m!=#@@@@@@#@#############@@@@@##!\033[0;31m:::::::~~~\033[0;37m                                                                    弛                                           弛\n");
	printf("弛                                                           \033[0;31m;;;;;;;;\033[0;30m*##@@@@@###$$$$$##$$$$$#@@@@@@@=\033[0;31m::::::::::\033[0;37m                                                                    弛                                           弛\n");
	printf("弛                                                           \033[0;31m;;;;;;;;\033[0;30m*@@@@@@@####@#@#$$@#@####@@@@#@$\033[0;31m::::::::::\033[0;37m                                                                    弛                                           弛\n");
	printf("弛                                                           \033[0;31m;;::;::;\033[0;30m##@@@@@@###@@####$##@@####@@@#@#!\033[0;31m:::::::::\033[0;37m                                                                    弛                                           弛\n");
	printf("弛                                                           \033[0;31m:::::::\033[0;30m!#@@@@@@@###@@@########@###@@@@#@\033[0;31m*~~~::::::\033[0;37m                                                                    弛                                           弛\n");
	printf("弛                                                           \033[0;31m:::::::\033[0;30m=@@@@@@@@##@@@@#######@@@###@@@#@=:\033[0;31m~~~~~:::\033[0;37m                                                                    弛                                           弛\n");
	printf("弛                                                           \033[0;31m~~:::::\033[0;30m#@@@@@@@##@@@@######@#@@####@@@#@#\033[0;31m;~~~~~~~~\033[0;37m                                                                    弛                                           弛\n");
	printf("弛                                                           \033[0;31m~~:::::\033[0;30m#@@@@@@@##@@@@######@#@@####@@@#@#\033[0;31m;~~~~~~~~\033[0;37m                                                                    弛                                           弛\n");
	printf("弛                                                           \033[0;31m~~~~~~:\033[0;30m#@@@@@@###!\033[0;37m;!;!;=\033[0;30m$\033[0;37m!;:-:;;\033[0;30m###@@@##@!\033[0;31m~~~~~~~~\033[0;37m                                                                    弛                                           弛\n");
	printf("弛                                                           \033[0;31m----~~~\033[0;30m#@@@@@@###!;\033[0;37m,.........\033[0;30m~;;####@@##@$\033[0;31m:~~~~~~~\033[0;37m                                                                    弛                                           弛\n");
	printf("弛                                                           \033[0;31m------~\033[0;30m@@@@@@##@#!;\033[0;37m....,~,....\033[0;30m:;#####@##@#\033[0;31m:~~----~\033[0;37m                                                                    弛                                           弛\n");
	printf("弛                                                           \033[0;31m,,,,,--\033[0;30m@@@@@###@#!:\033[0;37m....~;~-...\033[0;30m:;########@#*\033[0;31m~-----~\033[0;37m                                                                    弛                                           弛\n");
	printf("弛                                                           \033[0;31m,,,,,,-\033[0;30m@@##@##@@#!-\033[0;37m..,--;~;~,.\033[0;30m~;########@##\033[0;31m~-----~\033[0;37m                                                                    弛                                           弛\n");
	printf("弛                                                           \033[0;31m,,,,,,;\033[0;30m@@########!\033[0;37m...-:,;:;:-.,;\033[0;30m#######@@@#\033[0;31m~------\033[0;37m                                                                    弛                                           弛\n");
	printf("弛                                                           \033[0;31m,,,,,,\033[0;30m#@@########@$!\033[0;37m,.,,;;:-.-\033[0;30m$@@###@@#@@@#\033[0;31m=------\033[0;37m                                                                    弛                                           弛\n");
	printf("弛                                                           \033[0;31m,,,,,,\033[0;30m#@@########@$\033[0;37m!,.,,;;:-.-\033[0;30m$@@###@@#@@@#\033[0;31m=------\033[0;37m                                                                    弛                                           弛\n");
	printf("弛                                                           \033[0;31m,,,,,\033[0;30m~#@@####@###!#=\033[0;37m--~;--!--\033[0;30m=$;=###@##@@@@#\033[0;31m:-----\033[0;37m                                                                    弛                                           弛\n");
	printf("弛                                                           \033[0;31m,,,,,\033[0;30m$@@@########\033[0;37m*\033[0;30m!-=##\033[0;37m!!!\033[0;30m##==;!\033[0;37m=\033[0;30m@##@#@@@@@#$\033[0;31m,-,,,\033[0;37m                                                                    弛                                           弛\n");
	printf("弛                                                           \033[0;31m...,\033[0;30m;#@@@###@###*\033[0;37m::~~;*!!-=;~~-~\033[0;30m*@##@#@@@@@#$~\033[0;31m,,,,\033[0;37m                                                                    弛                                           弛\n");
	printf("弛                                                           \033[0;31m...,\033[0;30m=#@@@@##@###\033[0;37m**~~,-~;!-;,,,*:!\033[0;30m###@##@#@@##;\033[0;31m,,,,\033[0;37m                                                                    弛                                           弛\n");
	printf("弛                                                           \033[0;31m...;\033[0;30m#@@@@###@##$\033[0;37m!-,,,,,:!-;-..--;=\033[0;30m##@##@#@@##$\033[0;31m**!!\033[0;37m                                                                    弛                                           弛\n");
	printf("弛                                                           \033[0;31m...\033[0;30m*@@@@@##@@##\033[0;37m=~,,,,,~;!-;~.,.,,*\033[0;30m##@####@@###$$\033[0;31m=;\033[0;37m                                                                    弛                                           弛\n");
	printf("弛                                                           \033[0;31m,:\033[0;30m=#@@@@@##@@@#=\033[0;37m;,,,,,~;!-;~,,,,-*\033[0;30m@#@####@@@##$$\033[0;31m=;\033[0;37m                                                                    弛                                           弛\n");
	printf("弛                                                           \033[0;31m=\033[0;30m$$##@@@@@##@@##\033[0;37m=!;,,,:;!-;:,,,;**\033[0;30m#@@@@@#@@####\033[0;31m==:\033[0;37m                                                                    弛                                           弛\n");
	printf("弛                                                           \033[0;31m=\033[0;30m$$##@@#####@@##=*\033[0;37m;,,,-*!-;-,,,;;*\033[0;30m@@@@@@###@##$$\033[0;31m=:\033[0;37m                                                                    弛                                           弛\n");
	printf("弛                                                           \033[0;31m=\033[0;30m$$###@##@@#@@###$\033[0;37m;,,,\033[0;30m!#!!#\033[0;37m*-,,;;*\033[0;30m#@##@@######$$!\033[0;31m;\033[0;37m                                                                    弛                                           弛\n");
	printf("弛                                                           \033[0;31m\033[0;30m=$#@@#@##@@@#@##$!\033[0;37m;,:\033[0;30m@@#@@#@#\033[0;37m=;;1=\033[0;30m#@###@##@##$=!\033[0;31m;;\033[0;37m                                                                    戍式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式扣\n");
	printf("弛                                                           \033[0;31m\033[0;30m=$####@######@##*;!\033[0;30m$$$$=*;!**;!;\033[0;30m!##@@#@@####****\033[0;31m!;\033[0;37m                                                                    弛");
	printf("                                           弛\n");
	printf("弛                                                           \033[0;31m*=\033[0;30m$#######@##@#@*\033[0;37m;!:,--,,,,-~,;;\033[0;30m*@#@@#@####==#@@$\033[0;31m!\033[0;37m                                                                    弛");
	printf("                                           弛\n");
	printf("弛                                                           \033[0;31m!*=\033[0;30m#@#####@@#@##*\033[0;37m;;;~;;::::;;~;;!\033[0;30m@#@@@@###$$@@@\033[0;31m:;;\033[0;37m                                                                    弛");
	gotoxy(x - 2, y); // -2 > 轎溘й溥堅
	printf("               1. GAME START               弛\n");
	printf("弛                                                           \033[0;31m$!=\033[0;30m$#@#@##@@###@**\033[0;37m!;~;--~=--;*;;\033[0;30m;*##@#@###$#@@@@\033[0;31m@@\033[0;37m                                                                    弛");
	gotoxy(x, y + 1);
	printf("	          2. GAME EXIT                弛\n");
	printf("弛                                                           \033[0;31m@$*=$#\033[0;30m@@@@@@###@*;\033[0;37m=;,-,,;#,,,;!\033[0;30m$!=###@###$#@@\033[0;31m@@@@@\033[0;37m                                                                    弛                                           弛\n");
	printf("弛                                                           \033[0;31m@$*=$#@@@@@@###@*;=\033[0;37m;;,-,,;#,,,\033[0;31m;!$!=###@###$#@@@@@@\033[0;37m                                                                    弛                                           弛\n");
	printf("戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎\n");
	while (1) {
		int n = keyControl();
		switch (n) {
		case UP:
			if (y > 54) {
				gotoxy(x - 2, y);
				printf(" ");
				gotoxy(x - 2, --y);
				printf(">");
			}
			break;

		case DOWN:
			if (y < 55) {
				gotoxy(x - 2, y);
				printf(" ");
				gotoxy(x - 2, ++y);
				printf(">");
			}
			break;

		case SPACE:
			return y - 53;
		}
	}	
};

void showLayout() {
	SetConsoleTitle(TEXT("だ資曖 撩 - Castle of Doom"));
	printf("忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖\n");
	printf("弛                                                                                                                                                                                 弛                                           弛\n");
	printf("弛                                                                                                                                                                                 弛                                           弛\n");
	printf("弛                                                                                                                                                                                 弛                                           弛\n");
	printf("弛                                                                                                                                                                                 弛                                           弛\n");
	printf("弛                                                                                                                                                                                 弛                                           弛\n");
	printf("弛                                                                                                                                                                                 弛                                           弛\n");
	printf("弛                                                                                                                                                                                 弛                                           弛\n");
	printf("弛                                                                                                                                                                                 弛                                           弛\n");
	printf("弛                                                                                                                                                                                 弛                                           弛\n");
	printf("弛                                                                                                                                                                                 弛                                           弛\n");
	printf("弛                                                                                                                                                                                 弛                                           弛\n");
	printf("弛                                                                                                                                                                                 弛                                           弛\n");
	printf("弛                                                                                                                                                                                 弛                                           弛\n");
	printf("弛                                                                                                                                                                                 弛                                           弛\n");
	printf("弛                                                                                                                                                                                 弛                                           弛\n");
	printf("弛                                                                                                                                                                                 弛                                           弛\n");
	printf("弛                                                                                                                                                                                 弛                                           弛\n");
	printf("弛                                                                                                                                                                                 弛                                           弛\n");
	printf("弛                                                                                                                                                                                 弛                                           弛\n");
	printf("弛                                                                                                                                                                                 弛                                           弛\n");
	printf("弛                                                                                                                                                                                 弛                                           弛\n");
	printf("弛                                                                                                                                                                                 弛                                           弛\n");
	printf("弛                                                                                                                                                                                 弛                                           弛\n");
	printf("弛                                                                                                                                                                                 弛                                           弛\n");
	printf("弛                                                                                                                                                                                 弛                                           弛\n");
	printf("弛                                                                                                                                                                                 弛                                           弛\n");
	printf("弛                                                                                                                                                                                 弛                                           弛\n");
	printf("弛                                                                                                                                                                                 弛                                           弛\n");
	printf("弛                                                                                                                                                                                 弛                                           弛\n");
	printf("弛                                                                                                                                                                                 弛                                           弛\n");
	printf("弛                                                                                                                                                                                 弛                                           弛\n");
	printf("弛                                                                                                                                                                                 弛                                           弛\n");
	printf("弛                                                                                                                                                                                 弛                                           弛\n");
	printf("弛                                                                                                                                                                                 弛                                           弛\n");
	printf("弛                                                                                                                                                                                 弛                                           弛\n");
	printf("弛                                                                                                                                                                                 弛                                           弛\n");
	printf("弛                                                                                                                                                                                 弛                                           弛\n");
	printf("弛                                                                                                                                                                                 弛                                           弛\n");
	printf("弛                                                                                                                                                                                 弛                                           弛\n");
	printf("弛                                                                                                                                                                                 弛                                           弛\n");
	printf("弛                                                                                                                                                                                 弛                                           弛\n");
	printf("弛                                                                                                                                                                                 弛                                           弛\n");
	printf("弛                                                                                                                                                                                 弛                                           弛\n");
	printf("弛                                                                                                                                                                                 弛                                           弛\n");
	printf("弛                                                                                                                                                                                 弛                                           弛\n");
	printf("弛                                                                                                                                                                                 弛                                           弛\n");
	printf("弛                                                        旨                                                              旬                                                         弛                                           弛\n");
	printf("弛                                                        早                                                              早                                                         弛                                           弛\n");
	printf("弛                                                        早                                                              早                                                         弛                                           弛\n");
	printf("弛                                                        早                                                              早                                                         弛                                           弛\n");
	printf("弛                                                        早                                                              早                                                         戍式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式扣\n");
	printf("弛                                                        早                                                              早                                                         弛                                           弛\n");
	printf("弛                                                        早                                                              早                                                         弛                                           弛\n");
	printf("弛                                                        早                                                              早                                                         弛                                           弛\n");
	printf("弛                                                        早                                                              早                                                         弛                                           弛\n");
	printf("弛                                                        早                                                              早                                                         弛                                           弛\n");
	printf("弛                                                        曲                                                              旭                                                         弛                                           弛\n");
	printf("戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎\n");
};
