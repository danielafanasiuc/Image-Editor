#include <stdio.h>
#include <string.h>
#include "necessaries.h"
#include "save_operation.h"

int save_image(const image_t *picture)
{
	char filename[MAX_NAME + 1];
	scanf("%s", filename);
	char ascii[SMALL_BUFFER + 1];
	fgets(ascii, SMALL_BUFFER, stdin);
	if (picture->magic_word == '0') {
		printf("No image loaded\n");
	} else {
		if (!strstr(ascii, "ascii")) { //if we save in binary
			FILE *photo = fopen(filename, "wt");
			if (!photo)
				return ERR_FILE;
			int size;
			if (picture->magic_word == '2' || picture->magic_word == '5') {
				fprintf(photo, "P5\n"); //grey
				size = 1;
			} else {
				fprintf(photo, "P6\n"); //color
				size = 3;
			}
			fprintf(photo, "%d %d\n", picture->width, picture->height);
			fprintf(photo, "%d\n", picture->max_color);
			fclose(photo);
			FILE *binary_photo = fopen(filename, "ab");
			if (!binary_photo)
				return ERR_FILE;
			for (int i = 0; i < picture->height; ++i)
				for (int j = 0; j < size * picture->width; ++j)
					fwrite(&picture->mat[i][j], sizeof(uc), 1, binary_photo);
			fclose(binary_photo);
		} else { //if we save in ascii
			FILE *text_photo = fopen(filename, "wt");
			if (!text_photo)
				return ERR_FILE;
			int size;
			if (picture->magic_word == '2' || picture->magic_word == '5') {
				fprintf(text_photo, "P2\n"); //grey
				size = 1;
			} else {
				fprintf(text_photo, "P3\n"); //color
				size = 3;
			}
			fprintf(text_photo, "%d %d\n", picture->width, picture->height);
			fprintf(text_photo, "%d\n", picture->max_color);
			for (int i = 0; i < picture->height; ++i) {
				for (int j = 0; j < size * picture->width; ++j)
					fprintf(text_photo, "%d ", (int)picture->mat[i][j]);
				fprintf(text_photo, "\n");
			}
			fclose(text_photo);
		}
		printf("Saved %s\n", filename);
	}
	return 0;
}
