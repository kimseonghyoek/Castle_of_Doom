#include <stdio.h>

// player ����ü
struct player {
	// ����ġ, ü��, ����, ����, ���ݷ�, ����ִ� ������(���ڿ�), �����۵�(���ڿ� �迭)
	int level;
	int hp;
	double attack;
	double luck;
	double exp;
	char* item;
	char* bags;
};

// ������ ����ü
struct armor_item {
	// ü�� ����, ���� ����
	int increase_hp;
	double increase_luck;
};

struct attack_item {
	// ���ݷ�����
	double increase_attack;
};

// �� ����ü
struct enemy {
	// ü��, ����, ���ݷ�, ���� ����ִ� ������(���ڿ�), �� ����(����, ����)
	int hp;
	int level;
	int attack;
	char* mop_item;
	char* mop_category;
};

int main(void) {
	
	return 0;
}