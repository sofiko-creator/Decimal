#include "s21_decimal.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  if (NULL == result) return 1;

  big_decimal temp, temp2, zero;
  make_zero_bd(&zero);
  temp = decimal_to_big_dec(value);
  temp.ar_round = 0;

  make_zero(result);
  if ((compare_mantiss_only_bd(temp, zero)) == 0) {
    temp2 = zero;
  } else {
    temp2 = get_mantissa_with_scale_bd(0, temp);

    big_decimal decimal_one;
    make_zero_bd(&decimal_one);
    decimal_one.bits[0] = 1;

    if (temp.sign && (compare_mantiss_only_bd(simple_help_minus_bd(temp2, temp),
                                              zero)) != 0) {
      temp2 = simple_help_plus_bd(temp2, decimal_one);
      temp2.sign = 1;
    }
  }
  big_dec_to_decimal(temp2, result);
  return 0;
}
