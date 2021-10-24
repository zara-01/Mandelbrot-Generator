#pragma once


class mandelbrot
{
public:


	static void write_tga(const char* filename);

	static void compute_mandelbrot(double left, double right, double top, double bottom, int ystart, int yend);

	static void getColour(int colour, int part);

	

};