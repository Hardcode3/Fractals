/*
* @file sequence.h
* @brief contains the necessary mathematical sequences to compute fractals, such as Mandelbrot or Julia
*/
#pragma once

#include <cmath>
#include <complex>
#include <vector>

#include <sequence.h>

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

/*
* @brief the mandelbrot sequence itself
* @param iterations max number of iterations allowed for the sequence
* @param z the mooving complex number, with z = 0 + 0i at the start
* @param c the fixed complex number (set with the current pixel positon in the complex plane)
*/
unsigned int mandelbrot_sequence(
	const unsigned int &iterations, 
	std::complex<double> &z,  
	std::complex<double> &c);
