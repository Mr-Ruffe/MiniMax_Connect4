#ifndef SESSION_H
#define SESSION_H

#include <vector>
#include "Component.h"

class Session
{
public:
	Session();
	void add(Component *c);
	void run();
	~Session() {}

private:
	std::vector<Component *> comps;
	std::vector<Component *> newComps;

};

#endif