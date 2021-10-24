#pragma once
#include <string>
#include <iostream>
#include <iomanip>
#include <string>
#include "task.h"

class CalcTask : public Task
{
public:
	CalcTask(int loopCount, int totalCount) : loop(loopCount), total(totalCount)
	{

	}

	void run(); // run the calculation



private:
	float loop;
	float total;
	//float perc;
};

