#include <mandelbrot.hpp>

std::size_t mandelbrot(const std::complex<double>& c, const std::complex<double>& z0, std::size_t max_it, bool smooth)
{
	std::size_t iteration = 0;
	std::complex<double> zn = z0;

	while (iteration < max_it && std::abs(zn) <= 2)
	{
		zn = zn * zn + c;
		iteration++;
	}
	if (smooth)
	{
		return iteration + 1 - std::log(std::log(std::abs(zn)) / std::log(2));
	}
	else
	{
		return iteration;
	}
}