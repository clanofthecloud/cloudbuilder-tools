#pragma once

#include "CMatchManager.h"
using namespace CloudBuilder;
using namespace CotCHelpers;

struct Game: CMatchEventListener {

	void Run(autoref<CMatch> match);

private:
	enum Player {
		NONE = 0, CROSS, CIRCLE, LAST, DRAW
	};
	Player field[3][3];
	autoref<CMatch> currentMatch;
	bool running, pending;
	Player currentPlayer, me;

	Player &Block(int x, int y);
	void CheckForGameOver();
	CHJSON *CreateUpdatedWinsNode(const char *winnerGamerId);
	void DrawPlayfield();
	void RebuildGameState();
	void PerformMoveEvent(const CHJSON *eventNode);
	Player PlayerId(const char *gamerId);
	const char *PlayerId(Player p);

	virtual void onMatchEventReceived(const CCloudResult *event);

};


