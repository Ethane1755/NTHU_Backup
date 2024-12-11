#ifndef __FUNCTION_H__
#define __FUNCTION_H__

typedef struct {
    char *catName;
    int attack;
    int speed;
    int catType;
} Cat;

typedef struct {
    int catLevel;
    Cat *cat;
} Table;

typedef struct {
    char *monsterName;
    int hp;
} Monster;

Cat* newCatType();

Table* newCat(Cat **catTypes);

Table* deleteCat(Table *table);

Monster* newMonster();

int getAttackSum(Table *table[][5], int currentTime);

Monster* deleteMonster(Monster *monster);

#endif