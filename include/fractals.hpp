#include <vector>
#include <filesystem>
#include <iostream>
#include <thread>
#include <mutex>
#include <lodepng.h>
#include <numeric>
#include <chrono>

#include <mandelbrot.hpp>
#include <julia.hpp>

#ifndef FRACTALS_HPP
#define FRACTALS_HPP

struct RGBAPixel
{
	RGBAPixel(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha) : red_(red), green_(green), blue_(blue), alpha_(alpha) { ; }
	RGBAPixel(unsigned char uniform_color) : red_(uniform_color), green_(uniform_color), blue_(uniform_color), alpha_(255) { ; }
	enum ColorMap {LINEAR};
	unsigned char red_;
	unsigned char green_;
	unsigned char blue_;
	unsigned char alpha_;
};

class Fractals
{
public:
	Fractals(std::size_t width, std::size_t height, std::complex<long double> center, long double span_real);
	~Fractals();

	void compute_mandelbrot(std::size_t max_iteration, std::complex<long double> z0 = std::complex<long double>(0, 0));
	void compute_mandelbrot_async(std::size_t max_iteration, std::complex<long double> z0 = std::complex<long double>(0, 0), std::size_t thread_count = 20);

	bool export_png(const std::filesystem::path& file_name) const;

private:
	void set_pixel_color(std::size_t x, std::size_t y, const struct RGBAPixel& pixel);
	void build_grid();

	std::size_t width_, height_;
	std::vector<unsigned char> image_;  // RGBA format

	std::vector<long double> real_axis_;
	std::vector<long double> imaginary_axis_;

	long double start_real_ = -1.0, start_imaginary_= -1.0, end_real_, end_imaginary_;
	long double step_;
	
};

#endif // !FRACTALS_HPP
