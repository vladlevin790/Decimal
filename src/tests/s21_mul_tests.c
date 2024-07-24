#include <check.h>
#include <limits.h>

#include "../decimal_helper/s21_decimal_helper.h"
#include "../s21_decimal.h"
#include "helper_tests.h"

START_TEST(test_0) {
  s21_decimal num_1 = {{1, 0, 0, 0}};
  s21_decimal num_2 = {{3, 0, 0, 0}};
  s21_decimal result = {0};
  s21_decimal expected = {{3, 0, 0, 0}};

  int res_code = s21_mul(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(test_1) {
  s21_decimal num_1 = {{3, 0, 0, 0}};
  s21_decimal num_2 = {{1, 0, 0, 0}};
  s21_decimal result = {0};
  s21_decimal expected = {{3, 0, 0, 0}};

  int res_code = s21_mul(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(test_2) {
  s21_decimal num_1 = {{3, 0, 0, 0}};
  s21_decimal num_2 = {{3, 0, 0, 0}};
  s21_decimal result = {0};
  s21_decimal expected = {{9, 0, 0, 0}};

  int res_code = s21_mul(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(test_3) {
  s21_decimal num_1 = {{9, 0, 0, 0}};
  s21_decimal num_2 = {{9, 0, 0, 0}};
  s21_decimal result = {0};
  s21_decimal expected = {{81, 0, 0, 0}};

  int res_code = s21_mul(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(test_4) {
  s21_decimal num_1 = {{123456789, 0, 0, 0}};
  s21_decimal num_2 = {{987654321, 0, 0, 0}};
  s21_decimal result = {0};
  s21_decimal expected = {{-67153019, 28389652, 0, 0}};

  int res_code = s21_mul(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(test_5) {
  s21_decimal num_1 = {{1912284813, 287, 0, 0}};
  s21_decimal num_2 = {{-1881568455, 2299, 0, 0}};
  s21_decimal result = {0};
  s21_decimal expected = {{794764389, 526544783, 660998, 0}};

  int res_code = s21_mul(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(test_6) {
  s21_decimal num_1 = {{1942978950, 2874, 0, 0}};
  s21_decimal num_2 = {{-1635815360, 22995, 0, 0}};
  s21_decimal result = {0};
  s21_decimal expected = {{-1308294784, 1114979995, 66099812, 0}};

  int res_code = s21_mul(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(test_7) {
  s21_decimal num_1 = {{-2045046977, 28744, 0, 0}};
  s21_decimal num_2 = {{821715591, 229956, 0, 0}};
  s21_decimal result = {0};
  // s21_decimal expected = {{0, 0, 0, 0}};

  int res_code = s21_mul(num_1, num_2, &result);
  ck_assert_int_eq(res_code, ERROR_OVERFLOW);
  // check_decimal_bits(result, expected);
}
END_TEST

START_TEST(test_8) {
  s21_decimal num_1 = {{1653732529, 2874452, 0, -2147483648}};
  s21_decimal num_2 = {{567180565, 22995619, 0, 0}};
  s21_decimal result = {0};
  // s21_decimal expected = {{0, 0, 0, 0}};

  int res_code = s21_mul(num_1, num_2, &result);
  ck_assert_int_eq(res_code, ERROR_UNDERFLOW);
  // check_decimal_bits(result, expected);
}
END_TEST

START_TEST(test_9) {
  s21_decimal num_1 = {{123456, 0, 0, -2147287040}};
  s21_decimal num_2 = {{3, 0, 0, 0}};
  s21_decimal result = {0};
  s21_decimal expected = {{370368, 0, 0, -2147287040}};

  int res_code = s21_mul(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(test_10) {
  s21_decimal num_1 = {{-1019794767, 77, 0, 589824}};
  s21_decimal num_2 = {{-1883992299, 77, 0, -2146893824}};
  s21_decimal result = {0};
  s21_decimal expected = {{-1210884219, 1585209676, 6031, -2146304000}};

  int res_code = s21_mul(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(test_11) {
  s21_decimal num_1 = {{1233169989, 1016507639, 669, -2146304000}};
  s21_decimal num_2 = {{-1533265724, 1552338606, 294476024, -2145976320}};
  s21_decimal result = {0};
  s21_decimal expected = {{-1885176809, -1419499196, -659590793, 1310720}};

  int res_code = s21_mul(num_1, num_2, &result);

  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(test_12) {
  s21_decimal num_1 = {{-158867394, -1529088203, 399220997, 1835008}};
  s21_decimal num_2 = {{1719348742, -1633477906, 263338225, 1835008}};
  s21_decimal result = {0};
  s21_decimal expected = {{-539633203, -1805983613, 193930895, 1835008}};

  int res_code = s21_mul(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(test_13) {
  s21_decimal num_1 = {{-158867394, -1529088203, 399220997, 1835008}};
  s21_decimal num_2 = {{1719348196, -1633477906, 263338225, 1835008}};
  s21_decimal result = {0};
  s21_decimal expected = {{-539633605, -1805983613, 193930895, 1835008}};

  int res_code = s21_mul(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(test_14) {
  s21_decimal num_1 = {{-158867394, -1529088203, 399220997, 1835008}};
  s21_decimal num_2 = {{920244317, 29013649, 0, 0}};
  s21_decimal result = {0};
  s21_decimal expected = {{464574131, 1636883631, 497479962, 720896}};

  int res_code = s21_mul(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(test_15) {
  s21_decimal num_1 = {{1, 0, 0, 1835008}};
  s21_decimal num_2 = {{-1, -1, -1, 0}};
  s21_decimal result = {0};
  s21_decimal expected = {{-1, -1, -1, 1835008}};

  int res_code = s21_mul(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(test_16) {
  s21_decimal num_1 = {{1, 0, 0, 1835008}};
  s21_decimal num_2 = {{-1, -1, -1, -2147483648}};
  s21_decimal result = {0};
  s21_decimal expected = {{-1, -1, -1, -2145648640}};

  int res_code = s21_mul(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(test_17) {
  s21_decimal num_1 = {{-1, -1, -1, 0}};
  s21_decimal num_2 = {{-1, -1, -1, -2147483648}};
  s21_decimal result = {0};
  // s21_decimal expected = {{0, 0, 0, 0}};

  int res_code = s21_mul(num_1, num_2, &result);
  ck_assert_int_eq(res_code, ERROR_UNDERFLOW);
  // check_decimal_bits(result, expected);
}
END_TEST

START_TEST(test_18) {
  s21_decimal num_1 = {{-1, -1, -1, -2147483648}};
  s21_decimal num_2 = {{-1, -1, -1, -2147483648}};
  s21_decimal result = {0};
  // s21_decimal expected = {{0, 0, 0, 0}};

  int res_code = s21_mul(num_1, num_2, &result);
  ck_assert_int_eq(res_code, ERROR_OVERFLOW);
  // check_decimal_bits(result, expected);
}
END_TEST

START_TEST(test_19) {
  s21_decimal num_1 = {{1, 0, 0, 1835008}};
  s21_decimal num_2 = {{1, 0, 0, 1835008}};
  s21_decimal result = {0};
  s21_decimal expected = {{0, 0, 0, 0}};

  int res_code = s21_mul(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(test_20) {
  s21_decimal num_1 = {{4, 0, 0, 1835008}};
  s21_decimal num_2 = {{1, 0, 0, 65536}};
  s21_decimal result = {0};
  s21_decimal expected = {{0, 0, 0, 1835008}};

  int res_code = s21_mul(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(test_21) {
  s21_decimal num_1 = {{5, 0, 0, 1835008}};
  s21_decimal num_2 = {{1, 0, 0, 65536}};
  s21_decimal result = {0};
  s21_decimal expected = {{0, 0, 0, 1835008}};

  int res_code = s21_mul(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(test_22) {
  s21_decimal num_1 = {{6, 0, 0, 1835008}};
  s21_decimal num_2 = {{1, 0, 0, 65536}};
  s21_decimal result = {0};
  s21_decimal expected = {{1, 0, 0, 1835008}};

  int res_code = s21_mul(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(test_23) {
  s21_decimal num_1 = {{55, 0, 0, 1835008}};
  s21_decimal num_2 = {{1, 0, 0, 65536}};
  s21_decimal result = {0};
  s21_decimal expected = {{6, 0, 0, 1835008}};

  int res_code = s21_mul(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(test_24) {
  s21_decimal num_1 = {{54, 0, 0, 1835008}};
  s21_decimal num_2 = {{1, 0, 0, 65536}};
  s21_decimal result = {0};
  s21_decimal expected = {{5, 0, 0, 1835008}};

  int res_code = s21_mul(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(test_25) {
  s21_decimal num_1 = {{56, 0, 0, 1835008}};
  s21_decimal num_2 = {{1, 0, 0, 65536}};
  s21_decimal result = {0};
  s21_decimal expected = {{6, 0, 0, 1835008}};

  int res_code = s21_mul(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(test_26) {
  s21_decimal num_1 = {{550, 0, 0, 1835008}};
  s21_decimal num_2 = {{1, 0, 0, 65536}};
  s21_decimal result = {0};
  s21_decimal expected = {{55, 0, 0, 1835008}};

  int res_code = s21_mul(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(test_27) {
  s21_decimal num_1 = {{551, 0, 0, 1835008}};
  s21_decimal num_2 = {{1, 0, 0, 65536}};
  s21_decimal result = {0};
  s21_decimal expected = {{55, 0, 0, 1835008}};

  int res_code = s21_mul(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(test_28) {
  s21_decimal num_1 = {{555, 0, 0, 1835008}};
  s21_decimal num_2 = {{1, 0, 0, 65536}};
  s21_decimal result = {0};
  s21_decimal expected = {{56, 0, 0, 1835008}};

  int res_code = s21_mul(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(test_29) {
  s21_decimal num_1 = {{556, 0, 0, 1835008}};
  s21_decimal num_2 = {{1, 0, 0, 65536}};
  s21_decimal result = {0};
  s21_decimal expected = {{56, 0, 0, 1835008}};

  int res_code = s21_mul(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(test_30) {
  s21_decimal num_1 = {{1535271577, 1792610796, -808869272, -2146107392}};
  s21_decimal num_2 = {{1001475825, 1324918839, 240796599, -2145976320}};
  s21_decimal result = {0};
  s21_decimal expected = {{-1527620996, -2147123165, 1548494497, 1048576}};

  int res_code = s21_mul(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(test_31) {
  s21_decimal num_1 = {{251471400, -1439845512, -326685632, -2146435072}};
  s21_decimal num_2 = {{324887160, 1340391056, 648192061, -2145714176}};
  s21_decimal result = {0};
  s21_decimal expected = {{1023303095, -938591168, 474488750, 917504}};

  int res_code = s21_mul(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(test_32) {
  s21_decimal num_1 = {{1885946808, 600861669, 1433761521, 1769472}};
  s21_decimal num_2 = {{820448350, -1226060966, -1263983746, 720896}};
  s21_decimal result = {0};
  s21_decimal expected = {{1306020049, -1622455793, 801641556, 589824}};

  int res_code = s21_mul(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(test_33) {
  s21_decimal num_1 = {{1830986841, 540496461, -739330903, -2146107392}};
  s21_decimal num_2 = {{-1266829623, 1707741193, 1737550216, -2146238464}};
  s21_decimal result = {0};
  s21_decimal expected = {{1613693121, 1834810045, 1139657702, 720896}};

  int res_code = s21_mul(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(test_34) {
  s21_decimal num_1 = {{149268618, 626221330, -2054000444, -2146566144}};
  s21_decimal num_2 = {{1240422874, 81903313, 1225640607, -2145648640}};
  s21_decimal result = {0};
  s21_decimal expected = {{1463732249, 394405766, 506661957, 851968}};

  int res_code = s21_mul(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(test_35) {
  s21_decimal num_1 = {{1561891604, 626911701, 1061534027, -2146435072}};
  s21_decimal num_2 = {{-1870699632, 817454602, 1985660271, -2146500608}};
  s21_decimal result = {0};
  s21_decimal expected = {{1892604489, -68423331, -406677829, 196608}};

  int res_code = s21_mul(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(test_36) {
  s21_decimal num_1 = {{-2035422833, 1720849450, -1301669166, 917504}};
  s21_decimal num_2 = {{1174230271, -1801654400, -634234110, 1310720}};
  s21_decimal result = {0};
  s21_decimal expected = {{982330453, 793578124, 2021332567, 327680}};

  int res_code = s21_mul(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(test_37) {
  s21_decimal num_1 = {{-783565715, 107740578, -781458149, -2145976320}};
  s21_decimal num_2 = {{-855406646, 1869030735, 128157337, -2145976320}};
  s21_decimal result = {0};
  s21_decimal expected = {{642532625, -1315717685, 830623639, 1179648}};

  int res_code = s21_mul(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(test_38) {
  s21_decimal num_1 = {{-853063454, -1300572561, -33572690, 1835008}};
  s21_decimal num_2 = {{78453268, 574340377, -1253911201, 1245184}};
  s21_decimal result = {0};
  s21_decimal expected = {{-1538663216, -913097336, -1904427899, 1179648}};

  int res_code = s21_mul(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(test_41) {
  s21_decimal num_1 = {{-219011914, -1889548242, 1063391811, -2147024896}};
  s21_decimal num_2 = {{636932225, -1535283603, 75240318, 1703936}};
  s21_decimal result = {0};
  s21_decimal expected = {{-2048581384, 1534173760, 1475922863, -2147090432}};

  int res_code = s21_mul(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(test_42) {
  s21_decimal num_1 = {{-310693740, 1423476121, 2059815221, -2146304000}};
  s21_decimal num_2 = {{551892703, 1158745891, 252199148, -2146500608}};
  s21_decimal result = {0};
  s21_decimal expected = {{-1872688994, -445210367, 958278183, 327680}};

  int res_code = s21_mul(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(test_43) {
  s21_decimal num_1 = {{-1095965772, 1558697309, -1345550506, -2146500608}};
  s21_decimal num_2 = {{-31461234, -1171385771, -1031990361, -2146238464}};
  s21_decimal result = {0};
  s21_decimal expected = {{-1481570603, -590452288, 1775292321, 327680}};

  int res_code = s21_mul(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(test_44) {
  s21_decimal num_1 = {{29063961, -475991592, -1466679933, -2146304000}};
  s21_decimal num_2 = {{478025661, 1031886172, 358469045, -2146697216}};
  s21_decimal result = {0};
  s21_decimal expected = {{589444039, -966309993, 1870229550, 131072}};

  int res_code = s21_mul(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(test_45) {
  s21_decimal num_1 = {{1514863572, 2086514241, -1146533204, -2146369536}};
  s21_decimal num_2 = {{303132341, -1925495208, -1866636871, -2146697216}};
  s21_decimal result = {0};
  s21_decimal expected = {{-391072865, 1914069903, 1410334436, 0}};

  int res_code = s21_mul(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(test_46) {
  s21_decimal num_1 = {{-760589995, -2085489037, 1058057484, -2146500608}};
  s21_decimal num_2 = {{1518549447, -633067126, -1041840805, -2146041856}};
  s21_decimal result = {0};
  s21_decimal expected = {{-31595098, -718766918, 634935977, 524288}};

  int res_code = s21_mul(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(test_47) {
  s21_decimal num_1 = {{-1059284118, -1244370228, -1302972298, 1703936}};
  s21_decimal num_2 = {{-1906715509, -1988453618, -1402848158, -2147090432}};
  s21_decimal result = {0};
  s21_decimal expected = {{-1933360983, -1483465371, 1596234764, -2147287040}};

  int res_code = s21_mul(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(test_48) {
  s21_decimal num_1 = {{1347941844, 1363413593, -1784900900, -2146697216}};
  s21_decimal num_2 = {{-71815388, 1527272031, 448478893, 1507328}};
  s21_decimal result = {0};
  s21_decimal expected = {{941061523, -318449472, 2076571746, -2147024896}};

  int res_code = s21_mul(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(test_49) {
  s21_decimal num_1 = {{1221634508, 490055039, 723936407, -2146107392}};
  s21_decimal num_2 = {{-1950660732, -329010948, -1385692415, 1048576}};
  s21_decimal result = {0};
  s21_decimal expected = {{-772613970, 1815154558, -409843177, -2146893824}};

  int res_code = s21_mul(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(test_50) {
  s21_decimal num_1 = {{-90594807, -156581081, -513543997, 262144}};
  s21_decimal num_2 = {{-868005434, 1207599360, -1143302294, -2145779712}};
  s21_decimal result = {0};
  s21_decimal expected = {{-822151674, -1246466880, -2096525018, -2147418112}};

  int res_code = s21_mul(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(test_51) {
  s21_decimal num_1 = {{-63758827, -138056575, 1676975128, 1310720}};
  s21_decimal num_2 = {{1396223007, -495564625, -842561600, 1638400}};
  s21_decimal result = {0};
  s21_decimal expected = {{-2113867979, 519918687, 1067992416, 1048576}};

  int res_code = s21_mul(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(test_52) {
  s21_decimal num_1 = {{-1652272547, -194423321, -1143085376, -2146500608}};
  s21_decimal num_2 = {{1175743532, 1228472707, -656921428, -2146041856}};
  s21_decimal result = {0};
  s21_decimal expected = {{230226642, 2002740812, 2115231142, 524288}};

  int res_code = s21_mul(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(test_53) {
  s21_decimal num_1 = {{-494939452, -355577529, -1628083573, 1703936}};
  s21_decimal num_2 = {{-2068186492, 335687709, -157664559, 589824}};
  s21_decimal result = {0};
  s21_decimal expected = {{-1668438913, 652901114, 2035359384, 393216}};

  int res_code = s21_mul(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

// num_1: 79228162514264337593543950335
// num_2: 0.5
// result: 39614081257132168796771975168
START_TEST(test_54) {
  s21_decimal num_1 = {{-1, -1, -1, 0}};
  s21_decimal num_2 = {{5, 0, 0, 65536}};
  s21_decimal result = {0};
  s21_decimal expected = {{0, 0, -2147483648, 0}};

  int res_code = s21_mul(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(test_55) {
  // Decimal values:
  // num_1: экспонента более 28, некорректная
  // num_2: 0.001
  // result: ошибка
  s21_decimal num_1 = {{55, 0, 0, 2835008}};
  s21_decimal num_2 = {{1, 0, 0, 196608}};
  s21_decimal result = {0};

  int res_code = s21_mul(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_ERROR);
}
END_TEST

START_TEST(test_56) {
  // Decimal values:
  // num_1: экспонента 29
  // num_2: 0.001
  // result: ошибка
  s21_decimal num_1 = {{55, 0, 0, 1900544}};
  s21_decimal num_2 = {{1, 0, 0, 196608}};
  s21_decimal result = {0};

  int res_code = s21_mul(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_ERROR);
}
END_TEST

START_TEST(test_57) {
  s21_decimal num_1 = {{894784853, -819591186, 1807003620, 0}};
  s21_decimal num_2 = {{100000003, 0, 0, 524288}};
  s21_decimal result = {0};
  s21_decimal expected = {{334845269, 82818484, 1807003675, 0}};

  int res_code = s21_mul(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(test_58) {
  s21_decimal num_1 = {{894784853, -819591186, 1807003620, 0}};
  s21_decimal num_2 = {{15, 0, 0, 65536}};
  s21_decimal result = {0};
  s21_decimal expected = {{1342177280, 918096869, -1584461865, 0}};

  int res_code = s21_mul(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(test_59) {
  s21_decimal num_1 = {{894784853, -819591186, 1807003620, 0}};
  s21_decimal num_2 = {{153, 0, 0, 131072}};
  s21_decimal result = {0};
  s21_decimal expected = {{939524095, -695628766, -1530251757, 0}};

  int res_code = s21_mul(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(test_60) {
  s21_decimal num_1 = {{894784854, -819591186, 1807003620, 0}};
  s21_decimal num_2 = {{12, 0, 0, 65536}};
  s21_decimal result = {0};
  s21_decimal expected = {{1073741825, -124515964, -2126562952, 0}};

  int res_code = s21_mul(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(test_61) {
  s21_decimal num_1 = {{-402653185, -1613725636, 54210108, 0}};
  s21_decimal num_2 = {{-402653183, -1613725636, 54210108, 1769472}};
  s21_decimal result = {0};
  s21_decimal expected = {{268435456, 1042612833, 542101086, 65536}};

  int res_code = s21_mul(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(test_62) {
  s21_decimal num_1 = {{268435455, 1042612833, 542101086, 0}};
  s21_decimal num_2 = {{268435457, 1042612833, 542101086, 1835008}};
  s21_decimal result = {0};
  s21_decimal expected = {{268435456, 1042612833, 542101086, 0}};

  int res_code = s21_mul(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

START_TEST(test_63) {
  s21_decimal num_1 = {{268435456, 1042612833, 542101086, 1769472}};
  s21_decimal num_2 = {{11, 0, 0, 65536}};
  s21_decimal result = {0};
  s21_decimal expected = {{-134217728, -571112803, 596311194, 1769472}};

  int res_code = s21_mul(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
  check_decimal_bits(result, expected);
}
END_TEST

TCase *arithmetic_mul_tests(void) {
  TCase *test_cases = tcase_create("test_cases_s21_mul");

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

  return test_cases;
}
