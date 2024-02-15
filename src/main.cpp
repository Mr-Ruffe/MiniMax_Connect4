#include "System.h"
#include "Session.h"

#include "Constants.h"
#include "BoardTile.h"

void setScene(Session &ses)
{
	for (int i = 0; i < constants::sizeX; i++)
	{
		for (int j = 0; j < constants::sizeY; j++)
		{
			BoardTile *boardTile = BoardTile::getInstance(50 + 100*i, 100 + 100*j);
			ses.add(boardTile);
		}
	}
	// Object *object = Object::getInstance(720);
	// ses.add(object);
	return;
}

int main(int argc, char *argv[])
{
	Session ses;
	setScene(ses);
	ses.run();
	return 0;
}