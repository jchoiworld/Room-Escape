#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE = 10

typedef struct Player
{
	int x;
	int y;
	int key;
};

void printMap(char map[SIZE][SIZE], Player p)
{
	printf("=== [ Room Escape ] ===\n");
	printf("조작법: W(위), A(왼쪽), S(아래), D(오른쪽) + Enter\n");
	printf("목표: 열쇠를 찾아 암호를 풀고 출구로 탈출하세요!\n\n");
}