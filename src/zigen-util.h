#ifndef ZIGEN_UTIL_H
#define ZIGEN_UTIL_H

#include <wayland-util.h>

int zgn_wl_array_to_float(struct wl_array *array, float *f)
{
  if (array->size != sizeof(float)) return 1;
  *f = *(float *)array->data;
  return 0;
}

int zgn_float_to_array(float f, struct wl_array *array)
{
  float *target;
  if (array->size == sizeof(float)) {
    target = array->data;
  } else if (array->size == 0) {
    target = wl_array_add(array, sizeof(float));
  } else
    return 1;

  *target = f;
  return 0;
}

#endif  //  ZIGEN_UTIL_H
