#pragma once
#include <chrono>


class Clock
{
	std::chrono::time_point<std::chrono::steady_clock> start, end;
	std::chrono::duration<double> duration;
public:
	Clock();
	double getTime();
	void reset();

};

