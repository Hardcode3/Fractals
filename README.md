# Mandelbrot and Julia fractal image generator
![mandelbrot_image_rgb](assets/color_sample.jpg)
![julia_image_rgb](assets/julia_sample.jpg)
![mandelbrot_bnw_image](assets/presentation.jpg)
![julia_symmetry_6_image](assets/julia_symmetry_6.jpg)

## Description
Fractals is a console application to create [fractal](https://en.wikipedia.org/wiki/Fractal) images.
It uses the .bmp format as output.
Compiles every time the program has to output an image.
Supports both [Mandelbrot](https://en.wikipedia.org/wiki/Mandelbrot_set) and [Julia](https://en.wikipedia.org/wiki/Julia_set) sets.

## Install
### Dependencies
There is no dependency.
BMP format can only be read on Windows, or either on [VsCode](https://code.visualstudio.com/) or [Atom editor](https://atom.io/) with macOS / linux.
This format has also the inconvenient to produce very heavy files on the disk (to enhance).

### CMake installation
Make sure you have CMake installed and inside the clone repo, type:
```
mkdir build
cd build
cmake ..
cmake --build .
```
or use CMake GUI and create your project with your favourite IDE.
or use the build-in scripts present in the [scripts folder](scripts).

## Usage
### Pre-compile executable
If you do not want to compile windows binaries, you can use the [release executable](fractals.exe).
Simply launch the executable from the command line and some help will appear to guide you through the steps of creating julia or mandelbrot fractals.
$ ./main.exe
Arguments ( )

Usage: ./main.exe [options]

Options:
 -h:            show usage
 -mdb           computes a mandelbrot set, must be followed by its parameters
 -jul           computes a julia set, must be followed by its parameters

Note that a fractal identifier -mdb or -jul must be followed by some parameters:

Parameters are the following:
> File namme / path     -path           Mandelbrot & Julia              MANDATORY       const char*             ex: julia.bmp
> Julia complex x       -julia_cx       Julia only                      OPTIONAL        double                  ex: 0.2
> Julia complex y       -julia_cy       Julia only                      OPTIONAL        double                  ex: 0.145
> Escape radius         -esc            Mandelbrot & Julia              OPTIONAL        double > 0              ex: 2.0
> Number of iterations  -nit            Mandelbrot & Julia              OPTIONAL        unsigned int > 1        ex: 100
> Symmetry / power      -pow            Mandelbrot & Julia              OPTIONAL        int >= 2                ex: 3
> Image ratio           -ratio          Mandelbrot & Julia              OPTIONAL        double > 0              ex: 1.7778
> Resolution            -res            Mandelbrot & Julia              OPTIONAL        unsigned int > 50       ex: 1000
> Zoom                  -zoom           Mandelbrot & Julia              OPTIONAL        double > 0              ex: 0.5
> Offset x              -off_x          Mandelbrot & Julia              OPTIONAL        double > 0              ex: 0.5
> Offset y              -off_y          Mandelbrot & Julia              OPTIONAL        double > 0              ex: -0.9
> Smooth                -sm             Mandelbrot & Julia              OPTIONAL        boolean                 ex: 1 for true or 0 for false
> Red component         -r              Mandelbrot & Julia              OPTIONAL        0 < float < 1           ex: 0.2
> Green component               -g              Mandelbrot & Julia              OPTIONAL        0 < float < 1           ex: 0.2
> Blue component                -b              Mandelbrot & Julia              OPTIONAL        0 < float < 1           ex: 0.2

### Settings
The number of iterations controlls the detail of the fractal, see [assets/iteration_effect](assets/iteration_effect). It has an exponential cost on RAM and CPU usage and require mutliple gagabytes of memory to run a high resolution file with iterations per complex number. In addition the output file can also reach multiple gigabytes.

## Known bugs
- ...

## Improvements
Future versions will add:
- [ ] Add a smoothing option for the contour of the fractal
- [ ] Add a color options such as black and white, RGB and define color palets
- [ ] Parallelisation / concurrency to get faster computation speeds
- [ ] Optimize vectors by allocating them directly their definitive size
- [ ] Image compression
- [ ] Other, more common output formats
- [ ] Maybe a GUI, using ImGui ?

## Performances
- Bencharking is available in the main.cpp file
