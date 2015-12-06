#include "precompiled.h"
#include <conio.h>
#include "main.h"
#include "CClan.h"
#include "CMatchManager.h"
#include "CUserManager.h"
#include "CGameManager.h"
#include "Utils.h"

using namespace CloudBuilder;
using namespace CotCHelpers;

struct MyGame : CEventListener {
	CClan *clan;
	CUserManager *userManager;

	void Main(int argc, char *argv[]) {
		enum {RUNNING, TERMINATED, EXIT} state = RUNNING;
		
		CHJSON *setupJson = new CHJSON;
		setupJson->Put("key", "cloudbuilder-key");
		setupJson->Put("secret", "azerty");
		setupJson->Put("eventLoopTimeout", 10);
		setupJson->Put("httpVerbose", true);
 		setupJson->Put("env", "http://10.211.55.2:2000");
// 		setupJson->Put("env", "http://195.154.227.44:8000");
//		setupJson->Put("env", "sandbox");

		CClan::Instance()->Setup(setupJson, MakeResultHandler([] (eErrorCode, const CCloudResult *result) {
			printf("Result: %s\n", cstring(result->Print(), true));

			CUserManager::Instance()->LoginAnonymous(MakeResultHandler([] (eErrorCode, const CCloudResult *result) {
				printf("Result: %s\n", cstring(result->Print(), true));

				CHJSON config, *shoe = CHJSON::Array();
				config.Put("domain", "private");
				config.Put("maxPlayers", 10);
				// Put possible values in the shoe
				shoe->Add(new CHJSON(1.));
				shoe->Add(new CHJSON(2.));
				shoe->Add(new CHJSON(3.));
				shoe->Add(new CHJSON(4.));
				config.Put("shoe", shoe);
				CMatchManager::Instance()->HLCreateMatch(&config, MakeMatchResultHandler([&] (eErrorCode err, const CCloudResult *result, CMatch *match) {
					printf("Result: %s\n", cstring(result->Print(), true));

					match->DrawFromShoe(9, MakeMatchResultHandler([&] (eErrorCode err, const CCloudResult *result, CMatch *match) {
						printf("Result: %s\n", cstring(result->Print(), true));

						match->Finish(false, MakeMatchResultHandler([&] (eErrorCode err, const CCloudResult *result, CMatch *match) {
							printf("Result: %s\n", cstring(result->Print(), true));

							CHJSON config;
							config.Put("id", match->GetMatchId());
							CMatchManager::Instance()->FetchMatch(&config, MakeResultHandler([&] (eErrorCode err, const CCloudResult *result) {
								printf("Result: %s\n", cstring(result->Print(), true));

							}));
						}));
					}));
				}));
			}));
		}));

		printf("Press G to get data\n");
		while (state != EXIT) {
			CClan::Instance()->ProcessIdleTasks();
			Sleep(10);
			if (_kbhit()) {
				_getch();

				switch (state) {
				case RUNNING:
					CClan::Instance()->Terminate();
					printf("Terminated instance\n");
					state = EXIT;
					break;
				case TERMINATED:
					state = EXIT;
					break;
				}
			}
		}
	}

	virtual void onEventReceived(const char *aDomain, const CCloudResult *aEvent)
	{
		printf("Got event %s!\n", aDomain);
	}

	virtual void onEventError(eErrorCode aErrorCode, const char *aDomain, const CCloudResult *aEvent)
	{
		printf("Got error %s with code %d!\n", aDomain, aErrorCode);
	}
};


int main(int argc, char *argv[]) {
	while (true) {
		MyGame *game = new MyGame;
		game->Main(argc, argv);
		game->Release();
	}
	return 0;
}
