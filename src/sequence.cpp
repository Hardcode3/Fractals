#include <iostream>
#include <complex>
#include <cmath>

#include <sequence.h>


unsigned int mandelbrot_sequence(
	const unsigned int &iterations, 
	std::complex<double>& z, 
	std::complex<double>& c,
	unsigned int symmetry) 
{
	for (unsigned int it = 0; it < iterations; it++) 
	{
		z = std::pow(z, symmetry) + c;
		if (abs(z) > 2) 
		{
			return it;
		}
	}
	return 0;
}