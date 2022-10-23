#include <mandelbrot_set.h>
#include <image.h>
#include <misc.h>
#include <cmath>
#include <vector>
#include <complex>
#include <assert.h>

std::complex<double> mandelbrot_sequence(unsigned int n, const std::complex<double> &c) {
	if (n == 0) {
		return std::complex<double>(0., 0.);
	}
	else {
		return pow(mandelbrot_sequence(n - 1, c), 2) + c;
	}
}

void grid(
	complex_matrix& complex_range_matrix, 
	bool_matrix& stability_matrix, 
	const double x_min, 
	const double x_max, 
	const double y_min, 
	const double y_max, 
	const unsigned int width,
	const unsigned int height,
	const unsigned int iterations) {

	assert(x_min < x_max);
	assert(y_min < y_max);
	assert(width >= 0);
	assert(height >= 0);
	assert(iterations > 0);
	
	std::vector<double>  re = linspace<double>(x_min, x_max, width);
	std::vector<double>  im = linspace<double>(y_min, y_max, height);

	std::vector<std::complex<double>> complex_temp;
	std::vector<bool> bool_temp;

	for (unsigned int im_index = 0; im_index < im.size(); im_index++) {

		complex_temp.clear();
		bool_temp.clear();

		for (unsigned int re_index = 0; re_index < re.size(); re_index++) {
			std::complex<double> temp_complex(re[re_index], im[im_index]);

			complex_temp.push_back(temp_complex);
			bool_temp.push_back((std::abs(mandelbrot_sequence(iterations, temp_complex)) <= 2));
		}

		complex_range_matrix.push_back(complex_temp);
		stability_matrix.push_back(bool_temp);
	}
	//print_matrix(complex_range_matrix);
	//print_matrix(stability_matrix);

	assert((stability_matrix.size() == height) && (stability_matrix[0].size() == width));
}

void mandelbrot(
	const char* file_name,
	const double x_min,
	const double x_max,
	const double y_min,
	const double y_max,
	const unsigned int width,
	const unsigned int height,
	const unsigned int iterations, 
	const Img::Color &color_0,
	const Img::Color &color_1) {

	assert(x_min < x_max);
	assert(y_min < y_max);
	assert(width >= 100);
	assert(height >= 100);
	assert(iterations > 0);

	complex_matrix c_matrix;
	bool_matrix stability_matrix;

	grid(c_matrix, stability_matrix, x_min, x_max, y_min, y_max, width, height, iterations);
	
	Img::Image image(file_name, width, height);
	image.write_bool_matrix(stability_matrix, color_0, color_1);

	c_matrix.clear();
	stability_matrix.clear();
}
	



