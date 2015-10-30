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

	CU_ASSERT_STRING_EQUAL(mocks_allOutput(),
		"Phasers hit Klingon at 2000 sectors with 500 units\nKlingon destroyed!\n");
}


void test_PhotonScenario(void)
{
	init_game(); /* amazingly, CUnit does not call this for each test */

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

        /* PHOTONS! */

        || (NULL == CU_add_test(photonSuite,
            "description here", test_PhotonScenario))

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

