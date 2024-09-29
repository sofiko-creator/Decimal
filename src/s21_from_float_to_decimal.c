#include "s21_decimal.h"

/* Return value:
 * 1 -> Convertion error
 * 0 -> Ok
 */
float s21_fabs(float val) {
  if (val < 0) {
    val *= -1;
  }
  return val;
}

int s21_from_float_to_decimal(float value, s21_decimal *dst) {
  if (NULL == dst or value != value or
      (s21_fabs(value) > 0 and s21_fabs(value) < 1e-28) or
      s21_fabs(value) > 7.92281577919e+28) {
    if (NULL != dst) make_zero(dst);
    return 1;
  } else if (value == 0) {
    make_zero(dst);
    return 0;
  }
  make_zero(dst);

  int err_code = 0;
  char float_string[1024] = "";
  int sign = 0;
  if (value < 0) sign = 1;
  sprintf(float_string, "%.6e", value);
  if (float_string[0] == '-') {
    char buff[1024] = "";
    strcpy(buff, float_string + 1);
    strcpy(float_string, buff);
  }
  float_string[8] = ' ';
  float float_mantiss = atof(float_string);
  int scale = -(atoi(float_string + 9));
  int full_mantiss = (int)(float_mantiss * 10000000);
  int array_of_full_mantiss[8];
  for (int i = 7; full_mantiss > 0 and i >= 0; i--) {
    array_of_full_mantiss[i] = full_mantiss % 10;
    full_mantiss /= 10;
  }
  if (array_of_full_mantiss[7] > 4) array_of_full_mantiss[6]++;
  int int_mantiss = 0;
  int i = 0;
  scale--;
  for (; i < 7 and scale < 28; i++) {
    int_mantiss = int_mantiss * 10 + array_of_full_mantiss[i];
    scale++;
  }
  if (i > 0 and i < 7 and array_of_full_mantiss[i] > 4) int_mantiss++;
  dst->bits[0] = int_mantiss;
  if (scale < 0) {
    *dst = get_mantissa_with_scale(get_scale(*dst) - scale, *dst);
    set_scale(0, dst);
  } else
    set_scale(scale, dst);
  set_bit(127, sign, dst);
  return err_code;
}
