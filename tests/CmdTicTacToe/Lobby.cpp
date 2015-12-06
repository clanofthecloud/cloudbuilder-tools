#include <time.h>
#include "Lobby.h"
#include "Tokenizer.hpp"
#include "CUserManager.h"
#include "CFilesystem.h"
#include "Input.h"

//////////////////////////// Menu + commands ////////////////////////////
Lobby::Lobby() : verbose(true) {
	// Fill up supported commands
	commands.emplace_back("help", "Shows help", [&] (Tokenizer& cmd) {
		for (Command &c: commands) {
			printf("- %s%s: %s\n", c.name, c.syntax, c.helpText);
		}
		CommandDone();
	});
	// Exit
	commands.emplace_back("exit", "Quits abruptly", [&] (Tokenizer& cmd) { exit(0); });
	// List users
	commands.emplace_back("users", "Lists or clears stored users", " [clear]", [&] (Tokenizer& cmd) {
		char clear[1024];
		int index = 0;
		if (cmd.nextWord(clear)) {
			if (IsEqual(clear, "clear")) {
				printf("Cleared cached user list.\n");
				storedUsers <<= CHJSON::Array();
			} else {
				printf("Unrecognized argument %s.\n", clear);
			}
		}
		for (const CHJSON *node: *storedUsers) {
			printf("%d: %s\n", ++index, node->GetString("gamer_id"));
		}
		CommandDone();
	});
	// Login anonymous
	commands.emplace_back("loga", "Login anonymous (adding a user to the list)", [&] (Tokenizer& cmd) {
		CUserManager::Instance()->LoginAnonymous(MakeResultHandler([&] (eErrorCode err, const CCloudResult *result) {
			PrintResult("loga", result);
			if (!err) {
				AddUser(result->GetJSON()->GetString("gamer_id"), result->GetJSON()->GetString("gamer_secret"));
			}
			CommandDone();
		}));
	});
	// Log with stored user ID
	commands.emplace_back("log", "Logs as a stored user", " user_id (obtain through `users`)", [&] (Tokenizer& cmd) {
		char word[1024];
		cmd.nextWord(word);
		int index = atoi(word) - 1;
		if (index >= 0 && index < storedUsers->size()) {
			const CHJSON *node = storedUsers->Get(index);
			CHJSON config;
			config.Put("id", node->GetString("gamer_id"));
			config.Put("secret", node->GetString("gamer_secret"));

			CUserManager::Instance()->ResumeSession(&config, MakeResultHandler([&] (eErrorCode err, const CCloudResult *result) {
				PrintResult("log", result);
				CommandDone();
			}));
		} else {
			printf("%d: Out of range\n", index + 1);
			CommandDone();
		}
	});
	// Restore last match
	commands.emplace_back("resume", "Tries to resume the last played match", " [match_id]", [&] (Tokenizer& cmd) {
		CHJSON config;
		config.Put("id", GetStoredMatch(cmd));
		config.Put("domain", "private");
		CMatchManager::Instance()->HLRestoreMatch(&config, MakeMatchResultHandler([&] (eErrorCode err, const CCloudResult *result, CMatch *match) {
			PrintResult("resume", result);
			if (!err) {
				StartGame(match, result);
			}
			CommandDone();
		}));
	});
	// Join match
	commands.emplace_back("join", "Joins a match", " [match_id]", [&] (Tokenizer& cmd) {
		const char *matchId = GetStoredMatch(cmd);
		if (!matchId) {
			printf("Match ID required\n");
			CommandDone();
			return;
		}
		CHJSON config;
		config.Put("id", matchId);
		CMatchManager::Instance()->HLJoinMatch(&config, MakeMatchResultHandler([&] (eErrorCode err, const CCloudResult *result, CMatch *match) {
			PrintResult("join", result);
			if (!err) {
				StartGame(match, result);
			}
			CommandDone();
		}));
	});
	// Delete match
	commands.emplace_back("finish", "Finishes a match", " match_id", [&] (Tokenizer& cmd) {
		const char *matchId = GetStoredMatch(cmd);
		if (!matchId) {
			printf("Match ID required\n");
			CommandDone();
			return;
		}
		CHJSON config;
		config.Put("id", matchId);
		CMatchManager::Instance()->HLRestoreMatch(&config, MakeMatchResultHandler([&] (eErrorCode err, const CCloudResult *result, CMatch *match) {
			PrintResult("finish", result);
			if (match) {
				match->Finish(true, NULL, MakeMatchResultHandler([&] (eErrorCode err, const CCloudResult *result, CMatch *match) {
					PrintResult("finish.delete", result);
					if (result->GetJSON()->GetInt("done")) {
						printf("Match deleted!\n");
					}
					CommandDone();
				}));
			} else {
				CommandDone();
			}
		}));
	});
	// List matches
	commands.emplace_back("matches", "Lists available matches, IDs can be used when joining/resuming matches", " [FILTER | ONLY_PARTICIPATING] -- pass 1 to filter to participating matches or a JSON like {\"property\": \"value\"} to filter returned matches", [&] (Tokenizer& cmd) {
		CHJSON config;
		char filter[1024];
		Tokenizer::Type t = cmd.nextWord(filter);
		if (t == Tokenizer::OpeningBrace || t == Tokenizer::OpeningBracket) {
			// JSON?
			config.Put("filter", CHJSON::parse(filter));
		} else if (atoi(filter) == 1) {
			// Boolean
			config.Put("participating", true);
		}
		CMatchManager::Instance()->ListMatches(&config, MakeResultHandler([&] (eErrorCode err, const CCloudResult *result) {
			PrintResult("list", result);
			if (!err) {
				// Keep the list of matches
				int matchId = 0;
				storedMatches <<= CHJSON::Array();
				for (const CHJSON *node: *result->GetJSON()->GetSafe("matches")) {
					storedMatches->Add(new CHJSON(node->GetString("_id")));
					printf("%d: %s\n", ++matchId, node->GetString("_id"));
				}
			}
			CommandDone();
		}));
	});
	// Create a match
	commands.emplace_back("create", "Creates a match", " [description] [properties]", [&] (Tokenizer& cmd) {
		CHJSON config;
		char arg[1024];
		Tokenizer::Type t = cmd.nextWord(arg);
		config.Put("domain", "private");
		config.Put("description", "Console Tic Tac Toe match");
		config.Put("maxPlayers", 2);
		if (t == Tokenizer::Letter) {
			config.Put("description", arg);
			t = cmd.nextWord(arg);
		}
		if (t == Tokenizer::OpeningBrace || t == Tokenizer::OpeningBracket) {
			config.Put("customProperties", CHJSON::parse(arg));
		}
		CMatchManager::Instance()->HLCreateMatch(&config, MakeMatchResultHandler([&] (eErrorCode err, const CCloudResult *result, CMatch *match) {
			PrintResult("create", result);
			if (!err) {
				StartGame(match, result);
			}
			CommandDone();
		}));
	});
}

Lobby::RunResult Lobby::Run() {
	storedUsers <<= CFilesystemManager::Instance()->ReadJson("storedUsers.json");
	if (!storedUsers) { storedUsers <<= CHJSON::Array(); }
	storedMatches <<= CHJSON::Array();

	printf("~~~ In the lobby ~~~\nAllowed commands:\n");
	for (Command &c: commands) {
		printf("- %s: %s\n", c.name, c.helpText);
	}
	running = true, commandPending = false;

	while (running) {
		if (commandPending) {
			input::Idle();
			continue;
		}
		printf("Command:> ");
		fflush(stdout);
		while (!input::IsAvailable()) { input::Idle(); }
		RunCommand(input::GetLine());
	}
	return result;
}

//////////////////////////// Private stuff ////////////////////////////
void Lobby::AddUser(const char *gamerId, const char *gamerSecret) {
	CHJSON *user = new CHJSON;
	user->Put("gamer_id", gamerId);
	user->Put("gamer_secret", gamerSecret);
	storedUsers->Add(user);
	CFilesystemManager::Instance()->WriteJson("storedUsers.json", storedUsers);
}

void Lobby::CommandDone() {
	commandPending = false;
}

const char *Lobby::GetStoredMatch(Tokenizer &cmd) {
	char arg[1024];
	if (cmd.nextWord(arg)) {
		int id = atoi(arg) - 1;
		if (id >= 0 && id < storedMatches->size()) {
			return storedMatches->Get(id)->valueString();
		} else {
			printf("Match ID out of range: %d\n", id + 1);
		}
	}
	return NULL;
}

void Lobby::PrintResult(const char *cmdName, const CCloudResult *result) {
	if (verbose) {
		printf("Result of %s: %s\n", cmdName, cstring(result->Print(), true).c_str());
	}
}

void Lobby::RunCommand(const char *command) {
	char cmd[1024];
	Tokenizer t(command);
	t.nextWord(cmd);
	for (Command& command: commands) {
		if (!stricmp(cmd, command.name)) {
			commandPending = true;
			command.func(t);
			return;
		}
	}
	if (*cmd) {
		printf("Unrecognized command %s\n", cmd);
	}
}

void Lobby::StartGame(CMatch *match, const CCloudResult *matchData) {
	printf("Starting match %s\n", match->GetMatchId());
	result.match = mkref(match);
	result.matchConfig = shared_ptr<CHJSON>(matchData->GetJSON()->GetSafe("match")->Duplicate());
	running = false;
}
