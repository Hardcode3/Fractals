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
	enum ColorMap { BLACKNWHITE_CIRCULAR };

	RGBAPixel() : red_(255), green_(255), blue_(255), alpha_(255) { ; }
	RGBAPixel(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha) : red_(red), green_(green), blue_(blue), alpha_(alpha) { ; }
	RGBAPixel(unsigned char uniform_color) : red_(uniform_color), green_(uniform_color), blue_(uniform_color), alpha_(255) { ; }
	void set_colormap(long double& normalized_value, ColorMap colormap);
	
	unsigned char red_;
	unsigned char green_;
	unsigned char blue_;
	unsigned char alpha_;
};
				
class Fractals
{
public:
	Fractals() { ; }
	~Fractals() { ; }

	void reset();
	void init(std::size_t width, std::size_t height, std::complex<long double> center, long double span_real);
	void compute_mandelbrot(std::size_t max_iteration, std::complex<long double> z0 = std::complex<long double>(0, 0), RGBAPixel::ColorMap colormap = RGBAPixel::BLACKNWHITE_CIRCULAR);
	void compute_mandelbrot_async(std::size_t max_iteration, std::complex<long double> z0 = std::complex<long double>(0, 0), std::size_t thread_count = 20, RGBAPixel::ColorMap colormap = RGBAPixel::BLACKNWHITE_CIRCULAR, int symmetry = 2);

	bool export_png(const std::filesystem::path& file_name) const;

	std::vector<unsigned char>* get_image() { return &image_; }
	std::size_t get_height() const { return height_; }
	std::size_t get_width() const { return width_; }
	RGBAPixel get_pixel(std::size_t x, std::size_t y) const;
	bool is_computing() const { return is_computing_; }

private:
	void set_pixel_color(std::size_t x, std::size_t y, const struct RGBAPixel& pixel);
	void build_grid();

	std::size_t width_ = 0, height_ = 0;
	std::vector<unsigned char> image_;  // RGBA format

	std::vector<long double> real_axis_;
	std::vector<long double> imaginary_axis_;

	long double start_real_ = -1.0, start_imaginary_= -1.0, end_real_ = 1.0, end_imaginary_ = 1.0;
	long double step_real_ = 0., step_im_ = 0.;
	
	bool is_computing_ = false;
};

#endif // !FRACTALS_HPP
