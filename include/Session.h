#ifndef SESSION_H
#define SESSION_H

#include <vector>
#include "Component.h"

/// Based on the Session class by @author jozef

/// @brief The current session instance keeping track of all the components in the session.
class Session
{
public:
	/// @brief Constructor for the session.
	Session();

	/// @brief Add a component to the session (meaning that it will be updated accordingly).
	/// @param c Component to be added.
	void add(Component *c);
	
	/// @brief Start the session.
	void run();

	/// @brief Destructor for the session.
	~Session() {}

private:
	// Vector containing all components
	std::vector<Component *> comps;

	// Vector containing components to be added to the components vector
	std::vector<Component *> newComps;

};

#endif