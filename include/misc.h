/*
* @file misc.h
* @brief contains miscellaneous functions about the computation of fractals
* Contains templates functions and non templates functions, also print functions for a debugging purpose
*/
#pragma once

#include <iostream>
#include <vector>
#include <assert.h>

#include <sequence.h>
#include <image.h>
#include <assert.h>

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
void print_std_vector(const std::vector<T> &vector) 
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
void print_matrix(const std::vector < std::vector<T>> & matrix) 
{
	if ( (matrix.size() > 0) && (matrix[0].size() > 0)) 
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

/*
* @brief finds the extremum of a set of values that should be passed one at a time
* @param current_value value that will be compared to the min and max and eventually modify one of them
* @param min_value lower value
* @param max_value upper value
* Every parameter has to be defined in an other scope to be passed by reference
* If the function finds that the current values is out of the current bounds, sets the new boundary
*/
void find_extremums(
	double &current_value,
	double &min_value,
	double &max_value);

/*
* @brief computes a set based on its sequence
* @see sequence.h for more details
* @param stability_plane the matrix (std::vectors of std::vectors with a unsigned int type)
* @param is_julia true if the fractal set should be julia, false if mandelbrot
* @param c starting complex (does not matter in the mandelbrot set, very important in the julia set)
* @param min_value the minimum value of the stability_plane matrix
* @param max_value the maximum value of the stability_plane matrix
* @param x_min the lower real boudary of the complex plane
* @param x_max the upper real boudary of the complex plane
* @param y_min the lower imaginray boudary of the complex plane
* @param y_max the upper imaginray boudary of the complex plane
* @param width width of the image (in pixels or corresponds to the size of the stability_plane matrix)
* @param height height of the image (in pixels or corresponds to the size of the stability_plane matrix)
* @param iterations limit of iterations before stoppping the fractal sequence (@see sequence.h)
* @param symetry (the power of the mandelbrot sequence)
*/
void compute_set(
	double_matrix& stability_plane,
	const bool& is_julia,
	std::complex<double>& c,
	double & min_value,
	double & max_value,
	const double &x_min,
	const double &x_max,
	const double &y_min,
	const double &y_max,
	const unsigned int &width,
	const unsigned int &height,
	const unsigned int &iterations,
	unsigned int symmetry=2);

/*
* @brief creates the fractal
* @param file_name path of the output image
* @param is_julia true if the fractal set should be julia, false if mandelbrot
* @param c starting complex (does not matter in the mandelbrot set, very important in the julia set)
* @param offset_x offset that will be applied to the real axis in the complex plane
* @param offset_y offset that will be applied to the real axis in the complex plane
* @param image_ratio ratio of the image (common ratios are 16/9, 16/10, 4/3...)
* @param resolution number of pixel to enhance the quality of the image
* @param zoom zoom applied to the image (between lim -> 0. and infinite)
* @param iteratins limit of iterations before stoppping the fractal sequence (@see sequence.h)
* @param symetry (the power of the mandelbrot sequence)
*/
void fractal(
	const char* file_name,
	const bool &is_julia,
	std::complex<double>& c,
	const double& offset_x,
	const double& offset_y,
	const double& image_ratio,
	const double& resolution,
	const double& zoom,
	const unsigned int &iterations,
	unsigned int symmetry=2);