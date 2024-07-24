#include "s21_decimal.h"
#include "decimal_helper/s21_decimal_helper.h"
#include <stdlib.h>
#define DECIMAL_MAX_BITS 128

int s21_div_handle(s21_big_decimal value_2l, s21_big_decimal res, s21_big_decimal remainder, s21_decimal *result);
int s21_div_calc_fractional(s21_big_decimal *res, s21_big_decimal value_2l, s21_big_decimal *remainder);

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int result_code = 0;
    
    if (check_decimal(value_1) || check_decimal(value_2) || result == NULL) {
        result_code = 4;
    } else if (s21_is_equal(value_2, get_decimal_with_int_value(0))) {
        result_code = 3;
    } else {
        *result = get_new_decimal();
        int sign1 = get_decimal_sign(value_1), sign2 = get_decimal_sign(value_2);

        s21_big_decimal big_value_1 = {{get_new_decimal(), get_new_decimal()}};
        s21_big_decimal big_value_2 = {{get_new_decimal(), get_new_decimal()}};
        s21_decimal_equalize(value_1, value_2, &big_value_1, &big_value_2);

        s21_big_decimal div_remainder = {{get_new_decimal(), get_new_decimal()}};
        s21_big_decimal div_whole = {{get_new_decimal(), get_new_decimal()}};
        
        // Делим делимое на делитель. В div_whole будет целая часть деления
        // в div_remainder остаток от деления
        s21_big_div(big_value_1, big_value_2, &div_whole, &div_remainder);

        // Если целая часть деления не влезает в s21_decimal
        if (div_whole.decimal[0].bits[3] != 0 || !s21_is_full_equal_zero(div_whole.decimal[1])) {
            if (sign1 != sign2) {
                result_code = 2;
            } else {
                result_code = 1;
            }
        } else {
            // Получаем конечный результат на основе целой части деления и его остатка
            result_code = s21_div_handle(big_value_2, div_whole, div_remainder, result);

            // Если знаки делимого и делителя отличаются, то необходимо сделать результат отрицательным
            if (result_code == 0 && sign1 != sign2) {
                set_decimal_sign(result, 1);
            } else if (result_code == 1 && sign1 != sign2) {
                result_code = 2;
            }
        }
    }

    return result_code;
}

void s21_big_div(s21_big_decimal decimal1, s21_big_decimal decimal2, s21_big_decimal *div_whole, s21_big_decimal *div_remainder) {
    s21_big_decimal whole = {{get_new_decimal(), get_new_decimal()}}; // частное
    s21_big_decimal remainder = {{get_new_decimal(), get_new_decimal()}}; // остаток
    
    if (s21_is_less_big(decimal1, decimal2, 0, 0)) {
        remainder = decimal1;
    } else if (!s21_is_full_equal_zero(decimal1.decimal[0]) || !s21_is_full_equal_zero(decimal1.decimal[1])) {
        // Рассчитываем предварительный сдвиг делителя
        int left_1 = get_count_full_digits(decimal1.decimal[1]) - 1;
        left_1 = left_1 == -1 ? get_count_full_digits(decimal1.decimal[0]) - 1 : DECIMAL_MAX_BITS + left_1;

        int left_2 = get_count_full_digits(decimal2.decimal[1]) - 1;
        left_2 = left_2 == -1 ? get_count_full_digits(decimal2.decimal[0]) - 1 : DECIMAL_MAX_BITS + left_2;

        int shift = left_1 - left_2;

        s21_big_decimal shifted_divisor = s21_left_shift_big_decimal(decimal2, shift); // Сдвинутый делитель
        
        // Флаг необходимости проводить вычитание
        int is_current_sub = 1;
        // Повторяем действия k+1 раз (один раз пп.2-3 алгоритма и k раз пп.4-6)
        while (shift >= 0) {
            // Определяем необходимое действие (Прибавлять или вычитать Сдвинутый делитель)
            if (is_current_sub == 1) {
                remainder = s21_big_sub(decimal1, shifted_divisor);
            } else {
                remainder = s21_big_add(decimal1, shifted_divisor);
            }

            // Сдвигаем влево на 1 частное и записываем в младший бит результата 1,
            // если старший бит частичного остатка равен 1
            whole = s21_left_shift_big_decimal(whole, 1);
            if (!s21_get_bit(remainder.decimal[1].bits[3], 31)) {
                whole.decimal[0].bits[0] = s21_set_bit(whole.decimal[0].bits[0], 0);
            }

            // Рассчитываем делимое для следующей итерации цикла (сдвиг влево на 1 частичного остатка)
            decimal1 = s21_left_shift_big_decimal(remainder, 1);

            // Если старший бит частичного остатка равен 0, то на следующей итерации
            // необходимо проводить вычитание (Шаг 5 алгоритма)
            if (!s21_get_bit(remainder.decimal[1].bits[3], 31)) {
                is_current_sub = 1;
            } else {
                is_current_sub = 0;
            }
            shift--;
        }
    
        // Определяем, требуется ли коррекция остатка (п.8 алгоритма)
        if (s21_get_bit(remainder.decimal[1].bits[3], 31)) {
            remainder = s21_big_add(remainder, shifted_divisor);
        }

        // Возвращаем на место частичный остаток (п.9 алгоритма)
        remainder = s21_right_shift_big_decimal(remainder, left_1 - left_2);
    }

    // Заполняем переменные результата (частное и остаток)
    *div_whole = whole;
    *div_remainder = remainder;
}

// whole  цедая часть отделения  расчтиываем коолличестов раз сколько надо поделить на 10 чтобы влезло в децемал. возводим 10 в степень сколько раз поделил
//число которое после вычитания резаулт мы делим на возведенноую в степень 10 после чего я получу целую и дрбоную часть после чего я вызываю див хэндел
int s21_div_handle(s21_big_decimal value_2, s21_big_decimal whole, s21_big_decimal remainder, s21_decimal *result) {
    int result_code = 0;

    // рассчитываем дробную часть нашего результата и получаем в whole результат, включая дробную часть
    // после расчетов в remainder останется остаток от деления (который не поместился в дробную часть)
    // power1 - значение степени результата
    int power1 = s21_div_calc_fractional(&whole, value_2, &remainder);

    s21_big_decimal second_remainder = {{get_new_decimal(), get_new_decimal()}};

    // Переводим остаток, полученный в расчете выше, в decimal, чтобы использовать его для округления
    // power2 - значение степени данного decimal
    int power2 = s21_div_calc_fractional(&second_remainder, value_2, &remainder);

    // Устанавливаем полученную степень для нашего остатка
    set_decimal_exponent(&second_remainder.decimal[0], power2);
    
    // Выполняем банковское округления результата, исходя из остатка от деления
    whole = s21_round_banking(whole.decimal[0], second_remainder.decimal[0]);

    // Устанавливаем степень результата
    if (!s21_is_full_equal_zero(whole.decimal[0])) {
        set_decimal_exponent(&whole.decimal[0], power1);
        whole.decimal[0] = s21_remove_useless_zeros(whole.decimal[0]);
    }
    
    // Анализируем результат на корректность (переполнение)
    if (!s21_is_full_equal_zero(whole.decimal[1]) || check_decimal(whole.decimal[0])
        || s21_get_range_bits(whole.decimal[0].bits[3], 0, 15) != 0
        || s21_get_range_bits(whole.decimal[0].bits[3], 24, 30) != 0) {
        result_code = 1;
    } else {
        *result = whole.decimal[0];
    }

    return result_code;
}

/// @brief Высчитывание дробной части на основе остатка и запись её в res
/// @param res целая часть деления
/// @param value_2l делитель
/// @param remainder остаток от деления
/// @return количество знаков после запятой у res
int s21_div_calc_fractional(s21_big_decimal *result, s21_big_decimal value_2l, s21_big_decimal *remainder) {
    int exponent = 0;
    
    s21_big_decimal ten_decimal = {{get_decimal_with_int_value(10), get_new_decimal()}};
    
    // Пока остаток не равен 0 или пока decimal не переполнен
    int is_end = 0;
    while ((!s21_is_full_equal_zero(remainder->decimal[0]) || !s21_is_full_equal_zero(remainder->decimal[1]))
            && exponent < 28 && !is_end) {
        // Сохранение чисел, чтобы их вернуть, если будет переполнение decimal
        s21_big_decimal prev_result = *result;
        s21_big_decimal prev_remainder = *remainder;

        // Готовим место под новое число
        *result = s21_big_mul(*result, ten_decimal);
        // Умножаем текущий остаток на 10
        *remainder = s21_big_mul(*remainder, ten_decimal);

        // Делим остаток на делитель и получаем целую часть и остаток
        s21_big_decimal tmp_div_whole = {{get_new_decimal(), get_new_decimal()}};
        s21_big_div(*remainder, value_2l, &tmp_div_whole, remainder);

        // Целую часть от деления прибавляем к результату
        *result = s21_big_add(*result, tmp_div_whole);

        // Если decimal переполнен, то возвращаем предыдущий результат и выходим из цикла
        if (check_decimal(result->decimal[0]) || s21_get_range_bits(result->decimal[0].bits[3], 0, 15) != 0
            || s21_get_range_bits(result->decimal[0].bits[3], 24, 30) != 0) {
            *result = prev_result;
            *remainder = prev_remainder;

            is_end = 1;
        } else {
            exponent++;
        }
    }

    return exponent;
}