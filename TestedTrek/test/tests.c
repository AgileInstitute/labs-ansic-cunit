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

	char * oneMoreUnitOfEnergyThanWeHave = "10001";
	fireWeapon("phaser", "10001", &klingon);
	CU_ASSERT_STRING_EQUAL(mocks_allOutput(), "Insufficient energy to fire phasers!\n");
}

/*
void test_WhenEnergyExpendedEvenWhenPhasersFiredWhileKlingonOutOfRange
{
    int maxPhaserRange = 4000;
	klingon->distance = maxPhaserRange + 1;
	fireWeapon("phaser", "1000", &klingon);

	CU_ASSERT_STRING_EQUAL(mocks_allOutput(),
		"Klingon out of range of phasers at 4001 sectors...\n");

	CU_ASSERT_INT_EQUAL(ENERGY_IN_NEW_GAME - 1000, _e);
}
*/

void test_PhotonScenario(void)
{
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

        /* add the tests to the suites */

        || (NULL == CU_add_test(phaserSuite,
            "test_WhenPhasersFiredWithInsufficientEnergy", test_WhenPhasersFiredWithInsufficientEnergy))

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

