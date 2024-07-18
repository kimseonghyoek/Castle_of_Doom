#include <stdio.h>

// player 구조체
struct player {
	// 경험치, 체력, 레벨, 행운력, 공격력, 들고있는 아이템(문자열), 아이템들(문자열 배열)
	int level;
	int hp;
	double attack;
	double luck;
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
	int attack;
	char* mop_item;
	char* mop_category;
};

void showLayout();

int main(void) {
	showLayout();
	return 0;
}

// 게임 실행시 보여줄 레이아웃
void showLayout() {
	printf("┌────────────────────────────────────────────────────────────┐────────────────────┐\n");
	printf("│                                                            │                    │\n");
	printf("│                                                            │                    │\n");
	printf("│                                                            │                    │\n");
	printf("│                                                            │                    │\n");
	printf("│                                                            │                    │\n");
	printf("│                                                            │                    │\n");
	printf("│                                                            │                    │\n");
	printf("│                                                            │                    │\n");
	printf("│                                                            │                    │\n");
	printf("│                                                            │                    │\n");
	printf("│                                                            │                    │\n");
	printf("│                                                            │                    │\n");
	printf("│                                                            │                    │\n");
	printf("│                                                            │                    │\n");
	printf("│                                                            │                    │\n");
	printf("│                                                            │                    │\n");
	printf("│                                                            │                    │\n");
	printf("│                                                            │                    │\n");
	printf("│                                                            │                    │\n");
	printf("│                                                            │                    │\n");
	printf("│                                                            │                    │\n");
	printf("│                                                            │                    │\n");
	printf("│                                                            │                    │\n");
	printf("│                                                            │                    │\n");
	printf("│                                                            │                    │\n");
	printf("│                                                            │                    │\n");
	printf("│                                                            │                    │\n");
	printf("│                                                            │                    │\n");
	printf("│                                                            │                    │\n");
	printf("│                                                            │                    │\n");
	printf("└────────────────────────────────────────────────────────────┘────────────────────┘\n");
};