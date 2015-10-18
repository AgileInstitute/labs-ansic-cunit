#include <iostream>
#include <cstdlib>
#include <string>
#include <StarTrek/Game.h>
#include <StarTrek/Galaxy.h>
#include <MockGalaxy.h>
#include <MockKlingon.h>

#include "gtest/gtest.h"

using namespace std;
using namespace StarTrek;

void insertPhotonCommand(void) {
    galaxyDictionary["command"] = new string("photon");
}

static int mockRandom(void) {
    // it's not random; that's the point!
    return 1;
}

class GameFixturePhoton : public ::testing::Test {
public:
	GameFixturePhoton();

protected:
	virtual void SetUp() {
		Game::generator = &mockRandom; // without this the test would often fail
		galaxyOutput.clear();
		insertPhotonCommand();
	}
	virtual void TearDown() {
		// typically, we would want to save off the existing value in the setup and then restore it in the teardown
		Game::generator = &rand;
	}

	// because we are injecting a different Galaxy at link-time,
	// there is no differentiation here as far as type, namespace, etc
	Galaxy context;
	Game game;
};
GameFixturePhoton::GameFixturePhoton() :context(nullptr){}

TEST_F(GameFixturePhoton, NotifiedIfNoTorpedoesRemain) {
    game.torpedoes(0);
    galaxyDictionary["target"] = new MockKlingon(2000, 200);
    game.fireWeapon(context);

    EXPECT_EQ("No more photon torpedoes! || ", galaxyOutput);
}

TEST_F(GameFixturePhoton, TorpedoMissesDueToRandomFactors) {
    int distanceWhereRandomFactorsHoldSway = 3000;
    galaxyDictionary["target"] = new MockKlingon(distanceWhereRandomFactorsHoldSway, 200);
    game.fireWeapon(context);

    EXPECT_EQ("Torpedo missed Klingon at 3000 sectors... || ", galaxyOutput);
    EXPECT_EQ(7, game.torpedoes());
}

TEST_F(GameFixturePhoton, TorpedoMissesDueToDistanceAndCleverKlingonEvasiveActions) {
    int distanceWhereTorpedoesAlwaysMiss = 3500;
    galaxyDictionary["target"] = new MockKlingon(distanceWhereTorpedoesAlwaysMiss, 200);
    game.fireWeapon(context);

    EXPECT_EQ("Torpedo missed Klingon at 3500 sectors... || ", galaxyOutput);
    EXPECT_EQ(7, game.torpedoes());
}

TEST_F(GameFixturePhoton, TorpedoDestroysKlingon) {
    MockKlingon* klingon = new MockKlingon(500, 200);
    galaxyDictionary["target"] = klingon;
    game.fireWeapon(context);

    EXPECT_EQ("Photons hit Klingon at 500 sectors with 801 units || Klingon destroyed! || ", galaxyOutput);
    EXPECT_EQ(7, game.torpedoes());
    EXPECT_TRUE(klingon->deleteWasCalled());

}

TEST_F(GameFixturePhoton, TorpedoDamagesKlingon) {
    galaxyDictionary["target"] = new MockKlingon(500, 2000);
    game.fireWeapon(context);

    EXPECT_EQ("Photons hit Klingon at 500 sectors with 801 units || Klingon has 1199 remaining || ", galaxyOutput);
    EXPECT_EQ(7, game.torpedoes());
}
