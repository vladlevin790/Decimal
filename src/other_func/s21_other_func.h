#ifndef S21_OTHER_FUNC_H
#define S21_OTHER_FUNC_H

#include "../binary/s21_binary.h"
#include "../decimal_helper/s21_decimal_helper.h"
#include "../s21_decimal.h"

/**
@brief Функция s21_negate возвращает результат умножения указанного Decimal на
-1.
@param value - входное значение типа s21_decimal.
@param result - указатель на переменную, в которую будет записано результат
операции.
@return Возвращает 0 в случае успешного выполнения функции, и код ошибки в
противном случае. */
int s21_negate(s21_decimal value, s21_decimal *result);

/**
@brief Функция s21_truncate выполняет операцию усечения числа до целой части.
@param value - входное значение типа s21_decimal.
@param result - указатель на переменную, в которую будет записано результат
операции. return Возвращает 0 в случае успешного выполнения функции, и код
ошибки в противном случае. */
int s21_truncate(s21_decimal value, s21_decimal *result);

/**
@brief Функция s21_round выполняет операцию округления числа до ближайшего
целого.
@param value - входное значение типа s21_decimal.
@param result - указатель на переменную, в которую будет записано результат
операции.return Возвращает 0 в случае успешного выполнения функции, и код ошибки
в противном случае. */
int s21_round(s21_decimal value, s21_decimal *result);

/**
@brief Функция s21_floor выполняет операцию округления числа вниз до ближайшего
целого.
@param value - входное значение типа s21_decimal.
@param result - указатель на переменную, в которую будет записано результат.
@return Возвращает 0 в случае успешного выполнения функции, и код ошибки в
противном случае. */
int s21_floor(s21_decimal value, s21_decimal *result);

#endif