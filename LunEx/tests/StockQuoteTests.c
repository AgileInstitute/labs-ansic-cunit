// required includes

#include "gtest/gtest.h"
#include "gmock/gmock.h"

// some mock behaviors

using ::testing::Return;
using ::testing::Throw;

TEST(StockQuote, Total) {
    // TODO: Write a test here
    EXPECT_EQ(1234, 42);
}


int main(int argc, char** argv)
{
	// run all tests
	::testing::InitGoogleTest(&argc, argv);
    
	return RUN_ALL_TESTS();
}