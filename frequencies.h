#ifndef FREQUENCIES_H

#define FREQUENCIES_H
#include "necessaries.h"

void frequency_range(const image_t *picture, int freq[]);

void frequency_all(const image_t *picture, int freq[]);

void update_freq(int freq[], int bins, int pack);

int search_max_freq(int freq[]);

#endif
