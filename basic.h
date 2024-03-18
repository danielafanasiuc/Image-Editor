#ifndef BASIC_H

#define BASIC_H
#include "necessaries.h"

void select_pixels(image_t *picture, int X1, int Y1, int X2, int Y2);

void image_copy(const image_t *picture, uc **new_matrix, int size);

uc clamp(int value, int min, int max);

int is_number(char *str);

#endif
