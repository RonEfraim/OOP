#ifdef _DEBUG
#pragma comment ( lib , "sfml-main-d.lib" )
#pragma comment ( lib , "sfml-system-d.lib" )
#pragma comment ( lib , "sfml-window-d.lib" )
#pragma comment ( lib , "sfml-graphics-d.lib" )
#elif defined (NDEBUG)
#pragma comment ( lib , "sfml-main.lib" )
#pragma comment ( lib , "sfml-system.lib" )
#pragma comment ( lib , "sfml-window.lib" )
#pragma comment ( lib , "sfml-graphics.lib" )
#else
#error "Unrecognized configuration!"
#endif

#include "Map.h"
#include <iostream>
#include <experimental/filesystem>

int main()
{
	int row = 0;
	int col = 0;
	if (std::experimental::filesystem::exists("board.bomb.txt"))
	{
		std::fstream file;
		Map map(file);
		map.run();
	}
	else
	{
		Map map;
		map.run();
	}

	return 0;
}