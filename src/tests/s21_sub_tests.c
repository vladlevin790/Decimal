#include <check.h>
#include <limits.h>

#include "../decimal_helper/s21_decimal_helper.h"
#include "../s21_decimal.h"
#include "helper_tests.h"

START_TEST(test_0) {
  s21_decimal num_1 = {{3, 0, 0, 0}};
  s21_decimal num_2 = {{4, 0, 0, 0}};
  s21_decimal result = {0};
  s21_decimal expected = {{1, 0, 0, -2147483648}};

  int res_code = s21_sub(num_1, num_2, &result);
  ck_assert_int_eq(res_code, 0);
  ck_assert_int_eq(result.bits[0], expected.bits[0]);
  ck_assert_int_eq(result.bits[1], expected.bits[1]);
  ck_assert_int_eq(result.bits[2], expected.bits[2]);
  ck_assert_int_eq(result.bits[3], expected.bits[3]);
}
END_TEST

START_TEST(test_1) {
  // num_1: экспонента более 28, некорректная
  // num_2: 0.001
  // result: ошибка
  s21_decimal num_1 = {{55, 0, 0, 2835008}};
  s21_decimal num_2 = {{1, 0, 0, 196608}};
  s21_decimal result = {0};

  int res_code = s21_sub(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_ERROR);
}
END_TEST

START_TEST(test_2) {
  // num_1: экспонента 29
  // num_2: 0.001
  // result: ошибка
  s21_decimal num_1 = {{55, 0, 0, 1900544}};
  s21_decimal num_2 = {{1, 0, 0, 196608}};
  s21_decimal result = {0};

  int res_code = s21_sub(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_ERROR);
}
END_TEST

START_TEST(test_3) {
  s21_decimal num_1 = {{82, 1, 0, 0}};
  s21_decimal num_2 = {{4, 0, 0, 0}};
  s21_decimal result = {0};
  s21_decimal expected = {{78, 1, 0, 0}};

  int res_code = s21_sub(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(expected, result);
}
END_TEST

START_TEST(test_4) {
  // num_1: 18446744078004518.914
  // num_2: 18446744078004518.913
  // result: 0.001

  s21_decimal num_1 = {{2, 1, 1, 196608}};
  s21_decimal num_2 = {{1, 1, 1, 196608}};
  s21_decimal result = {0};
  s21_decimal expected = {{1, 0, 0, 196608}};

  int res_code = s21_sub(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(expected, result);
}
END_TEST

START_TEST(test_5) {
  // num_1: 4294967296
  // num_2: 1
  // result: 4294967295
  s21_decimal num_1 = {{0, 1, 0, 0}};
  s21_decimal num_2 = {{1, 0, 0, 0}};
  s21_decimal result = {0};
  s21_decimal expected = {{-1, 0, 0, 0}};

  int res_code = s21_sub(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(expected, result);
}
END_TEST

START_TEST(test_6) {
  // num_1: -4294967296
  // num_2: 1
  // result: -4294967297

  s21_decimal num_1 = {{0, 1, 0, -2147483648}};
  s21_decimal num_2 = {{1, 0, 0, 0}};
  s21_decimal result = {0};
  s21_decimal expected = {{1, 1, 0, -2147483648}};

  int res_code = s21_sub(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(expected, result);
}
END_TEST

START_TEST(test_7) {
  // num_1: 18446744073709551616
  // num_2: 1
  // result: 18446744073709551615

  s21_decimal num_1 = {{0, 0, 1, 0}};
  s21_decimal num_2 = {{1, 0, 0, 0}};
  s21_decimal result = {0};
  s21_decimal expected = {{-1, -1, 0, 0}};

  int res_code = s21_sub(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(expected, result);
}
END_TEST

START_TEST(test_8) {
  // num_1: 18446744073709551.624
  // num_2: 0.00001
  // result: 18446744073709551.62399

  s21_decimal num_1 = {{8, 0, 1, 196608}};
  s21_decimal num_2 = {{1, 0, 0, 327680}};
  s21_decimal result = {0};
  s21_decimal expected = {{799, 0, 100, 327680}};

  int res_code = s21_sub(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(expected, result);
}
END_TEST

START_TEST(test_9) {
  // num_1: -18446744073709551.624
  // num_2: 0.15
  // result: -18446744073709551.774

  s21_decimal num_1 = {{8, 0, 1, -2147287040}};
  s21_decimal num_2 = {{15, 0, 0, 131072}};
  s21_decimal result = {0};
  s21_decimal expected = {{158, 0, 1, -2147287040}};

  int res_code = s21_sub(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(expected, result);
}
END_TEST

START_TEST(test_10) {
  // num_1: 79228162514264337593543950335
  // num_2: 0.4
  // result: 79228162514264337593543950335

  s21_decimal num_1 = {{-1, -1, -1, 0}};
  s21_decimal num_2 = {{4, 0, 0, 65536}};
  s21_decimal result = {0};
  s21_decimal expected = {{-1, -1, -1, 0}};

  int res_code = s21_sub(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(expected, result);
}
END_TEST

START_TEST(test_11) {
  // num_1: 79228162514264337593543950335
  // num_2: 0.5
  // result: 79228162514264337593543950334

  s21_decimal num_1 = {{-1, -1, -1, 0}};
  s21_decimal num_2 = {{5, 0, 0, 65536}};
  s21_decimal result = {0};
  s21_decimal expected = {{-2, -1, -1, 0}};

  int res_code = s21_sub(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(expected, result);
}
END_TEST

START_TEST(test_12) {
  // num_1: 18446744073709551615
  // num_2: -0.5
  // result: 18446744073709551615.5

  s21_decimal num_1 = {{-1, -1, 0, 0}};
  s21_decimal num_2 = {{5, 0, 0, -2147418112}};
  s21_decimal result = {0};
  s21_decimal expected = {{-5, -1, 9, 65536}};

  int res_code = s21_sub(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(expected, result);
}
END_TEST

START_TEST(test_13) {
  // num_1: 79228162514264337593543950335
  // num_2: -0.4
  // result: 79228162514264337593543950335

  s21_decimal num_1 = {{-1, -1, -1, 0}};
  s21_decimal num_2 = {{4, 0, 0, -2147418112}};
  s21_decimal result = {0};
  s21_decimal expected = {{-1, -1, -1, 0}};

  int res_code = s21_sub(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(expected, result);
}
END_TEST

START_TEST(test_14) {
  // num_1: 79228162514264337593543950335
  // num_2: -0.4
  // result: 79228162514264337593543950335

  s21_decimal num_1 = {{-1, -1, -1, 0}};
  s21_decimal num_2 = {{5, 0, 0, -2147418112}};
  s21_decimal result = {0};

  int res_code = s21_sub(num_1, num_2, &result);
  ck_assert_int_eq(res_code, ERROR_OVERFLOW);
}
END_TEST

START_TEST(test_15) {
  s21_decimal num_1 = {{2, 1, 0, 131072}};
  s21_decimal num_2 = {{1, 0, 0, 196608}};
  s21_decimal expected = {{19, 10, 0, 196608}};
  s21_decimal result = {0};

  int res_code = s21_sub(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(test_16) {
  s21_decimal num_1 = {{-1, -1, -1, -2147483648}};
  s21_decimal num_2 = {{1, 0, 0, 0}};
  s21_decimal result = {0};
  int res_code = s21_sub(num_1, num_2, &result);
  ck_assert_int_eq(res_code, ERROR_UNDERFLOW);
}
END_TEST

START_TEST(test_17) {
  // num_1: -79228162514264337593543950335
  // num_2: 0.4
  // result: -79228162514264337593543950335

  s21_decimal num_1 = {{-1, -1, -1, -2147483648}};
  s21_decimal num_2 = {{4, 0, 0, 65536}};
  s21_decimal result = {0};
  s21_decimal expected = {{-1, -1, -1, -2147483648}};

  int res_code = s21_sub(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(expected, result);
}
END_TEST

START_TEST(test_18) {
  // num_1: -79228162514264337593543950335
  // num_2: 0.4
  // result: -79228162514264337593543950335

  s21_decimal num_1 = {{-1, -1, -1, -2147483648}};
  s21_decimal num_2 = {{5, 0, 0, 65536}};
  s21_decimal result = {0};

  int res_code = s21_sub(num_1, num_2, &result);
  ck_assert_int_eq(res_code, ERROR_UNDERFLOW);
}
END_TEST

START_TEST(test_19) {
  // num_1: 79228162514264337593543950335
  // num_2: 0.6
  // result: 79228162514264337593543950334

  s21_decimal num_1 = {{-1, -1, -1, 0}};
  s21_decimal num_2 = {{6, 0, 0, 65536}};
  s21_decimal result = {0};
  s21_decimal expected = {{-2, -1, -1, 0}};

  int res_code = s21_sub(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(expected, result);
}
END_TEST

START_TEST(test_20) {
  // num_1: -79228162514264337593543950335
  // num_2: -0.07
  // result: -79228162514264337593543950335

  s21_decimal num_1 = {{-1, -1, -1, -2147483648}};
  s21_decimal num_2 = {{7, 0, 0, -2147352576}};
  s21_decimal result = {0};
  s21_decimal expected = {{-1, -1, -1, -2147483648}};

  int res_code = s21_sub(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(expected, result);
}
END_TEST

START_TEST(test_21) {
  // num_1: -79228162514264337593543950335
  // num_2: -0.4
  // result: -79228162514264337593543950335

  s21_decimal num_1 = {{-1, -1, -1, -2147483648}};
  s21_decimal num_2 = {{4, 0, 0, -2147418112}};
  s21_decimal result = {0};
  s21_decimal expected = {{-1, -1, -1, -2147483648}};

  int res_code = s21_sub(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(expected, result);
}
END_TEST

START_TEST(test_22) {
  s21_decimal num_1 = {{8, 0, 0, -2147483648}};
  s21_decimal num_2 = {{2, 0, 0, 0}};
  s21_decimal result = {0};
  s21_decimal expected = {{10, 0, 0, -2147483648}};
  int res_code = s21_sub(num_1, num_2, &result);

  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(expected, result);
}
END_TEST

START_TEST(test_23) {
  // num_1: -1844674222903514854001.21359
  // num_2: 858993459.6
  // result: -1844674222904373847460.81359

  s21_decimal num_1 = {{15, 10, 9999999, -2147155968}};
  s21_decimal num_2 = {{4, 2, 0, 65536}};
  s21_decimal result = {0};
  s21_decimal expected = {{40015, 20010, 9999999, -2147155968}};

  int res_code = s21_sub(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(expected, result);
}
END_TEST

START_TEST(test_24) {
  // num_1: 1844674222903514854001.21359
  // num_2: -85899345.96
  // result: 1844674222903600753347.17359

  s21_decimal num_1 = {{15, 10, 9999999, 327680}};
  s21_decimal num_2 = {{4, 2, 0, -2147352576}};
  s21_decimal result = {0};
  s21_decimal expected = {{4015, 2010, 9999999, 327680}};

  int res_code = s21_sub(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(expected, result);
}
END_TEST

// Тест для сложения с нулем
START_TEST(test_25) {
  s21_decimal num_1 = {{123456789, 0, 0, 0}};
  s21_decimal num_2 = {{0, 0, 0, 0}};
  s21_decimal result = {0};
  s21_decimal expected = {{123456789, 0, 0, 0}};

  int res_code = s21_sub(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(test_26) {
  // num_1: 1844674222903943878284.41103
  // num_2: 0
  // result: 1844674222903943878284.41103

  s21_decimal num_1 = {{15, 9999, 9999999, 327680}};
  s21_decimal num_2 = {{0, 0, 0, 0}};
  s21_decimal result = {0};
  s21_decimal expected = {{15, 9999, 9999999, 327680}};

  int res_code = s21_sub(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(expected, result);
}
END_TEST

START_TEST(test_27) {
  // num_1: 1844674222903943878284.41103
  // num_2: 0.00000000
  // result: 1844674222903943878284.4110300

  s21_decimal num_1 = {{15, 9999, 9999999, 327680}};
  s21_decimal num_2 = {{0, 0, 0, 524288}};
  s21_decimal result = {0};
  s21_decimal expected = {{1500, 999900, 999999900, 458752}};

  int res_code = s21_sub(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(expected, result);
}
END_TEST

START_TEST(test_28) {
  // num_1: 1844674222903943878284.41103
  // num_2: 0.00000000
  // result: 1844674222903943878284.4110300

  s21_decimal num_1 = {{15, 9999, 9999999, 327680}};
  s21_decimal num_2 = {{0, 0, 0, -2146959360}};
  s21_decimal result = {0};
  s21_decimal expected = {{1500, 999900, 999999900, 458752}};

  int res_code = s21_sub(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(expected, result);
}
END_TEST

START_TEST(test_29) {
  // num_1: 0.00000
  // num_2: 15
  // result: -15.00000  //!!!!!!!!!!!!!! в Си шарпе так.. а верно ли?

  s21_decimal num_1 = {{0, 0, 0, 327680}};
  s21_decimal num_2 = {{15, 0, 0, 0}};
  s21_decimal result = {0};
  s21_decimal expected = {{1500000, 0, 0, -2147155968}};

  int res_code = s21_sub(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(expected, result);
}
END_TEST

START_TEST(test_30) {
  // num_1: 0
  // num_2: -3843995745907
  // result: 3843995745907

  s21_decimal num_1 = {{0, 0, 0, 0}};
  s21_decimal num_2 = {{15987, 895, 0, -2147483648}};
  s21_decimal result = {0};
  s21_decimal expected = {{15987, 895, 0, 0}};

  int res_code = s21_sub(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(expected, result);
}
END_TEST

START_TEST(test_31) {
  // num_1: 0
  // num_2: 38439957459.07
  // result: -38439957459.07

  s21_decimal num_1 = {{0, 0, 0, 0}};
  s21_decimal num_2 = {{15987, 895, 0, 131072}};
  s21_decimal result = {0};
  s21_decimal expected = {{15987, 895, 0, -2147352576}};

  int res_code = s21_sub(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(expected, result);
}
END_TEST

START_TEST(test_32) {
  // num_1: -20546923002176664317224094865
  // num_2: 57575839996315139930324186.098
  // result: -20604498842172979457154419051

  s21_decimal num_1 = {{742984849, -675958617, 1113850927, -2147483648}};
  s21_decimal num_2 = {{-135023630, 1435092952, -1173774756, 196608}};
  s21_decimal result = {0};
  s21_decimal expected = {{-146208405, 1644758815, 1116972120, -2147483648}};

  int res_code = s21_sub(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(expected, result);
}
END_TEST

START_TEST(test_33) {
  // num_1: -20546923002176.664317224094865
  // num_2: 57575839996315139930324186.098
  // result: -57575839996335686853326362.762

  s21_decimal num_1 = {{742984849, -675958617, 1113850927, -2146500608}};
  s21_decimal num_2 = {{-135023630, 1435092952, -1173774756, 196608}};
  s21_decimal result = {0};
  s21_decimal expected = {{1186551946, 1439876906, -1173774756, -2147287040}};

  int res_code = s21_sub(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(test_34) {
  // num_1: 55340.232230461574289
  // num_2: 276701161487895363.585
  // result: -276701161487840023.35276953843

  s21_decimal num_1 = {{742984849, 2, 3, 983040}};
  s21_decimal num_2 = {{1, 89, 15, 196608}};
  s21_decimal result = {0};
  s21_decimal expected = {{-711823117, 308776917, 1500000002, -2146762752}};

  int res_code = s21_sub(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(expected, result);
}
END_TEST

START_TEST(test_35) {
  // num_1: 37272241674075337972.047168716
  // num_2: -3630993559226994467995444166.9
  // result: 3630993596499236142070782138.9

  s21_decimal num_1 = {{1742750924, -765097718, 2020532269, 589824}};
  s21_decimal num_2 = {{-1135548987, -1729193528, 1968365552, -2147418112}};
  s21_decimal result = {0};
  s21_decimal expected = {{-1241024691, -847339254, 1968365572, 65536}};

  int res_code = s21_sub(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(expected, result);
}
END_TEST

START_TEST(test_36) {
  // num_1: 37272241674075337972.047168716
  // num_2: -3630993559226994467995444166.9
  // result: 3630993596499236142070782138.9

  s21_decimal num_1 = {{1742750924, -765097718, 2020532269, 589824}};
  s21_decimal num_2 = {{-1135548987, -1729193528, 1968365552, -2147418112}};
  s21_decimal result = {0};
  s21_decimal expected = {{-1241024691, -847339254, 1968365572, 65536}};

  int res_code = s21_sub(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(expected, result);
}
END_TEST

START_TEST(test_37) {
  // num_1: -2054692300217666431722409486.5
  // num_2: 57575839996315139930324186098
  // result: -59630532296532806362046595584

  s21_decimal num_1 = {{742984849, -675958617, 1113850927, -2147418112}};
  s21_decimal num_2 = {{-135023630, 1435092952, -1173774756, 0}};
  s21_decimal result = {0};
  s21_decimal expected = {{368771584, 508503632, -1062389663, -2147483648}};

  int res_code = s21_sub(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(expected, result);
}
END_TEST

START_TEST(test_38) {
  // num_1: -2054692300217666431722409486.5
  // num_2: -57575839996315139930324186098
  // result: 55521147696097473498601776612

  s21_decimal num_1 = {{742984849, -675958617, 1113850927, -2147418112}};
  s21_decimal num_2 = {{-135023630, 1435092952, -1173774756, -2147483648}};
  s21_decimal result = {0};
  s21_decimal expected = {{-638818844, -1933285023, -1285159849, 0}};

  int res_code = s21_sub(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(expected, result);
}
END_TEST

START_TEST(test_39) {
  // num_1: -2054692300217666431722409486.5
  // num_2: -57575839996315139930324186098
  // result: 55521147696097473498601776612

  s21_decimal num_1 = {{742984849, -675958617, 1113850927, -2147418112}};
  s21_decimal num_2 = {{-135023630, 1435092952, -1173774756, -2147483648}};
  s21_decimal result = {0};
  s21_decimal expected = {{-638818844, -1933285023, -1285159849, 0}};

  int res_code = s21_sub(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(expected, result);
}
END_TEST

START_TEST(test_40) {
  // num_1: 2.0546923002176664317224094865
  // num_2: 57575839996315139930324186098
  // result: -57575839996315139930324186096

  s21_decimal num_1 = {{742984849, -675958617, 1113850927, 1835008}};
  s21_decimal num_2 = {{-135023630, 1435092952, -1173774756, 0}};
  s21_decimal result = {0};
  s21_decimal expected = {{-135023632, 1435092952, -1173774756, -2147483648}};

  int res_code = s21_sub(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(expected, result);
}
END_TEST

START_TEST(test_41) {
  s21_decimal num_1 = {{1, 2, 3, 0}};
  s21_decimal num_2 = {{1, 2, 3, 0}};
  int res_code = s21_sub(num_1, num_2, NULL);
  ck_assert_int_eq(res_code, S21_DECIMAL_ERROR);
}
END_TEST

START_TEST(test_42) {
  s21_decimal num_1 = {{0, 0, 0, 0}};
  s21_decimal num_2 = {{0, 0, 0, 0}};
  s21_decimal result = {{0}};
  s21_decimal expected = {{0, 0, 0, 0}};
  int res_code = s21_sub(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(test_43) {
  s21_decimal num_1 = {{0, 0, 0, 0}};
  s21_decimal num_2 = {{0, 0, 0, 0x80000000}};
  s21_decimal result = {{0}};
  s21_decimal expected = {{0, 0, 0, 0}};  // возможно будет -0
  int res_code = s21_sub(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(test_44) {
  s21_decimal num_1 = {{0, 0, 0, 0}};
  s21_decimal num_2 = {{0, 0, 0, 0}};
  s21_decimal result = {{0}};
  s21_decimal expected = {
      {0, 0, 0, 0}};  // возможно будет -0 что тоже верно -0 == +0
  int res_code = s21_sub(num_2, num_1, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(test_45) {
  s21_decimal num_1 = {{0xffffffff, 0xffffffff, 0xffffffff, 0x0}};
  s21_decimal num_2 = {{0, 0, 0, 0}};
  s21_decimal result = {{0}};
  s21_decimal expected = {{0xffffffff, 0xffffffff, 0xffffffff, 0x0}};
  int res_code = s21_sub(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(test_46) {
  s21_decimal num_1 = {{0xffffffff, 0xffffffff, 0xffffffff, 0x80000000}};
  s21_decimal num_2 = {{0, 0, 0, 0}};
  s21_decimal result = {{0}};
  s21_decimal expected = {{0xffffffff, 0xffffffff, 0xffffffff, 0x80000000}};
  int res_code = s21_sub(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(test_47) {
  // num_1: 0
  // num_2: 79228162514264337593543950335
  // result: -79228162514264337593543950335

  s21_decimal num_1 = {{0, 0, 0, 0}};
  s21_decimal num_2 = {{-1, -1, -1, 0}};
  s21_decimal result = {0};
  s21_decimal expected = {{-1, -1, -1, -2147483648}};

  int res_code = s21_sub(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(expected, result);
}
END_TEST

START_TEST(test_48) {
  s21_decimal num_1 = {{0, 0, 0, 0}};
  s21_decimal num_2 = {{-1, -1, -1, -2147483648}};
  s21_decimal result = {{0}};
  s21_decimal expected = {{-1, -1, -1, 0}};
  int res_code = s21_sub(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(test_49) {
  s21_decimal num_1 = {{-1, -1, -1, -2147483648}};
  s21_decimal num_2 = {{1, 1, 1, 0}};

  s21_decimal result = {{0}};
  int res_code = s21_sub(num_1, num_2, &result);
  ck_assert_int_eq(res_code, ERROR_UNDERFLOW);
}
END_TEST

START_TEST(test_50) {
  s21_decimal num_1 = {{-1, -1, -1, 0}};
  s21_decimal num_2 = {{-1, -1, -1, -2147483648}};
  s21_decimal result = {{0}};
  int res_code = s21_sub(num_1, num_2, &result);
  ck_assert_int_eq(res_code, ERROR_OVERFLOW);
}
END_TEST

START_TEST(test_51) {
  s21_decimal num_1 = {{-1, -1, -1, 0}};
  s21_decimal num_2 = {{-1, -1, -1, 0}};
  s21_decimal result = {{0}};
  s21_decimal expected = {{0, 0, 0, 0}};
  int res_code = s21_sub(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(test_52) {
  s21_decimal num_1 = {{-1, -1, -1, -2147483648}};
  s21_decimal num_2 = {{-1, -1, -1, -2147483648}};
  s21_decimal expected = s21_get_new_decimal();
  s21_decimal result = {{0, 0, 0, -2147483648}};

  int res_code = s21_sub(num_1, num_2, &result);

  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(test_53) {
  // num_1: 0.0000000000000000000000000001
  // num_2: 2
  // result: -1.9999999999999999999999999999

  s21_decimal num_1 = {{1, 0, 0, 1835008}};
  s21_decimal num_2 = {{2, 0, 0, 0}};
  s21_decimal result = {0};
  s21_decimal expected = {{536870911, 2085225666, 1084202172, -2145648640}};

  int res_code = s21_sub(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(expected, result);
}
END_TEST

START_TEST(test_54) {
  // num_1: 0.0000000000000000000000000001
  // num_2: -2
  // result: 2.0000000000000000000000000001

  s21_decimal num_1 = {{1, 0, 0, 1835008}};
  s21_decimal num_2 = {{2, 0, 0, -2147483648}};
  s21_decimal result = {0};
  s21_decimal expected = {{536870913, 2085225666, 1084202172, 1835008}};

  int res_code = s21_sub(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(expected, result);
}
END_TEST

START_TEST(test_55) {
  // num_1: 0.0000000000000000000000000001
  // num_2: -2
  // result: 2.0000000000000000000000000001

  s21_decimal num_1 = {{1, 0, 0, 1835008}};
  s21_decimal num_2 = {{2, 0, 0, -2147483648}};
  s21_decimal result = {0};
  s21_decimal expected = {{536870913, 2085225666, 1084202172, 1835008}};

  int res_code = s21_sub(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(expected, result);
}
END_TEST

START_TEST(test_56) {
  // num_1: 0.0000000000000000000000000001
  // num_2: -0.0000000000000000000000000002
  // result: 0.0000000000000000000000000003

  s21_decimal num_1 = {{1, 0, 0, 1835008}};
  s21_decimal num_2 = {{2, 0, 0, -2145648640}};
  s21_decimal result = {0};
  s21_decimal expected = {{3, 0, 0, 1835008}};

  int res_code = s21_sub(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(expected, result);
}
END_TEST

START_TEST(test_57) {
  // num_1: 0.0000000000000000000000000001
  // num_2: 0.0000000000000000000000000002
  // result: -0.0000000000000000000000000001

  s21_decimal num_1 = {{1, 0, 0, 1835008}};
  s21_decimal num_2 = {{2, 0, 0, 1835008}};
  s21_decimal result = {0};
  s21_decimal expected = {{1, 0, 0, -2145648640}};

  int res_code = s21_sub(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(expected, result);
}
END_TEST

START_TEST(test_58) {
  // num_1: 0.0000000000000000000000000001
  // num_2: 589
  // result: -589.00000000000000000000000000

  s21_decimal num_1 = {{1, 0, 0, 1835008}};
  s21_decimal num_2 = {{589, 0, 0, 0}};
  s21_decimal result = {0};
  s21_decimal expected = {{-1811939328, -129662666, -1101991899, -2145779712}};

  int res_code = s21_sub(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(expected, result);
}
END_TEST

START_TEST(test_59) {
  // num_1: 0.0000000000000000000000000001
  // num_2: 589
  // result: -589.00000000000000000000000000

  s21_decimal num_1 = {{1, 0, 0, 1835008}};
  s21_decimal num_2 = {{589, 0, 0, 0}};
  s21_decimal result = {0};
  s21_decimal expected = {{-1811939328, -129662666, -1101991899, -2145779712}};

  int res_code = s21_sub(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(expected, result);
}
END_TEST

START_TEST(test_60) {
  // num_1: 0.0000000000000000000000000001
  // num_2: -589
  // result: 589.00000000000000000000000000

  s21_decimal num_1 = {{1, 0, 0, 1835008}};
  s21_decimal num_2 = {{589, 0, 0, -2147483648}};
  s21_decimal result = {0};
  s21_decimal expected = {{-1811939328, -129662666, -1101991899, 1703936}};

  int res_code = s21_sub(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(expected, result);
}
END_TEST

START_TEST(test_61) {
  // num_1: 79228162514264337593543950335
  // num_2: -0.0000000000000000000000000001
  // result: 79228162514264337593543950335

  s21_decimal num_1 = {{-1, -1, -1, 0}};
  s21_decimal num_2 = {{1, 0, 0, -2145648640}};
  s21_decimal result = {0};
  s21_decimal expected = {{-1, -1, -1, 0}};

  int res_code = s21_sub(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(expected, result);
}
END_TEST

START_TEST(test_62) {
  // num_1: 79228162514264337593543950335
  // num_2: -0.0000000000000000000000000005
  // result: 79228162514264337593543950335

  s21_decimal num_1 = {{-1, -1, -1, 0}};
  s21_decimal num_2 = {{5, 0, 0, -2145648640}};
  s21_decimal result = {0};
  s21_decimal expected = {{-1, -1, -1, 0}};

  int res_code = s21_sub(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(expected, result);
}
END_TEST

START_TEST(test_63) {
  // num_1: 79228162514264337593543950335
  // num_2: -0.0000000000000000000000000005
  // result: 79228162514264337593543950335

  s21_decimal num_1 = {{-1, -1, -1, 0}};
  s21_decimal num_2 = {{5, 0, 0, -2145648640}};
  s21_decimal result = {0};
  s21_decimal expected = {{-1, -1, -1, 0}};

  int res_code = s21_sub(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(expected, result);
}
END_TEST

START_TEST(test_64) {
  s21_decimal num_1 = {{-545094277, -845229340, 677280337, -2146107392}};
  s21_decimal num_2 = {{-40286452, 135710988, 359361990, 524288}};
  s21_decimal result = {0};
  s21_decimal expected = {{-827685762, 1360018786, -701347396, -2146893824}};

  int res_code = s21_sub(num_1, num_2, &result);
  ck_assert_int_eq(res_code, 0);
  for (int i = 0; i < 4; ++i) {
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
  }
}
END_TEST

START_TEST(test_65) {
  s21_decimal num_1 = {{-481263282, 414974053, -1632242189, -2146435072}};
  s21_decimal num_2 = {{-1566695876, 1467647794, 1769656798, -2146041856}};
  s21_decimal result = {0};
  s21_decimal expected = {{695546439, 1889013952, -1632243959, -2146435072}};

  int res_code = s21_sub(num_1, num_2, &result);
  ck_assert_int_eq(res_code, 0);
  for (int i = 0; i < 4; ++i) {
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
  }
}
END_TEST

START_TEST(test_66) {
  s21_decimal num_1 = {{-106947193, 1552635177, -835852774, 1376256}};
  s21_decimal num_2 = {{1684621492, -100420738, -423955410, 1638400}};
  s21_decimal result = {0};
  s21_decimal expected = {{1261260925, 742184891, -836239875, 1376256}};

  int res_code = s21_sub(num_1, num_2, &result);
  ck_assert_int_eq(res_code, 0);
  for (int i = 0; i < 4; ++i) {
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
  }
}
END_TEST

START_TEST(test_67) {
  s21_decimal num_1 = {{1008024429, 1274041519, -371838153, 720896}};
  s21_decimal num_2 = {{-230692850, -1625724429, -1504730336, -2147155968}};
  s21_decimal result = {0};
  s21_decimal expected = {{2126588074, -1071058193, -1504726413, 327680}};

  int res_code = s21_sub(num_1, num_2, &result);
  ck_assert_int_eq(res_code, 0);
  for (int i = 0; i < 4; ++i) {
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
  }
}
END_TEST

START_TEST(test_68) {
  s21_decimal num_1 = {{-470469060, 1615994755, 306589040, 1441792}};
  s21_decimal num_2 = {{466219629, -1988026465, 999145981, -2146304000}};
  s21_decimal result = {0};
  s21_decimal expected = {{722152633, 1894785570, 999176640, 1179648}};

  int res_code = s21_sub(num_1, num_2, &result);
  ck_assert_int_eq(res_code, 0);
  for (int i = 0; i < 4; ++i) {
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
  }
}
END_TEST

START_TEST(test_69) {
  s21_decimal num_1 = {{1303610063, -2100327507, -662347578, -2146959360}};
  s21_decimal num_2 = {{-1139722871, 1026381884, -812100980, 1245184}};
  s21_decimal result = {0};
  s21_decimal expected = {{-1935380106, -1950739538, -662347578, -2146959360}};

  int res_code = s21_sub(num_1, num_2, &result);
  ck_assert_int_eq(res_code, 0);
  for (int i = 0; i < 4; ++i) {
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
  }
}
END_TEST

START_TEST(test_70) {
  s21_decimal num_1 = {{581677060, -574891414, 375118760, 720896}};
  s21_decimal num_2 = {{-1608663099, -677177284, 1206571201, -2146369536}};
  s21_decimal result = {0};
  s21_decimal expected = {{-1376929160, 1604148999, -543767622, 786432}};

  int res_code = s21_sub(num_1, num_2, &result);
  ck_assert_int_eq(res_code, 0);
  for (int i = 0; i < 4; ++i) {
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
  }
}
END_TEST

START_TEST(test_71) {
  s21_decimal num_1 = {{2007364877, -59993199, 390017536, 196608}};
  s21_decimal num_2 = {{2016613614, 976424241, -65355661, 393216}};
  s21_decimal result = {0};
  s21_decimal expected = {{-1464303519, -2112934782, -437088043, 262144}};

  int res_code = s21_sub(num_1, num_2, &result);
  ck_assert_int_eq(res_code, 0);
  for (int i = 0; i < 4; ++i) {
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
  }
}
END_TEST

START_TEST(test_72) {
  s21_decimal num_1 = {{2037257346, 1655898722, 974261345, -2147090432}};
  s21_decimal num_2 = {{-233750107, -1345572337, 1054537182, -2145910784}};
  s21_decimal result = {0};
  s21_decimal expected = {{-235650995, 1655898717, 974261345, -2147090432}};

  int res_code = s21_sub(num_1, num_2, &result);
  ck_assert_int_eq(res_code, 0);
  for (int i = 0; i < 4; ++i) {
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
  }
}
END_TEST

START_TEST(test_73) {
  s21_decimal num_1 = {{2130228336, -1818477427, -1869901495, -2147090432}};
  s21_decimal num_2 = {{-579670104, 1437447303, 857674077, 851968}};
  s21_decimal result = {0};
  s21_decimal expected = {{1886744864, 1477513691, -1869901409, -2147090432}};

  int res_code = s21_sub(num_1, num_2, &result);
  ck_assert_int_eq(res_code, 0);
  for (int i = 0; i < 4; ++i) {
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
  }
}
END_TEST

TCase *arithmetic_sub_tests(void) {
  TCase *test_cases = tcase_create("test_cases_s21_sub");

  tcase_add_test(test_cases, test_0);
  tcase_add_test(test_cases, test_1);
  tcase_add_test(test_cases, test_2);
  tcase_add_test(test_cases, test_3);
  tcase_add_test(test_cases, test_4);
  tcase_add_test(test_cases, test_5);
  tcase_add_test(test_cases, test_6);
  tcase_add_test(test_cases, test_7);
  tcase_add_test(test_cases, test_8);
  tcase_add_test(test_cases, test_9);
  tcase_add_test(test_cases, test_10);
  tcase_add_test(test_cases, test_11);
  tcase_add_test(test_cases, test_12);
  tcase_add_test(test_cases, test_13);
  tcase_add_test(test_cases, test_14);
  tcase_add_test(test_cases, test_15);
  tcase_add_test(test_cases, test_16);
  tcase_add_test(test_cases, test_17);
  tcase_add_test(test_cases, test_18);
  tcase_add_test(test_cases, test_19);
  tcase_add_test(test_cases, test_20);
  tcase_add_test(test_cases, test_21);
  tcase_add_test(test_cases, test_22);
  tcase_add_test(test_cases, test_23);
  tcase_add_test(test_cases, test_24);
  tcase_add_test(test_cases, test_25);
  tcase_add_test(test_cases, test_26);
  tcase_add_test(test_cases, test_27);
  tcase_add_test(test_cases, test_28);
  tcase_add_test(test_cases, test_29);
  tcase_add_test(test_cases, test_30);
  tcase_add_test(test_cases, test_31);
  tcase_add_test(test_cases, test_32);
  tcase_add_test(test_cases, test_33);
  tcase_add_test(test_cases, test_34);
  tcase_add_test(test_cases, test_35);
  tcase_add_test(test_cases, test_36);
  tcase_add_test(test_cases, test_37);
  tcase_add_test(test_cases, test_38);
  tcase_add_test(test_cases, test_39);
  tcase_add_test(test_cases, test_40);
  tcase_add_test(test_cases, test_41);
  tcase_add_test(test_cases, test_42);
  tcase_add_test(test_cases, test_43);
  tcase_add_test(test_cases, test_44);
  tcase_add_test(test_cases, test_45);
  tcase_add_test(test_cases, test_46);
  tcase_add_test(test_cases, test_47);
  tcase_add_test(test_cases, test_48);
  tcase_add_test(test_cases, test_49);
  tcase_add_test(test_cases, test_50);
  tcase_add_test(test_cases, test_51);
  tcase_add_test(test_cases, test_52);
  tcase_add_test(test_cases, test_53);
  tcase_add_test(test_cases, test_54);
  tcase_add_test(test_cases, test_55);
  tcase_add_test(test_cases, test_56);
  tcase_add_test(test_cases, test_57);
  tcase_add_test(test_cases, test_58);
  tcase_add_test(test_cases, test_59);
  tcase_add_test(test_cases, test_60);
  tcase_add_test(test_cases, test_61);
  tcase_add_test(test_cases, test_62);
  tcase_add_test(test_cases, test_63);
  tcase_add_test(test_cases, test_64);
  tcase_add_test(test_cases, test_65);
  tcase_add_test(test_cases, test_66);
  tcase_add_test(test_cases, test_67);
  tcase_add_test(test_cases, test_68);
  tcase_add_test(test_cases, test_69);
  tcase_add_test(test_cases, test_70);
  tcase_add_test(test_cases, test_71);
  tcase_add_test(test_cases, test_72);
  tcase_add_test(test_cases, test_73);

  return test_cases;
}