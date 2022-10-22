#pragma once

#include <vector>
#include <complex>

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
	const unsigned int pixel_density,
	const unsigned int interations);