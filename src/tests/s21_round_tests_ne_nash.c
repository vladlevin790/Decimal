// #include <check.h>
// // #include <limits.h>

// #include "../s21_decimal.h"
// #include "../decimal_helper/s21_decimal_helper.h"

// #define CALCULATION_ERROR 1

// START_TEST(s21_round_to_1) {
//   s21_decimal dec = {{14500, 0, 0, 0}};
//   set_decimal_exponent(&dec, 4);
//   s21_decimal dec_res = get_new_decimal();
//   // 1.45 -> 1
//   int res = s21_round(dec, &dec_res);
//     print_m_decimal(dec_res);
//   ck_assert(res == S21_DECIMAL_OK && s21_is_equal());
// }
// END_TEST

// START_TEST(s21_round_to_2) {
//   s21_decimal dec = {{18, 0, 0, 0}};
//   set_decimal_exponent(&dec, 1);
//   s21_decimal dec_res;
//   // 1.8 -> 2
//   int res = s21_round(dec, &dec_res);

//   ck_assert(res == S21_DECIMAL_OK && dec_res.bits[0] == 2 && dec_res.bits[1] == 0 &&
//             dec_res.bits[2] == 0 && dec_res.bits[3] == 0);
// }
// END_TEST

// START_TEST(s21_round_to_minus_2) {
//   s21_decimal dec = {{18, 0, 0, 0x80000000}};
//   set_decimal_exponent(&dec, 1);
//   s21_decimal dec_res;
//   // -1.8 -> -2
//   int res = s21_round(dec, &dec_res);

//   ck_assert(res == S21_DECIMAL_OK && dec_res.bits[0] == 2 && dec_res.bits[1] == 0 &&
//             dec_res.bits[2] == 0 && (unsigned int)dec_res.bits[3] == 0x80000000);
// }
// END_TEST

// START_TEST(s21_round_zero_to_zero) {
//   s21_decimal dec = {{0, 0, 0, 0}};
//   s21_decimal dec_res;
//   // 0 -> 0
//   int res = s21_round(dec, &dec_res);

//   ck_assert(res == S21_DECIMAL_OK && dec_res.bits[0] == 0 && dec_res.bits[1] == 0 &&
//             dec_res.bits[2] == 0 && dec_res.bits[3] == 0);
// }
// END_TEST

// START_TEST(s21_round_099999999999999999999_to_1) {
//   s21_decimal dec = {{0x630FFFFF, 0x6BC75E2D, 0x5, 0x140000}};
//   s21_decimal dec_res;
//   // 0.99999999999999999999 -> 1
//   int res = s21_round(dec, &dec_res);

//   ck_assert(res == S21_DECIMAL_OK && dec_res.bits[0] == 1 && dec_res.bits[1] == 0 &&
//             dec_res.bits[2] == 0 && dec_res.bits[3] == 0);
// }
// END_TEST

// START_TEST(s21_round_minus_099999999999999999999_to_minus_1) {
//   s21_decimal dec = {{0x630FFFFF, 0x6BC75E2D, 0x5, 0x80140000}};
//   s21_decimal dec_res;
//   // -0.99999999999999999999 -> -1
//   int res = s21_round(dec, &dec_res);

//   ck_assert(res == S21_DECIMAL_OK && dec_res.bits[0] == 1 && dec_res.bits[1] == 0 &&
//             dec_res.bits[2] == 0 && (unsigned int)dec_res.bits[3] == 0x80000000);
// }
// END_TEST

// START_TEST(s21_round_09_to_1) {
//   s21_decimal dec = {{9, 0, 0, 0}};
//   set_decimal_exponent(&dec, 1);
//   s21_decimal dec_res;
//   // 0.9 -> 1
//   int res = s21_round(dec, &dec_res);

//   ck_assert(res == S21_DECIMAL_OK && dec_res.bits[0] == 1 && dec_res.bits[1] == 0 &&
//             dec_res.bits[2] == 0 && dec_res.bits[3] == 0);
// }
// END_TEST

// START_TEST(s21_round_minus_09_to_minus_1) {
//   s21_decimal dec = {{9, 0, 0, 0x80000000}};
//   set_decimal_exponent(&dec, 1);
//   s21_decimal dec_res;
//   // -0.9 -> -1
//   int res = s21_round(dec, &dec_res);

//   ck_assert(res == S21_DECIMAL_OK && dec_res.bits[0] == 1 && dec_res.bits[1] == 0 &&
//             dec_res.bits[2] == 0 && (unsigned int)dec_res.bits[3] == 0x80000000);
// }
// END_TEST

// START_TEST(s21_round_minus_05_to_minus_0) {
//   s21_decimal dec = {{0x5, 0x0, 0x0, 0x80010000}};
//   s21_decimal dec_res;
//   // -0.5 -> -0
//   int res = s21_round(dec, &dec_res);

//   ck_assert(res == S21_DECIMAL_OK && dec_res.bits[0] == 0 && dec_res.bits[1] == 0 &&
//             dec_res.bits[2] == 0 && (unsigned int)dec_res.bits[3] == 0x80000000);
// }
// END_TEST

// START_TEST(s21_round_minus_1_5_to_minus_2) {
//   s21_decimal dec = {{15, 0, 0, 2147549184}};
//   s21_decimal dec_res;
//   // -1.5 -> -2
//   int res = s21_round(dec, &dec_res);

//   ck_assert(res == S21_DECIMAL_OK && dec_res.bits[0] == 2 && dec_res.bits[1] == 0 &&
//             dec_res.bits[2] == 0 && dec_res.bits[3] == 2147483648);
// }
// END_TEST

// START_TEST(s21_round_minus_051_to_minus_1) {
//   s21_decimal dec = {{51, 0, 0, 2147614720}};
//   s21_decimal dec_res;
//   // -0.51 -> -1
//   int res = s21_round(dec, &dec_res);

//   ck_assert(res == S21_DECIMAL_OK && dec_res.bits[0] == 1 && dec_res.bits[1] == 0 &&
//             dec_res.bits[2] == 0 && dec_res.bits[3] == 2147483648);
// }
// END_TEST

// START_TEST(s21_round_049_to_0) {
//   s21_decimal dec = {{49, 0, 0, 131072}};
//   s21_decimal dec_res;
//   // 0.49 -> 0
//   int res = s21_round(dec, &dec_res);

//   ck_assert(res == S21_DECIMAL_OK && dec_res.bits[0] == 0 && dec_res.bits[1] == 0 &&
//             dec_res.bits[2] == 0 && dec_res.bits[3] == 0);
// }
// END_TEST

// START_TEST(s21_round_minus_049_to_minus_0) {
//   s21_decimal dec = {{0x31, 0x0, 0x0, 0x80020000}};
//   s21_decimal dec_res;
//   // -0.49 -> -0
//   int res = s21_round(dec, &dec_res);

//   ck_assert(res == S21_DECIMAL_OK && dec_res.bits[0] == 0 && dec_res.bits[1] == 0 &&
//             dec_res.bits[2] == 0 && (unsigned int)dec_res.bits[3] == 0x80000000);
// }
// END_TEST

// START_TEST(s21_round_051_to_1) {
//   s21_decimal dec = {{51, 0, 0, 131072}};
//   s21_decimal dec_res;
//   // 0.51 -> 1
//   int res = s21_round(dec, &dec_res);

//   ck_assert(res == S21_DECIMAL_OK && dec_res.bits[0] == 1 && dec_res.bits[1] == 0 &&
//             dec_res.bits[2] == 0 && dec_res.bits[3] == 0);
// }
// END_TEST

// START_TEST(s21_round_050_to_0) {
//   s21_decimal dec = {{0x32, 0x0, 0x0, 0x20000}};
//   s21_decimal dec_res;
//   // 0.50 -> 0
//   int res = s21_round(dec, &dec_res);

//   ck_assert(res == S21_DECIMAL_OK && dec_res.bits[0] == 0 && dec_res.bits[1] == 0 &&
//             dec_res.bits[2] == 0 && dec_res.bits[3] == 0);
// }
// END_TEST

// START_TEST(s21_round_1_low_to_1) {
//   s21_decimal dec = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x1C0000}};
//   s21_decimal dec_res;
//   // 1.0000000000000000000000000001 -> 1
//   int res = s21_round(dec, &dec_res);

//   ck_assert(res == S21_DECIMAL_OK && dec_res.bits[0] == 1 && dec_res.bits[1] == 0 &&
//             dec_res.bits[2] == 0 && dec_res.bits[3] == 0);
// }
// END_TEST

// START_TEST(s21_round_pos_to_zero) {
//   s21_decimal dec = {{0x1, 0x0, 0x0, 0xD0000}};
//   s21_decimal dec_res;
//   // 0.0000000000001 -> 0
//   int res = s21_round(dec, &dec_res);

//   ck_assert(res == S21_DECIMAL_OK && dec_res.bits[0] == 0 && dec_res.bits[1] == 0 &&
//             dec_res.bits[2] == 0 && dec_res.bits[3] == 0);
// }
// END_TEST

// START_TEST(s21_round_neg_to_zero) {
//   s21_decimal dec = {{0x1, 0x0, 0x0, 0x800E0000}};
//   s21_decimal dec_res;
//   // -0.00000000000001 -> -0
//   int res = s21_round(dec, &dec_res);

//   ck_assert(res == S21_DECIMAL_OK && dec_res.bits[0] == 0 && dec_res.bits[1] == 0 &&
//             dec_res.bits[2] == 0 && (unsigned int)dec_res.bits[3] == 0x80000000);
// }
// END_TEST

// START_TEST(s21_round_0_max_to_8) {
//   s21_decimal dec = {{4294967295, 4294967295, 4294967295, 1835008}};
//   s21_decimal dec_res;
//   // 7.9228162514264337593543950335 -> 8
//   int res = s21_round(dec, &dec_res);

//   ck_assert(res == S21_DECIMAL_OK && dec_res.bits[0] == 8 && dec_res.bits[1] == 0 &&
//             dec_res.bits[2] == 0 && dec_res.bits[3] == 0);
// }
// END_TEST

// START_TEST(s21_round_max_to_max) {
//   s21_decimal dec = {{0xffffffff, 0xffffffff, 0xffffffff, 0x0}};
//   s21_decimal dec_res;
//   // 79228162514264337593543950335
//   int res = s21_round(dec, &dec_res);

//   ck_assert(res == S21_DECIMAL_OK && (unsigned int)dec_res.bits[0] == 0xffffffff &&
//             (unsigned int)dec_res.bits[1] == 0xffffffff && (unsigned int)dec_res.bits[2] == 0xffffffff &&
//             dec_res.bits[3] == 0);
// }
// END_TEST

// START_TEST(s21_round_42949_67295_to_42950) {
//   s21_decimal dec = {{0xFFFFFFFF, 0x0, 0x0, 0x50000}};
//   s21_decimal dec_res;
//   // 42949.67295 -> 42950
//   int res = s21_round(dec, &dec_res);

//   ck_assert(res == S21_DECIMAL_OK && dec_res.bits[0] == 0xA7C6 && dec_res.bits[1] == 0 &&
//             dec_res.bits[2] == 0 && dec_res.bits[3] == 0);
// }
// END_TEST

// START_TEST(s21_round_minus_42949_67295_to_minus_42950) {
//   s21_decimal dec = {{0xFFFFFFFF, 0x0, 0x0, 0x80050000}};
//   s21_decimal dec_res;
//   // -42949.67295 -> -42950
//   int res = s21_round(dec, &dec_res);

//   ck_assert(res == S21_DECIMAL_OK && dec_res.bits[0] == 0xA7C6 && dec_res.bits[1] == 0 &&
//             dec_res.bits[2] == 0 && (unsigned int)dec_res.bits[3] == 0x80000000);
// }
// END_TEST

// START_TEST(s21_round_1234567_1234567_to_1234567) {
//   s21_decimal dec = {{0x73593407, 0xB3A, 0x0, 0x70000}};
//   s21_decimal dec_res;
//   // 1234567.1234567 -> 1234567
//   int res = s21_round(dec, &dec_res);

//   ck_assert(res == S21_DECIMAL_OK && dec_res.bits[0] == 0x12D687 && dec_res.bits[1] == 0 &&
//             dec_res.bits[2] == 0 && dec_res.bits[3] == 0x0);
// }
// END_TEST

// START_TEST(s21_round_minus_1234567_1234567_to_minus_1234567) {
//   s21_decimal dec = {{0x73593407, 0xB3A, 0x0, 0x80070000}};
//   s21_decimal dec_res;
//   // -1234567.1234567 -> -1234567
//   int res = s21_round(dec, &dec_res);

//   ck_assert(res == S21_DECIMAL_OK && dec_res.bits[0] == 0x12D687 && dec_res.bits[1] == 0 &&
//             dec_res.bits[2] == 0 && (unsigned int)dec_res.bits[3] == 0x80000000);
// }
// END_TEST

// START_TEST(s21_round_1234567890_1234567890_to_1234567890) {
//   s21_decimal dec = {{0xEB1F0AD2, 0xAB54A98C, 0x0, 0xA0000}};
//   s21_decimal dec_res;
//   // 1234567890.1234567890 -> 1234567890
//   int res = s21_round(dec, &dec_res);

//   ck_assert(res == S21_DECIMAL_OK && dec_res.bits[0] == 0x499602D2 &&
//             dec_res.bits[1] == 0 && dec_res.bits[2] == 0 &&
//             dec_res.bits[3] == 0x0);
// }
// END_TEST

// START_TEST(s21_round_minus_1234567890_1234567890_to_minus_1234567890) {
//   s21_decimal dec = {{0xEB1F0AD2, 0xAB54A98C, 0x0, 0x800A0000}};
//   s21_decimal dec_res;
//   // -1234567890.1234567890 -> -1234567890
//   int res = s21_round(dec, &dec_res);

//   ck_assert(res == S21_DECIMAL_OK && dec_res.bits[0] == 0x499602D2 &&
//             dec_res.bits[1] == 0 && dec_res.bits[2] == 0 &&
//             (unsigned int)dec_res.bits[3] == 0x80000000);
// }
// END_TEST

// START_TEST(s21_round_1234_5_to_1234) {
//   s21_decimal dec = {{0x3039, 0x0, 0x0, 0x0}};
//   set_decimal_exponent(&dec, 1);
//   s21_decimal dec_res;
//   // 1234.5 -> 1234
//   int res = s21_round(dec, &dec_res);

//   ck_assert(res == S21_DECIMAL_OK && dec_res.bits[0] == 0x4d2 && dec_res.bits[1] == 0 &&
//             dec_res.bits[2] == 0 && dec_res.bits[3] == 0x0);
// }
// END_TEST

// START_TEST(s21_round_1234_500000001_to_1235) {
//   s21_decimal dec = {{1844386049, 287, 0, 0}};
//   set_decimal_exponent(&dec, 9);
//   s21_decimal dec_res;
//   // 1234.500000001 -> 1235
//   int res = s21_round(dec, &dec_res);

//   ck_assert(res == S21_DECIMAL_OK && dec_res.bits[0] == 1235 && dec_res.bits[1] == 0 &&
//             dec_res.bits[2] == 0 && dec_res.bits[3] == 0);
// }
// END_TEST

// START_TEST(s21_round_1235_5_to_1236) {
//   s21_decimal dec = {{0x3043, 0x0, 0x0, 0x0}};
//   set_decimal_exponent(&dec, 1);
//   s21_decimal dec_res;
//   // 1235.5 -> -1236
//   int res = s21_round(dec, &dec_res);

//   ck_assert(res == S21_DECIMAL_OK && dec_res.bits[0] == 0x4d4 && dec_res.bits[1] == 0 &&
//             dec_res.bits[2] == 0 && dec_res.bits[3] == 0x0);
// }
// END_TEST

// START_TEST(s21_round_wrong_dec) {
//   s21_decimal dec = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
//   s21_decimal dec_res;
//   int res = s21_round(dec, &dec_res);

//   ck_assert(res == CALCULATION_ERROR);
// }
// END_TEST

// START_TEST(s21_round_null_dec) {
//   s21_decimal dec = {{0xFFFFFFFF, 0x0, 0x0, 0x0}};
//   int res = s21_round(dec, NULL);

//   ck_assert(res == CALCULATION_ERROR);
// }
// END_TEST

// START_TEST(s21_round_big00_5_to_big00) {
//   s21_decimal dec = {{1431655765, 0, 1431655765, 65536}};
//   set_decimal_exponent(&dec, 1);
//   s21_decimal dec_res;
//   // 2640938749860586450804312200.5 -> 2640938749860586450804312200
//   int res = s21_round(dec, &dec_res);

//   ck_assert(res == S21_DECIMAL_OK && dec_res.bits[0] == 143165576 &&
//             dec_res.bits[1] == 2147483648 && dec_res.bits[2] == 143165576 &&
//             dec_res.bits[3] == 0);
// }
// END_TEST

// START_TEST(s21_round_big93_5_to_big94) {
//   s21_decimal dec = {{4294967295, 4294967295, 4294967295, 589824}};
//   s21_decimal dec_res;
//   // 79228162514264337593.543950335 -> 79228162514264337594
//   int res = s21_round(dec, &dec_res);

//   ck_assert(res == S21_DECIMAL_OK && dec_res.bits[0] == 3047500986 &&
//             dec_res.bits[1] == 1266874889 && dec_res.bits[2] == 4 &&
//             dec_res.bits[3] == 0);
// }
// END_TEST

// START_TEST(s21_round_0_50000000000000001) {
//   s21_decimal num_1 = {{784662529, 11641532, 0, 1114112}};
//   s21_decimal orig_res = {{1, 0, 0, 0}};
//   s21_decimal s21_res = {{0, 0, 0, 0}};
//   int return_s21 = s21_round(num_1, &s21_res);
//   ck_assert_int_eq(s21_res.bits[0], orig_res.bits[0]);
//   ck_assert_int_eq(s21_res.bits[1], orig_res.bits[1]);
//   ck_assert_int_eq(s21_res.bits[2], orig_res.bits[2]);
//   ck_assert_int_eq(s21_res.bits[3], orig_res.bits[3]);
//   ck_assert_int_eq(return_s21, 0);
// }
// END_TEST

// START_TEST(s21_round_0_50000000000000000) {
//   s21_decimal num_1 = {{784662528, 11641532, 0, 1114112}};
//   s21_decimal orig_res = {{0, 0, 0, 0}};
//   s21_decimal s21_res = {{0, 0, 0, 0}};
//   int return_s21 = s21_round(num_1, &s21_res);
//   ck_assert_int_eq(s21_res.bits[0], orig_res.bits[0]);
//   ck_assert_int_eq(s21_res.bits[1], orig_res.bits[1]);
//   ck_assert_int_eq(s21_res.bits[2], orig_res.bits[2]);
//   ck_assert_int_eq(s21_res.bits[3], orig_res.bits[3]);
//   ck_assert_int_eq(return_s21, 0);
// }
// END_TEST

// START_TEST(s21_round_0_49999999999999999) {
//   s21_decimal num_1 = {{784662527, 11641532, 0, 1114112}};
//   s21_decimal orig_res = {{0, 0, 0, 0}};
//   s21_decimal s21_res = {{0, 0, 0, 0}};
//   int return_s21 = s21_round(num_1, &s21_res);
//   ck_assert_int_eq(s21_res.bits[0], orig_res.bits[0]);
//   ck_assert_int_eq(s21_res.bits[1], orig_res.bits[1]);
//   ck_assert_int_eq(s21_res.bits[2], orig_res.bits[2]);
//   ck_assert_int_eq(s21_res.bits[3], orig_res.bits[3]);
//   ck_assert_int_eq(return_s21, 0);
// }
// END_TEST

// START_TEST(s21_round_1_49999999999999999) {
//   s21_decimal num_1 = {{2353987583, 34924596, 0, 1114112}};
//   s21_decimal orig_res = {{1, 0, 0, 0}};
//   s21_decimal s21_res = {{0, 0, 0, 0}};
//   int return_s21 = s21_round(num_1, &s21_res);
//   ck_assert_int_eq(s21_res.bits[0], orig_res.bits[0]);
//   ck_assert_int_eq(s21_res.bits[1], orig_res.bits[1]);
//   ck_assert_int_eq(s21_res.bits[2], orig_res.bits[2]);
//   ck_assert_int_eq(s21_res.bits[3], orig_res.bits[3]);
//   ck_assert_int_eq(return_s21, 0);
// }
// END_TEST

// START_TEST(s21_round_1_50000000000000000) {
//   s21_decimal num_1 = {{2353987584, 34924596, 0, 1114112}};
//   s21_decimal orig_res = {{2, 0, 0, 0}};
//   s21_decimal s21_res = {{0, 0, 0, 0}};
//   int return_s21 = s21_round(num_1, &s21_res);
//   ck_assert_int_eq(s21_res.bits[0], orig_res.bits[0]);
//   ck_assert_int_eq(s21_res.bits[1], orig_res.bits[1]);
//   ck_assert_int_eq(s21_res.bits[2], orig_res.bits[2]);
//   ck_assert_int_eq(s21_res.bits[3], orig_res.bits[3]);
//   ck_assert_int_eq(return_s21, 0);
// }
// END_TEST

// START_TEST(s21_round_1_50000000000000001) {
//   s21_decimal num_1 = {{2353987585, 34924596, 0, 1114112}};
//   s21_decimal orig_res = {{2, 0, 0, 0}};
//   s21_decimal s21_res = {{0, 0, 0, 0}};
//   int return_s21 = s21_round(num_1, &s21_res);
//   ck_assert_int_eq(s21_res.bits[0], orig_res.bits[0]);
//   ck_assert_int_eq(s21_res.bits[1], orig_res.bits[1]);
//   ck_assert_int_eq(s21_res.bits[2], orig_res.bits[2]);
//   ck_assert_int_eq(s21_res.bits[3], orig_res.bits[3]);
//   ck_assert_int_eq(return_s21, 0);
// }
// END_TEST


// TCase *s21_round_tests(void)  {
//   TCase *test_cases = tcase_create("test_cases");

//   tcase_add_test(test_cases, s21_round_to_1);
//   tcase_add_test(test_cases, s21_round_to_2);
//   tcase_add_test(test_cases, s21_round_to_minus_2);
//   tcase_add_test(test_cases, s21_round_zero_to_zero);
//   tcase_add_test(test_cases, s21_round_pos_to_zero);
//   tcase_add_test(test_cases, s21_round_neg_to_zero);
//   tcase_add_test(test_cases, s21_round_0_max_to_8);
//   tcase_add_test(test_cases, s21_round_max_to_max);
//   tcase_add_test(test_cases, s21_round_099999999999999999999_to_1);
//   tcase_add_test(test_cases, s21_round_minus_099999999999999999999_to_minus_1);
//   tcase_add_test(test_cases, s21_round_09_to_1);
//   tcase_add_test(test_cases, s21_round_minus_09_to_minus_1);
//   tcase_add_test(test_cases, s21_round_minus_049_to_minus_0);
//   tcase_add_test(test_cases, s21_round_minus_05_to_minus_0);
//   tcase_add_test(test_cases, s21_round_minus_1_5_to_minus_2);
//   tcase_add_test(test_cases, s21_round_minus_051_to_minus_1);
//   tcase_add_test(test_cases, s21_round_049_to_0);
//   tcase_add_test(test_cases, s21_round_050_to_0);
//   tcase_add_test(test_cases, s21_round_051_to_1);
//   tcase_add_test(test_cases, s21_round_1_low_to_1);
//   tcase_add_test(test_cases, s21_round_42949_67295_to_42950);
//   tcase_add_test(test_cases, s21_round_minus_42949_67295_to_minus_42950);
//   tcase_add_test(test_cases, s21_round_minus_1234567890_1234567890_to_minus_1234567890);
//   tcase_add_test(test_cases, s21_round_1234567890_1234567890_to_1234567890);
//   tcase_add_test(test_cases, s21_round_minus_1234567_1234567_to_minus_1234567);
//   tcase_add_test(test_cases, s21_round_1234567_1234567_to_1234567);
//   tcase_add_test(test_cases, s21_round_1235_5_to_1236);
//   tcase_add_test(test_cases, s21_round_1234_5_to_1234);
//   tcase_add_test(test_cases, s21_round_1234_500000001_to_1235);
//   tcase_add_test(test_cases, s21_round_wrong_dec);
//   tcase_add_test(test_cases, s21_round_null_dec);
//   tcase_add_test(test_cases, s21_round_big00_5_to_big00);
//   tcase_add_test(test_cases, s21_round_big93_5_to_big94);
//   tcase_add_test(test_cases, s21_round_0_50000000000000001);
//   tcase_add_test(test_cases, s21_round_0_50000000000000000);
//   tcase_add_test(test_cases, s21_round_0_49999999999999999);
//   tcase_add_test(test_cases, s21_round_1_49999999999999999);
//   tcase_add_test(test_cases, s21_round_1_50000000000000000);
//   tcase_add_test(test_cases, s21_round_1_50000000000000001);


//   return test_cases;
// }
