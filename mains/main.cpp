/*
* @file main.cpp
* @brief contains the main code where you can trick values to create a specific fractal
* Contains a subsection for benchmarking.
*/

#include <iostream>
#include <chrono>
#include <omp.h>

#include <misc.h>


int main(int argc, char** argv) 
{
	auto begin = std::chrono::high_resolution_clock::now();

	// future versions of the code will let the user trick the colors right in the main function
	// args: path, x_offset, y_offset, image_ratio, zoom, iterations
	fractal("G:/test.bmp",0 ,0, 16./9., 1000, 1, 35);
	
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<float> execution_time = end - begin;
	std::cout << "Execution time : " << execution_time.count() << " s" << std::endl;

	return 0;
}


/*
* ___________________________________ BENCHMARK ZONE ___________________________________
* ---- File size
* 
* 10.000 px -> 659 Mb
*
* ---- Execution time x64 Release - Intel core i7 4790 @3.6 GHz - 16 Go LPDDR3 1600 MHz
* fractal("G:/test.bmp", 1.55,0, 16./9., 10000, .5, 35); 257.951 s
* 
*  ---- Execution time x64 Debug - Intel core i7 4790 @3.6 GHz - 16 Go LPDDR3 1600 MHz
* fractal("G:/test.bmp", 1.55,0, 16./9., 10000, .5, 35); 1131.92 s
* 
*/
