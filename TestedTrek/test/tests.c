/*VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV*/
/*
 * Characterization tests for the TestedTrek Star Trek "game."
 */
/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>

/* CUnit includes */
#include "Basic.h"

/*VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV*/

/* mocks */
#include "mocks.h"

/* production includes */
#include "game.h"

Klingon klingon;

/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

/* The suite initialization function.
 * Opens the temporary file used by the tests.
 * Returns zero on success, non-zero otherwise.
 */

int init_game(void)
{
/*VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV*/

	mocks_setup();
	e_ = INITIAL_ENERGY;
	initKlingon(&klingon);

/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
	return 0;
}

/* The suite cleanup function.
 * Closes the temporary file used by the tests.
 * Returns zero on success, non-zero otherwise.
 */
int clean_game(void)
{
/*VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV*/

	mocks_teardown();

/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
	return 0;
}

/*VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV*/

void test_WhenPhasersFiredWithInsufficientEnergy(void)
{
	init_game(); /* amazingly, CUnit does not call this for each test */

	char * oneMoreUnitOfEnergyThanWeHave = "10001";
	fireWeapon("phaser", "10001", &klingon);
	CU_ASSERT_STRING_EQUAL(mocks_allOutput(), "Insufficient energy to fire phasers!\n");
}

void test_WhenEnergyExpendedEvenWhenPhasersFiredWhileKlingonOutOfRange(void)
{
	init_game(); /* amazingly, CUnit does not call this for each test */

	int maxPhaserRange = 4000;
	klingon.distance = maxPhaserRange + 1;
	fireWeapon("phaser", "1000", &klingon);

	CU_ASSERT_EQUAL(INITIAL_ENERGY - 1000, e_);

	CU_ASSERT_STRING_EQUAL(mocks_allOutput(),
		"Klingon out of range of phasers at 4001 sectors...\n");
}

void test_WhenPhasersFiredKlingonDestroyed(void)
{
	init_game(); /* amazingly, CUnit does not call this for each test */

	klingon.distance = 2000;
	klingon.energy = 200;
	fireWeapon("phaser", "1000", &klingon);

	mocks_verboseAssertIntEquals(INITIAL_ENERGY - 1000, e_);
	CU_ASSERT_EQUAL(INITIAL_ENERGY - 1000, e_);

	CU_ASSERT_TRUE(klingon.destroyed);

	char *expected =
"Phasers hit Klingon at 2000 sectors with 500 units\nKlingon destroyed!\n";
	char *actual = mocks_allOutput();
	mocks_verboseAssertStringEquals(expected, actual);
	CU_ASSERT_STRING_EQUAL(actual, expected);
}

/*
** NOTE: This test covers two behaviors:
** First...
**   Characterizes a defect: firing 0 hits with 1 unit of energy.
**   We acknowledge it in this test, log it, but we don't fix it until asked!
**   After all, it's a "feature"!
** Second...
**   Tests that damage subtracts from Klingon energy and displays remaining
**   when the Klingon is not destroyed.
*/
void test_BUGWhenPhaserFireZeroStillHits_AndPhaserDamageDisplaysRemaining(void)
{
	init_game(); /* amazingly, CUnit does not call this for each test */

	klingon.distance = 2000;
	klingon.energy = 200;

	char *zeroEnergyFired = "0";
	fireWeapon("phaser", zeroEnergyFired, &klingon);

	mocks_verboseAssertIntEquals(INITIAL_ENERGY, e_);
	CU_ASSERT_EQUAL(e_, INITIAL_ENERGY);

	char *expected =
"Phasers hit Klingon at 2000 sectors with 1 units\nKlingon has 199 remaining\n";
	char *actual = mocks_allOutput();
	mocks_verboseAssertStringEquals(expected, actual);
	CU_ASSERT_STRING_EQUAL(actual, expected);
}

void test_NotifiedIfNoTorpedoesRemain(void)
{
	init_game(); /* amazingly, CUnit does not call this for each test */

	t_ = 0;

	klingon.distance = 2000;
	klingon.energy = 200;
	fireWeapon("photon", "", &klingon);

	char *expected = "No more photon torpedoes!\n";
	char *actual = mocks_allOutput();
	mocks_verboseAssertStringEquals(expected, actual);
	CU_ASSERT_STRING_EQUAL(actual, expected);

}

void test_WhenTorpedoMissesDueToRandomFactors(void)
{
	init_game(); /* amazingly, CUnit does not call this for each test */
	t_ = 5;

	/* in this test case, important that rand() return 2 or 3 */
	int random_numbers[1] = { 2 };
	mocks_setRand(random_numbers, 1);

    	int distanceWhereRandomFactorsHoldSway = 2500;
	klingon.distance = distanceWhereRandomFactorsHoldSway;
	klingon.energy = 200;
	fireWeapon("photon", "", &klingon);

	char *expected = "Torpedo missed Klingon at 2500 sectors...\n";
	char *actual = mocks_allOutput();
	mocks_verboseAssertStringEquals(expected, actual);
	CU_ASSERT_STRING_EQUAL(actual, expected);
    
	mocks_verboseAssertIntEquals(4, t_);
	CU_ASSERT_EQUAL(t_, 4);
}

void test_WhenTorpedoMissesDueToDistanceAndCleverKlingonEvasiveActions(void)
{
	init_game(); /* amazingly, CUnit does not call this for each test */
	t_ = 5;

	int random_numbers[1] = { 1 };
	mocks_setRand(random_numbers, 1);

    	int distanceWhereTorpedoesAlwaysMiss = 3500;
	klingon.distance = distanceWhereTorpedoesAlwaysMiss;
	klingon.energy = 200;
	fireWeapon("photon", "", &klingon);

	char *expected = "Torpedo missed Klingon at 3500 sectors...\n";
	char *actual = mocks_allOutput();
	mocks_verboseAssertStringEquals(expected, actual);
	CU_ASSERT_STRING_EQUAL(actual, expected);
    
	mocks_verboseAssertIntEquals(4, t_);
	CU_ASSERT_EQUAL(t_, 4);
}

void test_WhenTorpedoDestroysKlingon(void)
{
	init_game(); /* amazingly, CUnit does not call this for each test */
	t_ = 5;

	int random_numbers[1] = { 1 };
	mocks_setRand(random_numbers, 1);

	klingon.distance = 500;
	klingon.energy = 200;
	fireWeapon("photon", "", &klingon);

	CU_ASSERT_TRUE(klingon.destroyed);

	char *expected =
"Photons hit Klingon at 500 sectors with 801 units\nKlingon destroyed!\n";
	char *actual = mocks_allOutput();
	mocks_verboseAssertStringEquals(expected, actual);
	CU_ASSERT_STRING_EQUAL(actual, expected);
    
	mocks_verboseAssertIntEquals(4, t_);
	CU_ASSERT_EQUAL(t_, 4);
}

void test_WhenTorpedoDamagesKlingon(void)
{
	init_game(); /* amazingly, CUnit does not call this for each test */
	t_ = 5;

	int random_numbers[1] = { 1 };
	mocks_setRand(random_numbers, 1);

	klingon.distance = 500;
	klingon.energy = 2000;
	fireWeapon("photon", "", &klingon);

	char *expected =
"Photons hit Klingon at 500 sectors with 801 units\nKlingon has 1199 remaining\n";
	char *actual = mocks_allOutput();
	mocks_verboseAssertStringEquals(expected, actual);
	CU_ASSERT_STRING_EQUAL(actual, expected);
    
	mocks_verboseAssertIntEquals(4, t_);
	CU_ASSERT_EQUAL(t_, 4);
}

/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

/* The main() function for setting up and running the tests.
 * Returns a CUE_SUCCESS on successful running, another
 * CUnit error code on failure.
 */
int main()
{
   /* initialize the CUnit test registry */
   if (CUE_SUCCESS != CU_initialize_registry())
      return CU_get_error();

/*VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV*/

   /* add a suite to the registry */
   CU_pSuite phaserSuite = NULL;
   phaserSuite = CU_add_suite("Phasers", init_game, clean_game);
   if (NULL == phaserSuite) {
      CU_cleanup_registry();
      return CU_get_error();
   }

   /* add a suite to the registry */
   CU_pSuite photonSuite = NULL;
   photonSuite = CU_add_suite("Photons", init_game, clean_game);
   if (NULL == photonSuite) {
      CU_cleanup_registry();
      return CU_get_error();
   }

   if (0

        /* PHASERS! */

	|| (NULL == CU_add_test(phaserSuite,
	"test_WhenPhasersFiredWithInsufficientEnergy",
	test_WhenPhasersFiredWithInsufficientEnergy))

	|| (NULL == CU_add_test(phaserSuite,
	"test_WhenEnergyExpendedEvenWhenPhasersFiredWhileKlingonOutOfRange",
	test_WhenEnergyExpendedEvenWhenPhasersFiredWhileKlingonOutOfRange))

	|| (NULL == CU_add_test(phaserSuite,
	"test_WhenPhasersFiredKlingonDestroyed",
	test_WhenPhasersFiredKlingonDestroyed))

	|| (NULL == CU_add_test(phaserSuite,
	"test_BUGWhenPhaserFireZeroStillHits_AndPhaserDamageDisplaysRemaining",
	test_BUGWhenPhaserFireZeroStillHits_AndPhaserDamageDisplaysRemaining))

        /* PHOTONS! */

        || (NULL == CU_add_test(photonSuite,
	"test_NotifiedIfNoTorpedoesRemain",
	test_NotifiedIfNoTorpedoesRemain))

        || (NULL == CU_add_test(photonSuite,
	"test_WhenTorpedoMissesDueToRandomFactors",
	test_WhenTorpedoMissesDueToRandomFactors))

        || (NULL == CU_add_test(photonSuite,
	"test_WhenTorpedoMissesDueToDistanceAndCleverKlingonEvasiveActions",
	test_WhenTorpedoMissesDueToDistanceAndCleverKlingonEvasiveActions))

        || (NULL == CU_add_test(photonSuite,
	"test_WhenTorpedoDestroysKlingon",
	test_WhenTorpedoDestroysKlingon))

        || (NULL == CU_add_test(photonSuite,
	"test_WhenTorpedoDamagesKlingon",
	test_WhenTorpedoDamagesKlingon))

       )
   {
      CU_cleanup_registry();
      return CU_get_error();
   }


/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

   /* Run all tests using the CUnit Basic interface */
   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   CU_cleanup_registry();
   return CU_get_error();
}

