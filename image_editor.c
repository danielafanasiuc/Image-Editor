#include <stdio.h>
#include <string.h>
#include "necessaries.h"
#include "basic.h"
#include "frequencies.h"
#include "load_operation.h"
#include "save_operation.h"
#include "select_operation.h"
#include "filter_operation.h"
#include "histogram_operation.h"
#include "equalize_operation.h"
#include "crop_operation.h"
#include "rotate_operation.h"

int main(void)
{
	image_t picture;
	set_default(&picture);
	int ok = 0;
	while (1) {
		char operation[MEDIUM_BUFFER];
		scanf("%s", operation);
		if (strcmp(operation, "LOAD") == 0) {
			if (picture.magic_word != '0') {
				//if there is another photo, deallocate the old resources
				//and set the old one to default
				free_image_matrix(&picture);
				set_default(&picture);
			}
			load_image(&picture);
		} else if (strcmp(operation, "SELECT") == 0) {
			select_range(&picture);
		} else if (strcmp(operation, "HISTOGRAM") == 0) {
			histogram(&picture);
		} else if (strcmp(operation, "EQUALIZE") == 0) {
			equalize(&picture);
		} else if (strcmp(operation, "ROTATE") == 0) {
			ok = rotate_image(&picture);
			if (ok != 0)
				break;
		} else if (strcmp(operation, "CROP") == 0) {
			ok = crop_image(&picture);
			if (ok != 0)
				break;
		} else if (strcmp(operation, "APPLY") == 0) {
			ok = apply_filter(&picture);
			if (ok != 0)
				break;
		} else if (strcmp(operation, "EXIT") == 0) {
			if (picture.magic_word == '0')
				printf("No image loaded\n");
			break;
		} else if (strcmp(operation, "SAVE") == 0) {
			ok = save_image(&picture);
			if (ok != 0)
				break;
		} else {
			char buffer[MAX_BUFFER + 1];
			fgets(buffer, MAX_BUFFER, stdin);
			printf("Invalid command\n");
		}
	}
	//freeing all the resources and exiting
	free_image_matrix(&picture);
	return 0;
}
