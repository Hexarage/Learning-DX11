#include "Mouse.h"
#include "WindowsIncludes.h"

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

bool Mouse::isInWindow() const noexcept
{
	return isInWindowFlag;
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

void Mouse::onMouseLeave() noexcept
{
	isInWindowFlag = false;
	buffer.push(Mouse::Event(Mouse::Event::Type::Leave, *this));
	trimBuffer();
}

void Mouse::onMouseEnter() noexcept
{
	isInWindowFlag = true;
	buffer.push(Mouse::Event(Mouse::Event::Type::Enter, *this));
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

void Mouse::onWheelDelta(int x, int y, int delta) noexcept
{
	wheelDeltaCarry += delta;
	// Generate events for every 120
	while (wheelDeltaCarry >= WHEEL_DELTA)
	{
		wheelDeltaCarry -= WHEEL_DELTA;
		onWheelUp(x, y);
	}
	while (wheelDeltaCarry <= -WHEEL_DELTA)
	{
		wheelDeltaCarry += WHEEL_DELTA;
		onWheelDown(x, y);
	}
}