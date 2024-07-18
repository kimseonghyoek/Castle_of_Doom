#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>

// player 구조체
struct player {
	// 경험치, 체력, 레벨, 행운력, 공격력, 들고있는 아이템(문자열), 아이템들(문자열 배열)
	int level;
	int hp;
	float attack;
	float luck;
	double exp;
	char* item;
	char* bags;
};

// 아이템 구조체
struct armor_item {
	// 체력 증가, 행운력 증가
	int increase_hp;
	double increase_luck;
};

struct attack_item {
	// 공격력증가
	double increase_attack;
};

// 적 구조체
struct enemy {
	// 체력, 레벨, 공격력, 몹이 들고있는 아이템(문자열), 몹 유형(졸개, 보스)
	int hp;
	int level;
	float attack;
	char* mop_item;
	char* mop_category;
};

// 함수 선언부
void showLayout();
void runAway();
int attack(float damege, int hp);
char* selectItems(char *itmes);


int main(void) {
	showLayout();
//	runAway();
	
	
	
	
	return 0;
}

// 게임 실행시 보여줄 레이아웃
void showLayout() {
	SetConsoleTitle(TEXT("파멸의 성 - Castle of Doom"));
	printf("┌─────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐───────────────────────────────────────────┐\n");
	printf("│                                                                                                                                                                                 │                                           │\n");
	printf("│                                                                   ##                 ###                                                                                        │                                           │\n");
	printf("│                                             ####              ##  ##                ##     ####                                                                                 │                                           │\n");
	printf("│                                            ##     ###    ### #### ##  ###     ###  #####   ## ##   ###   ###  # ## ##                                                           │                                           │\n");
	printf("│                                           ##        ##  ##    ##  ## ## ##   ## ##  ##     ##  ## ## ## ## ## ## ## ##                                                          │                                           │\n");
	printf("│                                           ##      ####  ###   ##  ## ## ##   ## ##  ##     ##  ## ## ## ## ## ## ## ##                                                          │                                           │\n");
	printf("│                                           ##     ## ##   ###  ##  ## #####   ## ##  ##     ##  ## ## ## ## ## ## ## ##                                                          │                                           │\n");
	printf("│	                                     ##    ## ##    ##  ##  ## ##      ## ##  ##     ## ##  ## ## ## ## ## ## ##                                                          │                                           │\n");
	printf("│                                             ####  ## ## ###    ## ##  ####    ###   ##     ####    ###   ###  ## ## ##                                                          │                                           │\n");
	printf("│                                                                                                                                                                                 │                                           │\n");
	printf("│                                                                                                                                                                                 │                                           │\n");
	printf("│                                                                                                                                                                                 │                                           │\n");
	printf("│                                                                                                                                                                                 │                                           │\n");
	printf("│                                                                                                                                                                                 │                                           │\n");
	printf("│                                                                                                                                                                                 │                                           │\n");
	printf("│                                                                                                                                                                                 │                                           │\n");
	printf("│                                                                                                                                                                                 │                                           │\n");
	printf("│                                                                                                                                                                                 │                                           │\n");
	printf("│                                                                                                                                                                                 │                                           │\n");
	printf("│                                                                                                                                                                                 │                                           │\n");
	printf("│                                                                                                                                                                                 │                                           │\n");
	printf("│                                                                                                                                                                                 │                                           │\n");
	printf("│                                                                                                                                                                                 │                                           │\n");
	printf("│                                                                                                                                                                                 │                                           │\n");
	printf("│                                                                                                                                                                                 │                                           │\n");
	printf("│                                                                                                                                                                                 │                                           │\n");
	printf("│                                                                                                                                                                                 │                                           │\n");
	printf("│                                                                                                                                                                                 │                                           │\n");
	printf("│                                                                                                                                                                                 │                                           │\n");
	printf("│                                                                                                                                                                                 │                                           │\n");
	printf("│                                                                                                                                                                                 │                                           │\n");
	printf("│                                                                                                                                                                                 │                                           │\n");
	printf("│                                                                                                                                                                                 │                                           │\n");
	printf("│                                                                                                                                                                                 │                                           │\n");
	printf("│                                                                                                                                                                                 │                                           │\n");
	printf("│                                                                                                                                                                                 │                                           │\n");
	printf("│                                                                                                                                                                                 │                                           │\n");
	printf("│                                                                                                                                                                                 │                                           │\n");
	printf("│                                                                                                                                                                                 │                                           │\n");
	printf("│                                                                                                                                                                                 │                                           │\n");
	printf("│                                                                                                                                                                                 ├───────────────────────────────────────────┤\n");
	printf("│                                                                                                                                                                                 │                                           │\n");
	printf("│                                                                                                                                                                                 │                                           │\n");
	printf("│                                                                                                                                                                                 │                                           │\n");
	printf("│                                                                                                                                                                                 │                                           │\n");
	printf("└─────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘───────────────────────────────────────────┘\n");
};
                                                                                                                                           
// 전투시 도망(0~9중에서 6까지는 도망이 가능하고 6보다 크면 도망에 못가는 확률)
void runAway() {
	srand(time(NULL));
	int random = 0;
	random = rand() % 9;
	printf("%d\n", random);
	if (random <= 6) {
		printf("무사히 도망쳤습니다.");
	}
	else {
		printf("도망가지 못하였습니다.");
	}
};

// 전투시 공격(parameter로 현재 공격력과 공격받는 상대의 체력을 받음. 후에 공격을 받은 후의 체력을 반환함.)
int attack(float damege, int hp) {
	return 0;
}

// 현재 가지고 있는 아이템 중 선택
char* selectItems(char* items) {
	return "items";
}