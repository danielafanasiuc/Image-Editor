#include "necessaries.h"

void select_pixels(image_t *picture, int X1, int Y1, int X2, int Y2)
{
	picture->x1 = X1;
	picture->x2 = X2;
	picture->y1 = Y1;
	picture->y2 = Y2;
}

void image_copy(const image_t *picture, uc **new_matrix, int size)
{
	for (int i = 0; i < picture->height; ++i)
		for (int j = 0; j < size * picture->width; ++j)
			new_matrix[i][j] = picture->mat[i][j];
}

uc clamp(int value, int min, int max)
{
	if (value < min)
		value = min;
	if (value > max)
		value = max;
	return (uc)value;
}

int is_number(char *str)
{
	int i = 0;
	if (str[0] == '-')
		i = 1;
	while (str[i]) {
		if (str[i] < '0' || str[i] > '9')
			return 0;
		i++;
	}
	return 1;
}
