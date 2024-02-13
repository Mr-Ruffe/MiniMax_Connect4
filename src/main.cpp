#include "System.h"
#include "Session.h"

#include "Constants.h"

void setScene()
{
	// Static
	// Object *object = Object::getInstance(720);
	// ses.add(object);
	return;
}

int main(int argc, char *argv[])
{
	Session ses;
	setScene();
	ses.run();
	return 0;
}