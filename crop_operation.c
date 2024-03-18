#include <stdio.h>
#include "necessaries.h"
#include "basic.h"
#include "crop_operation.h"

int crop_image(image_t *picture)
{
	if (picture->magic_word == '0') {
		printf("No image loaded\n");
	} else {
		int w, h;
		w = picture->x2 - picture->x1;
		h = picture->y2 - picture->y1;
		int size;
		if (picture->magic_word == '3' || picture->magic_word == '6')
			size = 3;
		else if (picture->magic_word == '2' || picture->magic_word == '5')
			size = 1;
		uc **cropped_matrix = alloc_copy_matrix(w, h, size);
		if (!cropped_matrix)
			return ERR_ALLOC;
		for (int i = picture->y1; i < picture->y2; ++i) {
			for (int j = size * picture->x1; j < size * picture->x2; ++j) {
				int new_i = i - picture->y1;
				int new_j = j - size * picture->x1;
				cropped_matrix[new_i][new_j] = picture->mat[i][j];
			}
		}
		free_image_matrix(picture);
		picture->mat = cropped_matrix;
		picture->width = w;
		picture->height = h;
		select_pixels(picture, 0, 0, picture->width, picture->height);
		printf("Image cropped\n");
	}
	return 0;
}
