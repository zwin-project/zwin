#include <assert.h>
#include <wayland-util.h>

#include "test-runner.h"
#include "zigen-util.h"

TEST(array_to_float)
{
  float f;
  struct wl_array array;
  wl_array_init(&array);
  *(float *)wl_array_add(&array, sizeof(float)) = 1.3f;

  assert(zgn_wl_array_to_float(&array, &f) == 0);
  assert(f == 1.3f);

  *(float *)wl_array_add(&array, sizeof(float)) = 1.3f;
  assert(zgn_wl_array_to_float(&array, &f) == 1);
}

TEST(float_to_array)
{
  float f;
  struct wl_array array;

  wl_array_init(&array);
  assert(zgn_float_to_array(1.3f, &array) == 0);

  assert(*(float *)array.data == 1.3f);
  assert(zgn_wl_array_to_float(&array, &f) == 0);
  assert(f == 1.3f);

  wl_array_add(&array, sizeof(float));
  assert(zgn_float_to_array(1.3f, &array) == 1);
}
