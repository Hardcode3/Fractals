#include <complex>
#include <vector>
#include <assert.h>
#include <iostream>
#include <string>
#include <cmath>

#include <image.h>

/*
* Type definition of uint_matrix
* Corresponds to a std::vector<std::vector<double>>
*/
typedef std::vector<std::vector<float>> double_matrix;

/*
* Type definition of complex_matrix
* Corresponds to a std::vector <std::vector<std::complex<double>>>
*/
typedef std::vector <std::vector<std::complex<double>>> complex_matrix;

/*
* @brief creates a linearly spaced array of the generic type T
* @param min minimum value of the array
* @param max maximum value of the array
* @param size number of samples to store between min and max values
*/
template <typename T>
std::vector<T> linspace(const T& min, const T& max, const unsigned int& size)
{
	std::vector<T> returned_vector;

	assert(size > 0);
	assert(min < max);

	if (size == 1)
	{
		returned_vector.push_back(static_cast<T>(min));
	}
	else
	{
		const double step = (max - min) / (size - 1);
		for (unsigned int i = 0; i < size - 1; i++)
		{
			returned_vector.push_back(static_cast<T>(min + step * i));
		}
		returned_vector.push_back(static_cast<T>(max));
	}
	return returned_vector;
}

/*
* @brief prints a std::vector of a generic type
* @param vector the vector itself, having a generic type
*/
template <typename T>
void print_std_vector(const std::vector<T>& vector)
{
	if (vector.size() > 0)
	{
		for (unsigned int i = 0; i < vector.size(); i++)
		{
			std::cout << vector[i] << " | ";
		}
		std::cout << "\n";
	}
	else
	{
		std::cout << "Null vector \n";
	}
}

/*
* @brief prints a matrix, or std::vector os std::vector of a generic type
* @param matrix the matrix itself, having a generic type
*/
template <typename T>
void print_matrix(const std::vector < std::vector<T>>& matrix)
{
	if ((matrix.size() > 0) && (matrix[0].size() > 0))
	{
		for (unsigned int i = 0; i < matrix.size(); i++)
		{
			print_std_vector(matrix[i]);
		}
	}
	else
	{
		std::cout << "Null matrix\n";
	}
}

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
const int symmetry_;
const float escape_radius_;

double x_scale_ = 0;
double y_scale_ = 0;
double x_min_ = 0;
double x_max_ = 0;
double y_min_ = 0;
double y_max_ = 0;
unsigned int width_ = 0;
unsigned int height_ = 0;

const bool smooth_ = true;

// container
complex_matrix complex_plane_;
double_matrix output_array_;

float min_value_ = 1e30;
float max_value_ = -1e30;

float r_ = 0.9, g_ = 0.9, b_ = 0.9;

public:
Fractal() = delete;
Fractal(const char* filename,
	const double offset_x,
	const double offset_y,
	const double image_ratio,
	const unsigned int resolution,
	const double zoom,
	const unsigned int iterations,
	const double symmetry,
	const bool smooth,
	const double escape_radius,
	const float r,
	const float g,
	const float b);
~Fractal();

virtual void informations(std::ostream& out) const;
friend std::ostream& operator<<(std::ostream& out, const Fractal& fractal);

void scale();
virtual unsigned int sequence(std::complex<double>& c) = 0;
virtual void compute_set();
void save();

};


// Mandelbrot fractal class
class Mandelbrot: public Fractal
{
private:
	const std::string type_ = "mandelbrot";
public:
	Mandelbrot() = delete;
	Mandelbrot(
		const char* filename,
		const double offset_x = 0.0,
		const double offset_y = 0.0,
		const double image_ratio = 1.7778,
		const unsigned int resolution = 1000,
		const double zoom = 0.8,
		const unsigned int iterations = 20,
		const double symmetry = 2,
		const bool smooth = true,
		const double escape_radius = 2.0,
		const float r = 0.9,
		const float g = 0.9,
		const float b = 0.9
	);

	~Mandelbrot();

	virtual void informations(std::ostream& out) const override final;
	virtual unsigned int sequence(std::complex<double>& c) override final;

};


// Julia fractal class
class Julia: public Fractal
{
private:
	std::complex<double> julia_c_;
	const std::string type_ = "julia";
public:
	Julia() = delete;
	Julia(const char* filename,
		const std::complex<double> julia_c = std::complex<double>(0.0f, 0.0f),
		const double offset_x = 0.0,
		const double offset_y = 0.0,
		const double image_ratio = 1.7778,
		const unsigned int resolution = 1000,
		const double zoom = 0.8,
		const unsigned int iterations = 20,
		const double symmetry = 2,
		const bool smooth = true,
		const double escape_radius = 2.0,
		const float r = 0.9,
		const float g = 0.9,
		const float b = 0.9);
	~Julia();

	virtual void informations(std::ostream& out) const override final;
	virtual unsigned int sequence(std::complex<double>& c) override final;
};
