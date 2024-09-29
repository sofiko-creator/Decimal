#include "s21_decimal_test.h"

#define SIZE_OF_DECIMAL 3

void run_add_test(s21_decimal decimal_a, s21_decimal decimal_b,
                  int correct_answer, s21_decimal *result) {
  int tested_value = s21_add(decimal_a, decimal_b, &(*result));
  ck_assert_msg(tested_value == correct_answer,
                "FALSE: correct is '%d', but given is '%d'."
                "decimal_a is '%c%u:%u:%u:%u'. decimal_b is '%c%u:%u:%u:%u'",
                correct_answer, tested_value,
                get_bit(127, decimal_a) == 0 ? '+' : '-', get_scale(decimal_a),
                decimal_a.bits[2], decimal_a.bits[1], decimal_a.bits[0],
                get_bit(127, decimal_b) == 0 ? '+' : '-', get_scale(decimal_b),
                decimal_b.bits[2], decimal_b.bits[1], decimal_b.bits[0]);
}

START_TEST(test_suite_1_simple_level) {
  s21_decimal a, b;
  make_zero(&a);
  make_zero(&b);
  // 100101010010011001001000101010010110010101010101010010101010110101001101001010101
  // == 1408677636099673788422741
  a.bits[0] = 0b10010101010110101001101001010101;
  a.bits[1] = 0b10010001010100101100101010101010;
  a.bits[2] = 0b10010101001001100;
  // 1010010100000111110100101010011001010101001010101000000110000000001111111101010
  // == 389667387897621287804906
  b.bits[0] = 0b01000000110000000001111111101010;
  b.bits[1] = 0b11101001010100110010101010010101;
  b.bits[2] = 0b101001010000011;
  s21_decimal result;
  s21_add(a, b, &result);
  // 101111100110100000111101010100101111101010011111111010110000110101011101000111111==1,798,345,023,997,295,076,227,647
  ck_assert_msg(result.bits[0] == 0b11010110000110101011101000111111 and
                    result.bits[1] == 0b01111010101001011111010100111111 and
                    result.bits[2] == 0b10111110011010000 and
                    result.bits[3] == 0,
                "Failed. '%u:%u:%u:%u'", result.bits[3], result.bits[2],
                result.bits[1], result.bits[0]);
  run_add_test(a, b, 0, &result);

  make_zero(&b);
  b.bits[0] = 1;
  s21_add(a, b, &result);
  // 100101010010011001001000101010010110010101010101010010101010110101001101001010110
  ck_assert_msg(result.bits[0] == 0b10010101010110101001101001010110 and
                    result.bits[1] == 0b10010001010100101100101010101010 and
                    result.bits[2] == 0b10010101001001100 and
                    result.bits[3] == 0 and get_bit(127, result) == 0,
                "Failed. '%u:%u:%u:%u'", result.bits[3], result.bits[2],
                result.bits[1], result.bits[0]);
  run_add_test(a, b, 0, &result);

  make_zero(&a);
  make_zero(&b);
  b.bits[0] = 1;
  a.bits[0] = 1;
  s21_add(a, b, &result);
  ck_assert_msg(result.bits[0] == 2 and result.bits[1] == 0 and
                    result.bits[2] == 0 and result.bits[3] == 0 and
                    get_bit(127, result) == 0,
                "Failed. '%u:%u:%u:%u'", result.bits[3], result.bits[2],
                result.bits[1], result.bits[0]);
  run_add_test(a, b, 0, &result);

  make_zero(&a);
  make_zero(&b);
  b.bits[0] = 1;
  a.bits[0] = 3;
  s21_add(a, b, &result);
  ck_assert_msg(result.bits[0] == 4 and result.bits[1] == 0 and
                    result.bits[2] == 0 and result.bits[3] == 0 and
                    get_bit(127, result) == 0,
                "Failed. '%u:%u:%u:%u'", result.bits[3], result.bits[2],
                result.bits[1], result.bits[0]);
  run_add_test(a, b, 0, &result);

  // -a -b = -result
  make_zero(&a);
  make_zero(&b);
  // 100101010010011001001000101010010110010101010101010010101010110101001101001010101
  // == 1408677636099673788422741
  a.bits[0] = 0b10010101010110101001101001010101;
  a.bits[1] = 0b10010001010100101100101010101010;
  a.bits[2] = 0b10010101001001100;
  // 1010010100000111110100101010011001010101001010101000000110000000001111111101010
  // == 389667387897621287804906
  b.bits[0] = 0b01000000110000000001111111101010;
  b.bits[1] = 0b11101001010100110010101010010101;
  b.bits[2] = 0b101001010000011;
  set_bit(127, 1, &a);
  set_bit(127, 1, &b);
  s21_add(a, b, &result);
  // -101111100110100000111101010100101111101010011111111010110000110101011101000111111==-1,798,345,023,997,295,076,227,647
  ck_assert_msg(result.bits[0] == 0b11010110000110101011101000111111 and
                    result.bits[1] == 0b01111010101001011111010100111111 and
                    result.bits[2] == 0b10111110011010000 and
                    get_scale(result) == 0 and get_bit(127, result) == 1,
                "Failed. '%u:%u:%u:%u'", get_scale(result), result.bits[2],
                result.bits[1], result.bits[0]);
  run_add_test(a, b, 0, &result);

  // a - b = +result
  make_zero(&a);
  make_zero(&b);
  // 100101010010011001001000101010010110010101010101010010101010110101001101001010101
  // == 1408677636099673788422741
  a.bits[0] = 0b10010101010110101001101001010101;
  a.bits[1] = 0b10010001010100101100101010101010;
  a.bits[2] = 0b10010101001001100;
  // 1010010100000111110100101010011001010101001010101000000110000000001111111101010
  // == 389667387897621287804906
  b.bits[0] = 0b01000000110000000001111111101010;
  b.bits[1] = 0b11101001010100110010101010010101;
  b.bits[2] = 0b101001010000011;
  set_bit(127, 1, &b);
  s21_add(a, b, &result);
  // 1019010248202052500617835
  //  11010111110010001010011111111111101000000001010101010100100110100111101001101011
  //  result = 1019010248202052500617835 ==
  //  11010111110010001010011111111111101000000001010101010100100110100111101001101011
  ck_assert_msg(result.bits[0] == 0b01010100100110100111101001101011 and
                    result.bits[1] == 0b10100111111111111010000000010101 and
                    result.bits[2] == 0b1101011111001000 and
                    get_scale(result) == 0 and get_bit(127, result) == 0,
                "Failed. '%c%u:%u:%u:%u'",
                get_bit(127, result) == 0 ? '+' : '-', get_scale(result),
                result.bits[2], result.bits[1], result.bits[0]);
  run_add_test(a, b, 0, &result);

  // b - a = -result
  make_zero(&a);
  make_zero(&b);
  // 100101010010011001001000101010010110010101010101010010101010110101001101001010101
  // == 1408677636099673788422741
  a.bits[0] = 0b10010101010110101001101001010101;
  a.bits[1] = 0b10010001010100101100101010101010;
  a.bits[2] = 0b10010101001001100;
  // 1010010100000111110100101010011001010101001010101000000110000000001111111101010
  // == 389667387897621287804906
  b.bits[0] = 0b01000000110000000001111111101010;
  b.bits[1] = 0b11101001010100110010101010010101;
  b.bits[2] = 0b101001010000011;
  set_bit(127, 1, &a);
  s21_add(a, b, &result);
  // result = -1019010248202052500617835 =
  // -11010111110010001010011111111111101000000001010101010100100110100111101001101011
  ck_assert_msg(result.bits[0] == 0b01010100100110100111101001101011 and
                    result.bits[1] == 0b10100111111111111010000000010101 and
                    result.bits[2] == 0b1101011111001000 and
                    get_scale(result) == 0 and get_bit(127, result) == 1,
                "Failed. '%c%u:%u:%u:%u'",
                get_bit(127, result) == 0 ? '+' : '-', get_scale(result),
                result.bits[2], result.bits[1], result.bits[0]);
  run_add_test(a, b, 0, &result);
}

START_TEST(test_suite_2_average_level) {
  s21_decimal a, b, result;
  make_zero(&a);
  make_zero(&b);
  a.bits[0] = 0b00000000000000000000000000010101;
  a.bits[1] = 0b00000000000000000000001010101001;
  a.bits[2] = 0b01010111110;
  // a(2)010101111100000000000000000000000101010100100000000000000000000000000010101
  // a(10) 12949614342668977963029

  b.bits[0] = 0b00000000000000000000011100101010;
  b.bits[2] = 0b11111100000;
  // b(2) 11111100000  00000000000000000000000000000000
  // 00000000000000000000011100101010
  //  b(10) 37188636052598456059690
  set_scale(2, &a);
  set_scale(4, &b);
  s21_add(a, b, &result);
  // a(10) 1294961434266897796302900
  // result = 1332150070319496252362590
  // 10001101000011000 00000000000000010000101000000100
  // 00000000000000000000111101011110
  ck_assert_msg(result.bits[0] == 0b00000000000000000000111101011110 and
                    result.bits[1] == 0b00000000000000010000101000000100 and
                    result.bits[2] == 0b10001101000011000 and
                    get_scale(result) == 4 and get_bit(127, result) == 0,
                "Failed. '%c%u:%u:%u:%u'",
                get_bit(127, result) == 0 ? '+' : '-', get_scale(result),
                result.bits[2], result.bits[1], result.bits[0]);
  run_add_test(a, b, 0, &result);

  make_zero(&a);
  make_zero(&b);
  a.bits[0] = 0b00000000000000000000000000010101;
  a.bits[1] = 0b00000000000000000000001010101001;
  a.bits[2] = 0b01010111110;
  // a(2)010101111100000000000000000000000101010100100000000000000000000000000010101
  // a(10) 12949614342668977963029

  b.bits[0] = 0b00000000000000000000011100101010;
  b.bits[2] = 0b11111100000;
  // b(2) 11111100000  00000000000000000000000000000000
  // 00000000000000000000011100101010
  //  b(10) 37188636052598456059690
  set_scale(29, &a);
  set_scale(28, &b);
  s21_add(a, b, &result);
  // a(10) 1294961434266897796302,9 ~ 1294961434266897796303
  // result = 38483597486865353855993
  // 100000100110 00110011001100110011001101110111
  // 01001100110011001101001111111001
  ck_assert_msg(result.bits[0] == 0b01001100110011001101001111111001 and
                    result.bits[1] == 0b00110011001100110011001101110111 and
                    result.bits[2] == 0b100000100110 and
                    get_scale(result) == 28 and get_bit(127, result) == 0,
                "Failed. '%c%u:%u:%u:%u'",
                get_bit(127, result) == 0 ? '+' : '-', get_scale(result),
                result.bits[2], result.bits[1], result.bits[0]);
  run_add_test(a, b, 0, &result);

  make_zero(&a);
  make_zero(&b);
  a.bits[0] = 0b00000000000000000000000000010101;
  a.bits[1] = 0b00000000000000000000001010101001;
  a.bits[2] = 0b01010111110;
  // a(2)010101111100000000000000000000000101010100100000000000000000000000000010101
  // a(10) 12949614342668977963029

  b.bits[0] = 0b00000000000000000000011100101010;
  b.bits[2] = 0b11111100000;
  // b(2) 11111100000  00000000000000000000000000000000
  // 00000000000000000000011100101010
  //  b(10) 37188636052598456059690
  set_scale(28, &a);
  set_scale(33, &b);
  set_bit(127, 1, &b);
  // a-b = +result
  s21_add(a, b, &result);
  // b(10) 371886360525984560,59690 ~ 371886360525984561
  // result = 12949242456308451978468
  // 1010111101 11111010110101101100110111111100
  // 01010000000010010010110011100100
  ck_assert_msg(result.bits[0] == 0b01010000000010010010110011100100 and
                    result.bits[1] == 0b11111010110101101100110111111100 and
                    result.bits[2] == 0b1010111101 and
                    get_scale(result) == 28 and get_bit(127, result) == 0,
                "Failed. '%c%u:%u:%u:%u'",
                get_bit(127, result) == 0 ? '+' : '-', get_scale(result),
                result.bits[2], result.bits[1], result.bits[0]);
  run_add_test(a, b, 0, &result);

  make_zero(&a);
  make_zero(&b);
  a.bits[0] = 0b00000000000000000000000000010101;
  a.bits[1] = 0b00000000000000000000001010101001;
  a.bits[2] = 0b01010111110;
  // a(2)010101111100000000000000000000000101010100100000000000000000000000000010101
  // a(10) 12949614342668977963029

  b.bits[0] = 0b11111111111111111110010000000010;
  b.bits[1] = 0b11111111111111111111111111111111;
  b.bits[2] = 0b11111011111;
  // b(2)
  // 111110111111111111111111111111111111111111111111111111111111110010000000010
  //  b(10) 37188636052598456050690
  set_scale(28, &a);
  set_scale(33, &b);
  set_bit(127, 1, &a);
  // b-a = -result
  s21_add(a, b, &result);
  // b(10) 371886360525984560,50690 ~ 371886360525984561
  // result = -1010111101 11111010110101101100110111111100
  // 01010000000010010010110011100100
  ck_assert_msg(result.bits[0] == 0b01010000000010010010110011100100 and
                    result.bits[1] == 0b11111010110101101100110111111100 and
                    result.bits[2] == 0b1010111101 and
                    get_scale(result) == 28 and get_bit(127, result) == 1,
                "Failed. '%c%u:%u:%u:%u'",
                get_bit(127, result) == 0 ? '+' : '-', get_scale(result),
                result.bits[2], result.bits[1], result.bits[0]);
  run_add_test(a, b, 0, &result);
}

START_TEST(test_suite_3_hard_level) {
  s21_decimal a, b, result;
  make_zero(&a);
  make_zero(&b);
  // full value + 1 (= big value)
  a.bits[0] = 0b11111111111111111111111111111111;
  a.bits[1] = 0b11111111111111111111111111111111;
  a.bits[2] = 0b11111111111111111111111111111111;
  b.bits[0] = 0b00000000000000000000000000000001;
  b.bits[1] = 0b0;
  b.bits[2] = 0b0;
  s21_add(a, b, &result);
  run_add_test(a, b, 1, &result);

  make_zero(&a);
  make_zero(&b);
  // -full value - 1 (= -big value)
  a.bits[0] = 0b11111111111111111111111111111111;
  a.bits[1] = 0b11111111111111111111111111111111;
  a.bits[2] = 0b11111111111111111111111111111111;
  b.bits[0] = 0b00000000000000000000000000000001;
  b.bits[1] = 0b0;
  b.bits[2] = 0b0;
  set_bit(127, 1, &a);
  set_bit(127, 1, &b);
  s21_add(a, b, &result);
  run_add_test(a, b, 2, &result);

  make_zero(&a);
  make_zero(&b);
  // full value with scale + 0,5
  a.bits[0] = 0b11111111111111111111111111111111;
  a.bits[1] = 0b11111111111111111111111111111111;
  a.bits[2] = 0b11111111111111111111111111111111;
  b.bits[0] = 0b00000000000000000000000000000101;
  b.bits[1] = 0b0;
  b.bits[2] = 0b0;
  set_scale(28, &a);
  set_scale(29, &b);
  s21_add(a, b, &result);

  ck_assert_msg(result.bits[0] == 0b11111111111111111111111111111111 and
                    result.bits[1] == 0b11111111111111111111111111111111 and
                    result.bits[2] == 0b11111111111111111111111111111111 and
                    get_scale(result) == 28 and get_bit(127, result) == 0,
                "Failed. '%c%u:%u:%u:%u'",
                get_bit(127, result) == 0 ? '+' : '-', get_scale(result),
                result.bits[2], result.bits[1], result.bits[0]);
  run_add_test(a, b, 0, &result);  // ??

  make_zero(&a);
  make_zero(&b);
  // full value + 5 (= big value)
  // 79,228,162,514,264,337,593,543,950,335 ->
  // 79,228,162,514,264,337,593,543,950,3350
  // 79,228,162,514,264,337,593,543,950,3355
  a.bits[0] = 0b11111111111111111111111111111111;
  a.bits[1] = 0b11111111111111111111111111111111;
  a.bits[2] = 0b11111111111111111111111111111111;
  b.bits[0] = 0b00000000000000000000000000000101;
  b.bits[1] = 0b0;
  b.bits[2] = 0b0;
  set_scale(1, &b);
  s21_add(a, b, &result);
  run_add_test(a, b, 1, &result);

  make_zero(&a);
  make_zero(&b);
  // full value + 0,7
  // 79,228,162,514,264,337,593,543,950,335 ->
  // 79,228,162,514,264,337,593,543,950,33,6 ->
  // 79,228,162,514,264,337,593,543,950,34
  // 110011001100110011001100110011001100110011001100110011001100110011001100110011001100110011010
  a.bits[0] = 0b11111111111111111111111111111111;
  a.bits[1] = 0b11111111111111111111111111111111;
  a.bits[2] = 0b11111111111111111111111111111111;
  b.bits[0] = 0b00000000000000000000000000000111;
  b.bits[1] = 0b0;
  b.bits[2] = 0b0;
  set_scale(28, &a);
  set_scale(29, &b);
  s21_add(a, b, &result);
  ck_assert_msg(result.bits[0] == 0b10011001100110011001100110011010 and
                    result.bits[1] == 0b10011001100110011001100110011001 and
                    result.bits[2] == 0b11001100110011001100110011001 and
                    get_scale(result) == 27 and get_bit(127, result) == 0,
                "Failed. '%c%u:%u:%u:%u'",
                get_bit(127, result) == 0 ? '+' : '-', get_scale(result),
                result.bits[2], result.bits[1], result.bits[0]);
  run_add_test(a, b, 0, &result);

  make_zero(&a);
  make_zero(&b);
  // -full value - 0,5
  a.bits[0] = 0b11111111111111111111111111111111;
  a.bits[1] = 0b11111111111111111111111111111111;
  a.bits[2] = 0b11111111111111111111111111111111;
  b.bits[0] = 0b00000000000000000000000000000101;
  b.bits[1] = 0b0;
  b.bits[2] = 0b0;
  set_scale(28, &a);
  set_scale(29, &b);
  set_bit(127, 1, &a);
  set_bit(127, 1, &b);
  s21_add(a, b, &result);
  ck_assert_msg(result.bits[0] == 0b11111111111111111111111111111111 and
                    result.bits[1] == 0b11111111111111111111111111111111 and
                    result.bits[2] == 0b11111111111111111111111111111111 and
                    get_scale(result) == 28 and get_bit(127, result) == 1,
                "Failed. '%c%u:%u:%u:%u'",
                get_bit(127, result) == 0 ? '+' : '-', get_scale(result),
                result.bits[2], result.bits[1], result.bits[0]);
  run_add_test(a, b, 0, &result);  //??
  make_zero(&a);
  make_zero(&b);
  // -full value - 7 (= -big value)
  a.bits[0] = 0b11111111111111111111111111111111;
  a.bits[1] = 0b11111111111111111111111111111111;
  a.bits[2] = 0b11111111111111111111111111111111;
  b.bits[0] = 0b00000000000000000000000000000111;
  b.bits[1] = 0b0;
  b.bits[2] = 0b0;
  set_scale(1, &b);
  set_bit(127, 1, &a);
  set_bit(127, 1, &b);
  s21_add(a, b, &result);
  run_add_test(a, b, 2, &result);

  // 79228162514264337593543950334 + 1 (= full value)
  make_zero(&a);
  make_zero(&b);
  a.bits[0] = 0b11111111111111111111111111111110;
  a.bits[1] = 0b11111111111111111111111111111111;
  a.bits[2] = 0b11111111111111111111111111111111;
  b.bits[0] = 0b00000000000000000000000000000001;
  b.bits[1] = 0b0;
  b.bits[2] = 0b0;
  s21_add(a, b, &result);
  ck_assert_msg(result.bits[0] == 0b11111111111111111111111111111111 and
                    result.bits[1] == 0b11111111111111111111111111111111 and
                    result.bits[2] == 0b11111111111111111111111111111111 and
                    get_scale(result) == 0 and get_bit(127, result) == 0,
                "Failed. '%c%u:%u:%u:%u'",
                get_bit(127, result) == 0 ? '+' : '-', get_scale(result),
                result.bits[2], result.bits[1], result.bits[0]);
  run_add_test(a, b, 0, &result);

  // 79228162514264337593543950334 + 0,4 (= 79228162514264337593543950334)
  make_zero(&a);
  make_zero(&b);
  a.bits[0] = 0b11111111111111111111111111111110;
  a.bits[1] = 0b11111111111111111111111111111111;
  a.bits[2] = 0b11111111111111111111111111111111;
  b.bits[0] = 0b100;
  set_scale(28, &a);
  set_scale(29, &b);
  s21_add(a, b, &result);
  ck_assert_msg(result.bits[0] == 0b11111111111111111111111111111110 and
                    result.bits[1] == 0b11111111111111111111111111111111 and
                    result.bits[2] == 0b11111111111111111111111111111111 and
                    get_scale(result) == 28 and get_bit(127, result) == 0,
                "Failed. '%c%u:%u:%u:%u'",
                get_bit(127, result) == 0 ? '+' : '-', get_scale(result),
                result.bits[2], result.bits[1], result.bits[0]);
  run_add_test(a, b, 0, &result);

  // 79228162514264337593543950334 + 0,5 (= 79228162514264337593543950334)
  make_zero(&a);
  make_zero(&b);
  a.bits[0] = 0b11111111111111111111111111111110;
  a.bits[1] = 0b11111111111111111111111111111111;
  a.bits[2] = 0b11111111111111111111111111111111;
  b.bits[0] = 0b101;
  set_scale(28, &a);
  set_scale(29, &b);
  s21_add(a, b, &result);
  ck_assert_msg(result.bits[0] == 0b11111111111111111111111111111110 and
                    result.bits[1] == 0b11111111111111111111111111111111 and
                    result.bits[2] == 0b11111111111111111111111111111111 and
                    get_scale(result) == 28 and get_bit(127, result) == 0,
                "Failed. '%c%u:%u:%u:%u'",
                get_bit(127, result) == 0 ? '+' : '-', get_scale(result),
                result.bits[2], result.bits[1], result.bits[0]);
  run_add_test(a, b, 0, &result);

  // 79228162514264337593543950334 + 0,7 (= 79228162514264337593543950335)
  make_zero(&a);
  make_zero(&b);
  a.bits[0] = 0b11111111111111111111111111111110;
  a.bits[1] = 0b11111111111111111111111111111111;
  a.bits[2] = 0b11111111111111111111111111111111;
  b.bits[0] = 0b111;
  set_scale(28, &a);
  set_scale(29, &b);
  s21_add(a, b, &result);
  ck_assert_msg(result.bits[0] == 0b11111111111111111111111111111111 and
                    result.bits[1] == 0b11111111111111111111111111111111 and
                    result.bits[2] == 0b11111111111111111111111111111111 and
                    get_scale(result) == 28 and get_bit(127, result) == 0,
                "Failed. '%c%u:%u:%u:%u'",
                get_bit(127, result) == 0 ? '+' : '-', get_scale(result),
                result.bits[2], result.bits[1], result.bits[0]);
  run_add_test(a, b, 0, &result);

  // -79228162514264337593543950334 - 0,7 (= -79228162514264337593543950335)
  make_zero(&a);
  make_zero(&b);
  a.bits[0] = 0b11111111111111111111111111111110;
  a.bits[1] = 0b11111111111111111111111111111111;
  a.bits[2] = 0b11111111111111111111111111111111;
  b.bits[0] = 0b111;
  set_scale(28, &a);
  set_scale(29, &b);
  set_bit(127, 1, &a);
  set_bit(127, 1, &b);
  s21_add(a, b, &result);
  ck_assert_msg(result.bits[0] == 0b11111111111111111111111111111111 and
                    result.bits[1] == 0b11111111111111111111111111111111 and
                    result.bits[2] == 0b11111111111111111111111111111111 and
                    get_scale(result) == 28 and get_bit(127, result) == 1,
                "Failed. '%c%u:%u:%u:%u'",
                get_bit(127, result) == 0 ? '+' : '-', get_scale(result),
                result.bits[2], result.bits[1], result.bits[0]);
  run_add_test(a, b, 0, &result);

  // full + full (= big)
  make_zero(&a);
  make_zero(&b);
  a.bits[0] = 0b11111111111111111111111111111111;
  a.bits[1] = 0b11111111111111111111111111111111;
  a.bits[2] = 0b11111111111111111111111111111111;
  b.bits[0] = 0b11111111111111111111111111111111;
  b.bits[1] = 0b11111111111111111111111111111111;
  b.bits[2] = 0b11111111111111111111111111111111;
  s21_add(a, b, &result);
  run_add_test(a, b, 1, &result);

  // -full + -full (= -big)
  make_zero(&a);
  make_zero(&b);
  a.bits[0] = 0b11111111111111111111111111111111;
  a.bits[1] = 0b11111111111111111111111111111111;
  a.bits[2] = 0b11111111111111111111111111111111;
  b.bits[0] = 0b11111111111111111111111111111111;
  b.bits[1] = 0b11111111111111111111111111111111;
  b.bits[2] = 0b11111111111111111111111111111111;
  set_bit(127, 1, &a);
  set_bit(127, 1, &b);
  s21_add(a, b, &result);
  run_add_test(a, b, 2, &result);

  // full + rand_value (= big)
  make_zero(&a);
  make_zero(&b);
  a.bits[0] = 0b11111111111111111111111111111111;
  a.bits[1] = 0b11111111111111111111111111111111;
  a.bits[2] = 0b11111111111111111111111111111111;
  b.bits[0] = 0b001111;
  b.bits[1] = 0b100111111111111111111;
  b.bits[2] = 0b110011111111111111111111;
  s21_add(a, b, &result);
  run_add_test(a, b, 1, &result);

  // -full + -rand_value (= -big)
  make_zero(&a);
  make_zero(&b);
  a.bits[0] = 0b11111111111111111111111111111111;
  a.bits[1] = 0b11111111111111111111111111111111;
  a.bits[2] = 0b11111111111111111111111111111111;
  b.bits[0] = 0b001111;
  b.bits[1] = 0b100111111111111111111;
  b.bits[2] = 0b110011111111111111111111;
  set_bit(127, 1, &a);
  set_bit(127, 1, &b);
  s21_add(a, b, &result);
  run_add_test(a, b, 2, &result);
}

START_TEST(test_with_zero) {
  s21_decimal a, b, result;
  make_zero(&a);
  make_zero(&b);
  s21_add(a, b, &result);
  ck_assert_msg(result.bits[0] == 0b0 and result.bits[1] == 0b0 and
                    result.bits[2] == 0b0 and get_scale(result) == 0 and
                    get_bit(127, result) == 0,
                "Failed. '%c%u:%u:%u:%u'",
                get_bit(127, result) == 0 ? '+' : '-', get_scale(result),
                result.bits[2], result.bits[1], result.bits[0]);
  run_add_test(a, b, 0, &result);

  set_bit(127, 1, &a);
  s21_add(a, b, &result);
  ck_assert_msg(result.bits[0] == 0b0 and result.bits[1] == 0b0 and
                    result.bits[2] == 0b0 and get_scale(result) == 0 and
                    get_bit(127, result) == 0,
                "Failed. '%c%u:%u:%u:%u'",
                get_bit(127, result) == 0 ? '+' : '-', get_scale(result),
                result.bits[2], result.bits[1], result.bits[0]);
  run_add_test(a, b, 0, &result);

  set_bit(127, 0, &a);
  set_bit(127, 1, &b);
  ck_assert_msg(result.bits[0] == 0b0 and result.bits[1] == 0b0 and
                    result.bits[2] == 0b0 and get_scale(result) == 0 and
                    get_bit(127, result) == 0,
                "Failed. '%c%u:%u:%u:%u'",
                get_bit(127, result) == 0 ? '+' : '-', get_scale(result),
                result.bits[2], result.bits[1], result.bits[0]);
  run_add_test(a, b, 0, &result);

  set_bit(127, 1, &a);
  ck_assert_msg(result.bits[0] == 0b0 and result.bits[1] == 0b0 and
                    result.bits[2] == 0b0 and get_scale(result) == 0 and
                    get_bit(127, result) == 0,
                "Failed. '%c%u:%u:%u:%u'",
                get_bit(127, result) == 0 ? '+' : '-', get_scale(result),
                result.bits[2], result.bits[1], result.bits[0]);
  run_add_test(a, b, 0, &result);

  make_zero(&a);
  make_zero(&b);
  s21_add(a, b, &result);
  set_scale(28, &a);
  set_scale(33, &b);
  ck_assert_msg(result.bits[0] == 0b0 and result.bits[1] == 0b0 and
                    result.bits[2] == 0b0 and get_scale(result) == 0 and
                    get_bit(127, result) == 0,
                "Failed. '%c%u:%u:%u:%u'",
                get_bit(127, result) == 0 ? '+' : '-', get_scale(result),
                result.bits[2], result.bits[1], result.bits[0]);
  run_add_test(a, b, 0, &result);  // ??
}

START_TEST(level_1) {
  s21_decimal val1, val2, val3, val_ans;
  int int_res;
  val1.bits[3] = 0x00000000;  // 0
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000000;
  val2.bits[3] = 0x00000000;  // 0
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000000;
  val_ans.bits[3] = 0x00000000;  // 0
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000000;
  int_res = s21_add(val1, val2, &val3);
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);
}
START_TEST(level_2) {
  s21_decimal val1, val2, val3, val_ans;
  int int_res;
  val1.bits[3] = 0x00000000;  // 0
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000000;
  val2.bits[3] = 0x00000000;  // 1
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000001;
  val_ans.bits[3] = 0x00000000;  // 1
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000001;
  int_res = s21_add(val1, val2, &val3);
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);
}
START_TEST(level_3) {
  s21_decimal val1, val2, val3, val_ans;
  int int_res;
  val1.bits[3] = 0x00000000;  // 0
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000000;
  val2.bits[3] = 0x00000000;  // 12345
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00003039;
  val_ans.bits[3] = 0x00000000;  // 12345
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00003039;
  int_res = s21_add(val1, val2, &val3);
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);
}
START_TEST(level_4) {
  s21_decimal val1, val2, val3, val_ans;
  int int_res;
  val1.bits[3] = 0x00000000;  // 0
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000000;
  val2.bits[3] = 0x80000000;  // -1
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000001;
  val_ans.bits[3] = 0x80000000;  // -1
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000001;
  int_res = s21_add(val1, val2, &val3);
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);
}
START_TEST(level_5) {
  s21_decimal val1, val2, val3, val_ans;
  int int_res;
  val1.bits[3] = 0x00000000;  // 0
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000000;
  val2.bits[3] = 0x80000000;  // -12345
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00003039;
  val_ans.bits[3] = 0x80000000;  // -12345
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00003039;
  int_res = s21_add(val1, val2, &val3);
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);
}

START_TEST(level_6) {
  s21_decimal val1, val2, val3, val_ans;
  int int_res;
  val1.bits[3] = 0x00000000;  // 0
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000000;
  val2.bits[3] = 0x00000000;  // 79228162514264337593543950335
  val2.bits[2] = 0xFFFFFFFF;
  val2.bits[1] = 0xFFFFFFFF;
  val2.bits[0] = 0xFFFFFFFF;
  val_ans.bits[3] = 0x00000000;  // 79228162514264337593543950335
  val_ans.bits[2] = 0xFFFFFFFF;
  val_ans.bits[1] = 0xFFFFFFFF;
  val_ans.bits[0] = 0xFFFFFFFF;
  int_res = s21_add(val1, val2, &val3);
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);
}

START_TEST(level_7) {
  s21_decimal val1, val2, val3, val_ans;
  int int_res;
  val1.bits[3] = 0x00000000;  // 0
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000000;
  val2.bits[3] = 0x80000000;  // -79228162514264337593543950335
  val2.bits[2] = 0xFFFFFFFF;
  val2.bits[1] = 0xFFFFFFFF;
  val2.bits[0] = 0xFFFFFFFF;
  val_ans.bits[3] = 0x80000000;  // -79228162514264337593543950335
  val_ans.bits[2] = 0xFFFFFFFF;
  val_ans.bits[1] = 0xFFFFFFFF;
  val_ans.bits[0] = 0xFFFFFFFF;
  int_res = s21_add(val1, val2, &val3);
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);
}

START_TEST(level_8) {
  s21_decimal val1, val2, val3, val_ans;
  int int_res;
  val1.bits[3] = 0x00000000;  // 1
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000001;
  val2.bits[3] = 0x00000000;  // 0
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000000;
  val_ans.bits[3] = 0x00000000;  // 1
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000001;
  int_res = s21_add(val1, val2, &val3);
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);
}

START_TEST(level_9) {
  s21_decimal val1, val2, val3, val_ans;
  int int_res;
  val1.bits[3] = 0x00000000;  // 1
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000001;
  val2.bits[3] = 0x00000000;  // 1
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000001;
  val_ans.bits[3] = 0x00000000;  // 2
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000002;
  int_res = s21_add(val1, val2, &val3);
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);
}

START_TEST(level_10) {
  s21_decimal val1, val2, val3, val_ans;
  int int_res;
  val1.bits[3] = 0x00000000;  // 1
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000001;
  val2.bits[3] = 0x00000000;  // 12345
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00003039;
  val_ans.bits[3] = 0x00000000;  // 12346
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x0000303A;
  int_res = s21_add(val1, val2, &val3);
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);
}

START_TEST(level_11) {
  s21_decimal val1, val2, val3, val_ans;
  int int_res;
  val1.bits[3] = 0x00000000;  // 1
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000001;
  val2.bits[3] = 0x80000000;  // -1
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000001;
  val_ans.bits[3] = 0x00000000;  // 0
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000000;
  int_res = s21_add(val1, val2, &val3);
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);
}

START_TEST(level_12) {
  s21_decimal val1, val2, val3, val_ans;
  int int_res;
  val1.bits[3] = 0x00000000;  // 1
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000001;
  val2.bits[3] = 0x80000000;  // -12345
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00003039;
  val_ans.bits[3] = 0x80000000;  // -12344
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00003038;
  int_res = s21_add(val1, val2, &val3);
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);
}

START_TEST(level_13) {
  s21_decimal val1, val2, val3;
  int int_res;
  val1.bits[3] = 0x00000000;  // 1
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000001;
  val2.bits[3] = 0x00000000;  // 79228162514264337593543950335
  val2.bits[2] = 0xFFFFFFFF;
  val2.bits[1] = 0xFFFFFFFF;
  val2.bits[0] = 0xFFFFFFFF;
  int_res = s21_add(val1, val2, &val3);
  ck_assert_int_eq(int_res, 1);
}

START_TEST(level_14) {
  s21_decimal val1, val2, val3, val_ans;
  int int_res;
  val1.bits[3] = 0x00000000;  // 1
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000001;
  val2.bits[3] = 0x80000000;  // -79228162514264337593543950335
  val2.bits[2] = 0xFFFFFFFF;
  val2.bits[1] = 0xFFFFFFFF;
  val2.bits[0] = 0xFFFFFFFF;
  val_ans.bits[3] = 0x80000000;  // -79228162514264337593543950334
  val_ans.bits[2] = 0xFFFFFFFF;
  val_ans.bits[1] = 0xFFFFFFFF;
  val_ans.bits[0] = 0xFFFFFFFE;
  int_res = s21_add(val1, val2, &val3);
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);
}

START_TEST(level_15) {
  s21_decimal val1, val2, val3, val_ans;
  int int_res;
  val1.bits[3] = 0x00010000;  // 0,5
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000005;
  val2.bits[3] = 0x00000000;  // 0
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000000;
  val_ans.bits[3] = 0x00010000;  // 0,5
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000005;
  int_res = s21_add(val1, val2, &val3);
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);
}

START_TEST(level_16) {
  s21_decimal val1, val2, val3, val_ans;
  int int_res;
  val1.bits[3] = 0x00010000;  // 0,5
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000005;
  val2.bits[3] = 0x00000000;  // 1
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000001;
  val_ans.bits[3] = 0x00010000;  // 1,5
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x0000000F;
  int_res = s21_add(val1, val2, &val3);
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);
}

START_TEST(level_17) {
  s21_decimal val1, val2, val3, val_ans;
  int int_res;
  val1.bits[3] = 0x00010000;  // 0,5
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000005;
  val2.bits[3] = 0x00000000;  // 12345
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00003039;
  val_ans.bits[3] = 0x00010000;  // 12345,5
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x0001E23F;
  int_res = s21_add(val1, val2, &val3);
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);
}

START_TEST(level_18) {
  s21_decimal val1, val2, val3, val_ans;
  int int_res;
  val1.bits[3] = 0x00010000;  // 0,5
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000005;
  val2.bits[3] = 0x80000000;  // -1
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000001;
  val_ans.bits[3] = 0x80010000;  // -0,5
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000005;
  int_res = s21_add(val1, val2, &val3);
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);
}

START_TEST(level_19) {
  s21_decimal val1, val2, val3, val_ans;
  int int_res;
  val1.bits[3] = 0x00010000;  // 0,5
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000005;
  val2.bits[3] = 0x80000000;  // -12345
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00003039;
  val_ans.bits[3] = 0x80010000;  // -12344,5
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x0001E235;
  int_res = s21_add(val1, val2, &val3);
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);
}

START_TEST(level_20) {
  s21_decimal val1, val2, val3;
  int int_res;
  val1.bits[3] = 0x00010000;  // 0,5
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000005;
  val2.bits[3] = 0x00000000;  // 79228162514264337593543950335
  val2.bits[2] = 0xFFFFFFFF;
  val2.bits[1] = 0xFFFFFFFF;
  val2.bits[0] = 0xFFFFFFFF;
  int_res = s21_add(val1, val2, &val3);
  ck_assert_int_eq(int_res, 1);
}

START_TEST(level_21) {
  s21_decimal val1, val2, val3, val_ans;
  int int_res;
  val1.bits[3] = 0x00010000;  // 0,5
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000005;
  val2.bits[3] = 0x80000000;  // -79228162514264337593543950335 ->
                              // -792281625142643375935439503350 ->
                              // -792281625142643375935439503345
  val2.bits[2] = 0xFFFFFFFF;
  val2.bits[1] = 0xFFFFFFFF;
  val2.bits[0] = 0xFFFFFFFF;
  val_ans.bits[3] = 0x80000000;  // -79228162514264337593543950334
  val_ans.bits[2] = 0xFFFFFFFF;
  val_ans.bits[1] = 0xFFFFFFFF;
  val_ans.bits[0] = 0xFFFFFFFE;
  int_res = s21_add(val1, val2, &val3);
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);
}

START_TEST(level_22) {
  s21_decimal val1, val2, val3, val_ans;
  int int_res;
  val1.bits[3] = 0x00090000;  // 0,000000001
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000001;
  val2.bits[3] = 0x00000000;  // 0
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000000;
  val_ans.bits[3] = 0x00090000;  // 0,000000001
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000001;
  int_res = s21_add(val1, val2, &val3);
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);
}

START_TEST(level_23) {
  s21_decimal val1, val2, val3, val_ans;
  int int_res;
  val1.bits[3] = 0x00090000;  // 0,000000001
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000001;
  val2.bits[3] = 0x00000000;  // 1
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000001;
  val_ans.bits[3] = 0x00090000;  // 1,000000001
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x3B9ACA01;
  int_res = s21_add(val1, val2, &val3);
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);
}

START_TEST(level_24) {
  s21_decimal val1, val2, val3, val_ans;
  int int_res;
  val1.bits[3] = 0x00090000;  // 0,000000001
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000001;
  val2.bits[3] = 0x00000000;  // 12345
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00003039;
  val_ans.bits[3] = 0x00090000;  // 12345,000000001
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000B3A;
  val_ans.bits[0] = 0x4B56FA01;
  int_res = s21_add(val1, val2, &val3);
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);
}

START_TEST(level_25) {
  s21_decimal val1, val2, val3, val_ans;
  int int_res;
  val1.bits[3] = 0x00090000;  // 0,000000001
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000001;
  val2.bits[3] = 0x80000000;  // -1
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000001;
  val_ans.bits[3] = 0x80090000;  // -0,999999999
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x3B9AC9FF;
  int_res = s21_add(val1, val2, &val3);
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);
}

START_TEST(level_26) {
  s21_decimal val1, val2, val3, val_ans;
  int int_res;
  val1.bits[3] = 0x00090000;  // 0,000000001
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000001;
  val2.bits[3] = 0x80000000;  // -12345
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00003039;
  val_ans.bits[3] = 0x80090000;  // -12344,999999999
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000B3A;
  val_ans.bits[0] = 0x4B56F9FF;
  int_res = s21_add(val1, val2, &val3);
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);
}

START_TEST(level_27) {
  s21_decimal val1, val2, val3, val_ans;
  int int_res;
  val1.bits[3] = 0x00090000;  // 0,000000001
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000001;
  val2.bits[3] = 0x00000000;  // 79228162514264337593543950335
  val2.bits[2] = 0xFFFFFFFF;
  val2.bits[1] = 0xFFFFFFFF;
  val2.bits[0] = 0xFFFFFFFF;
  val_ans.bits[3] = 0x00000000;  // 79228162514264337593543950335
  val_ans.bits[2] = 0xFFFFFFFF;
  val_ans.bits[1] = 0xFFFFFFFF;
  val_ans.bits[0] = 0xFFFFFFFF;
  int_res = s21_add(val1, val2, &val3);
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);
}

START_TEST(level_28) {
  s21_decimal val1, val2, val3, val_ans;
  int int_res;
  val1.bits[3] = 0x00090000;  // 0,000000001
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000001;
  val2.bits[3] = 0x80000000;  // -79228162514264337593543950335
  val2.bits[2] = 0xFFFFFFFF;
  val2.bits[1] = 0xFFFFFFFF;
  val2.bits[0] = 0xFFFFFFFF;
  val_ans.bits[3] = 0x80000000;  // -79228162514264337593543950335
  val_ans.bits[2] = 0xFFFFFFFF;
  val_ans.bits[1] = 0xFFFFFFFF;
  val_ans.bits[0] = 0xFFFFFFFF;
  int_res = s21_add(val1, val2, &val3);
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);
}

START_TEST(level_29) {
  s21_decimal val1, val2, val3, val_ans;
  int int_res;
  val1.bits[3] = 0x00000000;  // 79228162514264337593543950334
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFE;
  val2.bits[3] = 0x001B0000;  // 0,000000000000000000000000001
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000001;
  val_ans.bits[3] = 0x00000000;  // 79228162514264337593543950334
  val_ans.bits[2] = 0xFFFFFFFF;
  val_ans.bits[1] = 0xFFFFFFFF;
  val_ans.bits[0] = 0xFFFFFFFE;
  int_res = s21_add(val1, val2, &val3);
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);
}

START_TEST(level_30) {
  s21_decimal val1, val2, val3, val_ans;
  int int_res;
  val1.bits[3] = 0x00000000;  // 79228162514264337593543950334
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFE;
  val2.bits[3] = 0x001B0000;  // 0,000000000000000000000000004
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000004;
  val_ans.bits[3] = 0x00000000;  // 79228162514264337593543950334
  val_ans.bits[2] = 0xFFFFFFFF;
  val_ans.bits[1] = 0xFFFFFFFF;
  val_ans.bits[0] = 0xFFFFFFFE;
  int_res = s21_add(val1, val2, &val3);
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);
}

START_TEST(level_31) {
  s21_decimal val1, val2, val3, val_ans;
  int int_res;
  val1.bits[3] = 0x00000000;  // 79228162514264337593543950334
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFE;
  val2.bits[3] = 0x001B0000;  // 0,000000000000000000000000005
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000005;
  val_ans.bits[3] = 0x00000000;  // 79228162514264337593543950334
  val_ans.bits[2] = 0xFFFFFFFF;
  val_ans.bits[1] = 0xFFFFFFFF;
  val_ans.bits[0] = 0xFFFFFFFE;
  int_res = s21_add(val1, val2, &val3);
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);
}

START_TEST(level_32) {
  s21_decimal val1, val2, val3, val_ans;
  int int_res;
  val1.bits[3] = 0x00000000;  // 79228162514264337593543950334
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFE;
  val2.bits[3] = 0x001B0000;  // 0,000000000000000000000000006
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000006;
  val_ans.bits[3] = 0x00000000;  // 79228162514264337593543950334
  val_ans.bits[2] = 0xFFFFFFFF;
  val_ans.bits[1] = 0xFFFFFFFF;
  val_ans.bits[0] = 0xFFFFFFFE;
  int_res = s21_add(val1, val2, &val3);
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);
}

START_TEST(level_33) {
  s21_decimal val1, val2, val3, val_ans;
  int int_res;
  val1.bits[3] = 0x00000000;  // 79228162514264337593543950334
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFE;
  val2.bits[3] = 0x001B0000;  // 0,000000000000000000000000009
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000009;
  val_ans.bits[3] = 0x00000000;  // 79228162514264337593543950334
  val_ans.bits[2] = 0xFFFFFFFF;
  val_ans.bits[1] = 0xFFFFFFFF;
  val_ans.bits[0] = 0xFFFFFFFE;
  int_res = s21_add(val1, val2, &val3);
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);
}

START_TEST(level_34) {
  s21_decimal val1, val2, val3, val_ans;
  int int_res;
  val1.bits[3] = 0x00000000;  // 79228162514264337593543950334
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFE;
  val2.bits[3] = 0x001A0000;  // 0,00000000000000000000000001
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000001;
  val_ans.bits[3] = 0x00000000;  // 79228162514264337593543950334
  val_ans.bits[2] = 0xFFFFFFFF;
  val_ans.bits[1] = 0xFFFFFFFF;
  val_ans.bits[0] = 0xFFFFFFFE;
  int_res = s21_add(val1, val2, &val3);
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);
}

START_TEST(level_35) {
  s21_decimal val1, val2, val3, val_ans;
  int int_res;
  val1.bits[3] = 0x00000000;  // 79228162514264337593543950335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val2.bits[3] = 0x001B0000;  // 0,000000000000000000000000001
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000001;
  val_ans.bits[3] = 0x00000000;  // 79228162514264337593543950335
  val_ans.bits[2] = 0xFFFFFFFF;
  val_ans.bits[1] = 0xFFFFFFFF;
  val_ans.bits[0] = 0xFFFFFFFF;
  int_res = s21_add(val1, val2, &val3);
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);
}

START_TEST(level_36) {
  s21_decimal val1, val2, val3, val_ans;
  int int_res;
  val1.bits[3] = 0x00000000;  // 79228162514264337593543950335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val2.bits[3] = 0x001B0000;  // 0,000000000000000000000000004
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000004;
  val_ans.bits[3] = 0x00000000;  // 79228162514264337593543950335
  val_ans.bits[2] = 0xFFFFFFFF;
  val_ans.bits[1] = 0xFFFFFFFF;
  val_ans.bits[0] = 0xFFFFFFFF;
  int_res = s21_add(val1, val2, &val3);
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);
}

START_TEST(level_37) {
  s21_decimal val1, val2, val3, val_ans;
  int int_res;
  val1.bits[3] = 0x00000000;  // 79228162514264337593543950335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val2.bits[3] = 0x001B0000;  // 0,000000000000000000000000005
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000005;
  val_ans.bits[3] = 0x00000000;  // 79228162514264337593543950335
  val_ans.bits[2] = 0xFFFFFFFF;
  val_ans.bits[1] = 0xFFFFFFFF;
  val_ans.bits[0] = 0xFFFFFFFF;
  int_res = s21_add(val1, val2, &val3);
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);
}

START_TEST(level_38) {
  s21_decimal val1, val2, val3, val_ans;
  int int_res;
  val1.bits[3] = 0x00000000;  // 79228162514264337593543950335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val2.bits[3] = 0x001B0000;  // 0,000000000000000000000000006
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000006;
  val_ans.bits[3] = 0x00000000;  // 79228162514264337593543950335
  val_ans.bits[2] = 0xFFFFFFFF;
  val_ans.bits[1] = 0xFFFFFFFF;
  val_ans.bits[0] = 0xFFFFFFFF;
  int_res = s21_add(val1, val2, &val3);
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);
}

START_TEST(level_39) {
  s21_decimal val1, val2, val3, val_ans;
  int int_res;
  val1.bits[3] = 0x00000000;  // 79228162514264337593543950335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val2.bits[3] = 0x001B0000;  // 0,000000000000000000000000009
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000009;
  val_ans.bits[3] = 0x00000000;  // 79228162514264337593543950335
  val_ans.bits[2] = 0xFFFFFFFF;
  val_ans.bits[1] = 0xFFFFFFFF;
  val_ans.bits[0] = 0xFFFFFFFF;
  int_res = s21_add(val1, val2, &val3);
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);
}

START_TEST(level_40) {
  s21_decimal val1, val2, val3, val_ans;
  int int_res;
  val1.bits[3] = 0x00000000;  // 79228162514264337593543950335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val2.bits[3] = 0x001A0000;  // 0,00000000000000000000000001
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000001;
  val_ans.bits[3] = 0x00000000;  // 79228162514264337593543950335
  val_ans.bits[2] = 0xFFFFFFFF;
  val_ans.bits[1] = 0xFFFFFFFF;
  val_ans.bits[0] = 0xFFFFFFFF;
  int_res = s21_add(val1, val2, &val3);
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);
}

START_TEST(level_41) {
  s21_decimal val1, val2, val3, val_ans;
  int int_res;
  val1.bits[3] = 0x00000000;  // 79228162514264337593543950335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  val2.bits[3] = 0x80000000;  // -79228162514264337593543950335
  val2.bits[2] = 0xFFFFFFFF;
  val2.bits[1] = 0xFFFFFFFF;
  val2.bits[0] = 0xFFFFFFFF;
  val_ans.bits[3] = 0x00000000;  // 0
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000000;
  int_res = s21_add(val1, val2, &val3);
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);
}

START_TEST(level_42) {
  s21_decimal val1, val2, val3, val_ans;
  int int_res;
  val1.bits[3] = 0x00000000;  // 9999999999999999999999999999
  val1.bits[2] = 0x204FCE5E;
  val1.bits[1] = 0x3E250261;
  val1.bits[0] = 0x0FFFFFFF;
  val2.bits[3] = 0x00000000;  // 9999999999999999999999999999
  val2.bits[2] = 0x204FCE5E;
  val2.bits[1] = 0x3E250261;
  val2.bits[0] = 0x0FFFFFFF;
  val_ans.bits[3] = 0x00000000;  // 19999999999999999999999999998
  val_ans.bits[2] = 0x409F9CBC;
  val_ans.bits[1] = 0x7C4A04C2;
  val_ans.bits[0] = 0x1FFFFFFE;
  int_res = s21_add(val1, val2, &val3);
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);
}

START_TEST(level_43) {
  s21_decimal val1, val2, val3, val_ans;
  int int_res;
  val1.bits[3] = 0x00080000;  // 9999999,99999999
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00038D7E;
  val1.bits[0] = 0xA4C67FFF;
  val2.bits[3] = 0x00090000;  // 9999999,999999999
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x002386F2;
  val2.bits[0] = 0x6FC0FFFF;
  val_ans.bits[3] = 0x00090000;  // 19999999,999999989
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00470DE4;
  val_ans.bits[0] = 0xDF81FFF5;
  int_res = s21_add(val1, val2, &val3);
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);
}

START_TEST(level_44) {
  s21_decimal val1, val2, val3, val_ans;
  int int_res;
  val1.bits[3] = 0x00050000;  // 99999999999999999999999,99999
  val1.bits[2] = 0x204FCE5E;
  val1.bits[1] = 0x3E250261;
  val1.bits[0] = 0x0FFFFFFF;
  val2.bits[3] = 0x00170000;  // 99999,99999999999999999999999
  val2.bits[2] = 0x204FCE5E;
  val2.bits[1] = 0x3E250261;
  val2.bits[0] = 0x0FFFFFFF;
  val_ans.bits[3] = 0x00050000;  // 100000000000000000099999,99999
  val_ans.bits[2] = 0x204FCE5E;
  val_ans.bits[1] = 0x3E250263;
  val_ans.bits[0] = 0x640BE3FF;
  int_res = s21_add(val1, val2, &val3);
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);
}

START_TEST(level_45) {
  s21_decimal val1, val2, val3, val_ans;
  int int_res;
  val1.bits[3] = 0x001B0000;  // 0,000000000000000000000000001
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000001;
  val2.bits[3] = 0x001B0000;  // 0,000000000000000000000000001
  val2.bits[2] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[0] = 0x00000001;
  val_ans.bits[3] = 0x001B0000;  // 0,000000000000000000000000002
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000002;
  int_res = s21_add(val1, val2, &val3);
  ck_assert_mem_eq(&val3, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);
}

Suite *suite_s21_add(void) {
  Suite *s = suite_create("\x1b[34m[s21_add]\x1b[0m");
  TCase *tc = tcase_create("s21_add_tc");

  tcase_add_test(tc, test_suite_1_simple_level);
  tcase_add_test(tc, test_suite_2_average_level);
  tcase_add_test(tc, test_suite_3_hard_level);
  tcase_add_test(tc, test_with_zero);
  tcase_add_test(tc, level_1);
  tcase_add_test(tc, level_2);
  tcase_add_test(tc, level_3);
  tcase_add_test(tc, level_4);
  tcase_add_test(tc, level_5);
  tcase_add_test(tc, level_6);
  tcase_add_test(tc, level_7);
  tcase_add_test(tc, level_8);
  tcase_add_test(tc, level_9);
  tcase_add_test(tc, level_10);
  tcase_add_test(tc, level_11);
  tcase_add_test(tc, level_12);
  tcase_add_test(tc, level_13);
  tcase_add_test(tc, level_14);
  tcase_add_test(tc, level_15);
  tcase_add_test(tc, level_16);
  tcase_add_test(tc, level_17);
  tcase_add_test(tc, level_18);
  tcase_add_test(tc, level_19);
  tcase_add_test(tc, level_20);
  tcase_add_test(tc, level_21);
  tcase_add_test(tc, level_22);
  tcase_add_test(tc, level_23);
  tcase_add_test(tc, level_24);
  tcase_add_test(tc, level_25);
  tcase_add_test(tc, level_26);
  tcase_add_test(tc, level_27);
  tcase_add_test(tc, level_28);
  tcase_add_test(tc, level_29);
  tcase_add_test(tc, level_30);
  tcase_add_test(tc, level_31);
  tcase_add_test(tc, level_32);
  tcase_add_test(tc, level_33);
  tcase_add_test(tc, level_34);
  tcase_add_test(tc, level_35);
  tcase_add_test(tc, level_36);
  tcase_add_test(tc, level_37);
  tcase_add_test(tc, level_38);
  tcase_add_test(tc, level_39);
  tcase_add_test(tc, level_40);
  tcase_add_test(tc, level_41);
  tcase_add_test(tc, level_42);
  tcase_add_test(tc, level_43);
  tcase_add_test(tc, level_44);
  tcase_add_test(tc, level_45);
  suite_add_tcase(s, tc);

  return s;
}