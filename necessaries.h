#ifndef NECESSARIES_H

#define NECESSARIES_H
#define ERR_ALLOC -1
#define ERR_FILE -2
#define MAX_NAME 4096
#define MAX_BUFFER 1000
#define SMALL_BUFFER 15
#define MEDIUM_BUFFER 50

typedef unsigned char uc;

typedef struct {
	char magic_word; //the number is stored as its character in ascii
	int width, height;
	int max_color;
	int x1, x2, y1, y2; //selected pixels
	uc **mat; //the image matrix (allocated dymanically)
} image_t;

void set_default(image_t *picture);

int alloc_image_matrix(image_t *picture, int size);

void free_image_matrix(image_t *picture);

uc **alloc_copy_matrix(int width, int height, int size);

#endif
