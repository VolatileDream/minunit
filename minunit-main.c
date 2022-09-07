#include "minunit.h"
#include <stdio.h>

int main(int argc, char **argv) {
  (void) argc;
  (void) argv;
  printf("Asserts checked: %d\n", asserts_run);
  printf("Asserts failed: %d\n", failures);
  printf("Tests run: %d\n", tests_run);

  // Return non-zero if tests failed.
  return failures > 0;
}
