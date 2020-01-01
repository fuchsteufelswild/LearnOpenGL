#pragma once
#include <memory>
class Camera;

class KeyCommand
{
public:
	KeyCommand() = default;
	virtual ~KeyCommand() = default;
public:
	KeyCommand(const KeyCommand& rCommand) = delete;
	KeyCommand& operator=(const KeyCommand& rCommand) = delete;

	virtual void PerformAction(Camera& target) = 0;
};


class DummyCommand : public KeyCommand
{
public:
	void PerformAction(Camera& target) override { return; }
};

class Key
{
private:
	//static std::unique_ptr<KeyCommand> dummyCommand; // Does nothing
	unsigned char m_KeyCode;
	KeyCommand* m_Command;
	bool isPressed = false;
public:
	Key(unsigned char p_KeyCode, KeyCommand* p_Command = nullptr)
		: m_KeyCode(p_KeyCode), m_Command(p_Command) { }

	// 
	void Perform(Camera& targetCamera) { m_Command->PerformAction(targetCamera); }
	//
	void SetKeyCommand(KeyCommand* newCommand) { m_Command = newCommand; }
	void SetPressed(bool newPress) { isPressed = newPress; }
	//
	KeyCommand* GetKeyCommand() const { return m_Command; }
	unsigned char GetKeyCode() const { return m_KeyCode; }
	bool IsPressed() const { return isPressed; }
};

//std::unique_ptr<KeyCommand> Key::dummyCommand = std::make_unique<DummyCommand>();



class GoRightCommand : public KeyCommand
{
public:
	void PerformAction(Camera& target) override;
};

class GoLeftCommand : public KeyCommand
{
public:
	void PerformAction(Camera& target) override;
};

class GoUpCommand : public KeyCommand
{
public:
	void PerformAction(Camera& target) override;
};

class GoDownCommand : public KeyCommand
{
public:
	void PerformAction(Camera& target) override;
};

class GoForwardCommand : public KeyCommand
{
public:
	void PerformAction(Camera& target) override;
};

class GoBackwardCommand : public KeyCommand
{
public:
	void PerformAction(Camera& target) override;
};

class MouseRotateHorizontalCommand : public KeyCommand
{
public:
	void PerformAction(Camera& target) override;
};

class MouseRotateVerticalCommand : public KeyCommand
{
public:
	void PerformAction(Camera& target) override;
};