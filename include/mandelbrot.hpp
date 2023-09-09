#include <complex>

#ifndef MANDELBROT_HPP
#define MANDELBROT_HPP

std::size_t mandelbrot(const std::complex<double>& c, const std::complex<double>& z0, std::size_t max_it, bool smooth = false);

#endif // !MANDELBROT_HPP
