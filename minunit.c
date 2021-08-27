#include "minunit.h"

jmp_buf __mu_test_buffer;
volatile int __mu_state = 0;
volatile int tests_run = 0;
volatile int asserts_run = 0;
volatile int failures = 0;

// Since minunit (ab)uses the compiler to run all the tests before running
// the main function, there's really nothing for this library code to do
// except define the variables that get used by header file.
