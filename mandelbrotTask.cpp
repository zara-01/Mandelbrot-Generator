#include "mandelbrotTask.h"

#include <iostream>

using std::cout;
using std::cin;

void MandelbrotTask::run() 
{
	mandelbrot::compute_mandelbrot(-2.0, 1.0, 1.125, -1.125, mandelbrot_start, mandelbrot_end); // run the compute mandelbrot
}

// colour selection
void MandelbrotTask::colourSelect(int part)
{
	cout << "Press ( 1 ) for: GOLD...\n";
	cout << "Press ( 2 ) for: PURPLE...\n";
	cout << "Press ( 3 ) for: RED...\n";
	cout << "Press ( 4 ) for: GREEN...\n";

	int colourSelected;
	cin >> colourSelected;
	while (colourSelected > 4)
	{
		cout << "That is not a correct option... please try again\n";
		cin >> colourSelected;
	}

	mandelbrot::getColour(colourSelected, part);

}