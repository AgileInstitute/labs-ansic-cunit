#include "game.h"
#include "klingon.h"

void initKlingon(Klingon *k) {
	k->distance = 100 + RND(4000);
	k->energy = 1000 + RND(2000);
	k->destroyed = 0;
}
