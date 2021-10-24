#ifndef MANDELBROTTASK_H
#define MANDELBROTTASK_H

#include "Mandelbrot.h"
#include <string>

#include "task.h"

///** Task that prints a message to cout. */

class MandelbrotTask : public Task
{
public:
	MandelbrotTask(int ystart, int yend) : mandelbrot_start(ystart), mandelbrot_end(yend)
	{

	}

	void run(); // run the mandelbrot

	static void colourSelect(int part); // selecting the colour

private:

	int mandelbrot_end;
	int mandelbrot_start;

};

#endif