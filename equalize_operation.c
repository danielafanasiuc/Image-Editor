#include <stdio.h>
#include <math.h>
#include "necessaries.h"
#include "basic.h"
#include "frequencies.h"
#include "equalize_operation.h"

void equalize(image_t *picture)
{
	if (picture->magic_word == '0') {
		printf("No image loaded\n");
	} else if (picture->magic_word == '3' || picture->magic_word == '6') {
		printf("Black and white image needed\n");
	} else {
		int freq[256] = {0};
		frequency_all(picture, freq);
		for (int i = 0; i < picture->height; ++i) {
			for (int j = 0; j < picture->width; ++j) {
				int sum_freq = 0;
				for (int k = 0; k <= (int)picture->mat[i][j]; ++k)
					sum_freq += freq[k];
				int area = picture->height * picture->width;
				double pixel = 255.0 * (1.0 / (double)area) * (double)sum_freq;
				picture->mat[i][j] = clamp(round(pixel), 0, 255);
			}
		}
		printf("Equalize done\n");
	}
}
