#include <stdio.h>
#include <stdlib.h>
#include "necessaries.h"
#include "basic.h"
#include "rotate_operation.h"

int is_square(const image_t *picture)
{
	if ((picture->x2 - picture->x1) == (picture->y2 - picture->y1))
		return 1;
	return 0;
}

int all_selected(const image_t *picture)
{
	if (picture->x1 == 0 && picture->y1 == 0)
		if (picture->x2 == picture->width && picture->y2 == picture->height)
			return 1;
	return 0;
}

int supported_angle(int angle)
{
	if (angle == 90 || angle == 180 || angle == 270)
		return 1;
	if (angle == -90 || angle == -180 || angle == -270)
		return 1;
	if (angle == 360 || angle == -360 || angle == 0)
		return 1;
	return 0;
}

void rotate_right(image_t *picture, uc **rotated_matrix, int size)
{
	int h = picture->y2 - picture->y1;
	int w = picture->x2 - picture->x1;
	for (int i = 0; i < h; ++i) {
		for (int j = 0; j < w; ++j) {
			int rot_i = j;
			int img_i = picture->y1 + i;
			if (size == 3) { //if colored
				//red
				int rot_j_r = size * (h - i) - 1 - 2;
				int img_j_r = size * (picture->x1 + j);
				rotated_matrix[rot_i][rot_j_r] = picture->mat[img_i][img_j_r];
				//green
				int rot_j_g = size * (h - i) - 1 - 1;
				int img_j_g = size * (picture->x1 + j) + 1;
				rotated_matrix[rot_i][rot_j_g] = picture->mat[img_i][img_j_g];
				//blue
				int rot_j_b = size * (h - i) - 1 - 0;
				int img_j_b = size * (picture->x1 + j) + 2;
				rotated_matrix[rot_i][rot_j_b] = picture->mat[img_i][img_j_b];
			} else {
				//grey
				int rot_j = h - i - 1;
				int img_j = size * (picture->x1 + j);
				rotated_matrix[rot_i][rot_j] = picture->mat[img_i][img_j];
			}
		}
	}
	if (all_selected(picture)) { //if the whole picture is selected
		free_image_matrix(picture);
		picture->mat = rotated_matrix;
		picture->width ^= picture->height;
		picture->height ^= picture->width;
		picture->width ^= picture->height;
		int rot_x1 = picture->y1;
		int rot_x2 = picture->y2;
		int rot_y1 = picture->x1;
		int rot_y2 = picture->x2;
		select_pixels(picture, rot_x1, rot_y1, rot_x2, rot_y2);
	} else { //if a NxN submatrix is selected
		//filling the submatrix with the rotated values
		int offset_i, offset_j;
		for (int i = picture->y1; i < picture->y2; ++i) {
			offset_j = 0;
			for (int j = size * picture->x1; j < size * picture->x2; ++j) {
				offset_i = i - picture->y1;
				offset_j = j - size * picture->x1;
				picture->mat[i][j] = rotated_matrix[offset_i][offset_j];
			}
		}
		//freeing the rotated submatrix
		for (int i = 0; i < h; ++i)
			free(rotated_matrix[i]);
		free(rotated_matrix);
	}
}

int rotate_image(image_t *picture)
{
	int angle;
	scanf("%d", &angle);
	if (picture->magic_word == '0') {
		printf("No image loaded\n");
	} else if (!all_selected(picture) && !is_square(picture)) {
		printf("The selection must be square\n");
	} else if (!supported_angle(angle)) {
		printf("Unsupported rotation angle\n");
	} else if (angle == 360 || angle == -360 || angle == 0) {
		printf("Rotated %d\n", angle);
	} else {
		int rotations;
		if (angle >= 0)
			rotations = angle / 90;
		else
			rotations = (360 + angle) / 90;
		int rot_w, rot_h;
		int size;
		if (picture->magic_word == '3' || picture->magic_word == '6')
			size = 3;
		else if (picture->magic_word == '2' || picture->magic_word == '5')
			size = 1;
		//initially the image is rotated 0 degrees
		rot_w = picture->x2 - picture->x1;
		rot_h = picture->y2 - picture->y1;
		for (int k = 0; k < rotations; ++k) {
			//at each step the image gets rotated 90 degrees
			//so width and height get swapped
			rot_w ^= rot_h;
			rot_h ^= rot_w;
			rot_w ^= rot_h;
			uc **rotated_matrix = alloc_copy_matrix(rot_w, rot_h, size);
			if (!rotated_matrix)
				return ERR_ALLOC;
			rotate_right(picture, rotated_matrix, size);
		}
		printf("Rotated %d\n", angle);
	}
	return 0;
}
