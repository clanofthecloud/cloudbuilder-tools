#include "Input.h"
#include "CClan.h"
#include "ClanUtils.h"
#include <thread>
#include <chrono>

namespace input {
	static char commandBuffer[1024];
	static bool commandReady = false;
	static bool running = true;

	void InputThread() {
		while (running) {
			fgets(commandBuffer, numberof(commandBuffer), stdin);
			commandReady = true;
			while (commandReady && running) {
				std::this_thread::sleep_for(std::chrono::milliseconds(10));
			}
		}
	}

	void StopThread() {
		running = false;
	}

	void Idle() {
		CClan::Instance()->ProcessIdleTasks();
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}

	bool IsAvailable() { return commandReady; }

	const char *GetLine() {
		if (commandReady) {
			commandReady = false;
			return commandBuffer;
		}
		return NULL;
	}
}
