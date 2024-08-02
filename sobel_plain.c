#include <stdlib.h>
#include "kernel.h"

void sobel_plain(unsigned char *dst, unsigned char *src, int cols, int rows)
{
	int sumx, sumy;
	for (int r = 1; r <= rows-2; ++r) {
		for (int c = 1; c <= cols-2; ++c) {
			sumx =	src[(r-1)*cols + c-1]*Gx_00 +
				src[(r-1)*cols + c  ]*Gx_01 +
				src[(r-1)*cols + c+1]*Gx_02 +
				src[(r  )*cols + c-1]*Gx_10 +
				src[(r  )*cols + c  ]*Gx_11 +
				src[(r  )*cols + c+1]*Gx_12 +
				src[(r+1)*cols + c-1]*Gx_20 +
				src[(r+1)*cols + c  ]*Gx_21 +
				src[(r+1)*cols + c+1]*Gx_22;

			sumy =	src[(r-1)*cols + c-1]*Gy_00 +
				src[(r-1)*cols + c  ]*Gy_01 +
				src[(r-1)*cols + c+1]*Gy_02 +
				src[(r  )*cols + c-1]*Gy_10 +
				src[(r  )*cols + c  ]*Gy_11 +
				src[(r  )*cols + c+1]*Gy_12 +
				src[(r+1)*cols + c-1]*Gy_20 +
				src[(r+1)*cols + c  ]*Gy_21 +
				src[(r+1)*cols + c+1]*Gy_22;

			dst[r*cols + c] = abs(sumx) + abs(sumy);
		}
	}
}
