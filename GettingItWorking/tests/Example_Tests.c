//
//  Example_Tests.cpp
//  Example
//

#include "gtest/gtest.h"
#include "Example.h"

TEST(ExampleClass, initializationTest) {
    ExampleClass myExample;
    EXPECT_EQ(0, myExample.GetValue());
}

TEST(ExampleClass, doSomethingTest) {
	ExampleClass myExample;
	myExample.DoSomething();
	EXPECT_EQ(5, myExample.GetValue());
}


int main(int argc, char** argv)
{
	// run all tests
	::testing::InitGoogleTest(&argc, argv);
    
	return RUN_ALL_TESTS();
}