#include "System.h"
#include "Session.h"

#include "Constants.h"
#include "BoardTile.h"
#include "Players.h"
#include "Tile.h"

void setScene(Session &ses)
{
	// Displaying the board
	BoardTile *boardTile = BoardTile::getInstance(100, 100, constants::sizeX, constants::sizeY);
	ses.add(boardTile);

	// Treating the creation of objects
	Players *players = Players::getInstance(ses);
	ses.add(players);

	return;
}

int main(int argc, char *argv[])
{
	Session ses;
	setScene(ses);
	ses.run();
	return 0;
}