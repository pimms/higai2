#pragma once

#include <ctime>

/* Class to track time.
 */
class Timer {
public:
	Timer();
	
	void Start();
	void Stop();
	float Get();

private:
	clock_t _start;
	clock_t _end;
};
