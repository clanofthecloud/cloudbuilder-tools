#include "Game.h"
#include "CClan.h"
#include "ClanUtils.h"
#include "Tokenizer.hpp"
#include "Input.h"

void Game::Run(autoref<CMatch> match) {
	bool alreadyShownWaitingMessage = false;
	currentMatch = match;
	running = true, pending = false;
	match->RegisterEventListener(this);
	RebuildGameState();

	me = PlayerId(match->GetGamerId());
	printf("~~~In the game~~~\nMake your moves: for example type 3 1 to place something on the game at row 3, column 1.\nOr type exit or leave.\n");
	while (running) {
		// Not our turn / command running
		if (pending) {
			input::Idle();
			continue;
		}
		if (currentPlayer != me) {
			if (!alreadyShownWaitingMessage) {
				DrawPlayfield();
				printf("Waiting on other player to take turn...\n");
				alreadyShownWaitingMessage = true;
			}
			input::Idle();
			continue;
		}

		DrawPlayfield();
		printf("Where to play:> ");
		while (!input::IsAvailable()) { input::Idle(); }
		
		// Parse position
		Tokenizer tok(input::GetLine());
		char arg1[1024], arg2[1024];
		if (tok.nextWord(arg1) == Tokenizer::Number &&
			tok.nextWord(arg2) == Tokenizer::Number) {
			// Sanity checks
			int x = atoi(arg2) - 1, y = atoi(arg1) - 1;
			if (x < 0 || x > 2 || y < 0 || y > 2) {
				printf("Invalid position lig=%d,col=%d\n", y, x);
				continue;
			}
			if (Block(x, y) != NONE) {
				printf("You cannot play here. Try again elsewhere.\n");
				continue;
			}

			// Make the actual move
			CHJSON move;
			move.Put("x", x);
			move.Put("y", y);
			// Select the next player
			currentPlayer = Player((currentPlayer % (LAST - 1)) + 1);
			move.Put("nextPlayer", currentPlayer);
			Block(x, y) = me;
			match->PostMove(&move, NULL, MakeMatchResultHandler([&] (eErrorCode err, const CCloudResult *result, CMatch*) {
				pending = false;
				CheckForGameOver();
			}));
			pending = true;
			alreadyShownWaitingMessage = false;
		} else if (!stricmp(arg1, "exit")) {
			running = false;
		} else {
			printf("Unrecognized command %s\n", arg1);
		}
	}
	match->UnregisterEventListener(this);
}

Game::Player& Game::Block(int x, int y) {
	if (x >= 0 && x < 3 && y >= 0 && y < 3)
		return field[y][x];
	else
		throw std::runtime_error("Invalid block");
}

void Game::CheckForGameOver() {
	// Check for a winner
	Player won = NONE;
	int totalOccupiedBlocks = 0;
	for (int i = 0; i < 3; i++) {
		int sameRow[LAST] = {0}, sameCol[LAST] = {0};
		for (int j = 0; j < 3; j++) {
			sameRow[Block(i, j)] += 1;
			sameCol[Block(j, i)] += 1;
			totalOccupiedBlocks += Block(i, j) != NONE ? 1 : 0;
		}
		for (int j = 1; j < LAST; j++) {
			if (sameRow[j] == 3 || sameCol[j] == 3) {
				won = Player(j);
			}
		}
	}
	// Diagonals
	if ((Block(0, 0) == Block(1, 1) && Block(1, 1) == Block(2, 2)) ||
		(Block(2, 0) == Block(1, 1) && Block(1, 1) == Block(0, 2))) {
		won = Block(1, 1);
	}
	// All the playfield used
	if (totalOccupiedBlocks == 3 * 3 && won == NONE) {
		won = DRAW;
	}

	if (won != NONE) {
		const char *gamerId = PlayerId(won);
		// Don't allow to play further
		currentPlayer = NONE;
		DrawPlayfield();
		if (won == me) {
			printf("You won! (%s)\n", gamerId);
		} else if (gamerId) {
			printf("Player %s won!\n", gamerId);
		} else {
			printf("It's a draw!\n");
		}
		memset(field, 0, sizeof(field));

		// Show stats
		owned_ref<CHJSON> wins (CreateUpdatedWinsNode(gamerId));
		printf("Win statistics:\n");
		for (const CHJSON *node: *wins) {
			int times = node->valueInt();
			printf("- Player %s has won %d time%c\n", node->name(), times, times == 1 ? '\0' : 's');
		}

		// It is up to the administrator to notify the winning game
		if (currentMatch->IsCreator()) {
			// Increment the number of wins for the player in question
			CHJSON move, globalState;
			globalState.Put("wins", wins.detachOwnership());
			// Select the next player
			currentPlayer = Player(1 + rand() % 2);
			move.Put("nextPlayer", currentPlayer);
			currentMatch->PostMove(&move, &globalState, MakeMatchResultHandler([&] (eErrorCode err, const CCloudResult *result, CMatch*) {
				pending = false;
			}));
			pending = true;
		}
	}
}

CHJSON *Game::CreateUpdatedWinsNode(const char *winnerGamerId) {
	CHJSON *winners = currentMatch->GetGlobalState()->GetSafe("wins")->Duplicate();
	if (winnerGamerId) {
		winners->Put(winnerGamerId, winners->GetInt(winnerGamerId) + 1);
	}
	return winners;
}

void Game::DrawPlayfield() {
	printf("-------\n");
	for (int j = 0; j < 3; j++) {
		for (int i = 0; i < 3; i++) {
			char c;
			switch (Block(i, j)) {
			case CROSS: c = 'X'; break;
			case CIRCLE: c = 'O'; break;
			default: c = ' '; break;
			}
			printf("|%c", c);
		}
		printf("|\n-------\n");
	}
}

void Game::onMatchEventReceived(const CCloudResult *event) {
	// Handling events
	const char *type = event->GetJSON()->GetString("type");
	const CHJSON *eventNode = event->GetJSON()->GetSafe("event");
	if (IsEqual(type, "match.move")) {
		// Move to perform
		PerformMoveEvent(eventNode);
	}
}

void Game::PerformMoveEvent(const CHJSON *eventNode) {
	const CHJSON *moveNode = eventNode->GetSafe("move");
	if (moveNode->Has("x")) {
		int x = moveNode->GetInt("x"), y = moveNode->GetInt("y");
		Player p = PlayerId(eventNode->GetString("player_id"));
		Block(x, y) = p;
	}
	currentPlayer = Player(moveNode->GetInt("nextPlayer"));
	CheckForGameOver();
}

Game::Player Game::PlayerId(const char *gamerId) {
	// Find the index of our gamer_id among players. This is a very basic way of doing things, we suggest assigning an ID to each new player and store it as globalState
	int foundAt = 0;
	if (!gamerId) {
		return DRAW;
	}
	for (const CHJSON *node: *currentMatch->GetPlayers()) {
		if (IsEqual(node->valueString(), gamerId)) {
			break;
		}
		foundAt++;
	}
	// Unknown player, shouldn't happen
	if (foundAt >= currentMatch->GetPlayers()->size()) {
		printf("WARNING: Unrecognized player %s (amongst %s).\n", gamerId, cstring(currentMatch->GetPlayers()->print(), true).c_str());
		foundAt = 0;
	}
	return Player(foundAt + 1);
}

const char* Game::PlayerId(Player p) {
	// The player number corresponds to the list of players (not very elaborate method)
	int id = p - 1;
	if (id >= 0 && id < currentMatch->GetPlayers()->size()) {
		return currentMatch->GetPlayers()->Get(id)->valueString();
	}
	return NULL;
}

void Game::RebuildGameState() {
	memset(field, 0, sizeof(field));

	// Randomly select first player
	srand(currentMatch->GetCustomProperties()->GetInt("seed"));
	currentPlayer = Player(1 + rand() % 2);

	// Apply each move
	for (const CHJSON *node: *currentMatch->GetEvents()) {
		if (IsEqual(node->GetString("type"), "match.move")) {
			PerformMoveEvent(node->GetSafe("event"));
		}
	}
}
