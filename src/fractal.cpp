#include <fractal.h>

Fractal::Fractal(
	const char* filename,
	const double offset_x,
	const double offset_y,
	const double image_ratio,
	const unsigned int resolution,
	const double zoom,
	const unsigned int iterations,
	const double symmetry,
	const bool smooth,
	const double escape_radius,
	const float r,
	const float g,
	const float b) :
	filename_(filename),
	image_offset_x_(offset_x),
	image_offset_y_(offset_y),
	image_ratio_(image_ratio),
	image_resolution_(resolution),
	image_zoom_(zoom),
	iterations_(iterations),
	symmetry_(symmetry),
	smooth_(smooth),
	escape_radius_(escape_radius),
	r_(r), g_(g), b_(b) {}

Fractal::~Fractal(){;}

void Fractal::informations(std::ostream& out) const
{
	out << "> File namme: " << filename_ << "\n"
		<< "> Number of iterations: " << iterations_ << "\n"
		<< "> Symmetry (power of the sequence): " << symmetry_ << "\n"
		<< "> Escape radius: " << escape_radius_ << "\n"
		<< "> Image ratio: " << image_ratio_ << "\n"
		<< "> Resolution: " << image_resolution_ << "\n"
		<< "> Width: " << width_ << "\n"
		<< "> Height: " << height_ << "\n"
		<< "> Zoom: " << image_zoom_ << "\n"
		<< "> Offset x: " << image_offset_x_ << "\n"
		<< "> Offset y: " << image_offset_y_ << "\n"
		<< "> Scale x: " << x_scale_ << "\n"
		<< "> Scale y: " << y_scale_ << "\n"
		<< "> Boundaries x: (" << x_min_ << " ," << x_max_ << ")\n"
		<< "> Boundaries y: (" << y_min_ << " ," << y_max_ << ")\n"
		<< "> Smooth: " << smooth_ << "\n"
		<< "> Red: " << r_ << " Green: " << g_ << " Blue: " << b_ << "\n"
		<< "----------------------------------------------------------- \n";
 }

std::ostream& operator<<(std::ostream& out, const Fractal& fractal)
{
	fractal.informations(out);
	return out;
}

void Fractal::scale()
{
	assert(iterations_ > 1);
	assert(image_ratio_ > 0);
	assert(image_resolution_ > 50);
	assert(image_zoom_ > 0);
	// for the moment, only positive symmetry is defined
	assert(symmetry_ >= 2);

	x_scale_ = 2.;
	y_scale_ = 2. / image_ratio_;
	x_min_ = -x_scale_ / (2. * image_zoom_) - image_offset_x_;
	x_max_ = x_scale_ / (2. * image_zoom_) - image_offset_x_;
	y_min_ = -y_scale_ / (2. * image_zoom_) - image_offset_y_;
	y_max_ = y_scale_ / (2. * image_zoom_) - image_offset_y_;
	width_ = image_resolution_ * x_scale_;
	height_ = image_resolution_ * y_scale_;

	assert(x_min_ <= x_max_);
	assert(y_min_ <= y_max_);
	assert(width_ >= 0);
	assert(height_ >= 0);
	assert(escape_radius_ > 0);
}

void Fractal::compute_set()
{
	std::vector<double>  re = linspace<double>(x_min_, x_max_, width_);
	std::vector<double>  im = linspace<double>(y_min_, y_max_, height_);

	assert(re.size() == width_);
	assert(im.size() == height_);

	std::vector<float> tmp_vect;

	for (unsigned int im_index = 0; im_index < height_; im_index++)
	{
		tmp_vect.clear();
		for (unsigned int re_index = 0; re_index < width_; re_index++)
		{
			std::complex<double> tmp_complex(re[re_index], im[im_index]);
			unsigned int seq = sequence(tmp_complex);
			if (seq < min_value_)
				min_value_ = seq;
			if (seq > max_value_)
				max_value_ = seq;
			tmp_vect.push_back(seq);
		}
		output_array_.push_back(tmp_vect);
	}
	assert((output_array_.size() == height_) && (output_array_[0].size() == width_));
}

void Fractal::save()
{
	Img::Image image(filename_, width_, height_);
	image.write_matrix(output_array_, min_value_, max_value_, r_, g_, b_);
}

Mandelbrot::Mandelbrot(
	const char* filename,
	const double offset_x,
	const double offset_y,
	const double image_ratio,
	const unsigned int resolution,
	const double zoom,
	const unsigned int iterations,
	const double symmetry,
	const bool smooth,
	const double escape_radius,
	const float r,
	const float g,
	const float b)
	: Fractal(
		filename,
		offset_x,
		offset_y,
		image_ratio,
		resolution,
		zoom,
		iterations,
		symmetry,
		smooth,
		escape_radius,
		r, g, b)
{
	scale();
	compute_set();
	save();
}

Mandelbrot::~Mandelbrot(){;}

void Mandelbrot::informations(std::ostream& out) const
{
	out << "\n ----------------------------------------------------------- \n" 
		<< "> Fractal type: " << type_ << "\n";
	Fractal::informations(out);
}

unsigned int Mandelbrot::sequence(std::complex<double>& c)
{
	std::complex<double> z(0.0, 0.0);
	for (unsigned int it = 0; it < iterations_; ++it)
	{
		z = std::pow(z, symmetry_) + c;
		if (abs(z) > escape_radius_)
		{
			if (smooth_)
			{
				// https://linas.org/art-gallery/escape/smooth.html
				return it + 1 - log(log(abs(z))) / log(symmetry_);
			}
			else
			{
				return it;
			}
		}
	}
	return 0;
}


Julia::Julia(
	const char* filename,
	const std::complex<double> julia_c,
	const double offset_x,
	const double offset_y,
	const double image_ratio,
	const unsigned int resolution,
	const double zoom,
	const unsigned int iterations,
	const double symmetry,
	const bool smooth,
	const double escape_radius,
	const float r,
	const float g,
	const float b)
	:Fractal(
		filename,
		offset_x,
		offset_y,
		image_ratio,
		resolution,
		zoom,
		iterations,
		symmetry,
		smooth,
		escape_radius,
		r, g, b),
	julia_c_(julia_c)
{
	scale();
	compute_set();
	save();
}

Julia::~Julia() { ; }

void Julia::informations(std::ostream& out) const
{
	out << "\n ----------------------------------------------------------- \n"
		<< "> Fractal type: " << type_ << "\n"
		<< "> Julia complex: " << julia_c_ << "\n";
	Fractal::informations(out);
}

unsigned int Julia::sequence(std::complex<double>& c) 
{	
	for (unsigned int it = 0; it < iterations_; ++it)
	{
		c = std::pow(c, symmetry_) + julia_c_;
		if (abs(c) > escape_radius_)
		{
			if (smooth_)
			{
				// https://linas.org/art-gallery/escape/smooth.html
				return it + 1 - log(log(abs(c))) / log(symmetry_);
			}
			else
			{
				return it;
			}
		}
	}
	return 0;
}

