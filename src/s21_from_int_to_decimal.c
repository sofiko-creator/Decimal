#include "s21_decimal.h"

/// @brief Функция для преобразования значения переменной типа int в
/// s21_decimal.
/// @param src целочисленная переменная с типом int.
/// @param dst указатель на переменную с типом данных s21_decimal.
/// @return Возвращаемое значение - код ошибки: 0 - OK, 1 - ошибка конвертации.
int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int error = 0;
  if (dst) {
    make_zero(dst);
    dst->bits[0] = src < 0 ? -src : src;
    set_bit(127, src < 0 ? 1 : 0, dst);
  } else {
    error = 1;
  }
  return error;
}
