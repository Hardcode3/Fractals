/*
* @file image.h
* @brief contains the code to create .bmp images
* Images are described in the RGB color-space with no compression.
* These are not limited to a specific scale or resolution and works for nearly every case
* @see https://en.wikipedia.org/wiki/BMP_file_format for more informations
*/
#pragma once

#include <fstream>
#include <vector>

/*
* @namespace Img
* Defines the structure Color containing RGB values
* Defines the Image class responsible for .bmp image creation
*/
namespace Img {
	/*
	* @struct Color
	* @brief structure containing an RGB color
	*/
	struct Color 
	{
		float r_, g_, b_;

		Color();
		Color(int r, int g, int b);
		Color(float r, float g, float b);
		Color(double r, double g, double b);
		~Color();
	}; 

	/*
	* @class Image
	* @brief Creates a bitmap image and export it
	* Supported:
	*	- any resolution
	*	- any ratio
	*	- any RGB color (should be normalized)
	*/
	class Image 
	{
	public:
		/*
		* @brief Constructor
		* @param path the path of the image (output)
		* @param width width of the image in pixels
		* @param height height of the image in pixels
		*/
		Image(const char* path, int width, int height);

		/*
		* @brief default constructor for Image
		*/
		Image();

		/*
		* @brief destructor for Image
		*/
		~Image();

		/*
		* @brief gets the color of a specific pixel described by its cartesian coordinates x and y
		* @param x abscissa of the pixel
		* @param y ordinate of the pixel
		* @return a Color structure corresponding to the RGB color of the pixel
		*/
		Color get_color(int x, int y) const;

		/*
		* @brief gets the width of the Image
		* @return width of the image
		*/
		const int get_width() const { return width_; }

		/*
		* @brief gets the height of the Image
		* @return height of the image
		*/
		const int get_height() const { return height_; }

		/*
		* @brief gets the path of the Image
		* @return path of the image
		*/
		const char* get_path() const { return path_; }

		/*
		* @brief sets the color of a pixel
		* @param color the new Color for the considered pixel
		* @param x abscissa of the pixel
		* @param y ordinate of the pixel
		*/
		void set_color(const Color& color, int x, int y);

		/*
		* @brief writes an image based on a matrix of unsigned integers
		* @param uint_matrix a matrix of unsigned integers having the same size as the Image
		* @param min_value the minimum value based on the whole matrix
		* @param max_value the maximum value based on the whole matrix
		*/
		void write_matrix(
			const std::vector<std::vector<double>>& double_matrix,
			const unsigned int& min_value,
			const unsigned int& max_value);

		/*
		* @brief save the image and close it
		* @return true if success, otherwise false
		*/
		bool save() const;

	private:
		int width_, height_;
		std::vector<Color> colors_;
		const char* path_;
		std::fstream image_;
	};
}