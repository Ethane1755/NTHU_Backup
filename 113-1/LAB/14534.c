#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function.h"

#define TABLE_ROW 3
#define TABLE_COLUMN 5
#define MAX_CAT_TYPE 5
#define MAX_MONSTER_NUM 100

Cat *newCatType() {
    Cat *newCat = (Cat *)malloc(sizeof(Cat));
    newCat->catName = (char *)malloc(21 * sizeof(char));
    scanf("%s %d %d", newCat->catName, &newCat->attack, &newCat->speed);
    return newCat;
}

Table *newCat(Cat **catTypes) {
    Table *newTable = (Table *)malloc(sizeof(Table));
    int tp;
    scanf("%d", &tp);

    newTable->cat = catTypes[tp];
    newTable->catLevel = 0;

    return newTable;
}

Table *deleteCat(Table *table) {
    if (table == NULL) return NULL;
    free(table);
    return NULL;
}

Monster *newMonster() {
    Monster *newMonster = (Monster *)malloc(sizeof(Monster));
    newMonster->monsterName = (char *)malloc(21 * sizeof(char));
    scanf("%s %d", newMonster->monsterName, &newMonster->hp);
    return newMonster;
}

Monster *deleteMonster(Monster *monster) {
    if (monster == NULL) return NULL;
    free(monster->monsterName);
    free(monster);
    return NULL;
}

int getAttackSum(Table *table[][5], int currentTime) {
    int totalAttack = 0;

    for (int i = 0; i < TABLE_ROW; i++) {
        for (int j = 0; j < TABLE_COLUMN; j++) {
            if (table[i][j] != NULL) {
                int attackSpeed = table[i][j]->cat->speed;
                if (currentTime % attackSpeed == 0) {
                    totalAttack += table[i][j]->cat->attack * (1 << table[i][j]->catLevel);
                }
            }
        }
    }

    return totalAttack;
}