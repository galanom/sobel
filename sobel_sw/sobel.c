#include <stdlib.h>
#include <pthread.h>
#include "kernel.h"

struct thr_arg {
	unsigned char *restrict dst;
	unsigned char *restrict src;
	int cols;
	int rows;
};

void sobel(unsigned char *restrict dst, unsigned char *restrict src, int cols, int rows)
{
	int sumx, sumy, idx;
	for (int r = 1; r <= rows-2; ++r) {
		for (int c = 1; c <= cols-2; ++c) {
			idx = r*cols+c;
			sumx =	src[idx-cols -1]*Gx_00 +
				src[idx-cols   ]*Gx_01 +
				src[idx-cols +1]*Gx_02 +
				src[idx      -1]*Gx_10 +
				src[idx        ]*Gx_11 +
				src[idx      +1]*Gx_12 +
				src[idx+cols -1]*Gx_20 +
				src[idx+cols   ]*Gx_21 +
				src[idx+cols +1]*Gx_22;

			sumy =	src[idx-cols -1]*Gy_00 +
				src[idx-cols   ]*Gy_01 +
				src[idx-cols +1]*Gy_02 +
				src[idx      -1]*Gy_10 +
				src[idx        ]*Gy_11 +
				src[idx      +1]*Gy_12 +
				src[idx+cols -1]*Gy_20 +
				src[idx+cols   ]*Gy_21 +
				src[idx+cols +1]*Gy_22;

			dst[idx] = abs(sumx) + abs(sumy);
		}
	}
}

void *sobel_thr(void *arg)
{
	struct thr_arg *p = (struct thr_arg *)arg;
	sobel(p->dst, p->src, p->cols, p->rows);
	return NULL;
}

void sobel_mt(unsigned char *restrict dst, unsigned char *restrict src, int cols, int rows)
{
	pthread_t thr0, thr1;
	static struct thr_arg arg0, arg1;
	arg0.dst=dst;
	arg0.src=src;
	arg0.cols=cols;
	arg0.rows=rows/2;
	arg1.dst=dst+cols*rows/2;
	arg1.src=src+cols*rows/2;
	arg1.cols=cols;
	arg1.rows=rows/2;
	pthread_create(&thr0, NULL, sobel_thr, (void *)&arg0);
	pthread_create(&thr1, NULL, sobel_thr, (void *)&arg1);
	pthread_join(thr0, NULL);
	pthread_join(thr1, NULL);
}
