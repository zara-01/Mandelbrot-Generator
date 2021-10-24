// Mandelbrot set example
// Adam Sampson <a.sampson@abertay.ac.uk>

#include "mandelbrot.h"

#include <chrono>
#include <cstdint>
#include <cstdlib>
#include <complex>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <thread>
#include <vector>

// Import things from the standard library
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::complex;
using std::cout;
using std::endl;
using std::ofstream;
using std::thread;

// Define the alias "the_clock" for the clock type we're going to use.
typedef std::chrono::steady_clock the_clock;


// The size of the image to generate.
static const int WIDTH = 1820;
static const int HEIGHT = 1101;

static int brotColour;
static int backgroundColour;

const int MAX_ITERATIONS = 500;

static uint32_t image[HEIGHT][WIDTH];


// Format specification: http://www.gamers.org/dEngine/quake3/TGA.txt
void mandelbrot::write_tga(const char* filename)
{
	ofstream outfile(filename, ofstream::binary);

	uint8_t header[18] = {
		0, // no image ID
		0, // no colour map
		2, // uncompressed 24-bit image
		0, 0, 0, 0, 0, // empty colour map specification
		0, 0, // x origin
		0, 0, // y origin
		WIDTH & 0xFF, (WIDTH >> 8) & 0xFF, // width
		HEIGHT & 0xFF, (HEIGHT >> 8) & 0xFF, // height
		24, // bits per pixel
		0, // image descriptor
	};
	outfile.write((const char*)header, 18);

	for (int y = 0; y < HEIGHT; ++y)
	{
		for (int x = 0; x < WIDTH; ++x)
		{
			uint8_t pixel[3] = {
				image[y][x] & 0xFF, // blue channel
				(image[y][x] >> 8) & 0xFF, // green channel
				(image[y][x] >> 16) & 0xFF, // red channel
			};
			outfile.write((const char*)pixel, 3);
		}
	}

	outfile.close();
	if (!outfile)
	{
		// An error has occurred 
		cout << "Error writing to " << filename << endl;
		exit(1);
	}
}


// render the mandelbrot
// parameters specify the region on the complex plane to plot.
void mandelbrot::compute_mandelbrot(double left, double right, double top, double bottom, int ystart, int yend)
{
	for (int y = ystart; y < yend; ++y)
		//for ( ystart; ystart < yend; ++ystart) 
	{
		for (int x = 0; x < WIDTH; ++x)
		{
			// Work out the point in the complex plane that
			// corresponds to this pixel in the output image.
			complex<double> c(left + (x * (right - left) / WIDTH),
				top + (y * (bottom - top) / HEIGHT));

			// Start off z at (0, 0).
			complex<double> z(0.0, 0.0);

			// Iterate z = z^2 + c until z moves more than 2 units
			// away from (0, 0), or we've iterated too many times.
			int iterations = 0;
			while (abs(z) < 2.0 && iterations < MAX_ITERATIONS)
			{
				z = (z * z) + c;
				

				++iterations;
			}

			if (iterations == MAX_ITERATIONS)
			{
				// z didn't escape from the circle.
				// This point is in the Mandelbrot set.
				image[y][x] = brotColour; // brot colour
			}
			else
			{
				// z escaped within less than MAX_ITERATIONS
				// iterations. This point isn't in the set.
				image[y][x] = backgroundColour; // brot background colour
			}
		}
	}
}


// colour select
void mandelbrot::getColour(int colour, int part)
{

	if (part == 1) // set the colur for the brot
	{
		if (colour == 1) // gold
		{
			brotColour = 0xEEB462;
			//return true;
		}
		else if (colour == 2) // purple
		{
			brotColour = 0x534666;
			//return true;
		}
		else if (colour == 3) // red
		{
			brotColour = 0xFF0000;
			//return true;
		}
		else if (colour == 4) // green
		{
			brotColour = 0x00FF00;
			//return true;
		}
	}
	else if (part == 2) // set background colour
	{
		if (colour == 1) // gold
		{
			backgroundColour = 0xEEB462;
			//return true;
		}
		else if (colour == 2) // purple
		{
			backgroundColour = 0x534666;
			//return true;
		}
		else if (colour == 3) // red
		{
			backgroundColour = 0xFF0000;
			//return true;
		}
		else if (colour == 4) // green
		{
			backgroundColour = 0x00FF00;
			//return true;
		}
	}
	


}
