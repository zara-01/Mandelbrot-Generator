// Task-based parallelism example
// Adam Sampson <a.sampson@abertay.ac.uk>

#include <iostream>
#include <string>
#include <chrono>
#include "farm.h"
#include "task.h"
#include "mandelbrotTask.h"
#include "CalcTask.h"

// Import things we need from the standard library
using std::cout;
using std::to_string;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
typedef std::chrono::steady_clock the_clock;



int main(int argc, char *argv[])
{
	
		// colour selection of the mandelbrot and the background
		cout << "Pick a Colour for the Mandelbrot...\n";
		MandelbrotTask::colourSelect(1);
		cout << "Pick a Colour for the Background...\n";
		MandelbrotTask::colourSelect(2);

		// init the farm
		Farm theFarm;

		// Start timing
		the_clock::time_point start = the_clock::now();

		// add the tasks to the farm
		for (int i = 0; i < 1100; ++i) // renders by slice
		{
			theFarm.callMainRelease(); // signal the semaphore

			theFarm.add_task(new MandelbrotTask(i, i + 1)); // first task computing the brot

			theFarm.callThreadRelease(); // signal the semaphore
			theFarm.callMainRelease(); // signal the semaphore

			theFarm.add_task(new CalcTask(i, 1100)); // second task calculating and outputting the %

			theFarm.callThreadRelease(); // signal the semaphore
		}
		cout << "Running task farm...\n";

		// run the farm
		theFarm.run();

		cout << "\nTasks complete!\n";

		// Stop timing
		the_clock::time_point end = the_clock::now();

		// Compute the difference between the two times in milliseconds
		auto time_taken = duration_cast<milliseconds>(end - start).count();
		cout << "The Farm Took " << time_taken << " ms." << "\n";


		// write to the file
		mandelbrot::write_tga("output.tga");
	
	return 0;
}