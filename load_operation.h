#ifndef LOAD_H

#define LOAD_H
#include <stdio.h>
#include "necessaries.h"

int read_raw(char *filename, image_t *picture, int curr_poz, int size);

void read_plain(FILE *photo, image_t *picture, int size);

void read_comment(FILE *photo);

void read_magic_word(FILE *photo, image_t *picture);

void read_width_height(FILE *photo, image_t *picture);

void read_max_color(FILE *photo, image_t *picture);

void load_image(image_t *picture);

#endif
