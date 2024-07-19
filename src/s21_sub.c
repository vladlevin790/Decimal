#include "s21_decimal.h"
#include "binary/s21_binary.h"
#include "decimal_helper/s21_decimal_helper.h"

typedef struct super_decimal {
    s21_decimal decimals[2];
} super_decimal;

// ---------------------------------------------------------------

void print_bits(int digit) {
    for (int i =31; i>=0; i--) printf("%d", (digit >> i) & 1);
    // printf(" ");
}

void print_decimals(s21_decimal digit) { 
    for (int i = 3; i >= 0; i--) {
        print_bits(digit.bits[i]);
   if (i==3) printf("    <-знаковый бит     ");}
   printf("\n");
}


void super_print(super_decimal digit) { 
    for (int i = 1; i >= 0; i--) {
        if (i==0) printf("  ------------>> \n");
            for (int j=3; j>=0; j--){
            print_bits(digit.decimals[i].bits[j]);
            if (j==3) printf("    <-знаковый бит     ");
        }
   }
   printf("\n");
}

// -------------------------------------------------------------------------



void helper_sub(s21_decimal *value, int number_bit, int index); // функция которая ищет у какого индекса числа можно занять десяток "1" если находит заменяет еденицу "0"
// далее бежит назад от наеденного индекса до начального индекса при этом попутно заменяя индексы которые были пропущены так как уних нельзя было занять десяток 
// были равны 0, на еденицы (1), 
void logic_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result); // не посредсвтенно осуществляет вычитаниеи
int cheak_res_on_zero(s21_decimal *res); // проверяет не равен ли результат нулю и если стояло отрицательное число убирает знак. 
super_decimal init_super_decimal(s21_decimal value);
s21_decimal binary_and(s21_decimal decimal1, s21_decimal decimal2);

super_decimal super_decimal_add_mirror(super_decimal value_1, super_decimal temp);
super_decimal super_decimal_exp_up(super_decimal digit, int exp);
void EXPONENT_N(s21_decimal *value_1, s21_decimal *value_2, s21_decimal* result);
void super_helper_sub(super_decimal *value, int number_decimal, int number_bit, int index);
void super_logic_sub(super_decimal value_1, super_decimal value_2, super_decimal *result);
int super_comparison_of_numbers(super_decimal value_1, super_decimal value_2);
void super_swap(super_decimal *value_1, super_decimal *value_2);
void set_sign_sub(s21_decimal* decimal, int sign); // для легкого управления знаком числа в переменную sign передовать только 0 или 1 


void set_sign_sub(s21_decimal* decimal, int sign) { // для легкого управления знаком числа в переменную sign передовать только 0 или 1 
    decimal->bits[3] = decimal->bits[3] | (sign << 31);
}

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
      int ii = 2;
      while (ii>=0)
      {
        if (value_1.bits[ii]> value_2.bits[ii]) return 0;
        else if (value_2.bits[ii]> value_1.bits[ii]) return 1;
        ii--;
      }
    } else if (index_1 > index_2) return 0;
    else return 1;
    return -1; // ошибка
}

void swap(s21_decimal *value_1, s21_decimal *value_2) {
    s21_decimal temp = *value_2;
    *value_2 = *value_1;
    *value_1 = temp;
}
super_decimal init_super_decimal(s21_decimal value) {
    super_decimal digit = {0};
    digit.decimals[0] = value;
    return digit;
}

super_decimal super_decimal_add_mirror(super_decimal value_1, super_decimal temp) {
    super_decimal result = {0};
    super_decimal tmp = temp;
    int carry=0;
    for (int k=0; k<2; k++){
        for (int i = 0; i < 3; i++) { 
            for (int j = 0; j<= 31; j++) {
                if ((s21_get_bit(value_1.decimals[k].bits[i], j) == 1) & (s21_get_bit(tmp.decimals[k].bits[i], j) == 1)) {
                    if (carry == 1) {
                        result.decimals[k].bits[i] = s21_set_bit(result.decimals[k].bits[i], j);
                    }
                    else {carry = 1;}
                }else if ((s21_get_bit(value_1.decimals[k].bits[i], j) == 0) & (s21_get_bit(tmp.decimals[k].bits[i], j) == 1)) {
                    if (carry == 1){
                    } else result.decimals[k].bits[i] = s21_set_bit(result.decimals[k].bits[i], j);
                } else if ((s21_get_bit(value_1.decimals[k].bits[i], j) == 1) & (s21_get_bit(tmp.decimals[k].bits[i], j) == 0)) {
                    if (carry == 1);
                    else result.decimals[k].bits[i] = s21_set_bit(result.decimals[k].bits[i], j);
                } else if (carry == 1) {
                    result.decimals[k].bits[i] = s21_set_bit(result.decimals[k].bits[i], j);
                    carry = 0;
                }
            }
        }
    }
    return result;
}


void EXPONENT_N(s21_decimal *value_1, s21_decimal *value_2, s21_decimal* result) { // выравнивает экспоненту и не только
    super_decimal val_1 = {0}, val_2 = {0}, res = {0};
    int sign_vol1 = get_decimal_sign(*value_1), sign_vol2 = get_decimal_sign(*value_2);  //сохраняем знак чисел
    printf("\n SAVE 1\n");
    print_bits(sign_vol1);
    printf("\n SAVE 2\n");
    print_bits(sign_vol2);
// БЛОК РАБОТЫ С ЭКСПОНЕНТОЙ УРАВНИВАНИЕ ЭКСПОНЕНТЫ
    int  exp1 = s21_get_range_bits(value_1->bits[3], 16, 23), exp2 = s21_get_range_bits(value_2->bits[3], 16, 23);
    result->bits[3] = exp1;
    printf("\n EXP1 = %d  EXP2  = %d\n", exp1, exp2);
    if (exp1 > exp2) {
        val_1 = init_super_decimal(*value_1);
        val_2 = init_super_decimal(*value_2);

        int i = exp1 - exp2 - 1; // нужна для правильной работы super_decimal_add_mirror
        super_decimal temp = val_2; // нужна для правильной работы super_decimal_add_mirror
        while (i >= 0) {
            for (int j=0; j<9; val_2 = super_decimal_add_mirror(val_2, temp), j++);
            temp = val_2;
            i--;
        }
        set_sign_sub(&val_2.decimals[0], sign_vol2); // с помощью этой строки востановили знак числа (отрицательное или положительно)
        set_decimal_exponent(&val_2.decimals[0], exp1); // меняем экспоненту числа делаем ее равной большей так как уравняли
        
    } else {
        val_1 = init_super_decimal(*value_1);
        val_2 = init_super_decimal(*value_2);
        int i = exp2 - exp1 - 1; // нужна для правильной работы super_decimal_add_mirror
        super_decimal temp = val_1; // нужна для правильной работы super_decimal_add_mirror
        while (i >= 0) {
            for (int j=0; j<9; val_1 = super_decimal_add_mirror(val_1, temp), j++);
            temp = val_1;
            i--;
        }
        set_sign_sub(&val_1.decimals[0], sign_vol1); // с помощью этой строки востановили знак числа (отрицательное или положительно)
        set_decimal_exponent(&val_1.decimals[0], exp2); // меняем экспоненту числа делаем ее равной большей так как уравняли
    }
// БЛОК РАБОТЫ С ЭКСПОНЕНТОЙ УРАВНИВАНИЕ ЭКСПОНЕНТЫ

    // printf("\n 1 SUPER_PRINT ДО ВЫЧИСЛЕНИЙ\n");
    // super_print(val_1);
    // printf("\n 2 SUPER_PRINT ДО ВЫЧИСЛЕНИЙ\n");
    // super_print(val_2);
    // printf("\n SUPER_PRINT res ДО ВЫЧИСЛЕНИЙ\n");
    // super_print(res);
    // printf("\n");

// ВСЯ ЛОГИКА ВЫЧИТАНИЯ КАК ОНА ЕСТЬ
// Приступаем к вычитанию
    if (sign_vol1 ==1 && sign_vol2 == 1) { // если оба числа отрицательные
        if (super_comparison_of_numbers(val_1, val_2) == 0) { // определяем какой из чисел больше 
            super_logic_sub(val_1, val_2, &res);
            set_sign_sub(&res.decimals[0], sign_vol1);
            set_decimal_exponent(&res.decimals[0], get_decimal_exponent(val_1.decimals[0]));
    } else {
            // super_swap(&val_1, &val_2);
            super_logic_sub(val_2, val_1, &res);
            sign_vol1 = 0; // так как оба числа отрицательные и первое число val1 меньше vol2 знак ответа положительный
            set_sign_sub(&res.decimals[0], sign_vol1);
            set_decimal_exponent(&res.decimals[0], get_decimal_exponent(val_1.decimals[0]));
            }
    } else if (sign_vol1 == 0 && sign_vol2 == 0) {
            if (super_comparison_of_numbers(val_1, val_2) == 0) { // определяем какой из чисел больше 
            super_logic_sub(val_1, val_2, &res);
            set_sign_sub(&res.decimals[0], sign_vol1);
            set_decimal_exponent(&res.decimals[0], get_decimal_exponent(val_1.decimals[0]));
    } else {
            super_logic_sub(val_2, val_1, &res);
            sign_vol1 = 1; // так как оба числа положительные и первое число val1 меньше vol2 знак ответа отрицательный
            set_sign_sub(&res.decimals[0], sign_vol1);
            set_decimal_exponent(&res.decimals[0], get_decimal_exponent(val_1.decimals[0]));
            }
    } else if (sign_vol1 == 0 && sign_vol2 == 1) {
            if (super_comparison_of_numbers(val_1, val_2) == 0) { // так как второе число отрицательно ответ будет положительный всегда
            sign_vol1 = 0;
            res = super_decimal_add_mirror(val_1,val_2);
            printf("\n ФУНКЦИЯ СЛОЖЕНИЯ ДВОЙНЫХ ДЕЦЕМОЛОВ ЕЩЕ НЕ РЕАЛИЗОВАНА  больше 1+ | меньше 2-\n");
            set_sign_sub(&res.decimals[0], sign_vol1);
            set_decimal_exponent(&res.decimals[0], get_decimal_exponent(val_1.decimals[0]));
    } else {
            sign_vol1 = 0;
            printf("\n ФУНКЦИЯ СЛОЖЕНИЯ ДВОЙНЫХ ДЕЦЕМОЛОВ ЕЩЕ НЕ РЕАЛИЗОВАНА больше 2- | меньше 1+\n");
            res = super_decimal_add_mirror(val_2,val_1);
            set_sign_sub(&res.decimals[0], sign_vol1);
            set_decimal_exponent(&res.decimals[0], get_decimal_exponent(val_1.decimals[0]));
            }
    } else if (sign_vol1 == 1 && sign_vol2 == 0) {
            if (super_comparison_of_numbers(val_1, val_2) == 0) { // так как первое число отрицательно ответ будет отрицательный всегда
            sign_vol1 = 1;
            printf("\n ФУНКЦИЯ СЛОЖЕНИЯ ДВОЙНЫХ ДЕЦЕМОЛОВ ЕЩЕ НЕ РЕАЛИЗОВАНА больше 1- | меньше 2+\n");
            res = super_decimal_add_mirror(val_1,val_2);
            set_sign_sub(&res.decimals[0], sign_vol1);
            set_decimal_exponent(&res.decimals[0], get_decimal_exponent(val_1.decimals[0]));
    } else {
            sign_vol1 = 0;
            printf("\n ФУНКЦИЯ СЛОЖЕНИЯ ДВОЙНЫХ ДЕЦЕМОЛОВ ЕЩЕ НЕ РЕАЛИЗОВАНА больше 2+ | меньше 1-\n");
            res = super_decimal_add_mirror(val_2,val_1);
            set_sign_sub(&res.decimals[0], sign_vol1);
            set_decimal_exponent(&res.decimals[0], get_decimal_exponent(val_1.decimals[0]));
            }
    }
    
// ВСЯ ЛОГИКА ВЫЧИТАНИЯ КАК ОНА ЕСТЬ

    printf("\n 1 SUPER_PRINT\n");
    super_print(val_1);
    printf("\n SUPER_PRINT\n");
    printf("\n 2 SUPER_PRINT\n");
    super_print(val_2);
    printf("\n SUPER_PRINT\n");
    printf("\n SUPER_PRINT res\n");
    super_print(res);
    printf("\n SUPER_PRINT res\n");

}




int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    if (check_decimal(value_1) || check_decimal(value_2) || result == NULL) {
        printf("в папраметр функции sub_21 передан неверный параметр (resualt == NULL, либо ошибка в экспоненте первого или второго числа)");
        return 9;
    }
    else {
        if (get_decimal_exponent(value_1) != get_decimal_exponent(value_2)) { // выполняется если есть экспонента; // если эуспонента разная то выполняем
            for (int i = 0; i<3; result->bits[i]=0, i++); // за нуляем структуру result
            EXPONENT_N(&value_1, &value_2, result);
            }

        else if (get_decimal_exponent(value_1) == get_decimal_exponent(value_2)){
            for (int i = 0; i<3; result->bits[i]=0, i++); // за нуляем структуру result
            if (get_decimal_sign(value_1) == 0 &&  get_decimal_sign(value_2) == 0) { // если оба числа положительные
                if (comparison_of_numbers(value_1,value_2) == 1) {
                    swap(&value_1, &value_2); // число 1 меньше второго меняем местами;
                    set_decimal_sign(result, 1); // меняем знаковый бит число отрицательное;
                }
                logic_sub(value_1, value_2, result);
            }
            else if (get_decimal_sign(value_1) == 1 &&  get_decimal_sign(value_2) == 1) {  // оба числа отрицатлльные
                if (comparison_of_numbers(value_1,value_2) == 1) {
                    swap(&value_1, &value_2); // число 1 меньше второго меняем местами;
                    set_decimal_sign(result, 0); // меняем знаковый бит число отрицательное;
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
                    // s_index = i;  выполниться если не найдеться бита у кторого можно занять еденицу;
        }
        if (stop_for == 1) break;
        count_bits++;
        
    }
    value->bits[i] = s21_clear_bit(value->bits[i], s_index); // обратить внимение внекоторыъх (мложет быть но это не точно) случаех возможно неврное решение.
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


void super_helper_sub(super_decimal *value, int number_decimal, int number_bit, int index) { // функция которая ищет у какого индекса числа можно занять десяток "1" если находит заменяет еденицу "0"
// далее бежит назад от наеденного индекса до начального индекса при этом попутно заменяя индексы которые были пропущены так как уних нельзя было занять десяток 
// были равны 0, на еденицы (1), number_bit - переменная номера бита где потребовалось занять 1, index индекс 0 для которого занимаем 1
    int count_bits = 0, flag = 0; // count_bits отслеживаем в каком биете нашли еденицу, flag - для определения с какого бита начинать замену 0 на 1;
    int count_decimal = 0; // отслеживаем в каком децимале занимаеме еденицу
    int k = number_decimal; // с какого децимала начинать;
    int i = number_bit; // с какого бита начинаем искать.
    int s_index; // переменаая для индекса первого вхождения еденицы;
    for (; k<2; k++){   
        int stop_for =0;
        for (; i<3; i++) {
            if (k==2) printf("\ni == %d\n", i);
            int  temp_index = index+1; // последние изменения;
            if (count_bits!=0) temp_index = 0;
            for (int j = temp_index; j < 32 ; j++) {
                if (s21_get_bit(value->decimals[k].bits[i], j) == 1) {
                    s_index = j; flag = 1; stop_for = 1; break;}
                if (k == 1 && i==2 && j== 31 && s21_get_bit(value->decimals[k].bits[i], j) == 0) {
                    s_index = index; count_bits=0; flag = -1;} // если не нашли у какого бита можно занять и достигли конца децимал скидывае счетчик битов и (index+1 было)
                        //устанавливаем индекс первого вхождения делаем его намерено меньше индекс для которого занимаем чтобы скипнуть цикл ниже.
                        // s_index = i;  выполниться если не найдеться бита у кторого можно занять еденицу;
            }
            if (stop_for == 1) break;
            count_bits++; // считаем биты
            
        }
        if (stop_for == 1) break;
        i = 0; //обнуляем i для перезапуска по битового цикла без него ответ не правильный
        count_decimal++; // по сути не нужная переменная обнуляем i в конце цикла.
    }
    
    value->decimals[k].bits[i] = s21_clear_bit(value->decimals[k].bits[i], s_index); // обратить внимение внекоторыъх (может быть но это не точно) случаех возможно неврное решение.
   // если нашли у кого занять обнуляем бит у которого заняли десяток
    if (flag !=-1){
        for (; k>=number_decimal; k--){ //number_decimal номер децемеала переданный в функцию через параметры
            
            for (; i>= number_bit; i--){  // number_bit  номер биты переданный в функцию через параметры
                
                int j;
                int temp_index;  
                if (flag == 1) {j = s_index-1; temp_index = index; flag=0; } //если флаг 1 j равна индексу первого вхождения еденицы у которой заняли бит flag=0;
                else  {j = 31; temp_index=0; }  // иначе j равна последнему биту
                // if (count_bits > 0) {temp_index = 0; count_bits--;} // если сетчиков битов больше нуля tenp_index равен нулю и уменшаям счетчик битов это сделано для того что бы
                // пройти бит до конца если еденица была наедена в следующем бите
                // else temp_index = index; // иначе есле десяток заняли в этом же бите спускаемся до индекса для которого занимали еденицу
                // printf("\nk =%d number_decimal = %d number_bit %d index %d flag = %d s_index = %d count_bits %d j= %d temp_index = %d\n", k, number_decimal, number_bit, index, flag, s_index, count_bits, j, temp_index);
                for (; j >= temp_index; j--) {
                    // printf ("\nj = %d temp = %d \n", j, temp_index );
                    value->decimals[k].bits[i] = s21_set_bit(value->decimals[k].bits[i], j); // устанавливаем биты у которых не могли занять десяток в 1
                }
            }
            i = 2; s_index =32;
        }
    }
}

void super_logic_sub(super_decimal value_1, super_decimal value_2, super_decimal *result){ // не посредственно осуществляет вычитание
for(int k = 0; k<2; k++) {
    for (int i = 0; i < 3; i++) { 
        for (int j = 0; j<= 31; j++) {
            if ((s21_get_bit(value_1.decimals[k].bits[i], j) == 0) & (s21_get_bit(value_2.decimals[k].bits[i], j) == 1)) {
            super_helper_sub(&value_1, k, i, j);
            result->decimals[k].bits[i] = s21_set_bit(result->decimals[k].bits[i], j);
            }
            else if((s21_get_bit(value_1.decimals[k].bits[i], j) == 1) & (s21_get_bit(value_2.decimals[k].bits[i], j) == 1)) {
                result->decimals[k].bits[i] = s21_clear_bit(result->decimals[k].bits[i], j);
                }
            else if((s21_get_bit(value_1.decimals[k].bits[i], j) == 1) & (s21_get_bit(value_2.decimals[k].bits[i], j) == 0)) {
                result->decimals[k].bits[i] = s21_set_bit(result->decimals[k].bits[i], j);
                }
            }
        }
    }
}

int super_comparison_of_numbers(super_decimal value_1, super_decimal value_2) { //сравнивает value1  с вторым если 1-ое больше возвращает 0 иначе 1  ИЗМЕНЕНА
    int index_1=0, index_2 = 0, count_1 =0, count_2=0, global_count =0;
    for (int k = 0; k<2; k++) {    
        for (int i = 0; i<3; i++) {
            for (int j = 0; j<32; j++) {
                if (s21_get_bit(value_1.decimals[k].bits[i], j) == 1) {
                    count_1+=1;
                    index_1 = global_count;
                }
                if (s21_get_bit(value_2.decimals[k].bits[i], j) == 1) {
                    count_2+=1;
                    index_2 = global_count;
                }
                global_count +=1;
            }
        }
    }
    if (index_1 == index_2) {
        for (int i=1; i>=0; i--){
            for(int j=2; j>=0; j--){
                if (value_1.decimals[i].bits[j] >= value_2.decimals[i].bits[j]) return 0;
                else return 1;
            }
        }
    } else if (index_1 > index_2) return 0;
        else return 1;
    return -1; // ошибка
}

void super_swap(super_decimal *value_1, super_decimal *value_2) {
    super_decimal temp = *value_2;
    *value_2 = *value_1;
    *value_1 = temp;
}