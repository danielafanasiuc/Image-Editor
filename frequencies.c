#include "necessaries.h"
#include "frequencies.h"

void frequency_range(const image_t *picture, int freq[])
{
	for (int i = picture->y1; i < picture->y2; ++i)
		for (int j = picture->x1; j < picture->x2; ++j)
			freq[picture->mat[i][j]]++;
}

void frequency_all(const image_t *picture, int freq[])
{
	for (int i = 0; i < picture->height; ++i)
		for (int j = 0; j < picture->width; ++j)
			freq[picture->mat[i][j]]++;
}

void update_freq(int freq[], int bins, int pack)
{
	for (int k = 0; k < bins; ++k) {
		int sum = 0;
		for (int it = 0; it < pack; ++it)
			sum += freq[k * pack + it];
		freq[k * pack] = sum;
		//not needed
		for (int it = 0; it < pack; ++it)
			freq[k * pack + it] = freq[k * pack];
	}
}

int search_max_freq(int freq[])
{
	//we can with ternary operator also
	int max = 0;
	for (int i = 0; i < 256; ++i)
		if (freq[i] > max)
			max = freq[i];
	return max;
}
