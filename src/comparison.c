#include "comparison.h"

/// @brief заполняет сртроку знаками конца строки
/// @param input строка, которую нужно занулить
/// @param size размер строки
void clear(char* input, int size) {
  for (int i = 0; i < size; ++i) {
    input[i] = 0;
  }
}

/// @brief добавляет нули в конец строки
/// @param left строка, поступившая как сравневоемое значение
/// @param right строка, поступившая как значение с которым сравниват
void addZeroes(char* left, char* right) {
  int len_l = strlen(left), len_r = strlen(right);
  char string_left[SIZE_ONE], string_right[SIZE_ONE];
  clear(string_left, SIZE_ONE);
  clear(string_right, SIZE_ONE);
  for (int i = 0; i < SIZE_ONE - len_l - 1; i++) strcat(string_left, "0");
  for (int i = 0; i < SIZE_ONE - len_r - 1; i++) strcat(string_right, "0");
  strcat(string_left, left);
  strcat(string_right, right);
  strcpy(left, string_left);
  strcpy(right, string_right);
}

/// @brief разворачивает строку
/// @param string строка
void reverseString(char* string) {
  int i = 0, last_char = strlen(string) - 1;
  while (i < last_char) {
    char temp = string[i];
    string[i] = string[last_char];
    string[last_char] = temp;
    i++;
    last_char--;
  }
}

/// @brief Приводит децимал к бинарному виду
/// @param value децимал
/// @param binaryOutput строка в бинароном виде
void decimalMantisToBinary(decimal value, char* binaryOutput) {
  char binaryLocal[SIZE_BIN];
  clear(binaryLocal, SIZE_BIN);
  for (int countBit = 0; countBit <= 2; countBit++) {
    char stack[SIZE_THRD];
    clear(stack, SIZE_THRD);
    for (int i = 0; i < SIZE_THRD - 1; ++i) stack[i] = '0';
    int i = 0;
    while (value.bits[countBit]) {
      if (value.bits[countBit] % 2 == 1) {
        stack[i] = '1';
      } else {
        stack[i] = '0';
      }
      ++i;
      value.bits[countBit] /= 2;
    }
    strcat(binaryLocal, stack);
  }
  reverseString(binaryLocal);
  binaryLocal[SIZE_BIN - 1] = 0;
  strcpy(binaryOutput, binaryLocal);
}

/// @brief Находит знак + или -
/// @param value 3 bits из которого берется знак
/// @return возвращает 0 если +, 1 если -
int getSign(int value) {
  unsigned char intToChars[4];
  int sign = 0;
  memcpy(intToChars, &value, sizeof(char) * 4);
  intToChars[3] == 0 ? (sign = 0) : (sign = 1);
  return sign;
}

/// @brief Ищет колличество знаков после запятой
/// @param value 3 bits из которого берется положение запятой
/// @return возвращает число знаков
int getScale(int value) {
  unsigned char intToChars[4];
  int scale = 0;
  memcpy(intToChars, &value, sizeof(char) * 4);
  scale = intToChars[2];
  return scale;
}

/// @brief Сложение двух десятичных строк
/// @param left строка, поступившая как сравневоемое значение
/// @param right строка, поступившая как значение с которым сравнивать
/// @param result строка, которая получилась после сложения
void baseTenCharArrayAdd(char* left, char* right, char* result) {
  addZeroes(left, right);
  short_int result_local[SIZE_ONE] = {0};
  clear(result_local, SIZE_ONE);
  for (int i = 0; i < SIZE_ONE - 1; i++) {
    result_local[i] = (left[i] - '0') + (right[i] - '0');
  }
  for (int i = SIZE_ONE - 1; i > 0; i--) {
    if (result_local[i] > 9) {
      result_local[i - 1] += 1;
      result_local[i] -= 10;
    }
  }
  int started = 0, j = 0;
  for (int i = 0; i < SIZE_ONE - 1; ++i) {
    if (result_local[i] != 0) started = 1;
    if (started) {
      result[j] = result_local[i] + '0';
      ++j;
    }
  }
}

/// @brief Преобразование из двоичной системы в десятичную
/// @param binary строка в двоичном виде
/// @param output получившаяся десятичная строка
void binaryToBaseTen(char* binary, char* output) {
  reverseString(binary);
  char sum[SIZE_ONE];
  clear(sum, SIZE_ONE);
  strcpy(sum, "0");
  for (int i = 0; i < SIZE_BIN; ++i) {
    if (binary[i] == '1') {
      char sila_dvuh_local[OVER_SIZE];
      clear(sila_dvuh_local, OVER_SIZE);
      strcpy(sila_dvuh_local, sily_dvuh[i]);
      char sum_temp[SIZE_ONE];
      clear(sum_temp, SIZE_ONE);
      baseTenCharArrayAdd(sum, sila_dvuh_local, sum_temp);
      strcpy(sum, sum_temp);
    }
  }
  strcpy(output, sum);
}

/// @brief Отделяет целую часть числа от дробной
/// @param tochka количество знаков после запятой
/// @param stroka десятичная строка
/// @param integral целая часть
/// @param fractional дробная часть
/// @return возвращает 1, если колличество знаков после запятой не входит в
/// диапозон от 0 до 28, иначе 0
int postavit_tochku(int tochka, char* stroka, char* integral,
                    char* fractional) {
  int error = 1;
  if (tochka >= 0 && tochka <= 28) {
    error = 0;
    char temp[SIZE_BTEN];
    clear(temp, SIZE_BTEN);
    int len = strlen(stroka);
    if (len > 30) printf("\nPEREVAL V STROKE!\n");
    if (30 - 1 - len < 0) printf("\nSCHAS BUDET SEGFAULT!!\n");
    for (int i = 0; i < 30 - 1 - len; i++) strcat(temp, "0");
    strcat(temp, stroka);
    char temp2[SIZE_BTEN];
    clear(temp2, SIZE_BTEN);
    strncat(temp2, temp, 29 - tochka);
    strcat(temp2, ".");
    strcat(temp2, temp + 29 - tochka);

    strncpy(integral, temp, 29 - tochka);
    strcpy(fractional, temp + 29 - tochka);
    static int zahod = 1;
    zahod++;

    clearCharZeroes(integral);

    strcpy(stroka, temp2);
  }
  return error;
}

/// @brief Удаляет нули из начала целой части
/// @param input строка из которой нужно удалить нули
void clearCharZeroes(char* input) {
  int started = 0;
  char temp[SIZE_BTEN];
  clear(temp, SIZE_BTEN);
  for (int i = 0; input[i] != '\0'; i++) {
    if (input[i] != '0') started = 1;
    if (started) {
      char temp_for_one_char[2];
      temp_for_one_char[0] = input[i];
      temp_for_one_char[1] = '\0';
      strcat(temp, temp_for_one_char);
    }
  }
  strcpy(input, temp);
}
/// @brief Сравнивает знаки
/// @param value_1 первый децимал
/// @param value_2 второй децимал
/// @return если знаки одинаковые возвращает kEqual, если знаки отличаются, то
/// возвращает либо kLess, либо kGreater
int checkSign(decimal value_1, decimal value_2) {
  int result = kEqual;
  int left_sign = getSign(value_1.bits[3]);
  int right_sign = getSign(value_2.bits[3]);
  int decimal_mantis_sum = value_1.bits[0] + value_1.bits[1] + value_1.bits[2] +
                           value_2.bits[0] + value_2.bits[1] + value_2.bits[2];
  if (left_sign > right_sign) result = kLess;
  if (left_sign < right_sign) result = kGreater;
  if (decimal_mantis_sum == 0) result = kEqual;
  return result;
}

/// @brief Сравнивает длинну стоки
/// @param left_len длинна первой сравнивоемой строки
/// @param right_len длина второй сравниваемой строки
/// @param both_negative 0 или 1 в зависимости от того, являются ли оба децимала
/// отрицательными
/// @return если строки одинаковые возвращает kEqual, если строки отличаются, то
/// возвращает либо kLess, либо kGreater, меняет значения возвращаемых значений,
/// если оба числа отрицательные
int checkLen(int left_len, int right_len, int both_negative) {
  int result = kEqual;
  if (left_len < right_len) {
    if (!both_negative) result = kLess;
    if (both_negative) result = kGreater;
  } else if (left_len > right_len) {
    if (!both_negative) result = kGreater;
    if (both_negative) result = kLess;
  }
  return result;
}

/// @brief Сравнивает числа
/// @param left_digits первая сравнивоемая строка
/// @param right_digits вторая сравнивоемая строка
/// @param both_negative 0 или 1 в зависимости от того, являются ли оба децимала
/// отрицательными
/// @return если все цифры одинаковые возвращает kEqual, если строки отличаются,
/// то возвращает либо kLess, либо kGreater, меняет значения возвращаемых
/// значений, если оба числа отрицательные
int checkNumber(const char* left_digits, const char* right_digits,
                int both_negative) {
  int result = kEqual;
  int loop_break = 0;
  for (int i = 0; left_digits[i] != '\0' && loop_break == 0; ++i) {
    if (left_digits[i] < right_digits[i]) {
      if (!both_negative) result = kLess;
      if (both_negative) result = kGreater;
      loop_break = 1;
    } else if (left_digits[i] > right_digits[i]) {
      if (!both_negative) result = kGreater;
      if (both_negative) result = kLess;
      loop_break = 1;
    }
  }
  return result;
}

/// @brief Добавляет нули в конец дробной части, чтобы сравнять их
/// @param left_fractional первая дробная часть
/// @param right_fractional вторая дроная часть
void equalizeFractional(char* left_fractional, char* right_fractional) {
  int left_len = strlen(left_fractional);
  int right_len = strlen(right_fractional);
  if (left_len > right_len) {
    for (int i = right_len; i < left_len; i++) strcat(right_fractional, "0");
  } else if (left_len < right_len)
    for (int i = left_len; i < right_len; i++) strcat(left_fractional, "0");
}

/// @brief Все сравнение и преобразование происходит здесь
/// @param value_1 первый децимал
/// @param value_2 второй децимал
/// @return если все цифры одинаковые возвращает kEqual, если строки отличаются,
/// то возвращает либо kLess, либо kGreater, меняет значения возвращаемых
/// значений, если оба числа отрицательные, возвращает kError, если что-то пошло
/// не так
int compare(decimal value_1, decimal value_2) {
  int result = 0;
  char left_binary_string[SIZE_BIN], right_binary_string[SIZE_BIN];
  clear(left_binary_string, SIZE_BIN);
  clear(right_binary_string, SIZE_BIN);
  char left_base_ten_string[SIZE_ONE], right_base_ten_string[SIZE_ONE];
  clear(left_base_ten_string, SIZE_ONE);
  clear(right_base_ten_string, SIZE_ONE);
  int both_neg = 0;

  int left_sign = getSign(value_1.bits[3]);
  int right_sign = getSign(value_2.bits[3]);
  if ((left_sign + right_sign) == 2) both_neg = 1;

  int left_scale = getScale(value_1.bits[3]);
  int right_scale = getScale(value_2.bits[3]);
  if ((left_scale >= 0 && left_scale <= 28) &&
      (right_scale >= 0 && right_scale <= 28)) {
    decimalMantisToBinary(value_1, left_binary_string);
    decimalMantisToBinary(value_2, right_binary_string);
    binaryToBaseTen(left_binary_string, left_base_ten_string);
    binaryToBaseTen(right_binary_string, right_base_ten_string);
    char l_integral[SIZE_BTEN], r_integral[SIZE_BTEN];
    clear(l_integral, SIZE_BTEN);
    clear(r_integral, SIZE_BTEN);
    char l_fractional[SIZE_BTEN], r_fractional[SIZE_BTEN];
    clear(l_fractional, SIZE_BTEN);
    clear(r_fractional, SIZE_BTEN);
    postavit_tochku(left_scale, left_base_ten_string, l_integral, l_fractional);
    postavit_tochku(right_scale, right_base_ten_string, r_integral,
                    r_fractional);
    int l_integr_len = strlen(l_integral);
    int r_integr_len = strlen(r_integral);

    if (checkSign(value_1, value_2) == kLess) {
      result = kLess;
    } else if (checkSign(value_1, value_2) == kGreater) {
      result = kGreater;
    } else {
      if (checkLen(l_integr_len, r_integr_len, both_neg) == kLess) {
        result = kLess;
      } else if (checkLen(l_integr_len, r_integr_len, both_neg) == kGreater) {
        result = kGreater;
      } else {
        int integral_compare = checkNumber(l_integral, r_integral, both_neg);
        if (integral_compare == kLess) {
          result = kLess;
        } else if (integral_compare == kGreater) {
          result = kGreater;
        } else {
          equalizeFractional(l_fractional, r_fractional);
          int fract_compare = checkNumber(l_fractional, r_fractional, both_neg);
          if (fract_compare == kLess) {
            result = kLess;
          } else if (fract_compare == kGreater) {
            result = kGreater;
          } else {
            result = kEqual;
          }
        }
      }
    }
  } else {
    result = kError;
  }
  return result;
}

/// @param value_1 первый децимал
/// @param value_2 второй децимал
/// @return возвращает kTrue, если compare возвращает kLess, иначе kFalse
int is_less(decimal value_1, decimal value_2) {
  int result = kFalse;
  if (compare(value_1, value_2) == kLess) result = kTrue;
  return result;
}

/// @brief Проверяет, является ли первый децимал меньше или равным второму
/// @param value_1 первый децимал
/// @param value_2 второй децимал
/// @return возвращает kTrue, если compare возвращает kLess или kEqual,
/// иначе kFalse
int is_less_or_equal(decimal value_1, decimal value_2) {
  int result = kFalse;
  int compare_result = compare(value_1, value_2);
  if (compare_result == kLess || compare_result == kEqual) {
    result = kTrue;
  }
  return result;
}

/// @brief Проверяет, является ли первый децимал больше второго
/// @param value_1 первый децимал
/// @param value_2 второй децимал
/// @return возвращает kTrue, если compare возвращает kGreater, иначе kFalse
int is_greater(decimal value_1, decimal value_2) {
  int result = kFalse;
  if (compare(value_1, value_2) == kGreater) result = kTrue;
  return result;
}

/// @brief Проверяет, является ли первый децимал больше или равным второму
/// @param value_1 первый децимал
/// @param value_2 второй децимал
/// @return возвращает kTrue, если compare возвращает kGreater или kEqual,
/// иначе kFalse
int is_greater_or_equal(decimal value_1, decimal value_2) {
  int result = kFalse;
  int compare_result = compare(value_1, value_2);
  if (compare_result == kGreater || compare_result == kEqual) {
    result = kTrue;
  }
  return result;
}

/// @brief Проверяет числа на не эквивалентность
/// @param value_1 первый децимал
/// @param value_2 второй децимал
/// @return возвращает kTrue, если is_equal возвращает kFalse, иначе kFalse
int is_not_equal(decimal value_1, decimal value_2) {
  int result = (!(is_equal(value_1, value_2)));
  return result;
}

/// @brief Проверяет числа на эквивалентность
/// @param value_1 первый децимал
/// @param value_2 второй децимал
/// @return возвращает kTrue, если compare возвращает kEqual, иначе kFalse
int is_equal(decimal value_1, decimal value_2) {
  int result = kFalse;
  if (compare(value_1, value_2) == kEqual) result = kTrue;
  return result;
}
