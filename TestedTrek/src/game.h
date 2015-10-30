#ifndef GAME_HEADER 
#define GAME_HEADER 

#include "klingon.h"

#define INITIAL_ENERGY 10000
#define RND(maximum) (rand() % maximum)
#define streq(a, b) (strcmp(a, b) == 0)

extern int e_;
void fireWeapon(char *command, char *parameter, struct Klingon *enemy);

#endif
