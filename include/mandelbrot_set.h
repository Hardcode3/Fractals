#pragma once

#include <vector>
#include <complex>
#include <image.h>

typedef std::vector <std::vector<std::complex<double>>> complex_matrix;
typedef std::vector <std::vector<bool>> bool_matrix;

std::complex<double> mandelbrot_sequence(unsigned int n, const std::complex<double> &c);

void grid(
	complex_matrix& complex_range_matrix,
	bool_matrix& stability_matrix,
	const double x_min,
	const double x_max,
	const double y_min,
	const double y_max,
	const unsigned int width,
	const unsigned int height,
	const unsigned int interations);

void mandelbrot(
	const char* file_name,
	const double x_min,
	const double x_max,
	const double y_min,
	const double y_max,
	const unsigned int width,
	const unsigned int height,
	const unsigned int iterations,
	const Img::Color &color_0=Img::BLACK,
	const Img::Color &color_1=Img::WHITE);