#ifndef TEST_RUNNDER_H
#define TEST_RUNNDER_H

struct test {
  const char *name;
  void (*run)(void);
  int must_fail;
} __attribute__((aligned(16)));

#define TEST(name)                                                       \
  static void name(void);                                                \
                                                                         \
  const struct test test##name                                           \
      __attribute__((used, section("test_section"))) = {#name, name, 0}; \
                                                                         \
  static void name(void)

#endif  //  TEST_RUNNDER_H
