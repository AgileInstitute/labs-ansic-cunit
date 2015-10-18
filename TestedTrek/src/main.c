#include <stdio.h>

#include "game.h"
#include "klingon.h"

int main(int argc, char** argv) {
	printf("Simple Star Trek\n");
	srand(time(0));
	Klingon klingon;
	initKlingon(&klingon);
	for (int i = 0; i < 12 && ! klingon.destroyed; i++) {
		if (RND(100) > 20) {
			fireWeapon("phaser", "1000", &klingon);
		} else {
			fireWeapon("photon", "unused", &klingon);
		}
	}
	return 0;
}

