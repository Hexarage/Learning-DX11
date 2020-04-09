#include "ConfuxTimer.h"

ConfuxTimer::ConfuxTimer()
{
	last = std::chrono::steady_clock::now();
}

float ConfuxTimer::mark()
{
	const auto old = last;
	last = std::chrono::steady_clock::now();
	const std::chrono::duration<float> frameTime = last - old;
	return frameTime.count();
}

float ConfuxTimer::peek() const
{
	return std::chrono::duration<float>(std::chrono::steady_clock::now() - last).count();
}