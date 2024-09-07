#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>

#include "sobel.h"

int main(int argc, char *argv[]) {
	if (argc != 4) {
		fprintf(stderr, "Usage: %s <filename> <cols> <rows>\n", argv[0]);
		return 1;
	}
	int err = 0;
	int cols = atoi(argv[2]);
	int rows = atoi(argv[3]);
	ssize_t expected_size = cols*rows;
	unsigned char *image_src = malloc(expected_size);
	unsigned char *image_dst = malloc(expected_size);
	char *fname = malloc(4096);
	if (!image_src || !image_dst || !fname) {
		fprintf(stderr, "Memory allocation failed\n");
		return 1;
	}
	strcpy(fname, argv[1]);

	// Image read

	int fd = open(fname, O_RDONLY);
	if (fd == -1) {
		perror("Error opening file");
		goto abort;
	}

	struct stat st;
	if (fstat(fd, &st) != 0) {
		perror("Error getting file size");
		goto abort;
	}

	ssize_t file_size = st.st_size;
	if (file_size != expected_size) {
		fprintf(stderr, "Error: file size (%zu bytes) does not match expected image size (%zu bytes)\n", file_size, expected_size);
		goto abort;
	}

	ssize_t read_size = read(fd, image_src, expected_size);
	if (read_size != expected_size) {
		fprintf(stderr, "Error reading image data\n");
		goto abort;
	}

	close(fd);

	// Processing
	struct timespec t0, t1;
	double dt;

	clock_gettime(CLOCK_MONOTONIC, &t0);
	sobel_mt(image_dst, image_src, cols, rows);
	clock_gettime(CLOCK_MONOTONIC, &t1);
	dt  = (t1.tv_sec - t0.tv_sec)*1e3 + (t1.tv_nsec - t0.tv_nsec)/1e6;
	printf("Execution time: %6.4f\n", dt);

	// Image write
	strcat(fname, "_out");
	fd = open(fname, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if (fd == -1) {
		perror("Error opening file for writing");
		goto abort;
	}

	ssize_t write_size = write(fd, image_dst, expected_size);
	if (write_size != expected_size) {
		fprintf(stderr, "Error writing image data\n");
		goto abort;
	}
	goto normal;
abort:	err = 1;
normal:
	if (fd > 0) {
		close(fd);
	}
	free(image_src);
	free(image_dst);
	return err;
}

