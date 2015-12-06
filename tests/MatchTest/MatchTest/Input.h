#pragma once

// Allows for asynchronous input
namespace input {
	void InputThread();
	void StopThread();

	extern const char *GetLine();
	extern void Idle();
	extern bool IsAvailable();
}
