// #include "s21_decimal.h"
// #include "decimal_helper/s21_decimal_helper.h"

// int s21_truncate(s21_decimal value, s21_decimal *result) {
//     int result_code = 0;

//     if (result == NULL || check_decimal(value)) {
//         result_code = 1;
//     } else {
//         clear_decimal(result);

//         int current_exponent = get_decimal_exponent(value);
//         set_decimal_exponent(&value, 0);

//         s21_decimal decimal_ten_div = get_new_decimal();
//         s21_from_int_to_decimal(10, &decimal_ten_div);

//         while (current_exponent > 0) {
//             s21_div(value, decimal_ten_div, &value);

//             current_exponent--;
//         }

//         *result = value;
//     }

//     return result_code;
// }