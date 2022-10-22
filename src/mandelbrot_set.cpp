#include <mandelbrot_set.h>
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

void grid(complex_matrix& complex_range_matrix, 
	bool_matrix& stability_matrix, 
	const double x_min, 
	const double x_max, 
	const double y_min, 
	const double y_max, 
	const unsigned int pixel_density,
	const unsigned int interations) {

	assert(x_min < x_max);
	assert(y_min < y_max);
	
	std::vector<double>  re = linspace<double>(x_min, x_max, static_cast<int>((x_max - x_min) * pixel_density));
	std::vector<double>  im = linspace<double>(y_min, y_max, static_cast<int>((y_max - y_min) * pixel_density));

	std::vector<std::complex<double>> complex_temp;
	std::vector<bool> bool_temp;

	for (unsigned int re_index = 0; re_index < re.size(); re_index++) {

		complex_temp.clear();
		bool_temp.clear();

		for (unsigned int im_index = 0; im_index < im.size(); im_index++) {
			std::complex<double> temp_complex(re[re_index], im[im_index]);
			complex_temp.push_back(temp_complex);
			bool_temp.push_back((std::abs(mandelbrot_sequence(interations, temp_complex)) <= 2));
		}

		complex_range_matrix.push_back(complex_temp);
		stability_matrix.push_back(bool_temp);
	}
}


