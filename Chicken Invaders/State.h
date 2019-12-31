#pragma once
#include <memory>

class GameManager;

class State
{
public:
	virtual~State() = default;
	virtual void draw() = 0;
	virtual void update() = 0;
	virtual void handleInput() = 0;

protected:
	//holds pointer to game manager so each state can remove add states to stack, and use window
	std::shared_ptr<GameManager> m_game;
};