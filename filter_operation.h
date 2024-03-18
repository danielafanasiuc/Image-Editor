#ifndef FILTER_H

#define FILTER_H
#include "necessaries.h"

int on_image_border(const image_t *picture, int i, int j);

double new_pixel(image_t *picture, int i, int j, int kernel[][3], double val);

void generate_kernel(int kernel[][3], int copy_kernel[][3]);

void apply(image_t *picture, uc **new_mat, int filter);

int apply_filter(image_t *picture);

#endif
