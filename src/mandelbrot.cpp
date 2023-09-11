#include <mandelbrot.hpp>

std::size_t mandelbrot(const std::complex<long double>& c, const std::complex<long double>& z0, std::size_t max_it, int symmetry)
{
	std::size_t iteration = 0;
	std::complex<long double> zn = z0;

	while (iteration < max_it && std::abs(zn) <= 2)
	{
		zn = std::pow(zn, symmetry) + c;
		iteration++;
	}
		return iteration;
}

std::size_t madelbrot_leaf(const std::complex<long double>& c, const std::complex<long double>& z0, std::size_t max_it)
{
	std::size_t iteration = 0;
	std::complex<long double> zn = z0;

	while (iteration < max_it && std::abs(zn) <= 2)
	{
		zn = std::cos(zn/c);
		iteration++;
	}
	return iteration;
}

std::size_t madelbrot_diablo(const std::complex<long double>& c, const std::complex<long double>& z0, std::size_t max_it)
{
	std::size_t iteration = 0;
	std::complex<long double> zn = z0;

	while (iteration < max_it && std::abs(zn) <= 2)
	{
		zn = std::sinh(zn) + std::pow(c, -2);
		iteration++;
	}
	return iteration;
}

std::size_t madelbrot_starship(const std::complex<long double>& c, const std::complex<long double>& z0, std::size_t max_it)
{
	std::size_t iteration = 0;
	std::complex<long double> zn = z0;

	while (iteration < max_it && std::abs(zn) <= 2)
	{
		zn = std::cos(zn) + std::pow(c, -1);
		iteration++;
	}
	return iteration;
}

std::size_t madelbrot_feigenbaum(const std::complex<long double>& c, const std::complex<long double>& z0, std::size_t max_it)
{
	std::size_t iteration = 0;
	std::complex<long double> zn = z0;
	std::complex<long double> delta(-1.401155, 0) ; // Feigenbaum point
	while (iteration < max_it && std::abs(zn) <= 2)
	{
		zn = zn * zn + c * c * c - delta;
		iteration++;
	}
	return iteration;
}