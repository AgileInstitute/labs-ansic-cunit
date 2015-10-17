#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>

#include "gtest/gtest.h"

using namespace std;

TEST(MessTrekCharacterizationTests, SomeAsYetUndeterminedScenario) {
    EXPECT_EQ("Some expected value", "some actual value");
}

int main(int argc, char** argv)
{
	// run all tests
	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}