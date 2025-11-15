//
// Created by germain on 15/11/2025.
//

#include <CUnit/Basic.h>
#include <CUnit/TestDB.h>

#include "test_synchronous_functions.cuh"

int main() {
    CU_initialize_registry();
    test_basic_functions();
    CU_basic_run_tests();
    CU_cleanup_registry();
    return 0;
}
