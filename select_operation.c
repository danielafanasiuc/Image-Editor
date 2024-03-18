#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "necessaries.h"
#include "basic.h"
#include "select_operation.h"

int in_range(const image_t *picture, int X1, int Y1, int X2, int Y2)
{
	if (X1 < 0 || X1 > picture->width)
		return 0;
	if (Y1 < 0 || Y1 > picture->height)
		return 0;
	if (X2 < 0 || X2 > picture->width)
		return 0;
	if (Y2 < 0 || Y2 > picture->height)
		return 0;
	if (X1 == X2 || Y1 == Y2)
		return 0;
	return 1;
}

void select_range(image_t *picture)
{
	char selection_type[MEDIUM_BUFFER + 1];
	fgets(selection_type, MEDIUM_BUFFER, stdin);
	if (picture->magic_word == '0') {
		printf("No image loaded\n");
	} else {
		if (strstr(selection_type, "ALL")) {
			select_pixels(picture, 0, 0, picture->width, picture->height);
			printf("Selected ALL\n");
		} else {
			char *val1 = strtok(selection_type, " ");
			if (!val1) {
				printf("Invalid command\n");
				return;
			}
			if (!is_number(val1)) {
				printf("Invalid command\n");
				return;
			}
			char *val2 = strtok(NULL, " ");
			if (!val2) {
				printf("Invalid command\n");
				return;
			}
			if (!is_number(val2)) {
				printf("Invalid command\n");
				return;
			}
			char *val3 = strtok(NULL, " ");
			if (!val3) {
				printf("Invalid command\n");
				return;
			}
			if (!is_number(val3)) {
				printf("Invalid command\n");
				return;
			}
			char *val4 = strtok(NULL, "\n ");
			if (!val4) {
				printf("Invalid command\n");
				return;
			}
			if (!is_number(val4)) {
				printf("Invalid command\n");
				return;
			}
			int X1 = atoi(val1);
			int Y1 = atoi(val2);
			int X2 = atoi(val3);
			int Y2 = atoi(val4);
			if (in_range(picture, X1, Y1, X2, Y2)) {
				if (X1 > X2) {
					X1 ^= X2;
					X2 ^= X1;
					X1 ^= X2;
				}
				if (Y1 > Y2) {
					Y1 ^= Y2;
					Y2 ^= Y1;
					Y1 ^= Y2;
				}
				select_pixels(picture, X1, Y1, X2, Y2);
				printf("Selected %d %d %d %d\n", X1, Y1, X2, Y2);
			} else {
				printf("Invalid set of coordinates\n");
			}
		}
	}
}
