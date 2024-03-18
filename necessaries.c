#include <stdlib.h>
#include "necessaries.h"

void set_default(image_t *picture)
{
	picture->magic_word = '0';
	picture->width = 0;
	picture->height = 0;
	picture->max_color = 0;
	picture->x1 = 0;
	picture->x2 = 0;
	picture->y1 = 0;
	picture->y2 = 0;
	picture->mat = NULL;
}

int alloc_image_matrix(image_t *picture, int size)
{
	picture->mat = (uc **)malloc(picture->height * sizeof(uc *));
	if (!picture->mat)
		return ERR_ALLOC;
	for (int i = 0; i < picture->height; ++i) {
		picture->mat[i] = (uc *)malloc(size * picture->width * sizeof(uc));
		if (!picture->mat[i]) {
			for (int j = 0; j < i; ++j)
				free(picture->mat[j]);
			free(picture->mat);
			return ERR_ALLOC;
		}
	}
	return 0;
}

void free_image_matrix(image_t *picture)
{
	for (int i = 0; i < picture->height; ++i)
		free(picture->mat[i]);
	free(picture->mat);
}

uc **alloc_copy_matrix(int width, int height, int size)
{
	uc **mat = (uc **)malloc(height * sizeof(uc *));
	if (!mat)
		return NULL;
	for (int i = 0; i < height; ++i) {
		mat[i] = (uc *)malloc(size * width * sizeof(uc));
		if (!mat[i]) {
			for (int j = 0; j < i; ++j)
				free(mat[j]);
			free(mat);
			return NULL;
		}
	}
	return mat;
}
