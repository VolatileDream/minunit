#ifndef __MIN_UNIT_H__
#define __MIN_UNIT_H__

// for fprintf
#include <stdio.h>
#include <setjmp.h>

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
#define AT __FILE__ ":" TOSTRING(__LINE__) ": "

// Prints an error message out.
#define mu_print_err(message)     \
    fprintf(stderr, "%s %s\n", AT,  message)

// Checks an expectation.
// Prints out and exits the test if the expecatiton is not met.
#define mu_expect(test)               \
    do {                              \
      if (!(test)) {                  \
        mu_print_err(                 \
            "expectation unmet: "     \
             TOSTRING(test));         \
        mu_exit_test();               \
      }                               \
     } while (0)

// Checks an assertion.
// Increments the number of assertions performed.
// On failure, increments the number of assertion failures, and
// exits the test.
//
// Assertions must be placed in a test.
#define mu_assert(message, test)      \
    do {                              \
      asserts_run++;                  \
      if (!(test)) {                  \
        mu_print_err(message);        \
        failures++;                   \
        mu_exit_test();               \
      }                               \
     } while (0)

#define mu_assert_error(...)          \
    do {                              \
      asserts_run++;                  \
      fprintf(stderr, AT);            \
      fprintf(stderr, __VA_ARGS__);   \
      fprintf(stderr, "\n");          \
      failures++;                     \
    } while (0)

#define mu_test(testname)                                     \
    void T_##testname(void) __attribute__((constructor));     \
    void _##testname(void);                                   \
    void T_##testname(void) {                                 \
      tests_run++;                                            \
      __mu_state = 1;                                              \
      setjmp(__mu_test_buffer);                                    \
      if (__mu_state == 1) {                                       \
        __mu_state = 2;                                            \
        _##testname();                                        \
      }                                                       \
      __mu_state = 0;                                              \
    }                                                         \
    void _##testname(void)

#define mu_exit_test()                \
  do {                                \
    if (__mu_state == 2) {            \
      longjmp(__mu_test_buffer, 0);   \
    } else {                          \
      mu_print_err("failed an assertion outside of a test?"); \
    }                                 \
  } while(0)

// To keep track of jumping around.
extern jmp_buf __mu_test_buffer;
// Used to check if we already attempted to start the test.
extern volatile int __mu_state;

extern volatile int tests_run;
extern volatile int asserts_run;
extern volatile int failures;

#endif /* __MIN_UNIT_H__ */
