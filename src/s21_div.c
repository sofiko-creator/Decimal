#include "s21_decimal.h"

void integer_big_div(big_decimal value, big_decimal dividing,
                     big_decimal *big_result, big_decimal *big_reminder) {
  if (NULL == big_result or NULL == big_reminder or
      s21_control_zero(dividing) == 0)
    return;
  int ar_round = big_result->ar_round;
  int bnk_round = big_result->bnk_round;
  int sing = big_result->sign;
  make_zero_bd(big_result);
  big_result->ar_round = ar_round;
  big_result->bnk_round = bnk_round;
  big_result->sign = sing;
  if (s21_control_zero(value) == 0) {
    return;
  }
  big_decimal big_multiplication = dividing;
  while (compare_mantiss_only_bd(value, big_multiplication) >= 0) {
    int s = 0;
    for (;; s++) {
      big_decimal buffer = big_multiplication;
      shift_to_left_bd(&buffer);
      if (compare_mantiss_only_bd(buffer, value) <= 0)
        shift_to_left_bd(&big_multiplication);
      else
        break;
    }
    set_bit_bd(s, 1, big_result);
    value = simple_help_minus_bd(value, big_multiplication);
    big_multiplication = dividing;
  }
  *big_reminder = value;
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  big_decimal big_result, big_copy, big_multiplication;
  make_zero_bd(&big_result);
  big_result.sign = get_bit(127, value_1) ^ get_bit(127, value_2);
  big_result.ar_round = 0;
  big_result.bnk_round = 1;
  big_copy = decimal_to_big_dec(value_1);
  big_multiplication = decimal_to_big_dec(value_2);
  if (s21_control_zero(big_multiplication) == 0) return 3;
  big_decimal big_reminder;
  make_zero_bd(&big_reminder);
  integer_big_div(big_copy, big_multiplication, &big_result, &big_reminder);
  if (s21_control_zero(big_reminder) == 1) {
    big_reminder = get_mantissa_with_scale_bd(28, big_reminder);
    big_result = get_mantissa_with_scale_bd(28, big_result);
    big_decimal big_devided, trash_reminder;
    make_zero_bd(&big_devided);
    make_zero_bd(&trash_reminder);
    integer_big_div(big_reminder, big_multiplication, &big_devided,
                    &trash_reminder);
    big_result = simple_help_plus_bd(big_result, big_devided);
  }
  int new_scale = big_result.scale + get_scale(value_1) - get_scale(value_2);
  big_result.scale = new_scale;
  if (big_result.scale < 0) {
    big_result = get_mantissa_with_scale_bd(0, big_result);
  }
  int error_code = s21_transform_to_96_bit(&big_result);
  if (error_code == 0) big_dec_to_decimal(big_result, result);
  return error_code;
}
