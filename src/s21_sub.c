#include "s21_decimal.h"
#include "binary/s21_binary.h"
#include "decimal_helper/s21_decimal_helper.h"

int comparison_of_numbers(s21_decimal value_1, s21_decimal value_2) { //сравнивает value1  с вторым если 1-ое больше возвращает 0 иначе 1  ИЗМЕНЕНА
    int index_1=0, index_2 = 0, count_1 =0, count_2=0, global_count =0;
    for (int i = 0; i<3; i++) {
      for (int j = 0; j<32; j++) {
        if (s21_get_bit(value_1.bits[i], j) == 1) {
          count_1+=1;
          index_1 = global_count;

        }
        if (s21_get_bit(value_2.bits[i], j) == 1) {
          count_2+=1;
          index_2 = global_count;
        }
        global_count +=1;
      }
    }
    if (index_1 == index_2) {
      if (count_1 >= count_2) return 0; // первое число больше
      else return 1; // второе число больше 
    } else if (index_1 > index_2) return 0;
    else return 1;
    return -1; // ошибка
}

void swap(s21_decimal *value_1, s21_decimal *value_2) {
    s21_decimal temp = *value_2;
    *value_2 = *value_1;
    *value_1 = temp;
}

void EXPONENT_N(s21_decimal *value_1, s21_decimal *value_2) { // выравнивает экспоненту
  s21_decimal res = {0}, temp;
  if (get_decimal_exponent(*value_1) != get_decimal_exponent(*value_2)) {
    if (get_decimal_exponent(*value_1) > get_decimal_exponent(*value_2)) {
      temp = *value_2;
      int i = get_decimal_exponent(*value_1) - get_decimal_exponent(*value_2);
      while (i >= 0) {
        *value_2 = temp;
        for (int j=0; j<9; j++) {
          s21_add(temp, *value_2, &res);
          temp = res;
          for (int i = 0; i<3; res.bits[i]=0, i++); // за нуляем структуру result
        }
        i--;
      }
      int exp = get_decimal_exponent(*value_1);
      set_decimal_exponent(value_2, exp);
    } else {
        temp = *value_1;
        int i = get_decimal_exponent(*value_2) - get_decimal_exponent(*value_1);
        while (i >= 0) {
          *value_1 = temp;
          for (int j=0; j<9; j++) {
            s21_add(temp, *value_1, &res);
            temp = res;
            for (int i = 0; i<3; res.bits[i]=0, i++); // за нуляем структуру result
          }
          i--;
        }
      int exp = get_decimal_exponent(*value_2);
      set_decimal_exponent(value_1, exp);
    }
  }
}


void helper_sub(s21_decimal *value, int number_bit, int index); // функция которая ищет у какого индекса числа можно занять десяток "1" если находит заменяет еденицу "0"
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
            if (comparison_of_numbers(value_1,value_2) == 1) {
                swap(&value_1, &value_2); // число 1 меньше второго меняем местами;
                set_decimal_sign(result, 1); // меняем знаковый бит число отрицательное;
            }
           
            logic_sub(value_1, value_2, result);
        }
        else if (get_decimal_sign(value_1) == 1 &&  get_decimal_sign(value_2) == 1) { 
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
        else { 
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
for (int i = 0; i < 3; i++) { 
    for (int j = 0; j<= 31; j++) {
        if ((s21_get_bit(value_1.bits[i], j) == 0) & (s21_get_bit(value_2.bits[i], j) == 1)) {
        helper_sub(&value_1, i, j);
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

void helper_sub(s21_decimal *value, int number_bit, int index) { // функция которая ищет у какого индекса числа можно занять десяток "1" если находит заменяет еденицу "0"
// далее бежит назад от наеденного индекса до начального индекса при этом попутно заменяя индексы которые были пропущены так как уних нельзя было занять десяток 
// были равны 0, на еденицы (1), number_bit - переменная номера бита где потребовалось занять 1, index индекс 0 для которого занимаем 1
    int count_bits = 0, flag = 0; // count_bits отслеживаем в каком биете нашли еденицу, flag - для определения с какого бита начинать замену 0 на 1;
    int i = number_bit; // с какого бита начинаем искать.
    int s_index; // переменаая для индекса первого вхождения еденицы;
    for (; i<3; i++) {
        
        int stop_for =0, temp_index = index+1; // последние изменения;
        if (count_bits!=0) temp_index = 0;
        for (int j = temp_index; j < 32 ; j++) {
            if (s21_get_bit(value->bits[i], j) == 1) {
                s_index = j; flag = 1; stop_for =1;  break;}
            if (i==2 && j== 31 && s21_get_bit(value->bits[i], j) == 0) {
                s_index = index+1; count_bits=0; flag = -1;} // если не нашли у какого бита можно занять и достигли конца децимал скидывае счетчик битов и 
                    //устанавливаем индекс первого вхождения делаем его намерено меньше индекс для которого занимаем чтобы скипнуть цикл ниже.
                    // s_index = i; // выполниться если не найдеться бита у кторого можно занять еденицу;
        }
        if (stop_for == 1) break;
        count_bits++;
        
    }
    value->bits[i] = s21_clear_bit(value->bits[i], s_index); // обратить внимение внекоторыъ случаех возможно неврное решение.
    if (flag !=-1){    
        for (; i>= number_bit; i--){
            int j;
            int temp_index;
            if (flag == 1) {j = s_index-1; flag=0;}
            else  j = 31;
            if (count_bits > 0) {temp_index = 0; count_bits--;}
            else temp_index = index;
            for (; j >= temp_index; j--) {
                value->bits[i] = s21_set_bit(value->bits[i], j); // устанавливаем биты у которых не могли занять десяток в 1
            }
        }
    }
}