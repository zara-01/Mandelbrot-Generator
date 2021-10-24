#include "farm.h"

#include <chrono>
#include <cstdint>
#include <cstdlib>
#include <complex>
#include <fstream>
#include <iostream>
#include <semaphore>
#include <thread>
#include <vector>

// import things from the standard library
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::complex;
using std::cout;
using std::endl;
using std::ofstream;
using std::thread;
using std::binary_semaphore;

// create the semaphores
binary_semaphore smphSignalMainToThread(0);
binary_semaphore smphSignalThreadToMain(0);


// add a task
void Farm::add_task(Task *task)
{
	smphSignalMainToThread.acquire(); // signal the semaphore
	taskQueue.push(task); // push a mandelbrot task
	smphSignalThreadToMain.release(); // get the signal from main

}

void Farm::run()
{
	// vector of threads
	std::vector<std::thread*> threads; 

	// generate as many threads as the hardware can handle 
	for (int i = 0; i < std::thread::hardware_concurrency(); i++)
	{
		// push back the threads into the vector
		threads.push_back(new std::thread([&]()
			{
				// while the task que isn't empty
				while (!taskQueue.empty())
				{
					// lock
					taskMutex.lock();

					Task* tempTask = taskQueue.front(); // store current task thread is running

					taskQueue.pop(); // pop the task from the queue

					//unlock
					taskMutex.unlock();

					tempTask->run(); // run the task


				}

			}));
	}

	for (auto thread : threads)
	{
		thread->join(); // join the threads
	}

}

void Farm::callMainAcquire()
{
	smphSignalMainToThread.acquire();
}

void Farm::callMainRelease()
{
	smphSignalMainToThread.release();
}

void Farm::callThreadAcquire()
{
	smphSignalThreadToMain.acquire();
}

void Farm::callThreadRelease()
{
	smphSignalThreadToMain.release();
}