#include "prompt.h"
#include <linux/limits.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void build_prompt(char *buf, size_t size) {
  // parts declaration
  char *user;
  char host[256];
  char cd[PATH_MAX];
  char display[PATH_MAX];

  // username
  struct passwd *pwd = getpwuid(geteuid());

  if (!pwd) {
    user = getenv("USER");

    if (!user) {
      user = "user";
    }

  } else {
    user = pwd->pw_name;
  }
  // host
  if (gethostname(host, sizeof(host)) == -1) {
    snprintf(host, sizeof(host), "%s", "localhost");
  } else {
    host[sizeof(host) - 1] = '\0';
  }
  // current dicrectory
  getcwd(cd, sizeof(cd));
  char *home = getenv("HOME");
  size_t home_len = strlen(home);

  if (strncmp(cd, home, home_len) == 0 && cd[home_len] == '\0' ||
      cd[home_len] == '/') {
    snprintf(display, sizeof(display), "~%s", cd + strlen(home));
  } else {
    snprintf(display, sizeof(display), "%s", cd);
  }
  snprintf(buf, size, "%s@%s:%s$", user, host, display);
}
