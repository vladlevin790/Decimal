#include "s21_decimal.h"

#include <math.h>
#include <stdio.h>

#include "binary/s21_binary.h"
#include "decimal_helper/s21_decimal_helper.h"

// int get_bit(s21_decimal number, int bit) {
//   int sign;
//   if ((number.bits[bit / 32] & (1 << bit % 32)) == 0) {
//     sign = 0;
//   } else {
//     sign = 1;
//   }
//   return sign;
// }

// void set_bit(s21_decimal *number, int bit, int sign) {
//   if (sign == 0) {
//     number->bits[bit / 32] = number->bits[bit / 32] & ~(1 << bit % 32);
//   } else {
//     number->bits[bit / 32] = number->bits[bit / 32] | (1 << bit % 32);
//   }
// }

// void initial_num(s21_decimal *number) {
//   for (int i = 0; i < 128; i++) {
//     set_bit(number, i, 0);
//   }
// }

// int s21_is_less_simple(s21_decimal value_1, s21_decimal value_2) {
//   int is_less = FALSE;
//   for (int i = 95; i >= 0; i--) {
//     if (get_bit(value_1, i) ^ get_bit(value_2, i)) {
//       is_less = get_bit(value_2, i);
//       break;
//     }
//   }

//   return is_less;
// }

// int s21_is_less_or_equal_simple(s21_decimal value_1, s21_decimal value_2) {
//   return s21_is_less_simple(value_1, value_2) || s21_is_equal(value_1, value_2);
// }

// int s21_is_greater_simple(s21_decimal value_1, s21_decimal value_2) {
//   return !s21_is_less_or_equal_simple(value_1, value_2);
// }

// int s21_is_greater_or_equal_simple(s21_decimal value_1, s21_decimal value_2) {
//   return s21_is_greater_simple(value_1, value_2) || s21_is_equal(value_1, value_2);
// }

// int s21_add_simple(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
//   initial_num(result);
//   int rank = 0;
//   for (int i = 0; i < 96; i++) {
//     int bit_value_1 = get_bit(value_1, i);
//     int bit_value_2 = get_bit(value_2, i);

//     set_bit(result, i, bit_value_1 ^ bit_value_2 ^ rank);

//     rank = (bit_value_1 && bit_value_2) || (bit_value_1 && rank) || (bit_value_2 && rank);
//   }

//   return rank;
// }

// void s21_sub_simple(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
//   initial_num(result);
//   for (int i = 0; i < 96; i++) {
//     int bit_value_1 = get_bit(value_1, i);
//     int bit_value_2 = get_bit(value_2, i);

//     set_bit(result, i, bit_value_1 ^ bit_value_2);

//     if (!bit_value_1 && bit_value_2) {
//       int k = i + 1;
//       while ((bit_value_1 = get_bit(value_1, k)) != 1) {
//         set_bit(&value_1, k, 1);
//         k++;
//       }
//       set_bit(&value_1, k, 0);
//     }
//   }
// }

// int shift_left(s21_decimal *number) {
//   int is_overflow = get_bit(*number, 95);
//   for (int i = 95; i >= 0; i--) {
//     if (i != 0) {
//       set_bit(number, i, get_bit(*number, i - 1));
//     } else {
//       set_bit(number, i, 0);
//     }
//   }
//   return is_overflow;
// }

// int shift_right(s21_decimal *number) {
//   int is_overflow = get_bit(*number, 1);
//   for (int i = 0; i < 96; i++) {
//     if (i != 95) {
//       set_bit(number, i, get_bit(*number, i + 1));
//     } else {
//       set_bit(number, i, 0);
//     }
//   }
//   return is_overflow;
// }

// int s21_mul_simple(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
//   s21_decimal tmp;
//   initial_num(&tmp);
//   int is_owerfull = 0;
//   for (int i = 0; i < 96 && !is_owerfull; i++) {
//     if (get_bit(value_2, i) == 1) {
//       s21_decimal temp = value_1;
//       int k = 0;
//       while (k < i) {
//         if (shift_left(&temp)) {
//           is_owerfull = 1;
//           break;
//         }
//         k++;
//       }
//       if (is_owerfull || (is_owerfull = s21_add_simple(temp, tmp, &tmp))) {
//         break;
//       }
//     }
//   }

//   if (!is_owerfull)
//     *result = tmp;

//   return is_owerfull;
// }

// s21_decimal s21_div_simple(s21_decimal value_1, s21_decimal value_2,
//                            s21_decimal *result) {
//   if (result)
//     initial_num(result);
//   s21_decimal fmod = {0};
//   s21_decimal temp = {0};
//   if (s21_is_greater_or_equal_simple(value_1, value_2))
//     set_bit(&temp, 0, 1);
//   if (!s21_is_greater_simple(value_2, value_1)) {
//     while (1) {
//       s21_decimal copy_value_2 = value_2;
//       while (s21_is_greater_or_equal_simple(value_1, copy_value_2) &&
//              !(get_bit(value_1, 95) && get_bit(copy_value_2, 95))) {
//         shift_left(&copy_value_2);
//         shift_left(&temp);
//       }

//       if (!(get_bit(value_1, 95) && get_bit(copy_value_2, 95)) ||
//           (s21_is_greater_or_equal_simple(copy_value_2, value_1))) {
//         shift_right(&copy_value_2);
//         shift_right(&temp);
//       }

//       s21_sub_simple(value_1, copy_value_2, &value_1);
//       if (result)
//         s21_add_simple(*result, temp, result);
//       initial_num(&temp);
//       set_bit(&temp, 0, 1);
//       if (s21_is_less_simple(value_1, value_2)) {
//         break;
//       }
//     }
//   }
//   fmod = value_1;
//   return fmod;
// }

// // void s21_bank_rounding(s21_decimal *value, int count) {
// //   int system_bit = value->bits[3];
// //   int exp = get_decimal_exponent(*value) - count;
// //   while (count > 0) {
// //     s21_decimal base = {0}, one = {0}, two = {0}, two_res = {0};
// //     s21_from_int_to_decimal(10, &base);
// //     s21_from_int_to_decimal(1, &one);
// //     s21_from_int_to_decimal(2, &two);
// //     s21_decimal dec_mod = s21_div_simple(*value, base, value);
// //     if (dec_mod.bits[0] > 5) {
// //       s21_add_simple(*value, one, value);
// //     } else if (dec_mod.bits[0] == 5) {
// //       two_res = s21_div_simple(*value, two, NULL);
// //       if (s21_is_equal(one, two_res))
// //         s21_add_simple(*value, one, value);
// //     }
// //     count--;
// //   }
// //   value->bits[3] = system_bit;
// //   set_decimal_exponent(value, exp);
// // }

// // void s21_bank_rounding(s21_decimal *value, int count) {
// //   int system_bit = value->bits[3];
// //   int exp = get_decimal_exponent(*value) - count;

// //   while (count > 0) {
// //     s21_decimal base = {0}, one = {0}, two = {0}, two_res = {0};
// //     s21_from_int_to_decimal(10, &base);
// //     s21_from_int_to_decimal(1, &one);
// //     s21_from_int_to_decimal(2, &two);

// //     s21_decimal dec_mod = s21_div_simple(*value, base, value);
// //     s21_decimal half_base;
// //     s21_from_int_to_decimal(5, &half_base);

// //     if (s21_is_greater_simple(dec_mod, half_base)) {
// //       s21_add_simple(*value, one, value);
// //     } else if (s21_is_equal(dec_mod, half_base)) {
// //       two_res = s21_div_simple(*value, two, s21_NULL);
// //       if (s21_is_equal(one, two_res) || (get_bit(*value, 0) == 1)) {
// //         s21_add_simple(*value, one, value);
// //       }
// //     }

// //     count--;
// //   }

// //   value->bits[3] = system_bit;
// //   set_decimal_exponent(value, exp);
// // }
// void s21_bank_rounding(s21_decimal *value, int count) {
//     int system_bit = value->bits[3];
//     int exp = get_decimal_exponent(*value) - count;

//     while (count > 0) {
//         s21_decimal base = {0}, one = {0}, two = {0};
//         s21_from_int_to_decimal(10, &base);
//         s21_from_int_to_decimal(1, &one);
//         s21_from_int_to_decimal(2, &two);

//         s21_decimal dec_mod = s21_div_simple(*value, base, value);
//         s21_decimal half_base;
//         s21_from_int_to_decimal(5, &half_base);

//         if (s21_is_greater_simple(dec_mod, half_base)) {
//             s21_add_simple(*value, one, value);
//         } else if (s21_is_equal(dec_mod, half_base)) {
//             s21_decimal two_times_mod = {0};
//             s21_mul_simple(dec_mod, two, &two_times_mod);
//             if (get_bit(two_times_mod, 0) == 1) { // проверяем нечетность
//                 s21_add_simple(*value, one, value);
//             }
//         }

//         count--;
//     }

//     value->bits[3] = system_bit;
//     set_decimal_exponent(value, exp);
// }


// // этот код решает проблем с округлением 
// // в test_2 test_27 test_32 test_33. Но тогда падают 31 других тестов
// // небанковское округление
// // void s21_bank_rounding(s21_decimal *value, int count) {
// //     int exp = get_decimal_exponent(*value);
// //     int new_exp = exp - count;

// //     while (count > 0) {
// //         s21_decimal base = {0}, half = {0}, remainder = {0};
// //         s21_from_int_to_decimal(10, &base);
// //         s21_from_int_to_decimal(5, &half);

// //         // Деление на 10
// //         s21_decimal quotient = s21_div_simple(*value, base, value);
// //         s21_decimal mod = s21_div_simple(*value, base, &remainder);
        
// //         // Округление
// //         if (s21_is_greater_simple(mod, half)) {
// //             s21_decimal one = {0};
// //             s21_from_int_to_decimal(1, &one);
// //             s21_add_simple(*value, one, value);
// //         } else if (s21_is_equal(mod, half)) {
// //             s21_decimal two = {0}, double_mod = {0};
// //             s21_from_int_to_decimal(2, &two);
// //             s21_mul_simple(mod, two, &double_mod);
// //             if (get_bit(double_mod, 0) == 1) {
// //                 s21_decimal one = {0};
// //                 s21_from_int_to_decimal(1, &one);
// //                 s21_add_simple(*value, one, value);
// //             }
// //         }

// //         count--;
// //     }

// //     set_decimal_exponent(value, new_exp);
// // }


// void normalize(s21_decimal *value_1, s21_decimal *value_2) {
//   int scl1 = get_decimal_exponent(*value_1);
//   int scl2 = get_decimal_exponent(*value_2);

//   int v1 = value_1->bits[3];
//   int v2 = value_2->bits[3];

//   int min_scl = (scl1 < scl2) ? scl1 : scl2;
//   int max_scl = (scl1 > scl2) ? scl1 : scl2;
//   s21_decimal *min_val = (scl1 < scl2) ? value_1 : value_2;
//   s21_decimal *max_val = (scl1 > scl2) ? value_1 : value_2;
//   s21_decimal ten;
//   s21_from_int_to_decimal(10, &ten);

//   while (min_scl != max_scl) {
//     if (min_scl < 28 && !s21_mul_simple(*min_val, ten, min_val)) {
//       min_scl++;
//       set_decimal_exponent(min_val, min_scl);
//     } else {
//       s21_bank_rounding(max_val, max_scl - min_scl);
//       break;
//     }
//   }

//   value_1->bits[3] = v1;
//   value_2->bits[3] = v2;
//   set_decimal_exponent(min_val, min_scl);
//   set_decimal_exponent(max_val, min_scl);
// }

// // int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
// //   if (result == s21_NULL) {
// //     return 1;
// //   }

// //   int s21_add_res_code = S21_DECIMAL_OK;

// //   normalize(&value_1, &value_2);
// //   int exp = get_decimal_exponent(value_1);
// //   int sign_1 = get_decimal_sign(value_1);
// //   int sign_2 = get_decimal_sign(value_2);

// //   if (!(sign_1 ^ sign_2)) {
// //     s21_add_res_code = s21_add_simple(value_1, value_2, result);
// //     set_decimal_sign(result, sign_1);
// //     if (s21_add_res_code && sign_1 && sign_2) {
// //       s21_add_res_code = ERROR_UNDERFLOW;
// //     }
// //   } else if (s21_is_less_or_equal_simple(value_1, value_2)) {
// //     s21_sub_simple(value_2, value_1, result);
// //     set_decimal_sign(result, sign_2);
// //   } else {
// //     s21_sub_simple(value_1, value_2, result);
// //     set_decimal_sign(result, sign_1);
// //   }

// //   if (s21_add_res_code && get_decimal_exponent(value_1)) {
// //     s21_bank_rounding(&value_1, 1);
// //     s21_bank_rounding(&value_2, 1);
// //     s21_add_res_code = s21_add(value_1, value_2, result);
// //   } else {
// //     set_decimal_exponent(result, exp);
// //   }

// //   return s21_add_res_code;
// // }

// int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
//   if (result == s21_NULL) {
//     return 1;
//   }
//   int s21_s21_add_res_code = S21_DECIMAL_OK;

//   normalize(&value_1, &value_2);
//   int exp = get_decimal_exponent(value_1);
//   int sign_1 = get_decimal_sign(value_1);
//   int sign_2 = get_decimal_sign(value_2);

//   if (!(sign_1 ^ sign_2)) {
//     s21_s21_add_res_code = s21_add_simple(value_1, value_2, result);
//     set_decimal_sign(result, sign_1);
//     if (s21_s21_add_res_code) {
//       // Если переполнение, результат в ноль . Нужно ли так?
//       initial_num(result);
//       if (sign_1 && sign_2) {
//         s21_s21_add_res_code = ERROR_UNDERFLOW;
//       } else {
//         s21_s21_add_res_code = ERROR_OVERFLOW;
//       }
//     }
//   } else if (s21_is_less_or_equal_simple(value_1, value_2)) {
//     s21_sub_simple(value_2, value_1, result);
//     set_decimal_sign(result, sign_2);
//   } else {
//     s21_sub_simple(value_1, value_2, result);
//     set_decimal_sign(result, sign_1);
//   }

//   if (s21_s21_add_res_code && get_decimal_exponent(value_1)) {
//     s21_bank_rounding(&value_1, 1);
//     s21_bank_rounding(&value_2, 1);
//     s21_s21_add_res_code = s21_add(value_1, value_2, result);
//   } else {
//     set_decimal_exponent(result, exp);
//   }

//   return s21_s21_add_res_code;
// }




// 47 из 78 *******************************************************
// int s21_add_handle(s21_big_decimal big_result, int result_exponent, int count_out_bounds, s21_decimal *result) {
//     int result_code = 0;

//     s21_big_decimal ten_big_decimal = {{get_decimal_with_int_value(10), get_new_decimal()}};

//     if (result_exponent > 28) {
//         count_out_bounds = result_exponent - 28 + count_out_bounds;
//         result_exponent = 28;
//     }

//     while (count_out_bounds > 17) {
//         s21_big_decimal tmp = {{get_new_decimal(), get_new_decimal()}};
//         s21_big_div(big_result, ten_big_decimal, &big_result, &tmp);
//         count_out_bounds--;
//     }

//     s21_big_decimal remainder = {{get_new_decimal(), get_new_decimal()}};
//     s21_big_decimal powerten = get_big_decimal_ten_pow(count_out_bounds);

//     s21_big_div(big_result, powerten, &big_result, &remainder);
//     set_decimal_exponent(&(remainder.decimal[0]), count_out_bounds);
//     big_result.decimal[0] = s21_round_banking(big_result.decimal[0], remainder.decimal[0]);

//     if (!s21_is_full_equal_zero(big_result.decimal[1]) || check_decimal(big_result.decimal[0]) ||
//         s21_get_range_bits(big_result.decimal[0].bits[3], 0, 15) || s21_get_range_bits(big_result.decimal[0].bits[3], 24, 30)) {
//         result_code = 1;
//     } else {
//         *result = big_result.decimal[0];
//         set_decimal_exponent(result, result_exponent);

//         if (s21_is_equal(*result, get_decimal_with_int_value(0)) && s21_is_equal(remainder.decimal[0], get_decimal_with_int_value(0))) {
//             *result = s21_remove_useless_zeros(*result);
//         }
//     }

//     return result_code;
// }

// int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
//     if (check_decimal(value_1) || check_decimal(value_2) || result == NULL) {
//         return 1;
//     }
    
//     int sign_1 = get_decimal_sign(value_1);
//     int sign_2 = get_decimal_sign(value_2);

//     s21_decimal zero = get_decimal_with_int_value(0);

//     if (s21_is_equal(value_1, zero)) {
//         *result = value_2;
//         return 0;
//     } else if (s21_is_equal(value_2, zero)) {
//         *result = value_1;
//         return 0;
//     }

//     if (sign_1 == sign_2) {
//         s21_big_decimal big_value_1 = {{value_1, zero}};
//         s21_big_decimal big_value_2 = {{value_2, zero}};
//         s21_decimal_equalize(value_1, value_2, &big_value_1, &big_value_2);

//         s21_big_decimal big_result = s21_big_add(big_value_1, big_value_2);
//         set_decimal_sign(&(big_result.decimal[0]), sign_1);

//         int result_exponent = get_decimal_exponent(value_1); // We use equalized exponents
//         int count_out_bounds = s21_count_digits_out_bounds(big_result);

//         return s21_add_handle(big_result, result_exponent, count_out_bounds, result);
//     } else {
//         if (s21_is_greater_or_equal(value_1, value_2)) {
//             s21_big_decimal big_value_1 = {{value_1, zero}};
//             s21_big_decimal big_value_2 = {{value_2, zero}};
//             s21_decimal_equalize(value_1, value_2, &big_value_1, &big_value_2);

//             s21_big_decimal big_result = s21_big_sub(big_value_1, big_value_2);
//             set_decimal_sign(&(big_result.decimal[0]), sign_1);

//             int result_exponent = get_decimal_exponent(value_1); // We use equalized exponents
//             int count_out_bounds = s21_count_digits_out_bounds(big_result);

//             return s21_add_handle(big_result, result_exponent, count_out_bounds, result);
//         } else {
//             s21_big_decimal big_value_1 = {{value_1, zero}};
//             s21_big_decimal big_value_2 = {{value_2, zero}};
//             s21_decimal_equalize(value_1, value_2, &big_value_1, &big_value_2);

//             s21_big_decimal big_result = s21_big_sub(big_value_2, big_value_1);
//             set_decimal_sign(&(big_result.decimal[0]), sign_2);


//             int result_exponent = get_decimal_exponent(value_2); // We use equalized exponents
//             int count_out_bounds = s21_count_digits_out_bounds(big_result);

//             return s21_add_handle(big_result, result_exponent, count_out_bounds, result);
//         }
//     }
// }
// ******************************************************************

int s21_add_handle(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int result_code = 0;

    if (check_decimal(value_1) || check_decimal(value_2) || result == NULL) {
        result_code = 4;
    } else {
        int sign_1 = get_decimal_sign(value_1), sign_2 = get_decimal_sign(value_2);

        // + +    a + b
        // + -    a - b    5 - 3
        // - +    b - a    -5 + 3
        // - -    a + b
        if (sign_1 == 0 && sign_2 == 0) {
            result_code = s21_add_handle(value_1, value_2, result);
        } else if (sign_1 == 0 && sign_2 == 1) {
            set_decimal_sign(&value_2, 0);
            result_code = s21_sub(value_1, value_2, result);
        } else if (sign_1 == 1 && sign_2 == 0) {
            set_decimal_sign(&value_1, 0);
            result_code = s21_sub(value_2, value_1, result);
        } else if (sign_1 == 1 && sign_2 == 1) {
            set_decimal_sign(&value_1, 0);
            set_decimal_sign(&value_2, 0);
            
            result_code = s21_add_handle(value_1, value_2, result);
            if (result_code == 0) {
                set_decimal_sign(result, 1);
            } else if (result_code == 1) {
                result_code = 2;
            }
        }
    }

    return result_code;
}

int s21_add_handle(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int result_code = 0;

    int exponent_1 = get_decimal_exponent(value_1), exponent_2 = get_decimal_exponent(value_2);
    int result_exponent = exponent_1 > exponent_2 ? exponent_1 : exponent_2;

    s21_big_decimal big_value_1 = {{get_new_decimal(), get_new_decimal()}};
    s21_big_decimal big_value_2 = {{get_new_decimal(), get_new_decimal()}};
    s21_decimal_equalize(value_1, value_2, &big_value_1, &big_value_2);

    s21_big_decimal big_result = s21_big_add(big_value_1, big_value_2);

    int count_out_bounds = s21_count_digits_out_bounds(big_result);
    result_exponent -= count_out_bounds;

    if (result_exponent < 0) {
        result_code = 1;
    } else {
        s21_big_decimal div_whole = {{get_new_decimal(), get_new_decimal()}};
        s21_big_decimal div_remainder = {{get_new_decimal(), get_new_decimal()}};
        s21_big_div(big_result, s21_get_big_decimal_ten_pow(count_out_bounds), &div_whole, &div_remainder);
        //print_big_decimal(div_whole);
        //print_big_decimal(div_remainder);

        set_decimal_exponent(&div_remainder.decimal[0], count_out_bounds);
        div_whole = s21_round_banking(div_whole.decimal[0], div_remainder.decimal[0]);

        if (!s21_is_full_equal_zero(div_whole.decimal[1]) || div_whole.decimal[0].bits[3] != 0) {
            result_code = 1;
        } else {
            *result = div_whole.decimal[0];
            set_decimal_exponent(result, result_exponent);
        }
    }

    return result_code;
}

s21_big_decimal s21_big_add(s21_big_decimal value_1, s21_big_decimal value_2) {
    s21_big_decimal carry = {{get_new_decimal(), get_new_decimal()}};
    
    while (!s21_is_full_equal_zero(value_2.decimal[0]) || !s21_is_full_equal_zero(value_2.decimal[1])) {
        carry.decimal[0] = s21_decimal_and(value_1.decimal[0], value_2.decimal[0]);
        carry.decimal[1] = s21_decimal_and(value_1.decimal[1], value_2.decimal[1]);

        value_1.decimal[0] = s21_decimal_xor(value_1.decimal[0], value_2.decimal[0]);
        value_1.decimal[1] = s21_decimal_xor(value_1.decimal[1], value_2.decimal[1]);

        value_2 = s21_left_shift_big_decimal(carry, 1);
    }
    
    return value_1;
}