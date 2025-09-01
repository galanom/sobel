#pragma once

void sobel(unsigned char *restrict dst, unsigned char *restrict src, int cols, int rows);
void sobel_mt(unsigned char *restrict dst, unsigned char *restrict src, int cols, int rows);
