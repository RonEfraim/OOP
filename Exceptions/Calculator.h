#pragma once
#include <vector>
#include <memory>
#include <string>
#include <fstream>


class CalculatorItem;

class Calculator
{
public:
	Calculator() = default;
	~Calculator() = default;
	void run();
	std::shared_ptr<CalculatorItem> operator[](int index) const;
private:
	std::vector<std::shared_ptr<CalculatorItem>> m_calculatorItems;
	std::string getUserCommand(std::istream &);
	static void exit();
	static void help(); 
	void calculateArea();
	void calculatePerimeter();
	void drawItem();
	void findAllSameShapes() const;
	void deleteItem();
	void findMin() const;
	void findMax() const;
	void same(int index) const;
	void createShape(std::istream &is);
	void printItemList() const;
	void MaxShapes();
	void resize(std::istream &);
	void read();
	void commandList(std::string, std::istream &);
	char answer();
	char resizeOrDelete();

	int maxShapes = 0;
	int numOfShapes = 1;
	std::ifstream m_file;

	bool fileOpened = false;
};

