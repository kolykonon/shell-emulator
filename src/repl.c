#include "prompt.h"
#include <linux/limits.h>
#include <stdio.h>

void run_repl(void) {
  int counter;
  char prompt[PATH_MAX + 512];
  char line[1024];
  char *argv[15];

  while (1) {
    if (counter == 1) {
      break;
    }
    build_prompt(prompt, sizeof(prompt));
    printf("%s", prompt);
    counter++;
  }
}
