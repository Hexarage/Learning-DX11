#pragma once

#include <chrono>

class ConfuxTimer
{
public:
	ConfuxTimer();
	float mark();
	float peek() const;
private:
	std::chrono::steady_clock::time_point last;
};

