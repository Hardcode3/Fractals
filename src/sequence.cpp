#include <iostream>
#include <complex>
#include <cmath>

#include <sequence.h>


unsigned int mandelbrot_sequence(
	const unsigned int &iterations, 
	std::complex<double>& z, 
	std::complex<double>& c) 
{
	for (unsigned int it = 0; it < iterations; it++) 
	{
		z = std::pow(z, 2) + c;
		if (abs(z) > 2) 
		{
			return it;
		}
	}
	return 0;
}