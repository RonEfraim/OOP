#pragma once
#ifndef UTILITIES_H
#define UTILITIES_H


#include <Windows.h>


#define RED  (FOREGROUND_RED | FOREGROUND_INTENSITY)
#define	WHITE  (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE)
#define BLUE (FOREGROUND_INTENSITY | FOREGROUND_BLUE)

//this needs to be inline becuase, each field T defines this function,
//this is telling the compiler that the many definitions of "change_color" is the same
inline void change_color(int color)
{
	static HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);

}
#endif UTILITIES_H