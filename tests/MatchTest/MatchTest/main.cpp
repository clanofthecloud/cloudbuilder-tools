#include "CClan.h"
#include "ClanUtils.h"
#include "Lobby.h"
#include "Input.h"
#include "Game.h"
#include <thread>

int main() {
	std::thread t(&input::InputThread);
	printf("Welcome to the Tic Tac Toe!\n");

	CHJSON setupJson;
	setupJson.Put("key", "cloudbuilder-key");
	setupJson.Put("secret", "azerty");
	setupJson.Put("env", "http://10.211.55.2:2000");
	setupJson.Put("appFolder", "CotC/cmdtictactoe");
	CClan::Instance()->Setup(&setupJson, MakeResultHandler([] (eErrorCode err, const CCloudResult *result) {
		if (err) {
			printf("Setup failed: %s\n", cstring(result->Print(), true).c_str());
			return;
		}

		autoref<Lobby> menu = newref Lobby;
		autoref<CMatch> match = menu->Run();
		autoref<Game> game = newref Game();
		game->Run(match);
	}));

	input::StopThread();
	t.join();
	return 0;
}
