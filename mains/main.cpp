/*
* @file main.cpp
* @brief contains the main code where you can trick values to create a specific fractal
*/

#include <fractals.hpp>
#include <chrono>

int main(int argc, char** argv)
{
	try
	{
		Fractals mandelbrot(3480 * 5, 3480 * 5, std::complex<double>(-1,-1), 1.0);
		
		mandelbrot.compute_mandelbrot_async(80, std::complex<double>(0.001,0.0002), 50);
		//mandelbrot.compute_mandelbrot(100);

		mandelbrot.export_png("mandelbrot.png");
		
		return 0;
	}
	catch (const std::exception& exception)
	{
		std::cerr << "Exception raised: " << exception.what() << "\n";
		return 1;
	}
}