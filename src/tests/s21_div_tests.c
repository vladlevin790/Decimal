#include <check.h>
#include <limits.h>

#include "../decimal_helper/s21_decimal_helper.h"
#include "../s21_decimal.h"

START_TEST(test_0) {
  s21_decimal num_1 = {{5, 0, 0, 0}};
  s21_decimal num_2 = {{1, 0, 0, 0}};
  s21_decimal result = {0};

  int res_code = s21_div(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
}
END_TEST

START_TEST(test_1) {
  s21_decimal num_1 = {{150, 0, 0, 0}};
  s21_decimal num_2 = {{10, 0, 0, 0}};
  s21_decimal result = {0};

  int res_code = s21_div(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
}
END_TEST

START_TEST(test_2) {
  s21_decimal num_1 = {{150, 0, 0, 0}};
  s21_decimal num_2 = {{0, 0, 0, 0}};
  s21_decimal result = {0};

  int res_code = s21_div(num_1, num_2, &result);
  ck_assert_int_eq(res_code, ERROR_DIVISION_BY_ZERO);
}
END_TEST

START_TEST(test_3) {
  s21_decimal num_1 = {{150, 0, 0, 0}};
  s21_decimal num_2 = {{0, 0, 0, 0}};
  s21_decimal result = {0};

  int res_code = s21_div(num_1, num_2, &result);
  ck_assert_int_eq(res_code, ERROR_DIVISION_BY_ZERO);
}
END_TEST

START_TEST(test_4) {
  s21_decimal num_1 = {{1144189273, 1421741867, 0, 0}};
  s21_decimal num_2 = {{237856235, 0, 0, 0}};
  s21_decimal result = {0};

  int res_code = s21_div(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
}
END_TEST

START_TEST(test_5) {
  s21_decimal num_1 = {{1, 5, 0, 0}};
  s21_decimal num_2 = {{7, 0, 0, 0}};
  s21_decimal result = {0};

  int res_code = s21_div(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
}
END_TEST

START_TEST(test_6) {
  s21_decimal num_1 = {{100, 5, 4, 0}};
  s21_decimal num_2 = {{2, 0, 0, 0}};
  s21_decimal result = {0};

  int res_code = s21_div(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
}
END_TEST

START_TEST(test_7) {
  s21_decimal num_1 = {{100, 5, 4, 0}};
  s21_decimal num_2 = {{4, 0, 0, 0}};
  s21_decimal result = {0};

  int res_code = s21_div(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
}
END_TEST

START_TEST(test_8) {
  s21_decimal num_1 = {{100, 500, 999, 0}};
  s21_decimal num_2 = {{4, 0, 0, 0}};
  s21_decimal result = {0};

  int res_code = s21_div(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
}
END_TEST

START_TEST(test_9) {
  s21_decimal num_1 = {{999, 999, 999, 0}};
  s21_decimal num_2 = {{333, 333, 333, 0}};
  s21_decimal result = {0};

  int res_code = s21_div(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
}
END_TEST

START_TEST(test_10) {
  s21_decimal num_1 = {{999999999, 999999999, 999999999, 0}};
  s21_decimal num_2 = {{3, 0, 0, 0}};
  s21_decimal result = {0};

  int res_code = s21_div(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
}
END_TEST

START_TEST(test_11) {
  s21_decimal num_1 = {{999999999, 999999999, 999999999, 0}};
  s21_decimal num_2 = {{999999999, 999999999, 999999999, 0}};
  s21_decimal result = {0};

  int res_code = s21_div(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
}
END_TEST

START_TEST(test_12) {
  s21_decimal num_1 = {{2147483647, 2147483647, 2147483647, 0}};
  s21_decimal num_2 = {{2147483647, 2147483647, 2147483647, 0}};
  s21_decimal result = {0};

  int res_code = s21_div(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
}
END_TEST

START_TEST(test_13) {
  s21_decimal num_1 = {{-2147483648, -2147483648, -2147483648, 0}};
  s21_decimal num_2 = {{-2147483648, -2147483648, -2147483648, 0}};
  s21_decimal result = {0};

  int res_code = s21_div(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
}
END_TEST

START_TEST(test_14) {
  s21_decimal num_1 = {{0, 0, 0, 0}};
  s21_decimal num_2 = {{333, 3, 3, 0}};
  s21_decimal result = {0};

  int res_code = s21_div(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
}
END_TEST

START_TEST(test_15) {
  s21_decimal num_1 = {{0, 0, 3, 0}};
  s21_decimal num_2 = {{3, 0, 0, 0}};
  s21_decimal result = {0};

  int res_code = s21_div(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
}
END_TEST

START_TEST(test_16) {
  s21_decimal num_1 = {{125, 0, 0, 0}};
  s21_decimal num_2 = {{15, 0, 0, 0}};
  s21_decimal result = {0};

  int res_code = s21_div(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
}
END_TEST

START_TEST(test_17) {
  s21_decimal num_1 = {{258762357, 0, 0, 0}};
  s21_decimal num_2 = {{92715829, 0, 0, 0}};
  s21_decimal result = {0};

  int res_code = s21_div(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
}
END_TEST

START_TEST(test_18) {
  s21_decimal num_1 = {{258762357, 0, 0, 0}};
  s21_decimal num_2 = {{-554643571, 215, 0, 0}};
  s21_decimal result = {0};

  int res_code = s21_div(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
}
END_TEST

START_TEST(test_19) {
  s21_decimal num_1 = {{3, 0, 0, 196608}};
  s21_decimal num_2 = {{-554643571, 215, 0, 0}};
  s21_decimal result = {0};

  int res_code = s21_div(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
}
END_TEST

START_TEST(test_20) {
  s21_decimal num_1 = {{-1, -1, -1, 0}};
  s21_decimal num_2 = {{3, 0, 0, 0}};
  s21_decimal result = {0};

  int res_code = s21_div(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
}
END_TEST

START_TEST(test_21) {
  s21_decimal num_1 = {{125, 0, 0, 0}};
  s21_decimal num_2 = {{3, 0, 0, 0}};
  s21_decimal result = {0};

  int res_code = s21_div(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
}
END_TEST

START_TEST(test_22) {
  s21_decimal num_1 = {{100, 0, 0, 0}};
  s21_decimal num_2 = {{3, 0, 0, 0}};
  s21_decimal result = {0};

  int res_code = s21_div(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
}
END_TEST

START_TEST(test_23) {
  s21_decimal num_1 = {{100, 0, 0, -2147483648}};
  s21_decimal num_2 = {{3, 0, 0, -2147483648}};
  s21_decimal result = {0};

  int res_code = s21_div(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
}
END_TEST

START_TEST(test_24) {
  s21_decimal num_1 = {{100000000, 0, 0, 0}};
  s21_decimal num_2 = {{3, 0, 0, -2147483648}};
  s21_decimal result = {0};

  int res_code = s21_div(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
}
END_TEST

START_TEST(test_25) {
  s21_decimal num_1 = {{100000000, 0, 0, -2147483648}};
  s21_decimal num_2 = {{30000, 0, 0, 0}};
  s21_decimal result = {0};

  int res_code = s21_div(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
}
END_TEST

START_TEST(test_26) {
  s21_decimal num_1 = {{15, 0, 0, 0}};
  s21_decimal num_2 = {{10, 0, 0, 0}};
  s21_decimal result = {0};

  int res_code = s21_div(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
}
END_TEST

START_TEST(test_27) {
  s21_decimal num_1 = {{15, 0, 0, 0}};
  s21_decimal num_2 = {{1000, 0, 0, 0}};
  s21_decimal result = {0};

  int res_code = s21_div(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
}
END_TEST

START_TEST(test_28) {
  s21_decimal num_1 = {{987654321, 0, 0, 0}};
  s21_decimal num_2 = {{123456789, 0, 0, 0}};
  s21_decimal result = {0};

  int res_code = s21_div(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
}
END_TEST

START_TEST(test_29) {
  s21_decimal num_1 = {{125, 0, 0, 0}};
  s21_decimal num_2 = {{10, 0, 0, 0}};
  s21_decimal result = {0};

  int res_code = s21_div(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
}
END_TEST

START_TEST(test_30) {
  s21_decimal num_1 = {{1265727253, 229956191, 0, 589824}};
  s21_decimal num_2 = {{-531432783, 28744523, 0, 589824}};
  s21_decimal result = {0};

  int res_code = s21_div(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
}
END_TEST

START_TEST(test_31) {
  s21_decimal num_1 = {{15, 0, 0, 0}};
  s21_decimal num_2 = {{125, 0, 0, 0}};
  s21_decimal result = {0};

  int res_code = s21_div(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
}
END_TEST

START_TEST(test_32) {
  s21_decimal num_1 = {{1, 0, 0, 1835008}};
  s21_decimal num_2 = {{1, 0, 0, 1835008}};
  s21_decimal result = {0};

  int res_code = s21_div(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
}
END_TEST

START_TEST(test_33) {
  s21_decimal num_1 = {{1, 0, 0, 1835008}};
  s21_decimal num_2 = {{2, 0, 0, 0}};
  s21_decimal result = {0};

  int res_code = s21_div(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
}
END_TEST

START_TEST(test_34) {
  s21_decimal num_1 = {{-1641299335, 1974798980, 468975097, -2146566144}};
  s21_decimal num_2 = {{-1647895021, 465593127, -413014535, -2145976320}};
  s21_decimal result = {0};

  int res_code = s21_div(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
}
END_TEST

START_TEST(test_35) {
  s21_decimal num_1 = {{71818791, -1377337568, 1220696712, -2146959360}};
  s21_decimal num_2 = {{2046630484, -1219338308, 876905378, 1048576}};
  s21_decimal result = {0};

  int res_code = s21_div(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
}
END_TEST

START_TEST(test_36) {
  s21_decimal num_1 = {{-1236516836, 1505416173, 1467175448, -2145845248}};
  s21_decimal num_2 = {{-980123790, -214756190, 2088886599, 262144}};
  s21_decimal result = {0};

  int res_code = s21_div(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
}
END_TEST

START_TEST(test_37) {
  s21_decimal num_1 = {{1206200230, -755381153, -429553693, -2145845248}};
  s21_decimal num_2 = {{-1394380167, 1061930675, 427657989, -2146959360}};
  s21_decimal result = {0};

  int res_code = s21_div(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
}
END_TEST

START_TEST(test_38) {
  s21_decimal num_1 = {{-262163820, 99833785, 642934634, -2147024896}};
  s21_decimal num_2 = {{-1193842237, -1272749176, -1517498943, 262144}};
  s21_decimal result = {0};

  int res_code = s21_div(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
}
END_TEST

START_TEST(test_39) {
  s21_decimal num_1 = {{789941267, 124687470, 2134298508, 1638400}};
  s21_decimal num_2 = {{1363698836, 1688945878, 1687418715, 327680}};
  s21_decimal result = {0};

  int res_code = s21_div(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
}
END_TEST

START_TEST(test_40) {
  s21_decimal num_1 = {{1870480705, 1681267546, 1986010352, 0}};
  s21_decimal num_2 = {{1743684613, 1338485643, 963117172, -2146959360}};
  s21_decimal result = {0};

  int res_code = s21_div(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
}
END_TEST

START_TEST(test_41) {
  s21_decimal num_1 = {{1464545097, 381486943, -1457508093, -2147221504}};
  s21_decimal num_2 = {{1070699014, -1917294781, -1451020091, 1048576}};
  s21_decimal result = {0};

  int res_code = s21_div(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
}
END_TEST

START_TEST(test_42) {
  s21_decimal num_1 = {{-1497382271, 951401017, 1701883950, -2146041856}};
  s21_decimal num_2 = {{-280410154, 624377478, -743150354, 1572864}};
  s21_decimal result = {0};

  int res_code = s21_div(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
}
END_TEST

START_TEST(test_43) {
  s21_decimal num_1 = {{1243935174, -1413685650, 118360552, 655360}};
  s21_decimal num_2 = {{-1578344803, -1706647318, -371900700, -2147287040}};
  s21_decimal result = {0};

  int res_code = s21_div(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
}
END_TEST

START_TEST(test_44) {
  s21_decimal num_1 = {{-1545676258, 485774650, -1697886816, -2147024896}};
  s21_decimal num_2 = {{360805690, 1995184227, -1127729269, -2146697216}};
  s21_decimal result = {0};

  int res_code = s21_div(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
}
END_TEST

START_TEST(test_45) {
  s21_decimal num_1 = {{1265727253, 229956191, 0, 589824}};
  s21_decimal num_2 = {{-531432783, 28744523, 0, 589824}};
  s21_decimal result = {0};

  int res_code = s21_div(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
}
END_TEST

START_TEST(test_46) {
  s21_decimal num_1 = {{-201781353, -627591504, -138155855, -2145910784}};
  s21_decimal num_2 = {{-532000358, -635646718, -1262683735, -2147483648}};
  s21_decimal result = {0};

  int res_code = s21_div(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
}
END_TEST

START_TEST(test_47) {
  s21_decimal num_1 = {{357312839, -1406876487, 886600856, -2145714176}};
  s21_decimal num_2 = {{-1580570890, -1764208409, 1064543710, -2146697216}};
  s21_decimal result = {0};

  int res_code = s21_div(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
}
END_TEST

START_TEST(test_48) {
  s21_decimal num_1 = {{-1747845031, 1863116172, -1168180170, 0}};
  s21_decimal num_2 = {{438444737, 932487449, 1302112110, 458752}};
  s21_decimal result = {0};

  int res_code = s21_div(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
}
END_TEST

START_TEST(test_49) {
  s21_decimal num_1 = {{968653181, -994690624, -1549533424, 1572864}};
  s21_decimal num_2 = {{607922416, 1816415363, 997106650, 0}};
  s21_decimal result = {0};

  int res_code = s21_div(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
}
END_TEST

START_TEST(test_50) {
  s21_decimal num_1 = {{2078828219, 1323220662, 1079459686, 1310720}};
  s21_decimal num_2 = {{-2008065905, -1393469691, 1435704635, 589824}};
  s21_decimal result = {0};

  int res_code = s21_div(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
}
END_TEST

START_TEST(test_51) {
  s21_decimal num_1 = {{1883022824, -1979523618, 37360257, 983040}};
  s21_decimal num_2 = {{1533934378, -1898648877, -1654590764, 262144}};
  s21_decimal result = {0};


  int res_code = s21_div(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
}
END_TEST

START_TEST(test_52) {
  s21_decimal num_1 = {{567407005, -2100899462, 378961768, 655360}};
  s21_decimal num_2 = {{-1946885802, -530604013, 224665207, -2146697216}};
  s21_decimal result = {0};

  int res_code = s21_div(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
}
END_TEST

START_TEST(test_53) {
  s21_decimal num_1 = {{82625857, 719179533, 293083563, 1769472}};
  s21_decimal num_2 = {{-2099990232, 1526316231, -648845376, 1638400}};
  s21_decimal result = {0};

  int res_code = s21_div(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
}
END_TEST

START_TEST(test_54) {
  s21_decimal num_1 = {{381487605, -2003799516, 368623971, 458752}};
  s21_decimal num_2 = {{248844296, 227032044, 323521285, 720896}};
  s21_decimal result = {0};

  int res_code = s21_div(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
}
END_TEST

START_TEST(test_55) {
  s21_decimal num_1 = {{844865444, 1145541890, 1151902113, -2147090432}};
  s21_decimal num_2 = {{-1900649374, -1692014530, 1953232443, -2147155968}};
  s21_decimal result = {0};

  int res_code = s21_div(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
}
END_TEST

START_TEST(test_56) {
  s21_decimal num_1 = {{-1715729846, -2106271899, -1818607331, 131072}};
  s21_decimal num_2 = {{2110943903, -1352309298, 1304335390, -2147352576}};
  s21_decimal result = {0};

  int res_code = s21_div(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
}
END_TEST

START_TEST(test_57) {
  s21_decimal num_1 = {{2120295747, -1471302785, -156504150, -2146500608}};
  s21_decimal num_2 = {{-433449025, -1982164600, 1192053391, 458752}};
  s21_decimal result = {0};

  int res_code = s21_div(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
}
END_TEST

START_TEST(test_58) {
  s21_decimal num_1 = {{1037087672, -1483521650, -1098324731, -2145714176}};
  s21_decimal num_2 = {{109427011, 800716759, -1225650131, 262144}};
  s21_decimal result = {0};

  int res_code = s21_div(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
}
END_TEST

START_TEST(test_59) {
  s21_decimal num_1 = {{1692969194, -1484405704, 1273572224, 1114112}};
  s21_decimal num_2 = {{1192070182, -19698963, 1198932854, 720896}};
  s21_decimal result = {0};

  int res_code = s21_div(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
}
END_TEST

START_TEST(test_60) {
  s21_decimal num_1 = {{-1332429500, -1788066737, 976485068, -2146107392}};
  s21_decimal num_2 = {{1504777922, 2136552186, 1795387132, -2146435072}};
  s21_decimal result = {0};

  int res_code = s21_div(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
}
END_TEST

START_TEST(test_61) {
  s21_decimal num_1 = {{1848546304, -280819311, 768832522, -2145648640}};
  s21_decimal num_2 = {{-1992540919, 198965295, 1783682665, -2146041856}};
  s21_decimal result = {0};

  int res_code = s21_div(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
}
END_TEST

START_TEST(test_62) {
  s21_decimal num_1 = {{1458494504, -1627747530, 164981608, 1638400}};
  s21_decimal num_2 = {{1434843504, -695168333, 1309934493, 1245184}};
  s21_decimal result = {0};

  int res_code = s21_div(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
}
END_TEST

START_TEST(test_73) {
  s21_decimal num_1 = {{-2095954756, -1070201828, 1489770052, -2145845248}};
  s21_decimal num_2 = {{-267260898, 725418822, -867579764, 589824}};
  s21_decimal result = {0};

  int res_code = s21_div(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
}
END_TEST

START_TEST(test_63) {
  s21_decimal num_1 = {{832666865, 2013574802, 1649546625, -2146566144}};
  s21_decimal num_2 = {{803139912, -1205242106, 340058332, -2146500608}};
  s21_decimal result = {0};

  int res_code = s21_div(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
}
END_TEST

START_TEST(test_64) {
  s21_decimal num_1 = {{-42971708, 1985512247, -240796934, 720896}};
  s21_decimal num_2 = {{1718887192, -909470324, -1921734474, 1245184}};
  s21_decimal result = {0};

  int res_code = s21_div(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
}
END_TEST

START_TEST(test_65) {
  s21_decimal num_1 = {{170411619, -316222172, -440773568, 65536}};
  s21_decimal num_2 = {{-1156075422, 1183127897, -1925510799, 589824}};
  s21_decimal result = {0};

  int res_code = s21_div(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
}
END_TEST

START_TEST(test_66) {
  s21_decimal num_1 = {{1282958772, -395837429, -20902902, 851968}};
  s21_decimal num_2 = {{1969671972, 115778610, 860092821, 983040}};
  s21_decimal result = {0};

  int res_code = s21_div(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
}
END_TEST

START_TEST(test_67) {
  s21_decimal num_1 = {{359873857, 482620122, 1380687829, -2147287040}};
  s21_decimal num_2 = {{32570533, -2129053404, 1149723045, 1245184}};
  s21_decimal result = {0};

  int res_code = s21_div(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
}
END_TEST

START_TEST(test_68) {
  s21_decimal num_1 = {{1848913336, 36387703, -1243742291, 0}};
  s21_decimal num_2 = {{-761065597, 490835372, -1982927025, 65536}};
  s21_decimal result = {0};

  int res_code = s21_div(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
}
END_TEST

START_TEST(test_69) {
  s21_decimal num_1 = {{124210470, -1466820235, 1904259641, -2146697216}};
  s21_decimal num_2 = {{-424079247, -398076964, 179138151, -2145714176}};
  s21_decimal result = {0};

  int res_code = s21_div(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
}
END_TEST

START_TEST(test_70) {
  s21_decimal num_1 = {{-116748148, -1136758324, 330230041, 851968}};
  s21_decimal num_2 = {{-1368533563, -1616518705, -1203320529, -2145779712}};
  s21_decimal result = {0};

  int res_code = s21_div(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
}
END_TEST

START_TEST(test_71) {
  s21_decimal num_1 = {{300781628, -782893715, 1906566761, -2146107392}};
  s21_decimal num_2 = {{1005228005, 1313272453, 281089824, -2145648640}};
  s21_decimal result = {0};

  int res_code = s21_div(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
}
END_TEST

START_TEST(test_72) {
  s21_decimal num_1 = {{-1805501953, 2083254768, 540916250, 1048576}};
  s21_decimal num_2 = {{1352946914, -949103767, -1273846379, 1638400}};
  s21_decimal result = {0};

  int res_code = s21_div(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
}
END_TEST

START_TEST(test_74) {
  s21_decimal num_1 = {{-1, -1, -1, 0}};
  s21_decimal num_2 = {{1, 0, 0, 131072}};
  s21_decimal result = {0};

  int res_code = s21_div(num_1, num_2, &result);
  ck_assert_int_eq(res_code, ERROR_OVERFLOW);
}
END_TEST

START_TEST(test_75) {
  s21_decimal num_1 = {{-1, -1, -1, -2147483648}};
  s21_decimal num_2 = {{1, 0, 0, 131072}};
  s21_decimal result = {0};

  int res_code = s21_div(num_1, num_2, &result);
  ck_assert_int_eq(res_code, ERROR_UNDERFLOW);
}
END_TEST

START_TEST(test_76) {
  // Decimal values:
  // num_1: -79228162514264337593543950335
  // num_2: 79228162514264337593543950335
  // result: -1

  s21_decimal num_1 = {{-1, -1, -1, -2147483648}};
  s21_decimal num_2 = {{-1, -1, -1, 0}};
  s21_decimal result = {0};

  int res_code = s21_div(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
}
END_TEST

START_TEST(test_77) {
  // Decimal values:
  // num_1: 0
  // num_2: -1
  // result: 0

  s21_decimal num_1 = {{0, 0, 0, 0}};
  s21_decimal num_2 = {{1, 0, 0, -2147483648}};
  s21_decimal result = {0};

  int res_code = s21_div(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
}
END_TEST

START_TEST(test_78) {
  // Decimal values:
  // num_1: 0
  // num_2: -1
  // result: 0

  s21_decimal num_1 = {{0, 0, 0, 0}};
  s21_decimal num_2 = {{1, 0, 0, -2147483648}};
  s21_decimal result = {0};

  int res_code = s21_div(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
}
END_TEST

START_TEST(test_79) {
  // Decimal values:
  // num_1: 0
  // num_2: 1
  // result: 0

  s21_decimal num_1 = {{0, 0, 0, -2147483648}};
  s21_decimal num_2 = {{1, 0, 0, 0}};
  s21_decimal result = {0};

  int res_code = s21_div(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
}
END_TEST

START_TEST(test_80) {
  // Decimal values:
  // num_1: 0
  // num_2: -1
  // result: 0

  s21_decimal num_1 = {{0, 0, 0, -2147483648}};
  s21_decimal num_2 = {{1, 0, 0, -2147483648}};
  s21_decimal result = {0};

  int res_code = s21_div(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
}
END_TEST

START_TEST(test_81) {
  // Decimal values:
  // num_1: экспонента более 28
  // num_2: 0.001
  // result: ошибка
  s21_decimal num_1 = {{55, 0, 0, 2835008}};
  s21_decimal num_2 = {{1, 0, 0, 196608}};
  s21_decimal result = {0};

  int res_code = s21_div(num_1, num_2, &result);
  ck_assert_int_eq(res_code, 4);
}
END_TEST

START_TEST(test_82) {
  // num_1: 10
  // num_2: 1.0000
  // result: 10

  s21_decimal num_1 = {{10, 0, 0, 0}};
  s21_decimal num_2 = {{10000, 0, 0, 262144}};
  s21_decimal result = {0};

  int res_code = s21_div(num_1, num_2, &result);
  ck_assert_int_eq(res_code, S21_DECIMAL_OK);
}
END_TEST

Suite *s21_div_tests(void) {
  Suite *s = suite_create("\033[1;35ms21_div\033[0m\n");
  TCase *testCase = tcase_create("s21_test_div");

  suite_add_tcase(s, testCase);
  tcase_add_test(testCase, test_0);
  tcase_add_test(testCase, test_1);
  tcase_add_test(testCase, test_2);
  tcase_add_test(testCase, test_3);
  tcase_add_test(testCase, test_4);
  tcase_add_test(testCase, test_5);
  tcase_add_test(testCase, test_6);
  tcase_add_test(testCase, test_7);
  tcase_add_test(testCase, test_8);
  tcase_add_test(testCase, test_9);
  tcase_add_test(testCase, test_10);
  tcase_add_test(testCase, test_11);
  tcase_add_test(testCase, test_12);
  tcase_add_test(testCase, test_13);
  tcase_add_test(testCase, test_14);
  tcase_add_test(testCase, test_15);
  tcase_add_test(testCase, test_16);
  tcase_add_test(testCase, test_17);
  tcase_add_test(testCase, test_18);
  tcase_add_test(testCase, test_19);
  tcase_add_test(testCase, test_20);
  tcase_add_test(testCase, test_21);
  tcase_add_test(testCase, test_22);
  tcase_add_test(testCase, test_23);
  tcase_add_test(testCase, test_24);
  tcase_add_test(testCase, test_25);
  tcase_add_test(testCase, test_26);
  tcase_add_test(testCase, test_27);
  tcase_add_test(testCase, test_28);
  tcase_add_test(testCase, test_29);
  tcase_add_test(testCase, test_30);
  tcase_add_test(testCase, test_31);
  tcase_add_test(testCase, test_32);
  tcase_add_test(testCase, test_33);
  tcase_add_test(testCase, test_34);
  tcase_add_test(testCase, test_35);
  tcase_add_test(testCase, test_36);
  tcase_add_test(testCase, test_37);
  tcase_add_test(testCase, test_38);
  tcase_add_test(testCase, test_39);
  tcase_add_test(testCase, test_40);
  tcase_add_test(testCase, test_41);
  tcase_add_test(testCase, test_42);
  tcase_add_test(testCase, test_43);
  tcase_add_test(testCase, test_44);
  tcase_add_test(testCase, test_45);
  tcase_add_test(testCase, test_46);
  tcase_add_test(testCase, test_47);
  tcase_add_test(testCase, test_48);
  tcase_add_test(testCase, test_49);
  tcase_add_test(testCase, test_50);
  tcase_add_test(testCase, test_51);
  tcase_add_test(testCase, test_52);
  tcase_add_test(testCase, test_53);
  tcase_add_test(testCase, test_54);
  tcase_add_test(testCase, test_55);
  tcase_add_test(testCase, test_56);
  tcase_add_test(testCase, test_57);
  tcase_add_test(testCase, test_58);
  tcase_add_test(testCase, test_59);
  tcase_add_test(testCase, test_60);
  tcase_add_test(testCase, test_61);
  tcase_add_test(testCase, test_62);
  tcase_add_test(testCase, test_63);
  tcase_add_test(testCase, test_64);
  tcase_add_test(testCase, test_65);
  tcase_add_test(testCase, test_66);
  tcase_add_test(testCase, test_67);
  tcase_add_test(testCase, test_68);
  tcase_add_test(testCase, test_69);
  tcase_add_test(testCase, test_70);
  tcase_add_test(testCase, test_71);
  tcase_add_test(testCase, test_72);
  tcase_add_test(testCase, test_73);
  tcase_add_test(testCase, test_74);
  tcase_add_test(testCase, test_75);
  tcase_add_test(testCase, test_76);
  tcase_add_test(testCase, test_77);
  tcase_add_test(testCase, test_78);
  tcase_add_test(testCase, test_79);
  tcase_add_test(testCase, test_80);
  tcase_add_test(testCase, test_81);
  tcase_add_test(testCase, test_82);
  
  return s;
}
