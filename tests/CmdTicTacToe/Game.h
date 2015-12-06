#pragma once

#include "CMatchManager.h"
#include "ClanUtils.h"

struct Game: CMatchEventListener {

	void Run(autoref<CMatch> match, shared_ptr<CHJSON> matchConfig);

private:
	enum Player {
		NONE = 0, CROSS, CIRCLE, LAST, DRAW
	};
	Player field[3][3];
	autoref<CMatch> currentMatch;
	owned_ref<CHJSON> winnersNode;
	bool running, pending;
	Player currentPlayer, myself;

	Player &Block(int x, int y);
	void CheckForGameOver();
	void DrawPlayfield();
	void PerformMoveEvent(const CHJSON *eventNode);
	Player PlayerId(const char *gamerId);
	const char *PlayerId(Player p);
	void RebuildGameState(const CHJSON *matchData);
	void UpdateWinersNode(const char *winnerGamerId);

	virtual void onMatchEventReceived(const CCloudResult *event);

};


