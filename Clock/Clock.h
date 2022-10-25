#pragma once
#include <chrono>


class Clock
{
	std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
	std::chrono::duration<double> duration;
public:
	Clock();
	double getTime();
	void reset();

};

