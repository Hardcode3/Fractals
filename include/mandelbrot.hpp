#include <complex>

#ifndef MANDELBROT_HPP
#define MANDELBROT_HPP

std::size_t mandelbrot(const std::complex<long double>& c, const std::complex<long double>& z0, std::size_t max_it, int symmetry = 6);

std::size_t madelbrot_leaf(const std::complex<long double>& c, const std::complex<long double>& z0, std::size_t max_it);

std::size_t madelbrot_diablo(const std::complex<long double>& c, const std::complex<long double>& z0, std::size_t max_it);

std::size_t madelbrot_starship(const std::complex<long double>& c, const std::complex<long double>& z0, std::size_t max_it);

std::size_t madelbrot_feigenbaum(const std::complex<long double>& c, const std::complex<long double>& z0, std::size_t max_it);

#endif // !MANDELBROT_HPP
