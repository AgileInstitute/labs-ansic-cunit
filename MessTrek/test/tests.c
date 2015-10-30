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

/***

	HINT: Put any global test variables here.

***/

/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

/* The suite initialization function.
 * Opens the temporary file used by the tests.
 * Returns zero on success, non-zero otherwise.
 */

int init_game(void)
{
/*VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV*/

/***

	HINT: Put any common test setup here.

***/

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

/***

	HINT: Tear down any resource used but not freed by the test.

***/

/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
	return 0;
}

/*VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV*/

void test_SomeScenario(void)
{

/***

	HINT: Here is a template for your first characterization test.

***/
	CU_FAIL("HINT: Here is a template for your first test.\n");
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
   CU_pSuite characterizationSuite = NULL;
   characterizationSuite = CU_add_suite("Game tests", init_game, clean_game);
   if (NULL == characterizationSuite) {
      CU_cleanup_registry();
      return CU_get_error();
   }

   if (0

/***

	HINT: Here is where you add more tests to the suite.
	Simply copy/paste/modify the two lines below...

***/

        || (NULL == CU_add_test(characterizationSuite,
            "HINT: here is the test description", test_SomeScenario))

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

