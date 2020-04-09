#include "Keyboard.h"

bool Keyboard::keyIsPressed(unsigned char keycode) const noexcept
{
	return keyStates[keycode];
}

Keyboard::Event Keyboard::readKey() noexcept
{
	if (keyBuffer.size() > 0u)
	{
		Keyboard::Event e = keyBuffer.front();
		keyBuffer.pop();
		return e;
	}
	else
	{
		return Keyboard::Event();
	}
}

bool Keyboard::keyIsEmpty() const noexcept
{
	return keyBuffer.empty();
}
char Keyboard::readChar() noexcept
{
	if (charBuffer.size() > 0u)
	{
		unsigned char charcode = charBuffer.front();
		charBuffer.pop();
		return charcode;
	}
	else
	{
		return 0;
	}
}

bool Keyboard::charIsEmpty() const noexcept
{
	return charBuffer.empty();
}

void Keyboard::flushKey() noexcept
{
	keyBuffer = std::queue<Event>();
}

void Keyboard::flushChar() noexcept
{
	charBuffer = std::queue<char>();
}

void Keyboard::flush() noexcept
{
	flushKey();
	flushChar();
}

void Keyboard::enableAutorepeat() noexcept
{
	autorepeatEnabled = true;
}

void Keyboard::disableAutorepeat() noexcept
{
	autorepeatEnabled = false;
}

bool Keyboard::autorepeatIsEnabled() const noexcept
{
	return autorepeatEnabled;
}

void Keyboard::onKeyPressed(unsigned char keycode) noexcept
{
	keyStates[keycode] = true;
	keyBuffer.push(Keyboard::Event(Keyboard::Event::Type::Press, keycode));
	trimBuffer(keyBuffer);
}

void Keyboard::onKeyReleased(unsigned char keycode) noexcept
{
	keyStates[keycode] = false;
	keyBuffer.push(Keyboard::Event(Keyboard::Event::Type::Release, keycode));
	trimBuffer(keyBuffer);
}

void Keyboard::onChar(char character) noexcept
{
	charBuffer.push(character);
	trimBuffer(charBuffer);
}

void Keyboard::clearState() noexcept
{
	keyStates.reset();
}

template<typename T>
void Keyboard::trimBuffer(std::queue<T>& buffer) noexcept
{
	while (buffer.size() > bufferSize)
	{
		buffer.pop();
	}
}