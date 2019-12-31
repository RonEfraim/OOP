#pragma once
#include "Command.h"

class NewGame : public Command
{
public:
	void execute(sf::RenderWindow&) override;
};