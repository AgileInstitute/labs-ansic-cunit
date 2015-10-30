#ifndef GAME_HEADER 
#define GAME_HEADER 

#include "klingon.h"

#define RND(maximum) (rand() % maximum)
#define streq(a, b) (strcmp(a, b) == 0)

void fireWeapon(char *command, char *parameter, struct Klingon *enemy);

#endif
