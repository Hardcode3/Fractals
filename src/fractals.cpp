#include <fractals.hpp>


Fractals::Fractals(std::size_t width, std::size_t height, std::complex<double> bottom_left, double span_real)
	:width_(width), height_(height), start_real_(bottom_left.real()), start_imaginary_(bottom_left.imag())
{
	end_real_ = start_real_ + span_real;
	end_imaginary_ = start_imaginary_ + height_ * span_real / width_;
	step_ = span_real / width_;
	image_.resize(width_ * height_ * 4);
	real_axis_.reserve(width_);
	imaginary_axis_.reserve(height_);
	build_grid();
}

Fractals::~Fractals()
{
}

void Fractals::build_grid()
{
	for (double real = start_real_; real < end_real_ - step_; real += step_)
	{
		real_axis_.emplace_back(real);
	}
	for (double im = end_imaginary_; im > start_imaginary_ + step_; im -= step_)
	{
		imaginary_axis_.emplace_back(im);
	}
}

void Fractals::set_pixel_color(std::size_t x, std::size_t y, const RGBAPixel& pixel)
{
	std::size_t pixel_index = (y * width_ + x) * 4;
	if (pixel_index >= image_.size())
		throw std::out_of_range("Out of range pixel index for x = " + std::to_string(x) + ", y = " + std::to_string(y) + "\n");
	image_[pixel_index + 0] = pixel.red_;
	image_[pixel_index + 1] = pixel.green_;
	image_[pixel_index + 2] = pixel.blue_;
	image_[pixel_index + 3] = pixel.alpha_;
}

bool Fractals::export_png(const std::filesystem::path& file_name)
{
	unsigned exit_code_1 = lodepng::encode(file_name.string(), image_, width_, height_);
	if (exit_code_1)
	{
		std::cerr << "PNG encoding error: " << lodepng_error_text(exit_code_1) << "\n";
		return false;
	}
	else
	{
		std::cout << "PNG image saved successfully for path " << file_name << "\n";
		return true;
	}
}

void Fractals::compute_mandelbrot(std::size_t max_iteration, std::complex<double> z0)
{
	auto start_time = std::chrono::high_resolution_clock::now();
	std::size_t iteration_nb = 0;
	unsigned char normalized_iteration = 0.0;
	std::complex<double> c;
	for (std::size_t real_ind = 0; real_ind < real_axis_.size(); real_ind++)
	{
		for (std::size_t im_ind = 0; im_ind < imaginary_axis_.size(); im_ind++)
		{
			c = std::complex<double>(real_axis_[real_ind], imaginary_axis_[im_ind]);
			iteration_nb = mandelbrot(c, z0, max_iteration);
			normalized_iteration = 255 - (int)(255 * iteration_nb / max_iteration);
			set_pixel_color(real_ind, im_ind, RGBAPixel(normalized_iteration));
		}
	}
	auto end_time = std::chrono::high_resolution_clock::now();
	std::cout << "Execution time " << std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time) << "\n";
}

void Fractals::compute_mandelbrot_async(std::size_t max_iteration, std::complex<double> z0, std::size_t thread_count)
{
	if (thread_count == 0)
	{
		throw std::invalid_argument("The number of thread must be greater than 1");
	}
	else if (thread_count == 1)
	{
		compute_mandelbrot(max_iteration, z0);
		return;
	}

	auto start_time = std::chrono::high_resolution_clock::now();
	
	// spread the work on a given number of threads
	std::size_t vertical_pixel_per_thread = height_ / thread_count;
	std::size_t remaining_vertical_pixels = height_ % thread_count;
	std::vector<std::size_t> vertical_pixels_for_each_thread;
	vertical_pixels_for_each_thread.resize(thread_count);
	for (std::size_t i = 0; i < vertical_pixels_for_each_thread.size(); i++)
	{
		vertical_pixels_for_each_thread[i] = vertical_pixel_per_thread;
	}
	vertical_pixels_for_each_thread[0] += remaining_vertical_pixels;

	if ((std::size_t)(std::accumulate(vertical_pixels_for_each_thread.begin(), vertical_pixels_for_each_thread.end(), 0)) != height_)
		throw std::out_of_range("The number of pixels must be unchanged after workload spread");

	auto compute_pixel_horiwontal_stripe = [this, &max_iteration, &z0](std::size_t start_index, std::size_t end_index)
	{
		std::size_t iteration_nb = 0;
		unsigned char normalized_iteration = 0.0;
		std::complex<double> c;
		for (std::size_t real_ind = 0; real_ind < real_axis_.size(); real_ind++)
		{
			for (std::size_t im_ind = start_index; im_ind < end_index; im_ind++)
			{
				c = std::complex<double>(real_axis_[real_ind], imaginary_axis_[im_ind]);
				iteration_nb = mandelbrot(c, z0, max_iteration, true);
				double fact = std::pow(static_cast<double>(iteration_nb) / max_iteration, -1);
				fact = (1 + std::cos(3.14 * fact)) / 2;
				set_pixel_color(real_ind, im_ind, RGBAPixel(255 * fact , 255 * fact, 255 * fact, 255));
			}
		}
	};

	std::vector<std::thread> threads;
	threads.reserve(thread_count);
	std::size_t pixel_pos_im = 0;
	for (std::size_t i = 0; i < thread_count; i++)
	{
		threads.push_back(std::thread(compute_pixel_horiwontal_stripe, pixel_pos_im, pixel_pos_im + vertical_pixels_for_each_thread[i]));
		pixel_pos_im += vertical_pixels_for_each_thread[i];
		//threads[i].detach();
	}
	std::cout << "Running " << thread_count << " threads \n";

	for (std::thread& thread : threads)
	{
		thread.join();
	}

	auto end_time = std::chrono::high_resolution_clock::now();
	std::cout << "Execution time " << std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time) << "\n";
}