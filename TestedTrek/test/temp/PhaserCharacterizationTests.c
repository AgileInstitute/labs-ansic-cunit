#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <StarTrek/Game.h>
#include <StarTrek/Galaxy.h>
#include <MockGalaxy.h>
#include <MockKlingon.h>

#include "gtest/gtest.h"

using namespace std;
using namespace StarTrek;

void insertPhaserCommand() {
    galaxyDictionary["command"] = new string("phaser");
}

class GameFixturePhaser : public ::testing::Test {
public:
	GameFixturePhaser();

protected:
	virtual void SetUp() {
		galaxyOutput.clear();
		insertPhaserCommand();
	}
	virtual void TearDown() {
	}

	// because we are injecting a different Galaxy at link-time,
	// there is no differentiation here as far as type, namespace, etc
	Galaxy context;
	Game game;
};
GameFixturePhaser::GameFixturePhaser() :context(nullptr){}



TEST_F(GameFixturePhaser, PhasersDamageOfZeroStillHits_AndNondestructivePhaserDamageDisplaysRemaining) {
    string* minimalFired = new string("0");
    galaxyDictionary["amount"] = minimalFired;
    galaxyDictionary["target"] = new MockKlingon(2000, 200);
    Game::generator = &mockRandom;
    game.fireWeapon(context);

    EXPECT_EQ("Phasers hit Klingon at 2000 sectors with 1 units || Klingon has 199 remaining || ", galaxyOutput);
    // Isn't this also a bug?  I *ask* to fire zero, and I still hit?
    // Acknowledge it, log it, but don't fix it yet!
}

int main(int argc, char** argv)
{
	// run all tests
	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}

