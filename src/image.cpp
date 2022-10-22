#include <iostream>
#include <fstream>
#include <string>
#include <image.h>
#include <vector>

bool p3_img(const std::string& file_name, unsigned int height, unsigned int width) {
	std::ofstream image;
	image.open(file_name + ".ppm");

	if (image.is_open()) {
		image << "p3" << std::endl;
		image << height << " " << width << std::endl;
		image << "255" << std::endl;

		for (unsigned int i = 0; i < width; i++) {
			for (unsigned int j = 0; i < height; i++) {
				image << 150 << " " << 150 << " " << 200 << std::endl;
			}
		}
	}
	else { return false; }
	image.close();
	return true;
}

Img::Color::Color() :r_(0), g_(0), b_(0){}

Img::Color::Color(int r, int g, int b) :r_((float)r), g_((float)g), b_((float)b) {}

Img::Color::Color(float r, float g, float b) : r_(r), g_(g), b_(b) { ; }

Img::Color::~Color(){};

Img::Image::Image(const char* path, int width, int height):path_(path), width_(width), height_(height), colors_(std::vector<Img::Color>(width * height)) {}

Img::Image::~Image(){}

Img::Color Img::Image::get_color(int x, int y) const {
	return colors_[y * width_ + x];
}
void Img::Image::set_color(const Color& color, int x, int y) {
	colors_[y * width_ + x].r_ = color.r_;
	colors_[y * width_ + x].g_ = color.g_;
	colors_[y * width_ + x].b_ = color.b_;
}

bool Img::Image::save() const
{	
	std::fstream image_;
	image_.open(path_, std::ios::out | std::ios::binary);
	if (!image_.is_open()) {
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

		file_header[0] = 'B';
		file_header[1] = 'M';

		file_header[2] = file_size;
		file_header[3] = file_size >> 8;
		file_header[4] = file_size >> 16;
		file_header[5] = file_size >> 24;

		file_header[6] = 0;
		file_header[7] = 0;
		file_header[8] = 0;
		file_header[9] = 0;

		file_header[10] = file_header_size + information_header_size;
		file_header[11] = 0;
		file_header[12] = 0;
		file_header[13] = 0;

		unsigned char information_header[information_header_size];

		information_header[0] = information_header_size;
		information_header[1] = 0;
		information_header[2] = 0;
		information_header[3] = 0;

		information_header[4] = width_;
		information_header[5] = width_ >> 8;
		information_header[6] = width_ >> 16;
		information_header[7] = width_ >> 24;

		information_header[8] = height_;
		information_header[9] = height_ >> 8;
		information_header[10] = height_ >> 16;
		information_header[11] = height_ >> 24;

		information_header[12] = 1;
		information_header[13] = 0;

		information_header[14] = 24;
		information_header[15] = 0;

		information_header[16] = 0;
		information_header[17] = 0;
		information_header[18] = 0;
		information_header[19] = 0;

		information_header[20] = 0;
		information_header[21] = 0;
		information_header[22] = 0;
		information_header[23] = 0;

		information_header[24] = 0;
		information_header[25] = 0;
		information_header[26] = 0;
		information_header[27] = 0;

		information_header[28] = 0;
		information_header[29] = 0;
		information_header[30] = 0;
		information_header[31] = 0;

		information_header[32] = 0;
		information_header[33] = 0;
		information_header[34] = 0;
		information_header[35] = 0;

		image_.write(reinterpret_cast<char*>(file_header), file_header_size);
		image_.write(reinterpret_cast<char*>(information_header), information_header_size);
	
		for (int y = 0; y < height_; y++) {
			for (int x = 0; x < width_; x++) {
				unsigned char r = static_cast<unsigned char>(get_color(x, y).r_ * 255.0f);
				unsigned char g = static_cast<unsigned char>(get_color(x, y).g_ * 255.0f);
				unsigned char b = static_cast<unsigned char>(get_color(x, y).b_ * 255.0f);

				unsigned char color[] = { b, g, r };
				image_.write(reinterpret_cast<char*>(color), 3);
			}
			image_.write(reinterpret_cast<char*>(bmp_padding), padding_amount);
		}
	}
	image_.close();
	std::cout << "Successfully created image at " << path_ << "\n";
	return true;
}
