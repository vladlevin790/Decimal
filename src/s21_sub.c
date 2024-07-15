#include "s21_decimal.h"
#include "binary/s21_binary.h"
#include "decimal_helper/s21_decimal_helper.h"

void helper_sub(int *digit, int index); // функция которая ищет у какого индекса числа можно занять десяток "1" если находит заменяет еденицу "0"
// далее бежит назад от наеденного индекса до начального индекса при этом попутно заменяя индексы которые были пропущены так как уних нельзя было занять десяток 
// были равны 0, на еденицы (1), 
void logic_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result); // не посредсвтенно осуществляет вычитаниеи
int cheak_res_on_zero(s21_decimal *res); // проверяет не равен ли результат нулю и если стояло отрицательное число убирает знак. 

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    if (check_decimal(value_1) || check_decimal(value_2) || result == NULL) {
        printf("в папраметр функции sub_21 передан неверный параметр (resualt == NULL, либо ошибка в экспоненте value1 или value 2)");
        return 9;
    }
    else {
        if (get_decimal_exponent(value_1) != get_decimal_exponent(value_2)) EXPONENT_N(&value_1, &value_2);
        for (int i = 0; i<3; result->bits[i]=0, i++); // за нуляем структуру result
        // if (((value_1.bits[3] >> 31) & 1) == 0 &&  ((value_2.bits[3] >> 31) & 1) == 0 ) { // если оба числа положительные
        if (get_decimal_sign(value_1) == 0 &&  get_decimal_sign(value_2) == 0) { // если оба числа положительные
            printf("ОБА ЧИСЛА ПОЛОЖИТЕЛЬНЫЕ\n");
            if (comparison_of_numbers(value_1,value_2) == 1) {
                swap(&value_1, &value_2); // число 1 меньше второго меняем местами;
                set_decimal_sign(result, 1); // меняем знаковый бит число отрицательное;
            }
            logic_sub(value_1, value_2, result);
        }
        else if (get_decimal_sign(value_1) == 1 &&  get_decimal_sign(value_2) == 1) { 
            printf("ОБА ЧИСЛА ОТРИЦАТЕЛЬНЫЕ\n");
            if (comparison_of_numbers(value_1,value_2) == 1) {
                swap(&value_1, &value_2); // число 1 меньше второго меняем местами;
                // set_decimal_sign(result, 0); // меняем знаковый бит число отрицательное;
                logic_sub(value_1, value_2, result); // число положительное
            }
            else {
                logic_sub(value_1, value_2, result);
                set_decimal_sign(result, 1); // число отрицательное;
            }

        }
        else { // если одно из чисел отрицательное if (get_decimal_sign(value_1) == 1 ||  get_decimal_sign(value_2) == 1) 
            printf("одно из чисел ОТРИЦАТЕЛЬНое\n");
            if (comparison_of_numbers(value_1, value_2) == 1) { // если value2 больше
                if (get_decimal_sign(value_2) == 1) {
                    set_decimal_sign(&value_2, 0);
                    s21_add(value_1, value_2, result);
                    set_decimal_sign(result, 0);
                } else {
                    set_decimal_sign(&value_1, 0);
                    s21_add(value_1, value_2, result);
                    set_decimal_sign(result, 1);
                }
            }else { // если value1 больше
                if (get_decimal_sign(value_1) == 1) {
                    set_decimal_sign(&value_1, 0);
                    s21_add(value_1, value_2, result);
                    set_decimal_sign(result, 1);
                } else {
                    set_decimal_sign(&value_2, 0);
                    s21_add(value_1, value_2, result);
                    set_decimal_sign(result, 0);
                }
            }
        }
    }
    cheak_res_on_zero(result); //проверка ответа на ноль если ноль и имеется знак минус меняем на плюс
    set_decimal_exponent(result, get_decimal_exponent(value_1)); //добавляем экспоненту в resault
return 0;
}

void logic_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result){ // не посредственно осуществляет вычитание
for (int i = 2; i>=0; i--) { 
    for (int j = 0; j<= 31; j++) {
        if ((s21_get_bit(value_1.bits[i], j) == 0) & (s21_get_bit(value_2.bits[i], j) == 1)) {
        helper_sub(&value_1.bits[i], j);
        result->bits[i] = s21_set_bit(result->bits[i], j);
        }
        else if((s21_get_bit(value_1.bits[i], j) == 1) & (s21_get_bit(value_2.bits[i], j) == 1)) {
            result->bits[i] = s21_clear_bit(result->bits[i], j);
            }
        else if((s21_get_bit(value_1.bits[i], j) == 1) & (s21_get_bit(value_2.bits[i], j) == 0)) {
            result->bits[i] = s21_set_bit(result->bits[i], j);
            }
        }
    }
}

int cheak_res_on_zero(s21_decimal *res) {
if (get_decimal_sign(*res) == 1) {
    for (int i = 2; i>=0; i--) { 
        for (int j = 0; j<= 31; j++) {
            if (s21_get_bit(res->bits[i], j) == 1) return 1;
        }
    }
    set_decimal_sign(res, 0);
}
return 0;
}

void helper_sub(int *digit, int index) { // функция которая ищет у какого индекса числа можно занять десяток "1" если находит заменяет еденицу "0"
// далее бежит назад от наеденного индекса до начального индекса при этом попутно заменяя индексы которые были пропущены так как уних нельзя было занять десяток 
// были равны 0, на еденицы (1), 
    int s_index; // переменаая для индекса первого вхождения еденицы;
    int d = *digit; //За сейвил на всякий случай на входе значение числа
    for (int i = (index + 1); i < 33 ; i++) {
        if (s21_get_bit(d, i) == 1) {s_index = i; break;}
        s_index = i; // выполниться если не найдеться бита у кторого можно занять еденицу;
    }
    *digit = s21_clear_bit(*digit, s_index);
    for (int i = s_index-1; i >= index; i--) {
        *digit = s21_set_bit(*digit, i); // устанавливаем биты у которых не могли занять десяток в 1
    }
    // *digit = s21_set_bit(*digit, index); // устанавливаем начальный бит в 1
}
