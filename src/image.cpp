#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <assert.h>

#include <image.h>


Img::Color::Color() :r_(0), g_(0), b_(0){}

Img::Color::Color(int r, int g, int b) :r_((float)r), g_((float)g), b_((float)b) {}

Img::Color::Color(float r, float g, float b) : r_(r), g_(g), b_(b) { ; }

Img::Color::Color(double r, double g, double b) : r_(r), g_(g), b_(b) { ; }

Img::Color::~Color(){};

Img::Image::Image(const char* path, int width, int height):path_(path), width_(width), height_(height), colors_(std::vector<Img::Color>(width * height)) 
{
	assert(width_ >= 100);
	assert(height_ >= 100);
}

Img::Image::Image():path_("default.bmp"), width_(500), height_(500), colors_(std::vector<Img::Color>(2500)) 
{
	assert(width_ >= 100);
	assert(height_ >= 100);
}

Img::Image::~Image(){}

Img::Color Img::Image::get_color(int x, int y) const
{
	return colors_[y * width_ + x];
}

void Img::Image::set_color(const Color& color, int x, int y) 
{
	colors_[y * width_ + x].r_ = color.r_;
	colors_[y * width_ + x].g_ = color.g_;
	colors_[y * width_ + x].b_ = color.b_;
}

void Img::Image::write_matrix(
	const std::vector<std::vector<double>>& double_matrix,
	const unsigned int &min_value, 
	const unsigned int &max_value) 
{
	assert((double_matrix.size() == height_) && (double_matrix[0].size() == width_));

	for (int y = 0; y < height_; y++) 
	{
		for (int x = 0; x < width_; x++) 
		{
			// normalisation of the values
			float current_value = double_matrix[y][x] / max_value;
			const float r = 3;
			const float g = 5;
			const float b = 3;
	
			// modify values here to change the colors of the image
			set_color(Img::Color(current_value * r, current_value * g, current_value * b), x, y);
		}
	}
	save();
}

bool Img::Image::save() const
{	
	std::fstream image_;
	image_.open(path_, std::ios::out | std::ios::binary);
	if (!image_.is_open()) 
	{
		std::cout << "Error, file can't be opened \n";
		return false;
	}
	else {
		unsigned char bmp_padding[3] = { 0, 0, 0 };
		const int padding_amount = (((4 - width_ * 3) % 4) % 4);
		const int file_header_size = 14;
		const int information_header_size = 40;
		const int file_size = file_header_size + information_header_size + width_ * height_ * 3 + padding_amount * width_;
		unsigned char file_header[file_header_size];

		// for file type
		file_header[0] = 'B';
		file_header[1] = 'M';

		// fore file size
		file_header[2] = file_size;
		file_header[3] = file_size >> 8;
		file_header[4] = file_size >> 16;
		file_header[5] = file_size >> 24;

		// some reserved space
		file_header[6] = 0;
		file_header[7] = 0;
		file_header[8] = 0;
		file_header[9] = 0;

		// some other reserved space
		file_header[10] = file_header_size + information_header_size;
		file_header[11] = 0;
		file_header[12] = 0;
		file_header[13] = 0;

		unsigned char information_header[information_header_size];

		// header size
		information_header[0] = information_header_size;
		information_header[1] = 0;
		information_header[2] = 0;
		information_header[3] = 0;

		// image width
		information_header[4] = width_;
		information_header[5] = width_ >> 8;
		information_header[6] = width_ >> 16;
		information_header[7] = width_ >> 24;

		// image height
		information_header[8] = height_;
		information_header[9] = height_ >> 8;
		information_header[10] = height_ >> 16;
		information_header[11] = height_ >> 24;

		// stuff
		information_header[12] = 1;
		information_header[13] = 0;

		// bits per pixel
		information_header[14] = 24;
		information_header[15] = 0;

		// compression but there is none here
		information_header[16] = 0;
		information_header[17] = 0;
		information_header[18] = 0;
		information_header[19] = 0;

		// image size but there is no compression here
		information_header[20] = 0;
		information_header[21] = 0;
		information_header[22] = 0;
		information_header[23] = 0;

		// x pixel per meter but it is not specified here
		information_header[24] = 0;
		information_header[25] = 0;
		information_header[26] = 0;
		information_header[27] = 0;

		// color palette, not used here
		information_header[28] = 0;
		information_header[29] = 0;
		information_header[30] = 0;
		information_header[31] = 0;

		// important colors, not used here
		information_header[32] = 0;
		information_header[33] = 0;
		information_header[34] = 0;
		information_header[35] = 0;

		image_.write(reinterpret_cast<char*>(file_header), file_header_size);
		image_.write(reinterpret_cast<char*>(information_header), information_header_size);
	
		for (int y = 0; y < height_; y++) 
		{
			for (int x = 0; x < width_; x++)
			{

				// since colors are considered as floating point between 0 and 1, they should be back to the classical range
				// colors are 0-255 values for red, green and blue
				unsigned char r = static_cast<unsigned char>(get_color(x, y).r_ * 255.0f);
				unsigned char g = static_cast<unsigned char>(get_color(x, y).g_ * 255.0f);
				unsigned char b = static_cast<unsigned char>(get_color(x, y).b_ * 255.0f);

				unsigned char color[] = { r, g, b };
				image_.write(reinterpret_cast<char*>(color), 3);
			}
			image_.write(reinterpret_cast<char*>(bmp_padding), padding_amount);
		}
	}
	image_.close();
	std::cout << "Successfully created image " << path_ << "\n";
	return true;
}

