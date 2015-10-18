/*
 * Characterization tests for the TestedTrek Star Trek "game."
 */

#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

/* Pointer to the file used by the tests. */
static FILE* temp_file = NULL;

/* The suite initialization function.
 * Opens the temporary file used by the tests.
 * Returns zero on success, non-zero otherwise.
 */
int init_game(void)
{
      return 0;
}

/* The suite cleanup function.
 * Closes the temporary file used by the tests.
 * Returns zero on success, non-zero otherwise.
 */
int clean_game(void)
{
      return 0;
}

void test_PassingScenario(void)
{
      CU_ASSERT(0);
}

void test_FailingScenario(void)
{
      CU_ASSERT(1);
}

/* The main() function for setting up and running the tests.
 * Returns a CUE_SUCCESS on successful running, another
 * CUnit error code on failure.
 */
int main()
{
   /* initialize the CUnit test registry */
   if (CUE_SUCCESS != CU_initialize_registry())
      return CU_get_error();

   /* add a suite to the registry */
   CU_pSuite phaserSuite = NULL;
   pSuite = CU_add_suite("Phasers", init_game, clean_game);
   if (NULL == pSuite) {
      CU_cleanup_registry();
      return CU_get_error();
   }

   /* add a suite to the registry */
   CU_pSuite photonSuite = NULL;
   pSuite = CU_add_suite("Photons", init_game, clean_game);
   if (NULL == pSuite) {
      CU_cleanup_registry();
      return CU_get_error();
   }

   if (0

        /* add the tests to the suites */

        || (NULL == CU_add_test(phaserSuite,
            "description here", test_PassingScenario))

        || (NULL == CU_add_test(photonSuite,
            "description here", test_FailingScenario))

       )
   {
      CU_cleanup_registry();
      return CU_get_error();
   }


   /* Run all tests using the CUnit Basic interface */
   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   CU_cleanup_registry();
   return CU_get_error();
}

