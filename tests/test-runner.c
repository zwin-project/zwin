#include "test-runner.h"

#define _GNU_SOURCE

#include <assert.h>
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

extern const struct test __start_test_section, __stop_test_section;

static int is_atty = 0;

#define RED "\033[31m"
#define GREEN "\033[32m"

static void stderr_set_color(const char *color)
{
  if (is_atty) fprintf(stderr, "%s", color);
}

static void stderr_reset_color(void)
{
  if (is_atty) fprintf(stderr, "\033[0m");
}

static void run_test(const struct test *t)
{
  t->run();

  exit(EXIT_SUCCESS);
}

int main()
{
  const struct test *t;
  pid_t pid;
  int total, pass;
  siginfo_t info;

  if (isatty(fileno(stderr))) is_atty = 1;

  pass = 0;
  for (t = &__start_test_section; t < &__stop_test_section; t++) {
    int success = 0;

    pid = fork();
    assert(pid >= 0);

    if (pid == 0) run_test(t); /* never returns */

    if (waitid(P_PID, pid, &info, WEXITED)) {
      stderr_set_color(RED);
      fprintf(stderr, "waitid failed: %s\n", strerror(errno));
      stderr_reset_color();

      abort();
    }

    switch (info.si_code) {
      case CLD_EXITED:
        if (info.si_status == EXIT_SUCCESS)
          success = !t->must_fail;
        else
          success = t->must_fail;

        stderr_set_color(success ? GREEN : RED);
        fprintf(stderr, "test \"%s\": \texit status %d", t->name,
                info.si_status);
        break;

      case CLD_KILLED:
      case CLD_DUMPED:
        if (t->must_fail) success = 1;

        stderr_set_color(success ? GREEN : RED);
        fprintf(stderr, "test \"%s\":\tsignal %d", t->name, info.si_status);
        break;
    }

    if (success) {
      pass++;
      fprintf(stderr, ", pass.\n");
    } else
      fprintf(stderr, ", fail.\n");

    stderr_reset_color();

    fprintf(stderr, "-----------------------------------\n");
  }

  total = &__stop_test_section - &__start_test_section;
  fprintf(stderr, "%d tests, %d pass, %d fail\n", total, pass, total - pass);

  return pass == total ? EXIT_SUCCESS : EXIT_FAILURE;
}
