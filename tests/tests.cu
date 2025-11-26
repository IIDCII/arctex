#include <CUnit/Basic.h>
#include <CUnit/TestDB.h>

#include "exploration_tests.cuh"
#include "test_synchronous_functions.cuh"

int main() {
    CU_initialize_registry();
    test_basic_functions();
    // test_experimentation();
    CU_basic_run_tests();
    CU_cleanup_registry();
    return 0;
}
