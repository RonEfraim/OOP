
#ifdef _DEBUG
#pragma comment ( lib , "sfml-main-d.lib" )
#pragma comment ( lib , "sfml-system-d.lib" )
#pragma comment ( lib , "sfml-window-d.lib" )
#pragma comment ( lib , "sfml-graphics-d.lib" )
#pragma comment ( lib , "sfml-audio-d.lib" )
#elif defined (NDEBUG)
#pragma comment ( lib , "sfml-main.lib" )
#pragma comment ( lib , "sfml-system.lib" )
#pragma comment ( lib , "sfml-window.lib" )
#pragma comment ( lib , "sfml-graphics.lib" )
#pragma comment ( lib , "sfml-audio-d.lib" )
#else
#error "Unrecognized configuration!"
#endif

#include "MenuState.h"
#include "MyExceptions.h"
#include <fstream>
#include <sstream>
#include <string>
#include <random>
#include "GameManager.h"
#include "Logger.h"
#include "HighScoreManager.h"

//-----------------------------------------------------------------------------
int main()
{
	srand((unsigned)time(nullptr));
	//load last highscores
	HighScoreManager::get_instance().readHighScore();

	try
	{
		//creating GameManager
		std::shared_ptr<GameManager> game = std::make_shared<GameManager>();
		//pushing main menu first state
		game->pushState(std::make_shared<MenuState>(game));  
		game->gameLoop();
	}
	catch (std::exception &e)
	{
		std::string s = "Exception";
		Logger::getInstance().addLog(s + e.what());
	}

	HighScoreManager::get_instance().updateHighscoreFile();

	return EXIT_SUCCESS;
}