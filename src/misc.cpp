#include <assert.h>

#include <misc.h>
#include <sequence.h>


void find_extremums(
	double & current_value,
	double & min_value,
	double & max_value)
{
	if (current_value > max_value) { max_value = current_value; }
	else if (current_value < min_value) { min_value = current_value; }
}

void compute_set(
	double_matrix& stability_plane,
	double & min_value,
	double & max_value,
	const double& x_min,
	const double& x_max,
	const double& y_min,
	const double& y_max,
	const unsigned int& width,
	const unsigned int& height,
	const unsigned int& iterations)
{
	assert(x_min < x_max);
	assert(y_min < y_max);
	assert(width >= 0);
	assert(height >= 0);
	assert(iterations > 0);

	std::vector<double>  re = linspace<double>(x_min, x_max, width);
	std::vector<double>  im = linspace<double>(y_min, y_max, height);

	assert(re.size() == width);
	assert(im.size() == height);

	std::vector<double> __temp_vector;
	double __temp_current_value(0);

	for (unsigned int im_index = 0; im_index < height; im_index++) 
		{
			__temp_vector.clear();
			for (unsigned int re_index = 0; re_index < width; re_index++) 
			{
				std::complex<double> temp_complex(re[re_index], im[im_index]);
				__temp_current_value = mandelbrot_sequence(iterations, std::complex<double>(0, 0), temp_complex);
				
				find_extremums(__temp_current_value, min_value, max_value);
				__temp_vector.push_back(__temp_current_value);
			}
			stability_plane.push_back(__temp_vector);
		}
	assert((stability_plane.size() == height) && (stability_plane[0].size() == width));
}


void fractal(
	const char* file_name,
	const double& offset_x,
	const double& offset_y,
	const double& image_ratio,
	const double& resolution,
	const double& zoom,
	const unsigned int& iterations)
{
	const double x_scale = 2.;
	const double y_scale = 2. / image_ratio;
	const double x_min = -x_scale / (2. * zoom) - offset_x;
	const double x_max = x_scale / (2. * zoom) - offset_x;
	const double y_min = -y_scale / (2. * zoom) - offset_y;
	const double y_max = y_scale / (2. * zoom) - offset_y;
	const double width = resolution * x_scale;
	const double height = resolution * y_scale;

	double_matrix complex_plane;
	double min_value = 25000000, max_value = 0;
	
	assert(x_min < x_max);
	assert(y_min < y_max);
	assert(width >= 100);
	assert(height >= 100);
	assert(iterations > 0);

	compute_set(complex_plane, min_value, max_value, x_min, x_max, y_min, y_max, width, height, iterations);
	Img::Image image(file_name, width, height);
	image.write_matrix(complex_plane, min_value, max_value);

	complex_plane.clear();
}