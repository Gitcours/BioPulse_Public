#pragma once
#include "Outils.h"
#include "TextureManager.h"
#include "EntityManager.h"
#include "Map.hpp"

class UserInput
{
private :
	Clock bulletclock;
	Clock dashSpamClock;
	Clock dashClock;
	Clock timeSinceLastPressOfDorQ;
	int dashCout = 0;
	bool isConnected = false;
	bool canClimb = false;
	int collide;
	int collideClimb;

public :

	void userInputManagement(EntityManager* manager, TextureManager& text, shared_ptr<Player> player);

};

