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
		Image();
		~Image();

		// accessors
		Color get_color(int x, int y) const;
		const int get_width() const { return width_; }
		const int get_height() const { return height_; }
		const char* get_path() const { return path_; }

		// mutators
		void set_color(const Color& color, int x, int y);

		void write_bool_matrix(
			const std::vector<std::vector<bool>> &boolean_matrix, 
			const Img::Color color_0 = Img::BLACK, 
			const Img::Color color_1=Img::WHITE);
		bool save() const;

	private:
		int width_, height_;
		std::vector<Color> colors_;
		const char* path_;
		std::fstream image_;

	};
}