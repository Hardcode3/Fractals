#include <complex>
#include <vector>
#include <assert.h>

/*
* Type definition of uint_matrix
* Corresponds to a std::vector<std::vector<double>>
*/
typedef std::vector<std::vector<double>> double_matrix;

/*
* Type definition of complex_matrix
* Corresponds to a std::vector <std::vector<std::complex<double>>>
*/
typedef std::vector <std::vector<std::complex<double>>> complex_matrix;


class Fractal
{
protected:
// fractal properties
const char* filename_;
const double image_offset_x_;
const double image_offset_y_;
const double image_ratio_;
const int image_resolution_;
const double image_zoom_;
const unsigned int iterations_;
const unsigned int symmetry_;
const std::complex<double> complex_;

double x_scale_;
double y_scale_;
double x_min_;
double x_max_;
double y_min_;
double y_max_;
double width_;
double height_;

// container
complex_matrix complex_plane_;
double_matrix output_array_;


public:
Fractal() = delete;
Fractal(const char* filename,
	const std::complex<double> complex,
	const double offset_x,
	const double offset_y,
	const double image_ratio,
	const unsigned int resolution,
	const double zoom,
	const unsigned int iterations,
	const double symmetry);
~Fractal();

virtual unsigned int sequence(unsigned int real, unsigned int imaginary) = 0;
void compute_set();

};


// Mandelbrot fractal class
class Mandelbrot: public Fractal
{
public:
Mandelbrot(
	const char* filename,
	const std::complex<double> complex,
	const double offset_x,
	const double offset_y,
	const double image_ratio,
	const unsigned int resolution,
	const double zoom,
	const unsigned int iterations,
	const double symmetry
);

~Mandelbrot();

virtual unsigned int sequence(unsigned int real, unsigned int imaginary);

};


// Julia fractal class
class Julia: public Fractal
{
public:
Julia(
	const char* filename,
	const std::complex<double> complex,
	const double offset_x,
	const double offset_y,
	const double image_ratio,
	const unsigned int resolution,
	const double zoom,
	const unsigned int iterations,
	const double symmetry);
~Julia();

virtual unsigned int sequence(unsigned int real, unsigned int imaginary);
};
