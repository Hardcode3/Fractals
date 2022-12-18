#include <fractal.h>

Fractal::Fractal(
	const char* filename,
	const std::complex<double> complex,
	const double offset_x,
	const double offset_y,
	const double image_ratio,
	const unsigned int resolution,
	const double zoom,
	const unsigned int iterations,
	const double symmetry)
	:
	filename_(filename),
	complex_(complex),
	image_offset_x_(offset_x),
	image_offset_y_(offset_y),
	image_ratio_(image_ratio),
	image_resolution_(resolution),
	image_zoom_(zoom),
	iterations_(iterations),
	symmetry_(symmetry)
{
    assert(iterations > 0);
    assert(image_ratio > 0);
    assert(resolution > 100);
    assert(zoom > 0);
    // for the moment, only positive symmetry is defined
    assert(symmetry >= 2);

	x_scale_ = 2.;
	y_scale_ = 2. / image_ratio_;
	x_min_ = -x_scale_ / (2. * image_zoom_) - image_offset_x_;
	x_max_ = x_scale_ / (2. * image_zoom_) - image_offset_x_;
	y_min_ = -y_scale_ / (2. * image_zoom_) - image_offset_y_;
	y_max_ = y_scale_ / (2. * image_zoom_) - image_offset_y_;
	width_ = image_resolution_ * x_scale_;
	height_ = image_resolution_ * y_scale_;
}

Fractal::~Fractal(){;}

Mandelbrot::Mandelbrot(
	const char* filename,
	const std::complex<double> complex,
	const double offset_x,
	const double offset_y,
	const double image_ratio,
	const unsigned int resolution,
	const double zoom,
	const unsigned int iterations,
	const double symmetry)
	:
	filename_(filename),
	complex_(complex),
	image_offset_x_(offset_x),
	image_offset_y_(offset_y),
	image_ratio_(image_ratio),
	image_resolution_(resolution),
	image_zoom_(zoom),
	iterations_(iterations),
	symmetry_(symmetry)
{
    assert(iterations > 0);
    assert(image_ratio > 0);
    assert(resolution > 100);
    assert(zoom > 0);
    // for the moment, only positive symmetry is defined
    assert(symmetry >= 2);

	x_scale_ = 2.;
	y_scale_ = 2. / image_ratio_;
	x_min_ = -x_scale_ / (2. * image_zoom_) - image_offset_x_;
	x_max_ = x_scale_ / (2. * image_zoom_) - image_offset_x_;
	y_min_ = -y_scale_ / (2. * image_zoom_) - image_offset_y_;
	y_max_ = y_scale_ / (2. * image_zoom_) - image_offset_y_;
	width_ = image_resolution_ * x_scale_;
	height_ = image_resolution_ * y_scale_;
}

Mandelbrot::~Mandelbrot(){;}

