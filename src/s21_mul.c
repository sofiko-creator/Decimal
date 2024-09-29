#include "s21_decimal.h"
/* Return value:
 * 0 -> Ok
 * 1 -> the number is too large or equal to infinity
 * 2 -> the number is too small or equal to negative infinity
 */
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int sing_bit = get_bit(127, value_1) ^ get_bit(127, value_2);
  big_decimal sum;
  make_zero_bd(&sum);
  sum.bnk_round = 1;
  sum.ar_round = 0;
  sum.sign = sing_bit;
  sum.scale = get_scale(value_1) + get_scale(value_2);
  big_decimal big_input_1 = decimal_to_big_dec(value_1);
  big_decimal big_input_2 = decimal_to_big_dec(value_2);

  for (int i = 0; i < 32 * SIZE_OF_BD; i++) {
    if (get_bit_bd(i, big_input_1)) {
      sum = simple_help_plus_bd(sum, big_input_2);
    }
    shift_to_left_bd(&big_input_2);
  }
  int error_code = s21_transform_to_96_bit(&sum);
  big_dec_to_decimal(sum, result);
  return error_code;
}
