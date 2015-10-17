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


static const int EnergyInNewGame = 10000;

TEST_F(GameFixturePhaser, PhasersFiredWithInsufficientEnergy) {
    stringstream ten_thousand_and_one;
    ten_thousand_and_one << EnergyInNewGame + 1;
    galaxyDictionary["amount"] =  new string(ten_thousand_and_one.str());
    game.fireWeapon(context);

    EXPECT_EQ("Insufficient energy to fire phasers! || ", galaxyOutput);
}

TEST_F(GameFixturePhaser, EnergyExpendedEvenWhenPhasersFiredWhileKlingonOutOfRange) {
    int maxPhaserRange = 4000;
    galaxyDictionary["amount"] = new string("1000");
    galaxyDictionary["target"] = new MockKlingon(maxPhaserRange + 1);
    game.fireWeapon(context);

    EXPECT_EQ("Klingon out of range of phasers at 4001 sectors... || ", galaxyOutput);

    EXPECT_EQ(EnergyInNewGame - 1000, game.energyRemaining());
}

static int mockRandom(void) {
    // it's not random; that's the point!
    return 0;
}

TEST_F(GameFixturePhaser, PhasersFiredKlingonDestroyed) {
    MockKlingon* klingon = new MockKlingon(2000, 200);
    galaxyDictionary["amount"] = new string("1000");
    galaxyDictionary["target"] = klingon;
    Game::generator = &mockRandom;
    game.fireWeapon(context);

    EXPECT_EQ("Phasers hit Klingon at 2000 sectors with 500 units || Klingon destroyed! || ", galaxyOutput);
    EXPECT_EQ(EnergyInNewGame - 1000, game.energyRemaining());

    EXPECT_TRUE(klingon->deleteWasCalled());
}

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