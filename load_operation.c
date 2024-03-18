#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "necessaries.h"
#include "basic.h"
#include "load_operation.h"

int read_raw(char *filename, image_t *picture, int curr_poz, int size)
{
	FILE *photo = fopen(filename, "rb");
	if (!photo)
		return ERR_FILE;
	fseek(photo, curr_poz, SEEK_SET);
	for (int i = 0; i < picture->height; ++i)
		for (int j = 0; j < size * picture->width; ++j)
			fread(&picture->mat[i][j], sizeof(uc), 1, photo);
	fclose(photo);
	return 0;
}

void read_plain(FILE *photo, image_t *picture, int size)
{
	for (int i = 0; i < picture->height; ++i)
		for (int j = 0; j < size * picture->width; ++j) {
			int value;
			fscanf(photo, "%d", &value);
			picture->mat[i][j] = (uc)value;
		}
}

void read_comment(FILE *photo)
{
	//creating a buffer for temporarily storing data
	char buffer[MAX_BUFFER + 1];
	int buffer_len;
	//reading the comment till we reach endline
	do {
		fgets(buffer, MAX_BUFFER, photo);
		buffer_len = strlen(buffer);
	} while (buffer[buffer_len - 1] != '\n');
}

void read_magic_word(FILE *photo, image_t *picture)
{
	char magic_word_buffer[SMALL_BUFFER + 1];
	fgets(magic_word_buffer, SMALL_BUFFER, photo);
	picture->magic_word = magic_word_buffer[1];
}

void read_width_height(FILE *photo, image_t *picture)
{
	char wh_buffer[SMALL_BUFFER + 1];
	fgets(wh_buffer, SMALL_BUFFER, photo);
	char *w = strtok(wh_buffer, " ");
	char *h = strtok(NULL, "\n ");
	picture->width = atoi(w);
	picture->height = atoi(h);
}

void read_max_color(FILE *photo, image_t *picture)
{
	char max_c_val_buffer[SMALL_BUFFER + 1];
	fgets(max_c_val_buffer, SMALL_BUFFER, photo);
	char *color = strtok(max_c_val_buffer, "\n ");
	picture->max_color = atoi(color);
}

void load_image(image_t *picture)
{
	int ok = 0;
	char filename[MAX_NAME + 1];
	scanf("%s", filename);
	FILE *photo = fopen(filename, "r");
	if (!photo) {
		printf("Failed to load %s\n", filename);
		return;
	}
	int row_number = 0;
	while (row_number <= 3) {
		char check_comment;
		fscanf(photo, "%c", &check_comment);
		//if we reach a comment we ignore it
		if (check_comment == '#') {
			read_comment(photo);
		} else { //reading data
			fseek(photo, -1, SEEK_CUR);
			if (row_number == 0) { //reading magic_word
				read_magic_word(photo, picture);
			} else if (row_number == 1) { //reading width and height
				read_width_height(photo, picture);
			} else if (row_number == 2) { //reading maximum color value
				read_max_color(photo, picture);
			} else if (row_number == 3) { //reading mat depending on the format
				//allocating the image matrix depending on the format
				if (picture->magic_word != '3' && picture->magic_word != '6')
					ok = alloc_image_matrix(picture, 1);
				else
					ok = alloc_image_matrix(picture, 3);
				if (ok != 0) {
					fclose(photo);
					//if cannot allocate, the pictures get back to default
					set_default(picture);
					printf("Failed to load %s\n", filename);
					return;
				}
				//reading the image matrix
				if (picture->magic_word == '2') {
					read_plain(photo, picture, 1);
					fclose(photo);
				} else if (picture->magic_word == '5') {
					int curr_poz = ftell(photo);
					fclose(photo);
					ok = read_raw(filename, picture, curr_poz, 1);
					if (ok != 0) {
						//if binary file cannot be opened, the matrix gets
						//deallocated and the picture gets set to default
						free_image_matrix(picture);
						set_default(picture);
						printf("Failed to load %s\n", filename);
						return;
					}
				} else if (picture->magic_word == '3') {
					read_plain(photo, picture, 3);
					fclose(photo);
				} else if (picture->magic_word == '6') {
					int curr_poz = ftell(photo);
					fclose(photo);
					ok = read_raw(filename, picture, curr_poz, 3);
					if (ok != 0) {
						free_image_matrix(picture);
						set_default(picture);
						printf("Failed to load %s\n", filename);
						return;
					}
				}
			}
			row_number++;
		}
	}
	//upon loading an image all the pixels are selected
	select_pixels(picture, 0, 0, picture->width, picture->height);
	printf("Loaded %s\n", filename);
}
