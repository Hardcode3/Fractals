/*
* @file main.cpp
* @brief contains the main code where you can trick values to create a specific fractal
* Contains a subsection for benchmarking.
*/

#include <iostream>
#include <chrono>

#include <fractal.h>

int flag_is_used(
	const std::string& flag,
	const std::vector< std::string >& arguments)
{
	for (int i = 0; i < arguments.size(); ++i)
	{
		if (arguments[i] == flag)
		{
			return i;
		}
	}
	return -1;
}


int main(int argc, char** argv) 
{
	std::cout << "Arguments (";
	std::vector< std::string > arguments;
	for (int i = 1; i < argc; ++i) {
		// les arguments de argv sont ajoutes dans le vecteur argument
		arguments.push_back(std::string(argv[i]));
		std::cout << argv[i] << " ";
	}
	std::cout << " )\n\n";


	if (arguments.size() == 0 || (flag_is_used("-h", arguments) == 0)) {
		std::cout << "Usage: ./main.exe [options]\n\n"
			<< "Options: \n";
		std::cout << " -h:		show usage\n";
		std::cout << " -mdb		computes a mandelbrot set, must be followed by its parameters\n";
		std::cout << " -jul		computes a julia set, must be followed by its parameters\n\n";
		
		std::cout << "Note that a fractal identifier -mdb or -jul must be followed by some parameters:\n\n";

		std::cout << "Parameters are the following:\n"
			<< "> File namme / path	-path		Mandelbrot & Julia		MANDATORY       const char*		ex: julia.bmp\n"
			<< "> Julia complex x	-julia_cx	Julia only			OPTIONAL        double			ex: 0.2\n"
			<< "> Julia complex y	-julia_cy	Julia only			OPTIONAL        double			ex: 0.145\n"
			<< "> Escape radius		-esc		Mandelbrot & Julia		OPTIONAL	double > 0		ex: 2.0\n"
			<< "> Number of iterations	-nit		Mandelbrot & Julia		OPTIONAL	unsigned int > 1	ex: 100\n"
			<< "> Symmetry / power	-pow		Mandelbrot & Julia		OPTIONAL        int >= 2		ex: 3\n"
			<< "> Image ratio		-ratio		Mandelbrot & Julia		OPTIONAL        double > 0		ex: 1.7778\n"
			<< "> Resolution		-res		Mandelbrot & Julia		OPTIONAL        unsigned int > 50	ex: 1000\n"
			<< "> Zoom			-zoom		Mandelbrot & Julia		OPTIONAL        double > 0		ex: 0.5\n"
			<< "> Offset x		-off_x		Mandelbrot & Julia		OPTIONAL        double > 0		ex: 0.5\n"
			<< "> Offset y		-off_y		Mandelbrot & Julia		OPTIONAL        double > 0		ex: -0.9\n"
			<< "> Smooth		-sm		Mandelbrot & Julia		OPTIONAL	boolean			ex: 1 for true or 0 for false\n"
			<< "> Red component		-r		Mandelbrot & Julia		OPTIONAL	0 < float < 1		ex: 0.2\n"
			<< "> Green component		-g		Mandelbrot & Julia		OPTIONAL	0 < float < 1		ex: 0.2\n"
			<< "> Blue component		-b		Mandelbrot & Julia		OPTIONAL	0 < float < 1		ex: 0.2\n";
		return 0;
	}

	std::string path_s = "default_path.bmp";
	std::string julia_cx_s = "0.0";
	std::string julia_cy_s = "0.0";
	std::string iterations_s = "100";
	std::string symmetry_s = "2";
	std::string image_ratio_s = "1.7778";
	std::string resolution_s = "1000";
	std::string zoom_s = "0.5";
	std::string offset_x_s = "0.0";
	std::string offset_y_s = "0.0";
	std::string smooth_s = "1.0";
	std::string escape_radius_s = "2.0";
	std::string r_s = "0.9";
	std::string g_s = "0.9";
	std::string b_s = "0.9";

	
	int path_ind = flag_is_used("-path", arguments);
	if (path_ind >= 0);
	{
		path_s = arguments[path_ind + 1];
	}
	int iter_ind = flag_is_used("-nit", arguments);
	if (iter_ind >= 0)
	{
		iterations_s = arguments[iter_ind + 1];
	}
	int pow_ind = flag_is_used("-pow", arguments);
	if (pow_ind >= 0)
	{
		symmetry_s = arguments[pow_ind + 1];
	}
	int ratio_ind = flag_is_used("-ratio", arguments);
	if (ratio_ind >= 0)
	{
		image_ratio_s = arguments[ratio_ind + 1];
	}
	int res_ind = flag_is_used("-res", arguments);
	if (res_ind >= 0)
	{
		resolution_s = arguments[res_ind + 1];
	}
	int zoom_ind = flag_is_used("-zoom", arguments);
	if (zoom_ind >= 0)
	{
		zoom_s = arguments[zoom_ind + 1];
	}
	int offx_ind = flag_is_used("-off_x", arguments);
	if (offx_ind >= 0)
	{
		offset_x_s = arguments[offx_ind + 1];
	}
	int offy_ind = flag_is_used("-off_y", arguments);
	if (offy_ind >= 0)
	{
		offset_y_s = arguments[offy_ind + 1];
	}
	int julia_cx_ind = flag_is_used("-julia_cx", arguments);
	if (julia_cx_ind >= 0)
	{
		julia_cx_s = arguments[julia_cx_ind + 1];
	}
	int julia_cy_ind = flag_is_used("-julia_cy", arguments);
	if (julia_cy_ind >= 0)
	{
		julia_cy_s = arguments[julia_cy_ind + 1];
	}
	int smooth_ind = flag_is_used("-sm", arguments);
	if (smooth_ind >= 0)
	{
		smooth_s = arguments[smooth_ind + 1];
	}
	int esc_ind = flag_is_used("-esc", arguments);
	if (esc_ind >= 0)
	{
		escape_radius_s = arguments[esc_ind + 1];
	}
	int r_ind = flag_is_used("-r", arguments);
	if (r_ind >= 0)
	{
		r_s = arguments[r_ind + 1];
	}
	int g_ind = flag_is_used("-g", arguments);
	if (g_ind >= 0)
	{
		g_s = arguments[g_ind + 1];
	}
	int b_ind = flag_is_used("-b", arguments);
	if (b_ind >= 0)
	{
		b_s = arguments[b_ind + 1];
	}

	char* path = new char[path_s.length() + 1];
	strcpy(path, path_s.c_str());
	unsigned int iterations = stoi(iterations_s);
	int symmetry = stoi(symmetry_s);
	double julia_cx = stof(julia_cx_s);
	double julia_cy = stof(julia_cy_s);
	double image_ratio = stof(image_ratio_s);
	int resolution = stoi(resolution_s);
	double zoom = stof(zoom_s);
	double offset_x = stof(offset_x_s);
	double offset_y = stof(offset_y_s);
	double escape_radius = stof(escape_radius_s);
	bool smooth = stoi(smooth_s);
	float r = stof(r_s);
	float g = stof(g_s);
	float b = stof(b_s);

	auto begin = std::chrono::high_resolution_clock::now();

	
	if (flag_is_used("-mdb", arguments) >= 0 && flag_is_used("-path", arguments) >= 0)
	{
		Mandelbrot fractal(path, offset_x, offset_y, image_ratio, resolution, zoom, iterations, symmetry, smooth, escape_radius, r, g, b);
		std::cout << fractal << "\n";
	}
	else if (flag_is_used("-jul", arguments) >= 0 && flag_is_used("-path", arguments) >= 0)
	{
		Julia fractal(path, std::complex<double>(julia_cx, julia_cy), offset_x, offset_y, image_ratio, resolution, zoom, iterations, symmetry, smooth,escape_radius, r, g, b);
		std::cout << fractal << "\n";
	}
	else
	{
		// if -mdb and -path are not used together, then the command is incorrect
		// if -jul and -path are not used together, then the command is incorrect
		// otherwise, if not --help or -h, command is incorrect
		return 1;
	}

	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<float> execution_time = end - begin;
	
	std::cout << "Execution time : " << execution_time.count() << " s" << std::endl;

	delete[] path;

	return 0;
}

