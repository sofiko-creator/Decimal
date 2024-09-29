#include "s21_decimal_test.h"

// decimal = +0
START_TEST(s21_from_decimal_to_int_01) {
  s21_decimal src_decimal = {.bits = {0x00000000, 0, 0, 0x00000000}};
  int dst_int;
  int control_int = 0;
  int s21_error = s21_from_decimal_to_int(src_decimal, &dst_int);
  ck_assert_int_eq(control_int, dst_int);
  ck_assert_int_eq(0, s21_error);
}
END_TEST

// decimal = -0
START_TEST(s21_from_decimal_to_int_02) {
  s21_decimal src_decimal = {.bits = {0x00000000, 0, 0, 0x80000000}};
  int dst_int;
  int control_int = 0;
  int s21_error = s21_from_decimal_to_int(src_decimal, &dst_int);
  ck_assert_int_eq(control_int, dst_int);
  ck_assert_int_eq(0, s21_error);
}
END_TEST

// decimal = 321.4
START_TEST(s21_from_decimal_to_int_03) {
  s21_decimal src_decimal = {.bits = {0x00000C8E, 0, 0, 0x00010000}};
  int dst_int;
  int control_int = 321;
  int s21_error = s21_from_decimal_to_int(src_decimal, &dst_int);
  ck_assert_int_eq(control_int, dst_int);
  ck_assert_int_eq(0, s21_error);
}
END_TEST

// decimal = -321.4
START_TEST(s21_from_decimal_to_int_04) {
  s21_decimal src_decimal = {.bits = {0x00000C8E, 0, 0, 0x80010000}};
  int dst_int;
  int control_int = -321;
  int s21_error = s21_from_decimal_to_int(src_decimal, &dst_int);
  ck_assert_int_eq(control_int, dst_int);
  ck_assert_int_eq(0, s21_error);
}
END_TEST

// decimal = 0.321
START_TEST(s21_from_decimal_to_int_05) {
  s21_decimal src_decimal = {.bits = {0x00000141, 0, 0, 0x00030000}};
  int dst_int;
  int control_int = 0;
  int s21_error = s21_from_decimal_to_int(src_decimal, &dst_int);
  ck_assert_int_eq(control_int, dst_int);
  ck_assert_int_eq(0, s21_error);
}
END_TEST

// decimal = -0.321
START_TEST(s21_from_decimal_to_int_06) {
  s21_decimal src_decimal = {.bits = {0x00000141, 0, 0, 0x80030000}};
  int dst_int;
  int control_int = 0;
  int s21_error = s21_from_decimal_to_int(src_decimal, &dst_int);
  ck_assert_int_eq(control_int, dst_int);
  ck_assert_int_eq(0, s21_error);
}
END_TEST

// decimal = 321.67
START_TEST(s21_from_decimal_to_int_07) {
  s21_decimal src_decimal = {.bits = {0x00007DA7, 0, 0, 0x00020000}};
  int dst_int;
  int control_int = 321;
  int s21_error = s21_from_decimal_to_int(src_decimal, &dst_int);
  ck_assert_int_eq(control_int, dst_int);
  ck_assert_int_eq(0, s21_error);
}
END_TEST

// decimal = -321.67
START_TEST(s21_from_decimal_to_int_08) {
  s21_decimal src_decimal = {.bits = {0x00007DA7, 0, 0, 0x80020000}};
  int dst_int;
  int control_int = -321;
  int s21_error = s21_from_decimal_to_int(src_decimal, &dst_int);
  ck_assert_int_eq(control_int, dst_int);
  ck_assert_int_eq(0, s21_error);
}
END_TEST

// decimal = 321
START_TEST(s21_from_decimal_to_int_09) {
  s21_decimal src_decimal = {.bits = {0x00000141, 0, 0, 0x00000000}};
  int dst_int;
  int control_int = 321;
  int s21_error = s21_from_decimal_to_int(src_decimal, &dst_int);
  ck_assert_int_eq(control_int, dst_int);
  ck_assert_int_eq(0, s21_error);
}
END_TEST

// decimal = -321
START_TEST(s21_from_decimal_to_int_10) {
  s21_decimal src_decimal = {.bits = {0x00000141, 0, 0, 0x80000000}};
  int dst_int;
  int control_int = -321;
  int s21_error = s21_from_decimal_to_int(src_decimal, &dst_int);
  ck_assert_int_eq(control_int, dst_int);
  ck_assert_int_eq(0, s21_error);
}
END_TEST

// decimal = 321.12345
START_TEST(s21_from_decimal_to_int_11) {
  s21_decimal src_decimal = {.bits = {0x01E9FED9, 0, 0, 0x00050000}};
  int dst_int;
  int control_int = 321;
  int s21_error = s21_from_decimal_to_int(src_decimal, &dst_int);
  ck_assert_int_eq(control_int, dst_int);
  ck_assert_int_eq(0, s21_error);
}
END_TEST

// decimal = -321.12345
START_TEST(s21_from_decimal_to_int_12) {
  s21_decimal src_decimal = {.bits = {0x01E9FED9, 0, 0, 0x80050000}};
  int dst_int;
  int control_int = -321;
  int s21_error = s21_from_decimal_to_int(src_decimal, &dst_int);
  ck_assert_int_eq(control_int, dst_int);
  ck_assert_int_eq(0, s21_error);
}
END_TEST

// decimal = INT_MAX
START_TEST(s21_from_decimal_to_int_13) {
  s21_decimal src_decimal = {.bits = {INT_MAX, 0, 0, 0x00000000}};
  int dst_int;
  int control_int = INT_MAX;
  int s21_error = s21_from_decimal_to_int(src_decimal, &dst_int);
  ck_assert_int_eq(control_int, dst_int);
  ck_assert_int_eq(0, s21_error);
}
END_TEST

// decimal = INT_MIN
START_TEST(s21_from_decimal_to_int_14) {
  s21_decimal src_decimal = {.bits = {2147483648U, 0, 0, 0x80000000}};
  int dst_int;
  int control_int = INT_MIN;
  int s21_error = s21_from_decimal_to_int(src_decimal, &dst_int);
  ck_assert_int_eq(control_int, dst_int);
  ck_assert_int_eq(0, s21_error);
}
END_TEST

// decimal = 0.0000000000000000000000000001
START_TEST(s21_from_decimal_to_int_15) {
  s21_decimal src_decimal = {.bits = {0x00000001, 0, 0, 0x001C0000}};
  int dst_int;
  int control_int = 0;
  int s21_error = s21_from_decimal_to_int(src_decimal, &dst_int);
  ck_assert_int_eq(control_int, dst_int);
  ck_assert_int_eq(0, s21_error);
}
END_TEST

// decimal = -0.0000000000000000000000000001
START_TEST(s21_from_decimal_to_int_16) {
  s21_decimal src_decimal = {.bits = {0x00000001, 0, 0, 0x801C0000}};
  int dst_int;
  int control_int = 0;
  int s21_error = s21_from_decimal_to_int(src_decimal, &dst_int);
  ck_assert_int_eq(control_int, dst_int);
  ck_assert_int_eq(0, s21_error);
}
END_TEST

// decimal = 7.9228162514264337593543950335
START_TEST(s21_from_decimal_to_int_17) {
  s21_decimal src_decimal = {
      .bits = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x001C0000}};
  int dst_int;
  int control_int = 7;
  int s21_error = s21_from_decimal_to_int(src_decimal, &dst_int);
  ck_assert_int_eq(control_int, dst_int);
  ck_assert_int_eq(0, s21_error);
}
END_TEST

// decimal = -7.9228162514264337593543950335
START_TEST(s21_from_decimal_to_int_18) {
  s21_decimal src_decimal = {
      .bits = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  int dst_int;
  int control_int = -7;
  int s21_error = s21_from_decimal_to_int(src_decimal, &dst_int);
  ck_assert_int_eq(control_int, dst_int);
  ck_assert_int_eq(0, s21_error);
}
END_TEST

// decimal = 4294967295
START_TEST(s21_from_decimal_to_int_19) {
  s21_decimal src_decimal = {.bits = {0xFFFFFFFF, 0, 0, 0x00000000}};
  int dst_int;  // int dst_int = 0;
  int control_int = 0;
  int s21_error = s21_from_decimal_to_int(src_decimal, &dst_int);
  ck_assert_int_eq(control_int, dst_int);
  ck_assert_int_eq(1, s21_error);
}
END_TEST

// decimal = -4294967295
START_TEST(s21_from_decimal_to_int_20) {
  s21_decimal src_decimal = {.bits = {0xFFFFFFFF, 0, 0, 0x80000000}};
  int dst_int;  // int dst_int = 0;
  int control_int = 0;
  int s21_error = s21_from_decimal_to_int(src_decimal, &dst_int);
  ck_assert_int_eq(control_int, dst_int);
  ck_assert_int_eq(1, s21_error);
}
END_TEST

// decimal = -1
START_TEST(s21_from_decimal_to_int_21) {
  s21_decimal src_decimal = {.bits = {0x00000001, 0, 0, 0x80000000}};
  int s21_error = s21_from_decimal_to_int(src_decimal, NULL);
  ck_assert_int_eq(1, s21_error);
}
END_TEST

// other_test

START_TEST(s21_from_decimal_to_int_22) {
  s21_decimal val1 = {{0}};
  int int_res, int_ans;
  // test_from_decimal_to_int0
  val1.bits[3] = 0x00000000;  // 0
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000000;
  int_res = s21_from_decimal_to_int(val1, &int_ans);
  ck_assert_int_eq(int_ans, (int)0);
  ck_assert_int_eq(int_res, 0);

  // test_from_decimal_to_int1
  val1.bits[3] = 0x00000000;  // 0
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000000;
  int_res = s21_from_decimal_to_int(val1, &int_ans);
  ck_assert_int_eq(int_ans, (int)0);
  ck_assert_int_eq(int_res, 0);

  // test_from_decimal_to_int2
  val1.bits[3] = 0x00000000;  // 1
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000001;
  int_res = s21_from_decimal_to_int(val1, &int_ans);
  ck_assert_int_eq(int_ans, (int)1);
  ck_assert_int_eq(int_res, 0);

  // test_from_decimal_to_int3
  val1.bits[3] = 0x80000000;  // -1
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000001;
  int_res = s21_from_decimal_to_int(val1, &int_ans);
  ck_assert_int_eq(int_ans, (int)-1);
  ck_assert_int_eq(int_res, 0);

  // test_from_decimal_to_int4
  val1.bits[3] = 0x00000000;  // 0,1
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000000;
  int_res = s21_from_decimal_to_int(val1, &int_ans);
  ck_assert_int_eq(int_ans, (int)0);
  ck_assert_int_eq(int_res, 0);

  // test_from_decimal_to_int5
  val1.bits[3] = 0x80000000;  // -0,1
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000000;
  int_res = s21_from_decimal_to_int(val1, &int_ans);
  ck_assert_int_eq(int_ans, (int)0);
  ck_assert_int_eq(int_res, 0);

  // test_from_decimal_to_int6
  val1.bits[3] = 0x00000000;  // 0,4
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000000;
  int_res = s21_from_decimal_to_int(val1, &int_ans);
  ck_assert_int_eq(int_ans, (int)0);
  ck_assert_int_eq(int_res, 0);

  // test_from_decimal_to_int7
  val1.bits[3] = 0x80000000;  // -0,4
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000000;
  int_res = s21_from_decimal_to_int(val1, &int_ans);
  ck_assert_int_eq(int_ans, (int)0);
  ck_assert_int_eq(int_res, 0);

  // test_from_decimal_to_int8
  val1.bits[3] = 0x00000000;  // 0,5
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000000;
  int_res = s21_from_decimal_to_int(val1, &int_ans);
  ck_assert_int_eq(int_ans, (int)0);
  ck_assert_int_eq(int_res, 0);

  // test_from_decimal_to_int9
  val1.bits[3] = 0x80000000;  // -0,5
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000000;
  int_res = s21_from_decimal_to_int(val1, &int_ans);
  ck_assert_int_eq(int_ans, (int)0);
  ck_assert_int_eq(int_res, 0);

  // test_from_decimal_to_int10
  val1.bits[3] = 0x00000000;  // 0,9999999999
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000000;
  int_res = s21_from_decimal_to_int(val1, &int_ans);
  ck_assert_int_eq(int_ans, (int)0);
  ck_assert_int_eq(int_res, 0);

  // test_from_decimal_to_int11
  val1.bits[3] = 0x80000000;  // -0,9999999999
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000000;
  int_res = s21_from_decimal_to_int(val1, &int_ans);
  ck_assert_int_eq(int_ans, (int)0);
  ck_assert_int_eq(int_res, 0);

  // test_from_decimal_to_int12
  val1.bits[3] = 0x00000000;  // 999999,999999
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x000F423F;
  int_res = s21_from_decimal_to_int(val1, &int_ans);
  ck_assert_int_eq(int_ans, (int)999999);
  ck_assert_int_eq(int_res, 0);

  // test_from_decimal_to_int13
  val1.bits[3] = 0x80000000;  // -9999999,99999999
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x0098967F;
  int_res = s21_from_decimal_to_int(val1, &int_ans);
  ck_assert_int_eq(int_ans, (int)-9999999);
  ck_assert_int_eq(int_res, 0);

  // test_from_decimal_to_int14
  val1.bits[3] = 0x00000000;  // 0,0000000000000000000000000001
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000000;
  int_res = s21_from_decimal_to_int(val1, &int_ans);
  ck_assert_int_eq(int_ans, (int)0);
  ck_assert_int_eq(int_res, 0);

  // test_from_decimal_to_int15
  val1.bits[3] = 0x80000000;  // -0,0000000000000000000000000001
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000000;
  int_res = s21_from_decimal_to_int(val1, &int_ans);
  ck_assert_int_eq(int_ans, (int)0);
  ck_assert_int_eq(int_res, 0);

  // test_from_decimal_to_int16
  val1.bits[3] = 0x00000000;  // 0,1
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000000;
  int_res = s21_from_decimal_to_int(val1, &int_ans);
  ck_assert_int_eq(int_ans, (int)0);
  ck_assert_int_eq(int_res, 0);

  // test_from_decimal_to_int17
  val1.bits[3] = 0x00000000;  // 999
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x000003E7;
  int_res = s21_from_decimal_to_int(val1, &int_ans);
  ck_assert_int_eq(int_ans, (int)999);
  ck_assert_int_eq(int_res, 0);

  // test_from_decimal_to_int18
  val1.bits[3] = 0x80000000;  // -999
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x000003E7;
  int_res = s21_from_decimal_to_int(val1, &int_ans);
  ck_assert_int_eq(int_ans, (int)-999);
  ck_assert_int_eq(int_res, 0);

  // test_from_decimal_to_int19
  val1.bits[3] = 0x00000000;  // 99999999
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x05F5E0FF;
  int_res = s21_from_decimal_to_int(val1, &int_ans);
  ck_assert_int_eq(int_ans, (int)99999999);
  ck_assert_int_eq(int_res, 0);

  // test_from_decimal_to_int20
  val1.bits[3] = 0x80000000;  // -99999999
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x05F5E0FF;
  int_res = s21_from_decimal_to_int(val1, &int_ans);
  ck_assert_int_eq(int_ans, (int)-99999999);
  ck_assert_int_eq(int_res, 0);

  // test_from_decimal_to_int21
  val1.bits[3] = 0x00000000;  // 2147483647
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x7FFFFFFF;
  int_res = s21_from_decimal_to_int(val1, &int_ans);
  ck_assert_int_eq(int_ans, (int)2147483647);
  ck_assert_int_eq(int_res, 0);

  // test_from_decimal_to_int22
  val1.bits[3] = 0x80000000;  // -2147483648
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x80000000;
  int_res = s21_from_decimal_to_int(val1, &int_ans);
  ck_assert_int_eq(int_ans, (int)-2147483648);
  ck_assert_int_eq(int_res, 0);

  // test_from_decimal_to_int23
  val1.bits[3] = 0x00000000;  // 2147483648
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x80000000;
  int_res = s21_from_decimal_to_int(val1, &int_ans);
  ck_assert_int_eq(int_ans, 0);
  ck_assert_int_eq(int_res, 1);

  // test_from_decimal_to_int24
  val1.bits[3] = 0x80000000;  // -2147483649
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x80000001;
  int_res = s21_from_decimal_to_int(val1, &int_ans);
  ck_assert_int_eq(int_ans, 0);
  ck_assert_int_eq(int_res, 1);

  // test_from_decimal_to_int25
  val1.bits[3] = 0x00000000;  // 79228162514264337593543950335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  int_res = s21_from_decimal_to_int(val1, &int_ans);
  ck_assert_int_eq(int_ans, 0);
  ck_assert_int_eq(int_res, 1);

  //_from_decimal_to_int26
  val1.bits[3] = 0x80000000;  // -79228162514264337593543950335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  int_res = s21_from_decimal_to_int(val1, &int_ans);
  ck_assert_int_eq(int_ans, 0);
  ck_assert_int_eq(int_res, 1);
}
END_TEST

Suite *test_s21_from_decimal_to_int(void) {
  Suite *s = suite_create("\x1b[34m[s21_from_decimal_to_int]\x1b[0m");
  TCase *tc = tcase_create("s21_from_decimal_to_int");
  suite_add_tcase(s, tc);
  tcase_add_test(tc, s21_from_decimal_to_int_01);
  tcase_add_test(tc, s21_from_decimal_to_int_02);
  tcase_add_test(tc, s21_from_decimal_to_int_03);
  tcase_add_test(tc, s21_from_decimal_to_int_04);
  tcase_add_test(tc, s21_from_decimal_to_int_06);
  tcase_add_test(tc, s21_from_decimal_to_int_05);
  tcase_add_test(tc, s21_from_decimal_to_int_07);
  tcase_add_test(tc, s21_from_decimal_to_int_08);
  tcase_add_test(tc, s21_from_decimal_to_int_09);
  tcase_add_test(tc, s21_from_decimal_to_int_10);
  tcase_add_test(tc, s21_from_decimal_to_int_11);
  tcase_add_test(tc, s21_from_decimal_to_int_12);
  tcase_add_test(tc, s21_from_decimal_to_int_13);
  tcase_add_test(tc, s21_from_decimal_to_int_14);
  tcase_add_test(tc, s21_from_decimal_to_int_15);
  tcase_add_test(tc, s21_from_decimal_to_int_16);
  tcase_add_test(tc, s21_from_decimal_to_int_17);
  tcase_add_test(tc, s21_from_decimal_to_int_18);
  tcase_add_test(tc, s21_from_decimal_to_int_19);
  tcase_add_test(tc, s21_from_decimal_to_int_20);
  tcase_add_test(tc, s21_from_decimal_to_int_21);
  tcase_add_test(tc, s21_from_decimal_to_int_22);
  return s;
}
