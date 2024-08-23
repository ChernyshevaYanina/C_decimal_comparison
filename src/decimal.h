#ifndef SRC_DECIMAL_H_
#define SRC_DECIMAL_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct {
  unsigned int bits[4];
} decimal;

typedef enum { false_comparison = 0, true_comparison = 1 } comparison;

// операторы сравнения
int is_less(decimal value_1, decimal value_2);
int is_less_or_equal(decimal value_1, decimal value_2);
int is_greater(decimal value_1, decimal value_2);
int is_greater_or_equal(decimal value_1, decimal value_2);
int compare(decimal value_1, decimal value_2);
int is_not_equal(decimal value_1, decimal value_2);
int is_equal(decimal value_1, decimal value_2);


#endif  // SRC_DECIMAL_H_