#include "s21_decimal.h"

/// @brief Функция для преобразования значения переменной типа s21_decimal в
/// float.
/// @param src переменная с типом s21_decimal.
/// @param dst указатель на переменную с типом данных float.
/// @return Возвращаемое значение - код ошибки: 0 - OK, 1 - ошибка конвертации.
int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int error = 0;
  char str[32] = {0};
  if (!s21_decimal_print(src, str) && dst) {
    *dst = (float)atof(str);
  } else {
    error = 1;
  }
  return error;
}
