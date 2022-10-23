#include <image.h>

// testing different size of image (square, rectangular...)

bool test_h_rectangle_image() {

	unsigned int width = 200, height = 100;
	Img::Image image("test_rectangle_image.bmp", width, height);
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			image.set_color(Img::Color((float)x / (float)width, 1.0f - (float)x / (float)width, (float)y / (float)height), x, y);
		}
	}
	image.save();
	return true;
}

bool test_v_rectangle_image() {

	unsigned int width = 100, height = 200;
	Img::Image image("test_square_image.bmp", width, height);
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			image.set_color(Img::Color((float)x / (float)width, 1.0f - (float)x / (float)width, (float)y / (float)height), x, y);
		}
	}
	image.save();
	return true;
}

bool test_square_image() {

	unsigned int width = 200, height = 200;
	Img::Image image("test_square_image.bmp", width, height);
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			image.set_color(Img::Color((float)x / (float)width, 1.0f - (float)x / (float)width, (float)y / (float)height), x, y);
		}
	}
	image.save();
	return true;
}

int main() {
	if (test_v_rectangle_image() &&
		test_h_rectangle_image() &&
		test_square_image()) 
	{
		return 0;
	}
	return 1;
}