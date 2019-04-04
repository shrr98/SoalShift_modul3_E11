#include "monster.h"
#include "stdio.h"

int main(){
    char name[20];
    printf("Name > ");
    scanf("%s", name);
    Monster *monster = new Monster(name);
    monster->play();
    delete monster;
    return 0;
}