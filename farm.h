#ifndef FARM_H
#define FARM_H

#include "task.h"
#include <queue>
#include <thread>
#include <mutex>
#include <semaphore>


/** A collection of tasks that should be performed in parallel. */
class Farm {
public:
	
	void add_task(Task *task); // add task

	void run(); // run the task

	void callMainAcquire();
	void callMainRelease();
	void callThreadAcquire();
	void callThreadRelease();

private:

	std::queue<Task*> taskQueue; // task queue
	std::mutex taskMutex; // task mutex


};

#endif
