#include <stdio.h>
#include <string.h>
#include <math.h>
#include "necessaries.h"
#include "basic.h"
#include "filter_operation.h"

int on_image_border(const image_t *picture, int i, int j)
{
	//if the pixel is on the image frame (border) return 1, else return 0
	int h = picture->height;
	int w = picture->width;
	if (i == 0 || i == (h - 1) || j == 0 || j == (w - 1))
		return 1;
	return 0;
}

double new_pixel(image_t *picture, int i, int j, int kernel[][3], double val)
{
	int submat[3][3], offset_i, offset_j;
	for (int i1 = i - 1; i1 <= i + 1; ++i1) {
		offset_j = 0;
		for (int j3 = j - 3; j3 <= j + 3; j3 += 3) {
			offset_i = i1 - (i - 1);
			submat[offset_i][offset_j++] = (int)picture->mat[i1][j3];
		}
	}
	double sum = 0.0;
	for (int i_mat = 0; i_mat <= 2; ++i_mat)
		for (int j_mat = 0; j_mat <= 2; ++j_mat)
			sum += (double)(submat[i_mat][j_mat] * kernel[i_mat][j_mat]) * val;
	return sum;
}

void generate_kernel(int kernel[][3], int copy_kernel[][3])
{
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			kernel[i][j] = copy_kernel[i][j];
}

void apply(image_t *picture, uc **new_mat, int filter)
{
	int image_kernel[3][3];
	double mult;
	if (filter == 1) {
		int copy_kernel[3][3] = {{-1, -1, -1}, {-1, 8, -1}, {-1, -1, -1}};
		generate_kernel(image_kernel, copy_kernel);
		mult = 1.0;
	}
	if (filter == 2) {
		int copy_kernel[3][3] = {{0, -1, 0}, {-1, 5, -1}, {0, -1, 0}};
		generate_kernel(image_kernel, copy_kernel);
		mult = 1.0;
	}
	if (filter == 3) {
		int copy_kernel[3][3] = {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}};
		generate_kernel(image_kernel, copy_kernel);
		mult = 1.0 / 9;
	}
	if (filter == 4) {
		int copy_kernel[3][3] = {{1, 2, 1}, {2, 4, 2}, {1, 2, 1}};
		generate_kernel(image_kernel, copy_kernel);
		mult = 1.0 / 16;
	}
	for (int i = picture->y1; i < picture->y2; ++i) {
		for (int j = picture->x1; j < picture->x2; ++j) {
			if (!on_image_border(picture, i, j)) {
				//apply filter
				double r_pixel, g_pixel, b_pixel;
				int j_r = 3 * j;
				r_pixel = new_pixel(picture, i, j_r, image_kernel, mult);
				new_mat[i][j_r] = clamp((int)round(r_pixel), 0, 255);
				int j_g = 3 * j + 1;
				g_pixel = new_pixel(picture, i, j_g, image_kernel, mult);
				new_mat[i][j_g] = clamp((int)round(g_pixel), 0, 255);
				int j_b = 3 * j + 2;
				b_pixel = new_pixel(picture, i, j_b, image_kernel, mult);
				new_mat[i][j_b] = clamp((int)round(b_pixel), 0, 255);
			}
		}
	}
}

int apply_filter(image_t *picture)
{
	char filter_buffer[MEDIUM_BUFFER + 1];
	fgets(filter_buffer, MEDIUM_BUFFER, stdin);
	int len = strlen(filter_buffer);
	filter_buffer[len - 1] = '\0';
	char *filter = strtok(filter_buffer, " ");
	if (picture->magic_word == '0') { //no image
		printf("No image loaded\n");
		return 0;
	}
	if (!filter) {
		printf("Invalid command\n");
		return 0;
	}
	if (picture->magic_word == '2' || picture->magic_word == '5') { //grey
		printf("Easy, Charlie Chaplin\n");
	} else { //apply filter
		uc **new_mat = alloc_copy_matrix(picture->width, picture->height, 3);
		if (!new_mat)
			return ERR_ALLOC;
		image_copy(picture, new_mat, 3);
		if (strstr(filter, "EDGE")) {
			apply(picture, new_mat, 1);
			printf("APPLY %s done\n", filter);
		} else if (strstr(filter, "SHARPEN")) {
			apply(picture, new_mat, 2);
			printf("APPLY %s done\n", filter);
		} else if (strstr(filter, "BLUR") && !strstr(filter, "GAUSSIAN_BLUR")) {
			apply(picture, new_mat, 3);
			printf("APPLY %s done\n", filter);
		} else if (strstr(filter, "GAUSSIAN_BLUR")) {
			apply(picture, new_mat, 4);
			printf("APPLY %s done\n", filter);
		} else {
			printf("APPLY parameter invalid\n");
		}
		free_image_matrix(picture);
		picture->mat = new_mat;
	}
	return 0;
}
