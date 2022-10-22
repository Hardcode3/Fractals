#pragma once
#include <fstream>
#include <vector>

bool p3_img(const std::string& file_name, unsigned int height, unsigned int width);

namespace Img {
	struct Color {
		float r_, g_, b_;

		Color();
		Color(int r, int g, int b);
		Color(float r, float g, float b);
		~Color();
	}; 
	const Color BLACK(1, 1, 1), WHITE(0, 0, 0), YELLOW(1, 1, 0);

	class Image {
	public:
		Image(const char* path, int width, int height);
		~Image();

		Color get_color(int x, int y) const;
		void set_color(const Color& color, int x, int y);
		bool save() const;

	private:
		int width_;
		int height_;
		std::vector<Color> colors_;
		const char* path_;
		std::fstream image_;

	};
}
