#include "s21_decimal.h"

/// @brief Функция для преобразования значения переменной типа s21_decimal в
/// int.
/// @param src переменная с типом s21_decimal.
/// @param dst указатель на целочисленную переменную с типом данных int, может
/// принимать значения от -2147483648 до 2147483647.
/// @return Возвращаемое значение - код ошибки: 0 - OK, 1 - ошибка конвертации.
int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int error = 0;
  char str[32] = {0};
  if (!s21_decimal_print(src, str) && dst) {
    *dst = 0;
    long int temp = atol(str);
    if (temp <= 2147483647 && temp >= -2147483648) {
      *dst = (int)temp;
    } else {
      error = 1;
    }
  } else {
    error = 1;
  }
  return error;
}