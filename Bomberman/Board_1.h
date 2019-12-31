#pragma once

#include <vector>
#include <fstream>

class Board
{
public:
	Board();
	~Board();
	Board(char * fileName);
	void fileToMatrix();
	bool notEmptyLine(char *numString);
	void readMatrix();
	char getChar(unsigned int i, unsigned int j) const;
	int boardInfo(int type) const;
	float getTime() const;

private:
	std::ifstream m_file;
	std::vector<std::vector<char>> m_boardMatrix;
	int m_boardInfo[4];	
	float m_time;
};

