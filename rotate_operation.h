#ifndef ROTATE_H

#define ROTATE_H
#include "necessaries.h"

int is_square(const image_t *picture);

int all_selected(const image_t *picture);

int supported_angle(int angle);

void rotate_right(image_t *picture, uc **rotated_matrix, int size);

int rotate_image(image_t *picture);

#endif
