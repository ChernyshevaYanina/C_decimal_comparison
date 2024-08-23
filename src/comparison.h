#ifndef SRC_COMPARISON_H_
#define SRC_COMPARISON_H_

#include "decimal.h"
#include "stepeni_dvuh.h"
#include "string.h"

#define SIZE_ONE \
  60  // размер для представления децимала в десятичном виде, максимально
      // возможный децимал при умножении
#define SIZE_BIN 97  // размер для представления децимала в бинарном виде
#define SIZE_THRD \
  33  // одна третья бинарного размера, максимально возможная для одного битса
#define OVER_SIZE 256  // огромный размер, можно убрать
#define short_int char  // для удобного представления чара, как мамленького инта
#define SIZE_BTEN 31

typedef enum { kError = 0, kEqual = 1, kLess = 2, kGreater = 3 } comp;
typedef enum {
  kFalse = 0,
  kTrue = 1,
} s21_comp;

void addZeroes(char* left, char* right);
void clear(char* input, int size);
void reverseString(char* string);
void decimalMantisToBinary(decimal value, char* binaryOutput);
int getSign(int value);
int getScale(int value);
void baseTenCharArrayAdd(char* left, char* right, char* result);
void binaryToBaseTen(char* binary, char* output);
void clearCharZeroes(char* input);
int postavit_tochku(int tochka, char* stroka, char* integral,
                    char* fractional);  // переименовать
int compare(decimal value_1, decimal value_2);
int checkSign(decimal value_1, decimal value_2);
int checkLen(int left_len, int right_len, int both_negative);
int checkNumber(const char* left_digits, const char* right_digits,
                int both_negative);
void equalizeFractional(char* left_fractional, char* right_fractional);

#endif  // SRC_COMPARISON_H_
