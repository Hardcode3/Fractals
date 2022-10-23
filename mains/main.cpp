#include <iostream>
#include <mandelbrot_set.h>
#include <image.h>
#include <misc.h>

int main(int argc, char** argv) {

	mandelbrot("G:\sample_1.bmp", -2, 1, -1, 1, 1368 * .6, 720 * .6, 1);
	mandelbrot("G:\sample_5.bmp", -2, 1, -1, 1, 1368 * .6, 720 * .6, 5);
	mandelbrot("G:\sample_10.bmp", -2, 1, -1, 1, 1368 * .6, 720 * .6, 10);
	mandelbrot("G:\sample_20.bmp", -2, 1, -1, 1, 1368 * .6, 720 * .6, 20);
	mandelbrot("G:\sample_30.bmp", -2, 1, -1, 1, 1368 * .6, 720 * .6, 30);
	mandelbrot("G:\sample_40.bmp", -2, 1, -1, 1, 1368 * .6, 720 * .6, 40);
	mandelbrot("G:\sample_50.bmp", -2, 1, -1, 1, 1368 * .6, 720 * .6, 50);
	mandelbrot("G:\sample_60.bmp", -2, 1, -1, 1, 1368 * .6, 720 * .6, 60);
	mandelbrot("G:\sample_70.bmp", -2, 1, -1, 1, 1368 * .6, 720 * .6, 70);
	mandelbrot("G:\sample_80.bmp", -2, 1, -1, 1, 1368 * .6, 720 * .6, 80);
	mandelbrot("G:\sample_90.bmp", -2, 1, -1, 1, 1368 * .6, 720 * .6, 90);
	mandelbrot("G:\sample_100.bmp", -2, 1, -1, 1, 1368 * .6, 720 * .6, 100);
	mandelbrot("G:\sample_110.bmp", -2, 1, -1, 1, 1368 * .6, 720 * .6, 110);

	return 0;
}