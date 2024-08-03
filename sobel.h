#pragma once

void sobel(unsigned char *dst, unsigned char *src, int cols, int rows);
void sobel_mt(unsigned char *dst, unsigned char *src, int cols, int rows);
