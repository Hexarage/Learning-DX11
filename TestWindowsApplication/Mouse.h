#pragma once
#include <queue>

class Mouse
{
	friend class Window;
public:
	class Event 
	{
	public:
		enum class Type
		{
			LPress,
			LRelease,
			RPress,
			RRelease,
			WheelUp,
			WheelDown,
			Move,
			Enter,
			Leave,
			Invalid
		};
	private:
		Type type;
		bool leftIsPressedFlag;
		bool rightIsPressedFlag;
		int x;
		int y;
	public:
		Event() noexcept
			:
			type(Type::Invalid),
			leftIsPressedFlag(false),
			rightIsPressedFlag(false),
			x(0),
			y(0)
		{}

		Event(Type type, const Mouse& parent) noexcept
			:
			type(type),
			leftIsPressedFlag(parent.leftIsPressedFlag),
			rightIsPressedFlag(parent.rightIsPressedFlag),
			x(parent.x),
			y(parent.y)
		{}

		bool isValid() const noexcept
		{
			return type != Type::Invalid;
		}

		Type getType() const noexcept
		{
			return type;
		}

		std::pair<int, int> getPos() const noexcept
		{
			return { x,y };
		}

		int getPosX() const noexcept
		{
			return x;
		}

		int getPosY() const noexcept
		{
			return y;
		}

		bool leftIsPressed() const noexcept
		{
			return leftIsPressedFlag;
		}

		bool rightIsPressed() const noexcept
		{
			return rightIsPressedFlag;
		}
	};
public:
	Mouse() = default;
	Mouse(const Mouse&) = delete;
	Mouse& operator=(const Mouse&) = delete;
	std::pair<int, int> getPos() const noexcept;
	int getPosX() const noexcept;
	int getPosY() const noexcept;
	bool isInWindow() const noexcept;
	bool leftIsPressed() const noexcept;
	bool rightIsPressed() const noexcept;
	Mouse::Event read() noexcept;

	bool isEmpty() const noexcept
	{
		return buffer.empty();
	}

	void flush() noexcept;
private:
	void onMouseMove(int x, int y) noexcept;
	void onMouseLeave() noexcept;
	void onMouseEnter() noexcept;
	void onLeftPressed(int x, int y) noexcept;
	void onLeftReleased(int x, int y) noexcept;
	void onRightPressed(int x, int y) noexcept;
	void onRightReleased(int x, int y) noexcept;
	void onWheelUp(int x, int y) noexcept;
	void onWheelDown(int x, int y) noexcept;
	void trimBuffer() noexcept;
	void onWheelDelta(int x, int y, int delta) noexcept;
private:
	static constexpr unsigned int bufferSize = 16u;
	int x;
	int y;
	bool leftIsPressedFlag = false;
	bool rightIsPressedFlag = false;
	bool isInWindowFlag = false;
	int wheelDeltaCarry = 0;
	std::queue<Event> buffer;
};

