#include "s21_decimal_test.h"

// int = 0
START_TEST(s21_from_int_to_decimal_01) {
  int src_int = 0;
  s21_decimal control_decimal = {.bits = {0, 0, 0, 0x00000000}}, dst_decimal;
  int s21_error = s21_from_int_to_decimal(src_int, &dst_decimal);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(control_decimal.bits[i], dst_decimal.bits[i]);
  ck_assert_int_eq(0, s21_error);
}
END_TEST

// int = 1
START_TEST(s21_from_int_to_decimal_02) {
  int src_int = 1;
  s21_decimal control_decimal = {.bits = {1, 0, 0, 0x00000000}}, dst_decimal;
  int s21_error = s21_from_int_to_decimal(src_int, &dst_decimal);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(control_decimal.bits[i], dst_decimal.bits[i]);
  ck_assert_int_eq(0, s21_error);
}
END_TEST

// int = -1
START_TEST(s21_from_int_to_decimal_03) {
  int src_int = -1;
  s21_decimal control_decimal = {.bits = {1, 0, 0, 0x80000000}}, dst_decimal;
  int s21_error = s21_from_int_to_decimal(src_int, &dst_decimal);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(control_decimal.bits[i], dst_decimal.bits[i]);
  ck_assert_int_eq(0, s21_error);
}
END_TEST

// int == INT_MAX
START_TEST(s21_from_int_to_decimal_04) {
  int src_int = INT_MAX;
  s21_decimal control_decimal = {.bits = {INT_MAX, 0, 0, 0x00000000}},
              dst_decimal;
  int s21_error = s21_from_int_to_decimal(src_int, &dst_decimal);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(control_decimal.bits[i], dst_decimal.bits[i]);
  ck_assert_int_eq(0, s21_error);
}
END_TEST

// int == INT_MIN
START_TEST(s21_from_int_to_decimal_05) {
  int src_int = INT_MIN;
  s21_decimal control_decimal = {.bits = {2147483648U, 0, 0, 0x80000000}},
              dst_decimal;
  int s21_error = s21_from_int_to_decimal(src_int, &dst_decimal);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(control_decimal.bits[i], dst_decimal.bits[i]);
  ck_assert_int_eq(0, s21_error);
}
END_TEST

// int == -12345
START_TEST(s21_from_int_to_decimal_06) {
  int src_int = -12345;
  s21_decimal control_decimal = {.bits = {12345, 0, 0, 0x80000000}},
              dst_decimal;
  int s21_error = s21_from_int_to_decimal(src_int, &dst_decimal);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(control_decimal.bits[i], dst_decimal.bits[i]);
  ck_assert_int_eq(0, s21_error);
}
END_TEST

// int == 12345
START_TEST(s21_from_int_to_decimal_07) {
  int src_int = 12345;
  s21_decimal control_decimal = {.bits = {12345, 0, 0, 0x00000000}},
              dst_decimal;
  int s21_error = s21_from_int_to_decimal(src_int, &dst_decimal);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(control_decimal.bits[i], dst_decimal.bits[i]);
  ck_assert_int_eq(0, s21_error);
}
END_TEST

// int == -0
START_TEST(s21_from_int_to_decimal_08) {
  int src_int = -0;
  s21_decimal control_decimal = {.bits = {0, 0, 0, 0x00000000}}, dst_decimal;
  int s21_error = s21_from_int_to_decimal(src_int, &dst_decimal);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(control_decimal.bits[i], dst_decimal.bits[i]);
  ck_assert_int_eq(0, s21_error);
}
END_TEST

// int == 32167
START_TEST(s21_from_int_to_decimal_09) {
  int src_int = 32167;
  s21_decimal control_decimal = {.bits = {32167, 0, 0, 0x00000000}},
              dst_decimal;
  int s21_error = s21_from_int_to_decimal(src_int, &dst_decimal);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(control_decimal.bits[i], dst_decimal.bits[i]);
  ck_assert_int_eq(0, s21_error);
}
END_TEST

// int == -32167
START_TEST(s21_from_int_to_decimal_10) {
  int src_int = -32167;
  s21_decimal control_decimal = {.bits = {32167, 0, 0, 0x80000000}},
              dst_decimal;
  int s21_error = s21_from_int_to_decimal(src_int, &dst_decimal);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(control_decimal.bits[i], dst_decimal.bits[i]);
  ck_assert_int_eq(0, s21_error);
}
END_TEST

// int == -43543
START_TEST(s21_from_int_to_decimal_11) {
  int src_int = -43543;
  s21_decimal control_decimal = {.bits = {43543, 0, 0, 0x80000000}},
              dst_decimal;
  int s21_error = s21_from_int_to_decimal(src_int, &dst_decimal);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(control_decimal.bits[i], dst_decimal.bits[i]);
  ck_assert_int_eq(0, s21_error);
}
END_TEST

// int == 43543
START_TEST(s21_from_int_to_decimal_12) {
  int src_int = 43543;
  s21_decimal control_decimal = {.bits = {43543, 0, 0, 0x00000000}},
              dst_decimal;
  int s21_error = s21_from_int_to_decimal(src_int, &dst_decimal);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(control_decimal.bits[i], dst_decimal.bits[i]);
  ck_assert_int_eq(0, s21_error);
}
END_TEST

// int == -32767
START_TEST(s21_from_int_to_decimal_13) {
  int src_int = -32767;
  s21_decimal control_decimal = {.bits = {32767, 0, 0, 0x80000000}},
              dst_decimal;
  int s21_error = s21_from_int_to_decimal(src_int, &dst_decimal);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(control_decimal.bits[i], dst_decimal.bits[i]);
  ck_assert_int_eq(0, s21_error);
}
END_TEST

// int == 32767
START_TEST(s21_from_int_to_decimal_14) {
  int src_int = 32767;
  s21_decimal control_decimal = {.bits = {32767, 0, 0, 0x00000000}},
              dst_decimal;
  int s21_error = s21_from_int_to_decimal(src_int, &dst_decimal);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(control_decimal.bits[i], dst_decimal.bits[i]);
  ck_assert_int_eq(0, s21_error);
}
END_TEST

// int == -123456
START_TEST(s21_from_int_to_decimal_15) {
  int src_int = -123456;
  s21_decimal control_decimal = {.bits = {123456, 0, 0, 0x80000000}},
              dst_decimal;
  int s21_error = s21_from_int_to_decimal(src_int, &dst_decimal);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(control_decimal.bits[i], dst_decimal.bits[i]);
  ck_assert_int_eq(0, s21_error);
}
END_TEST

// int == 123456
START_TEST(s21_from_int_to_decimal_16) {
  int src_int = 123456;
  s21_decimal control_decimal = {.bits = {123456, 0, 0, 0x00000000}},
              dst_decimal;
  int s21_error = s21_from_int_to_decimal(src_int, &dst_decimal);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(control_decimal.bits[i], dst_decimal.bits[i]);
  ck_assert_int_eq(0, s21_error);
}
END_TEST

// int == -320167
START_TEST(s21_from_int_to_decimal_17) {
  int src_int = -320167;
  s21_decimal control_decimal = {.bits = {320167, 0, 0, 0x80000000}},
              dst_decimal;
  int s21_error = s21_from_int_to_decimal(src_int, &dst_decimal);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(control_decimal.bits[i], dst_decimal.bits[i]);
  ck_assert_int_eq(0, s21_error);
}
END_TEST

// int == 320167
START_TEST(s21_from_int_to_decimal_18) {
  int src_int = 320167;
  s21_decimal control_decimal = {.bits = {320167, 0, 0, 0x00000000}},
              dst_decimal;
  int s21_error = s21_from_int_to_decimal(src_int, &dst_decimal);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(control_decimal.bits[i], dst_decimal.bits[i]);
  ck_assert_int_eq(0, s21_error);
}
END_TEST

// int == -1234567890
START_TEST(s21_from_int_to_decimal_19) {
  int src_int = -1234567890;
  s21_decimal control_decimal = {.bits = {1234567890, 0, 0, 0x80000000}},
              dst_decimal;
  int s21_error = s21_from_int_to_decimal(src_int, &dst_decimal);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(control_decimal.bits[i], dst_decimal.bits[i]);
  ck_assert_int_eq(0, s21_error);
}
END_TEST

// int == 1234567890
START_TEST(s21_from_int_to_decimal_20) {
  int src_int = 1234567890;
  s21_decimal control_decimal = {.bits = {1234567890, 0, 0, 0x00000000}},
              dst_decimal;
  int s21_error = s21_from_int_to_decimal(src_int, &dst_decimal);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(control_decimal.bits[i], dst_decimal.bits[i]);
  ck_assert_int_eq(0, s21_error);
}
END_TEST

// int == 1234567890
START_TEST(s21_from_int_to_decimal_21) {
  int src_int = 1234567890;
  int s21_error = s21_from_int_to_decimal(src_int, NULL);
  ck_assert_int_eq(1, s21_error);
}
END_TEST

// other_tests
START_TEST(s21_from_int_to_decimal_22) {
  s21_decimal val1 = {{0}};
  s21_decimal val_ans = {{0}};
  int SIZE_OF_DECIMAL = 4;
  int int_res = 0;
  // #test test_from_int_to_decimal
  val_ans.bits[3] = 0x00000000;
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000000;
  int_res = s21_from_int_to_decimal((int)0, &val1);
  ck_assert_mem_eq(&val1, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  val_ans.bits[3] = 0x00000000;
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000000;
  int_res = s21_from_int_to_decimal((int)0, &val1);
  ck_assert_mem_eq(&val1, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  val_ans.bits[3] = 0x00000000;
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000001;
  int_res = s21_from_int_to_decimal((int)1, &val1);
  ck_assert_mem_eq(&val1, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  val_ans.bits[3] = 0x80000000;
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x00000001;
  int_res = s21_from_int_to_decimal((int)-1, &val1);
  ck_assert_mem_eq(&val1, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  val_ans.bits[3] = 0x00000000;
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x000003E7;
  int_res = s21_from_int_to_decimal((int)999, &val1);
  ck_assert_mem_eq(&val1, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  val_ans.bits[3] = 0x80000000;
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x000003E7;
  int_res = s21_from_int_to_decimal((int)-999, &val1);
  ck_assert_mem_eq(&val1, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  val_ans.bits[3] = 0x00000000;
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x05F5E0FF;
  int_res = s21_from_int_to_decimal((int)99999999, &val1);
  ck_assert_mem_eq(&val1, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  val_ans.bits[3] = 0x80000000;
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x05F5E0FF;
  int_res = s21_from_int_to_decimal((int)-99999999, &val1);
  ck_assert_mem_eq(&val1, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  val_ans.bits[3] = 0x00000000;
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x7FFFFFFF;
  int_res = s21_from_int_to_decimal((int)2147483647, &val1);
  ck_assert_mem_eq(&val1, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);

  val_ans.bits[3] = 0x80000000;
  val_ans.bits[2] = 0x00000000;
  val_ans.bits[1] = 0x00000000;
  val_ans.bits[0] = 0x80000000;
  int_res = s21_from_int_to_decimal((int)-2147483648, &val1);
  ck_assert_mem_eq(&val1, &val_ans, SIZE_OF_DECIMAL);
  ck_assert_int_eq(int_res, 0);
}
END_TEST

Suite *test_s21_from_int_to_decimal(void) {
  Suite *s = suite_create("\x1b[34m[s21_s21_from_int_to_decimal]\x1b[0m");
  TCase *tc = tcase_create("s21_s21_from_int_to_decimal");
  suite_add_tcase(s, tc);

  tcase_add_test(tc, s21_from_int_to_decimal_01);
  tcase_add_test(tc, s21_from_int_to_decimal_02);
  tcase_add_test(tc, s21_from_int_to_decimal_03);
  tcase_add_test(tc, s21_from_int_to_decimal_04);
  tcase_add_test(tc, s21_from_int_to_decimal_05);
  tcase_add_test(tc, s21_from_int_to_decimal_06);
  tcase_add_test(tc, s21_from_int_to_decimal_07);
  tcase_add_test(tc, s21_from_int_to_decimal_08);
  tcase_add_test(tc, s21_from_int_to_decimal_09);
  tcase_add_test(tc, s21_from_int_to_decimal_10);
  tcase_add_test(tc, s21_from_int_to_decimal_11);
  tcase_add_test(tc, s21_from_int_to_decimal_12);
  tcase_add_test(tc, s21_from_int_to_decimal_13);
  tcase_add_test(tc, s21_from_int_to_decimal_14);
  tcase_add_test(tc, s21_from_int_to_decimal_15);
  tcase_add_test(tc, s21_from_int_to_decimal_16);
  tcase_add_test(tc, s21_from_int_to_decimal_17);
  tcase_add_test(tc, s21_from_int_to_decimal_18);
  tcase_add_test(tc, s21_from_int_to_decimal_19);
  tcase_add_test(tc, s21_from_int_to_decimal_20);
  tcase_add_test(tc, s21_from_int_to_decimal_21);
  tcase_add_test(tc, s21_from_int_to_decimal_22);
  return s;
}
