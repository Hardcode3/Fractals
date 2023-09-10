#include <complex>

#ifndef MANDELBROT_HPP
#define MANDELBROT_HPP

std::size_t mandelbrot(const std::complex<long double>& c, const std::complex<long double>& z0, std::size_t max_it, bool smooth = false);

#endif // !MANDELBROT_HPP
