#include "Mouse.h"

std::pair<int, int> Mouse::getPos() const noexcept
{
	return { x,y };
}

int Mouse::getPosX() const noexcept
{
	return x;
}

int Mouse::getPosY() const noexcept
{
	return y;
}

bool Mouse::leftIsPressed() const noexcept
{
	return leftIsPressedFlag;
}

bool Mouse::rightIsPressed() const noexcept
{
	return rightIsPressedFlag;
}

Mouse::Event Mouse::read() noexcept
{
	if (buffer.size() > 0u)
	{
		Mouse::Event e = buffer.front();
		buffer.pop();
		return e;
	}
	else
	{
		return Mouse::Event();
	}
}

void Mouse::flush() noexcept
{
	buffer = std::queue<Event>();
}

void Mouse::onMouseMove(int newX, int newY) noexcept
{
	x = newX;
	y = newY;

	buffer.push(Mouse::Event(Mouse::Event::Type::Move, *this));
	trimBuffer();
}

void Mouse::onLeftPressed(int x, int y) noexcept
{
	leftIsPressedFlag = true;

	buffer.push(Mouse::Event(Mouse::Event::Type::LPress, *this));
	trimBuffer();
}

void Mouse::onLeftReleased(int x, int y) noexcept
{
	leftIsPressedFlag = false;

	buffer.push(Mouse::Event(Mouse::Event::Type::LRelease, *this));
	trimBuffer();
}

void Mouse::onRightPressed(int x, int y) noexcept
{
	rightIsPressedFlag = true;

	buffer.push(Mouse::Event(Mouse::Event::Type::RPress, *this));
	trimBuffer();
}

void Mouse::onRightReleased(int x, int y) noexcept
{
	rightIsPressedFlag = false;

	buffer.push(Mouse::Event(Mouse::Event::Type::RRelease, *this));
	trimBuffer();
}

void Mouse::onWheelDown(int x, int y) noexcept
{
	buffer.push(Mouse::Event(Mouse::Event::Type::WheelDown, *this));
	trimBuffer();
}

void Mouse::onWheelUp(int x, int y) noexcept
{
	buffer.push(Mouse::Event(Mouse::Event::Type::WheelUp, *this));
	trimBuffer();
}

void Mouse::trimBuffer() noexcept
{
	while (buffer.size() > bufferSize)
	{
		buffer.pop();
	}
}