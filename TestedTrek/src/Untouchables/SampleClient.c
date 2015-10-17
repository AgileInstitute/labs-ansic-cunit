#include "WebGadget.h"

#include <cstdio>
#include <tr1/memory>

#include <StarTrek/Game.h>
#include <StarTrek/Klingon.h>

using namespace StarTrek;

namespace Untouchables {
	static void waitForUserToEndGame(void);
}
 
/**
 * 
 * Note: SampleClient is UNTOUCHABLE! It represents one of hundreds of Game
 * clients, and should not have to change.
 * 
 */

using namespace Untouchables;

int main(int argc, char** argv) {
	printf("Simple Star Trek");
	std::tr1::shared_ptr<Klingon> klingon(new Klingon);
	WebGadget wg("phaser", "1000", (void*)klingon.get());
	Game game;
	game.fireWeapon(&wg);
	waitForUserToEndGame();

	return 0;
}

static void Untouchables::waitForUserToEndGame(void) {
	// no-op
}

