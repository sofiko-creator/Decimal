#include "s21_decimal_test.h"

// decimal = +0
START_TEST(s21_from_decimal_to_float_01) {
  s21_decimal src_decimal = {
      .bits = {0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  float dst_float;
  float control_float = 0.f;
  int s21_error = s21_from_decimal_to_float(src_decimal, &dst_float);
  ck_assert_float_eq(control_float, dst_float);
  ck_assert_int_eq(0, s21_error);
}
END_TEST

// decimal = -0
START_TEST(s21_from_decimal_to_float_02) {
  s21_decimal src_decimal = {
      .bits = {0x00000000, 0x00000000, 0x00000000, 0x80000000}};
  float dst_float;
  float control_float = -0.f;
  int s21_error = s21_from_decimal_to_float(src_decimal, &dst_float);
  ck_assert_float_eq(control_float, dst_float);
  ck_assert_int_eq(0, s21_error);
}
END_TEST

// decimal = -321.4
START_TEST(s21_from_decimal_to_float_03) {
  s21_decimal src_decimal = {
      .bits = {0x00000C8E, 0x00000000, 0x00000000, 0x80010000}};
  float dst_float;
  float control_float = -321.4f;
  int s21_error = s21_from_decimal_to_float(src_decimal, &dst_float);
  ck_assert_float_eq(control_float, dst_float);
  ck_assert_int_eq(0, s21_error);
}
END_TEST

// decimal = 0.0000000000000000001069902512
START_TEST(s21_from_decimal_to_float_04) {
  s21_decimal src_decimal = {
      .bits = {0x3FC56AB0, 0x00000000, 0x00000000, 0x801C0000}};
  float dst_float;
  float control_float = -0.0000000000000000001069902512f;
  int s21_error = s21_from_decimal_to_float(src_decimal, &dst_float);
  ck_assert_float_eq(control_float, dst_float);
  ck_assert_int_eq(0, s21_error);
}
END_TEST

// decimal = 0.0000000000000000000000000001
START_TEST(s21_from_decimal_to_float_05) {
  s21_decimal src_decimal = {
      .bits = {0x00000001, 0x00000000, 0x00000000, 0x001C0000}};
  float dst_float;
  float control_float = 0.0000000000000000000000000001f;
  int s21_error = s21_from_decimal_to_float(src_decimal, &dst_float);
  ck_assert_float_eq(control_float, dst_float);
  ck_assert_int_eq(0, s21_error);
}
END_TEST

// decimal = 7.9228162514264337593543950335
START_TEST(s21_from_decimal_to_float_06) {
  s21_decimal src_decimal = {
      .bits = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x001C0000}};
  float dst_float;
  float control_float = 7.9228162514264337593543950335f;
  int s21_error = s21_from_decimal_to_float(src_decimal, &dst_float);
  ck_assert_float_eq(control_float, dst_float);
  ck_assert_int_eq(0, s21_error);
}
END_TEST

// decimal = 79228162514264337593543950335
START_TEST(s21_from_decimal_to_float_07) {
  s21_decimal src_decimal = {
      .bits = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}};
  float dst_float;
  float control_float = 79228162514264337593543950335.f;
  int s21_error = s21_from_decimal_to_float(src_decimal, &dst_float);
  ck_assert_float_eq(control_float, dst_float);
  ck_assert_int_eq(0, s21_error);
}
END_TEST

// decimal = 0.324524
START_TEST(s21_from_decimal_to_float_08) {
  s21_decimal src_decimal = {
      .bits = {0x0004F3AC, 0x00000000, 0x00000000, 0x00060000}};
  float dst_float;
  float control_float = 0.324524f;
  int s21_error = s21_from_decimal_to_float(src_decimal, &dst_float);
  ck_assert_float_eq(control_float, dst_float);
  ck_assert_int_eq(0, s21_error);
}
END_TEST

// decimal = 0.0000589123
START_TEST(s21_from_decimal_to_float_09) {
  s21_decimal src_decimal = {
      .bits = {0x0008FD43, 0x00000000, 0x00000000, 0x000A0000}};
  float dst_float;
  float control_float = 0.0000589123f;
  int s21_error = s21_from_decimal_to_float(src_decimal, &dst_float);
  ck_assert_float_eq(control_float, dst_float);
  ck_assert_int_eq(0, s21_error);
}
END_TEST

// decimal = 589.12355
START_TEST(s21_from_decimal_to_float_10) {
  s21_decimal src_decimal = {
      .bits = {0x0382EE63, 0x00000000, 0x00000000, 0x00050000}};
  float dst_float;
  float control_float = 589.12355;
  int s21_error = s21_from_decimal_to_float(src_decimal, &dst_float);
  ck_assert_float_eq(control_float, dst_float);
  ck_assert_int_eq(0, s21_error);
}
END_TEST

// decimal = 589.12355
START_TEST(s21_from_decimal_to_float_11) {
  s21_decimal src_decimal = {
      .bits = {0x0382EE63, 0x00000000, 0x00000000, 0x00050000}};
  int s21_error = s21_from_decimal_to_float(src_decimal, NULL);
  ck_assert_int_eq(1, s21_error);
}
END_TEST

// other_test
START_TEST(s21_from_decimal_to_float_12) {
  s21_decimal val1 = {{0}};
  int int_res;
  float float_ans;
  val1.bits[3] = 0x00000000;  // 0
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000000;
  int_res = s21_from_decimal_to_float(val1, &float_ans);
  ck_assert_float_eq(float_ans, (float)0.000000000e+000);
  ck_assert_int_eq(int_res, 0);

  // #test test_from_decimal_to_float1
  val1.bits[3] = 0x00000000;  // 0
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000000;
  int_res = s21_from_decimal_to_float(val1, &float_ans);
  ck_assert_float_eq(float_ans, (float)0.000000000e+000);
  ck_assert_int_eq(int_res, 0);

  // #test test_from_decimal_to_float2
  val1.bits[3] = 0x00000000;  // 1
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000001;
  int_res = s21_from_decimal_to_float(val1, &float_ans);
  ck_assert_float_eq(float_ans, (float)1.000000000e+000);
  ck_assert_int_eq(int_res, 0);

  // #test test_from_decimal_to_float3
  val1.bits[3] = 0x80000000;  //-1
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000001;
  int_res = s21_from_decimal_to_float(val1, &float_ans);
  ck_assert_float_eq(float_ans, (float)-1.000000000e+000);
  ck_assert_int_eq(int_res, 0);

  // #test test_from_decimal_to_float4
  val1.bits[3] = 0x00000000;  // 999
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x000003E7;
  int_res = s21_from_decimal_to_float(val1, &float_ans);
  ck_assert_float_eq(float_ans, (float)9.990000000e+002);
  ck_assert_int_eq(int_res, 0);

  // #test test_from_decimal_to_float5
  val1.bits[3] = 0x80000000;  //-999
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x000003E7;
  int_res = s21_from_decimal_to_float(val1, &float_ans);
  ck_assert_float_eq(float_ans, (float)-9.990000000e+002);
  ck_assert_int_eq(int_res, 0);

  // #test test_from_decimal_to_float6
  val1.bits[3] = 0x00000000;  // 99999999
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x05F5E0FF;
  int_res = s21_from_decimal_to_float(val1, &float_ans);
  ck_assert_float_eq(float_ans, (float)1.000000000e+008);
  ck_assert_int_eq(int_res, 0);

  // #test test_from_decimal_to_float7
  val1.bits[3] = 0x80000000;  //-99999999
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x05F5E0FF;
  int_res = s21_from_decimal_to_float(val1, &float_ans);
  ck_assert_float_eq(float_ans, (float)-1.000000000e+008);
  ck_assert_int_eq(int_res, 0);

  // #test test_from_decimal_to_float8
  val1.bits[3] = 0x00030000;  // 99999.999
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x05F5E0FF;
  int_res = s21_from_decimal_to_float(val1, &float_ans);
  ck_assert_float_eq(float_ans, (float)1.000000000e+005);
  ck_assert_int_eq(int_res, 0);

  // #test test_from_decimal_to_float9
  val1.bits[3] = 0x80070000;  //-9.9999999
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x05F5E0FF;
  int_res = s21_from_decimal_to_float(val1, &float_ans);
  ck_assert_float_eq(float_ans, (float)-1.000000000e+001);
  ck_assert_int_eq(int_res, 0);

  // #test test_from_decimal_to_float10
  val1.bits[3] = 0x00000000;  // 79228162514264337593543950335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  int_res = s21_from_decimal_to_float(val1, &float_ans);
  ck_assert_float_eq(float_ans, (float)7.922816251e+028);
  ck_assert_int_eq(int_res, 0);

  // #test test_from_decimal_to_float11
  val1.bits[3] = 0x80000000;  //-79228162514264337593543950335
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[0] = 0xFFFFFFFF;
  int_res = s21_from_decimal_to_float(val1, &float_ans);
  ck_assert_float_eq(float_ans, (float)-7.922816251e+028);
  ck_assert_int_eq(int_res, 0);

  // #test test_from_decimal_to_float12
  val1.bits[3] = 0x00000000;  // 79228157791900000000000000000
  val1.bits[2] = 0xFFFFFF00;
  val1.bits[1] = 0x00079F1E;
  val1.bits[0] = 0x03F60000;
  int_res = s21_from_decimal_to_float(val1, &float_ans);
  ck_assert_float_eq(float_ans, (float)7.922815779e+028);
  ck_assert_int_eq(int_res, 0);

  // #test test_from_decimal_to_float13
  val1.bits[3] = 0x00000000;  // 79228157791900000000000000000
  val1.bits[2] = 0xFFFFFF00;
  val1.bits[1] = 0x00079F1E;
  val1.bits[0] = 0x03F60000;
  int_res = s21_from_decimal_to_float(val1, &float_ans);
  ck_assert_float_eq(float_ans, (float)7.922815779e+028);
  ck_assert_int_eq(int_res, 0);

  // #test test_from_decimal_to_float14
  val1.bits[3] = 0x001C0000;  // 0.0000000000000000000000000001
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000001;
  int_res = s21_from_decimal_to_float(val1, &float_ans);
  ck_assert_float_eq(float_ans, (float)1.000000003e-028);
  ck_assert_int_eq(int_res, 0);

  // #test test_from_decimal_to_float15
  val1.bits[3] = 0x801C0000;  //-0.0000000000000000000000000001
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000001;
  int_res = s21_from_decimal_to_float(val1, &float_ans);
  ck_assert_float_eq(float_ans, (float)-1.000000003e-028);
  ck_assert_int_eq(int_res, 0);

  // #test test_from_decimal_to_float16
  val1.bits[3] = 0x001C0000;  // 0.0000000000000000000000000001
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000001;
  int_res = s21_from_decimal_to_float(val1, &float_ans);
  ck_assert_float_eq(float_ans, (float)1.000000003e-028);
  ck_assert_int_eq(int_res, 0);

  // #test test_from_decimal_to_float17
  val1.bits[3] = 0x801C0000;  //-0.0000000000000000000000000001
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000001;
  int_res = s21_from_decimal_to_float(val1, &float_ans);
  ck_assert_float_eq(float_ans, (float)-1.000000003e-028);
  ck_assert_int_eq(int_res, 0);

  // #test test_from_decimal_to_float18
  val1.bits[3] = 0x001C0000;  // 0.0000000000000000000000000001
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000001;
  int_res = s21_from_decimal_to_float(val1, &float_ans);
  ck_assert_float_eq(float_ans, (float)1.000000003e-028);
  ck_assert_int_eq(int_res, 0);

  // #test test_from_decimal_to_float19
  val1.bits[3] = 0x801C0000;  //-0.0000000000000000000000000001
  val1.bits[2] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[0] = 0x00000001;
  int_res = s21_from_decimal_to_float(val1, &float_ans);
  ck_assert_float_eq(float_ans, (float)-1.000000003e-028);
  ck_assert_int_eq(int_res, 0);
}
END_TEST

Suite *test_s21_from_decimal_to_float(void) {
  Suite *s = suite_create("\x1b[34m[s21_from_decimal_to_float]\x1b[0m");
  TCase *tc = tcase_create("s21_from_decimal_to_float");
  suite_add_tcase(s, tc);
  tcase_add_test(tc, s21_from_decimal_to_float_01);
  tcase_add_test(tc, s21_from_decimal_to_float_02);
  tcase_add_test(tc, s21_from_decimal_to_float_03);
  tcase_add_test(tc, s21_from_decimal_to_float_04);
  tcase_add_test(tc, s21_from_decimal_to_float_05);
  tcase_add_test(tc, s21_from_decimal_to_float_06);
  tcase_add_test(tc, s21_from_decimal_to_float_07);
  tcase_add_test(tc, s21_from_decimal_to_float_08);
  tcase_add_test(tc, s21_from_decimal_to_float_09);
  tcase_add_test(tc, s21_from_decimal_to_float_10);
  tcase_add_test(tc, s21_from_decimal_to_float_11);
  tcase_add_test(tc, s21_from_decimal_to_float_12);
  return s;
}
