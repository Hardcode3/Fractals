#include <iostream>
#include <mandelbrot_set.h>
#include <misc.h>
#include <image.h>

int main(int argc, char** argv) {

	complex_matrix c_matrix;
	bool_matrix stability_matrix;

	grid(c_matrix, stability_matrix, -2, 2, -2, 2, 10000, 20);

	//draw_bool_matrix(stability_matrix);

	const int width = stability_matrix.size();
	const int height = stability_matrix[0].size();
	const char* path = "test.bmp";

	std::cout << "height : " << height << "; width : " << width << "\n";
	Img::Image image(path, width, height);
	

	for (int y = 0; y < stability_matrix.size(); y++) {
		for (int x = 0; x < stability_matrix[0].size(); x++) {
			if (stability_matrix[y][x]) {
				image.set_color(Img::BLACK, x, y);
			}
			else {
				image.set_color(Img::WHITE, x, y);
			}
			//image.set_color(Img::Color((float)x / (float)width, 1.0f - (float)x / (float)width, (float)y / (float)height), x, y);
		}
	}
	image.save();
	return 0;
}