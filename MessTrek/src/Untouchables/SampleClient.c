#include "WebGadget.h"

#include <cstdio>
#include <tr1/memory>

#include <StarTrek/Game.h>
#include <StarTrek/Klingon.h>

/**
 * 
 * Note: SampleClient is UNTOUCHABLE! It represents one of hundreds of Game
 * clients, and should not have to change.
 * 
 */

int main(int argc, char** argv) {
	printf("Simple Star Trek");
	Klingon klingon;
	fireWeapon("phaser", "1000", &klingon);
	waitForUserToEndGame();

	return 0;
}

static void waitForUserToEndGame(void) {
	// no-op
}

