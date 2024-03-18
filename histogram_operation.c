#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "necessaries.h"
#include "frequencies.h"
#include "histogram_operation.h"

void histogram(const image_t *picture)
{
	char histogram_buffer[MEDIUM_BUFFER + 1];
	fgets(histogram_buffer, MEDIUM_BUFFER, stdin);
	int len = strlen(histogram_buffer);
	histogram_buffer[len - 1] = '\0';
	char *star_str = strtok(histogram_buffer, " ");
	if (picture->magic_word == '0') {
		printf("No image loaded\n");
		return;
	}
	if (!star_str) {
		printf("Invalid command\n");
		return;
	}
	int stars = atoi(star_str);
	char *bin_str = strtok(NULL, " ");
	if (!bin_str) {
		printf("Invalid command\n");
		return;
	}
	//check if there are more parameters
	char *parameter = strtok(NULL, " ");
	if (parameter) {
		printf("Invalid command\n");
		return;
	}
	int bins = atoi(bin_str);
	if (picture->magic_word == '3' || picture->magic_word == '6') {
		printf("Black and white image needed\n");
	} else {
		int freq[256] = {0};
		frequency_range(picture, freq);
		int pack = 256 / bins;
		update_freq(freq, bins, pack);
		int max_freq = search_max_freq(freq);
		for (int k = 0; k < bins; ++k) {
			int count;
			count = stars * freq[k * pack] / max_freq;
			printf("%d\t|\t", count);
			for (int i = 0; i < count; ++i)
				printf("*");
			printf("\n");
		}
	}
}
