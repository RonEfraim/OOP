#include "CalculatorItem.h"
#include "Calculator.h"
#include "Add.h"
#include "Subtraction.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Triangle.h"
#include "Multiply.h"
#include "Utils.h"
#include "Exceptions.h"
#include <sstream>
#include <iostream>
#include <sstream>

const int MINSHAPE = 0;
const int MAXSHAPE = 100;

using std::cout;
using std::cin;
using std::endl;
using std::string;

string Calculator::getUserCommand(std::istream & stream)
{
	string act;
	if(!fileOpened)
		cout << endl << "Please enter a command (\"help\" for command list):" << endl;
	stream >> act;
	return act;
}

void Calculator::exit()
{
	cout << "Goodbye.";
	std::exit(EXIT_SUCCESS);
}

void Calculator::calculateArea()
{
	try{
	const int index = Utils::readInt(std::cin);
	if (m_calculatorItems.empty() || (m_calculatorItems.size() < index))
		throw(OutOfRange());
	
	cout << "Area ";
	m_calculatorItems[index]->printDetails();
	cout << " = " << m_calculatorItems[index]->area() << endl;
	}
	catch (exception &c)
	{
		cout << endl << c.what() << endl;
		if (fileOpened) {
			if (answer() == 'Y')
				return;
			else {
				m_file.close();
				fileOpened = false;
				run();
			}
		}
		help();
	}
}
void Calculator::calculatePerimeter()
{
	try{
	const int index = Utils::readInt(std::cin);
	if (m_calculatorItems.empty() || (m_calculatorItems.size() < index))
		throw(OutOfRange());
	cout << "Perimeter ";
	m_calculatorItems[index]->printDetails();
	cout << " = " << m_calculatorItems[index]->perimeter() << endl;
	}
	catch (exception &c)
	{
		cout << endl << c.what() << endl;
		if (fileOpened) {
			if (answer() == 'Y')
				return;
			else {
				m_file.close();
				fileOpened = false;
				run();
			}
		}
		help();
	}
}
void Calculator::drawItem()
{
	const int index = Utils::readInt(std::cin);
	m_calculatorItems[index]->draw();
}

void Calculator::findAllSameShapes() const
{
	const int index = Utils::readInt(std::cin);
	same(index);
}

void Calculator::deleteItem()
{
	try{
	const int index = Utils::readInt(std::cin);
	if (m_calculatorItems.empty() || (m_calculatorItems.size() < index))
		throw(OutOfRange());
	m_calculatorItems.erase(m_calculatorItems.begin() + index);
	numOfShapes--;
	}
	catch (exception &c)
	{
		cout << endl << c.what() << endl;
		if (fileOpened) {
			if (answer() == 'Y')
				return;
			else {
				m_file.close();
				fileOpened = false;
				run();
			}
		}
		help();
	}
}

void Calculator::findMin() const
{
	const int amount = Utils::readInt(std::cin);
	//in first time (for Comparison)
	int index = Utils::readInt(std::cin);
	double min = m_calculatorItems[index]->area();

	for (int i = 0; i < amount - 1; i++)
	{
		index = Utils::readInt(std::cin);
		min = m_calculatorItems[index]->area() < min ? m_calculatorItems[index]->area() : min;
	}
	cout << "The minimum area is:" << min << endl;
}

void Calculator::findMax() const
{
	const int amount = Utils::readInt(std::cin);
	//Calculates the largest area of all selected shapes, return the index of the maxim
	double max = 0;
	for (int i = 0; i < amount; i++)
	{
		const int index = Utils::readInt(std::cin);
		max = m_calculatorItems[index]->area() > max ? m_calculatorItems[index]->area() : max;
	}
	cout << "The maximum area is:" << max << endl;
}

//the main function in this class, performs actions at user request
void Calculator::run()
{
	MaxShapes();
	while (true)
	{
		try {
			printItemList();
			//the user request is in the form of string
			std::istream* stream = (fileOpened) ? &m_file : &std::cin;
			auto command = getUserCommand(*stream);
			commandList(command, *stream);
		}
		catch(exception &c)
		{
			cout << endl << c.what() << endl;
			if (fileOpened) {
				if (answer() == 'Y')
					return;
				else {
					m_file.close();
					fileOpened = false;
					run();
				}
			}
			help();
		}
	}
}

std::shared_ptr<CalculatorItem> Calculator::operator[](int index) const
{
	return m_calculatorItems[index];
}

//--------------------------------------------------------
//Prints a help screen with a list of possible commands and a brief explanation of it
void Calculator::help()
{
	cout << "Following is the list of the calculator's available commands" << endl
		<< "cre(ate) #shape <R - rectangle | T-triangle | C- circle>" << endl
		<< "area num - Computes the area of shape #num" << endl
		<< "per(imeter) num - Computes the perimeter of shape #num" << endl
		<< "draw num - Draw the shape" << endl
		<< "#num mul(tiply) num x - Creates an item that is the multiplication of shape #num x times" << endl
		<< "add num1 num2 - Creates an item that is the sum of item #num1 and function #num2" << endl
		<< "sub num1 num2 - Creates an item that is the subtraction of item #num1 and function #num2" << endl
		<< "min n #num1-#numN - Returns the smallest area in the chosen shapes. n - the requested shapes: #num1..." << endl
		<< "max n #num1-#numN - Returns the biggest area in the chosen shapes. n - the requested shapes: #num1..." << endl
		<< "same num - Returns shapes with which have the same area and perimeter to the shape #num" << endl
		<< "del(ete) num - Deletes item #num from function list" << endl
		<< "help - Prints this help screen" << endl
		<< "exit - Exits the program." << endl;
}
//--------------------------------------------------------
//Prints all indices of the shapes that are equal in their area and scope to the selected shape
void Calculator::same(int index) const
{
	const double area = m_calculatorItems[index]->area();
	const double perimeter = m_calculatorItems[index]->perimeter();
	
	for (auto i = 0; i < m_calculatorItems.size(); ++i)
	{
		if (m_calculatorItems[i]->area() == area 
			&& m_calculatorItems[i]->perimeter() == perimeter
			&& i != index)
		{
			cout << i << ": ";
			m_calculatorItems[i]->printDetails();
			cout << endl;
		}
	}
	cout << endl;
}


//-----------------------------------------------------------
//create new shape rectangle/circle/triangle and insert to the list of the shapes (to the vector)
void Calculator::createShape(std::istream &is)
{
	char shape;
	is >> shape;
	shape = toupper(shape);
	try {
		if (numOfShapes > maxShapes)
			throw(ToManyShapes());

		if (shape == 'R')
		{
			m_calculatorItems.push_back(std::make_shared<Rectangle>(is));
		}
		else if (shape == 'C')
		{
			m_calculatorItems.push_back(std::make_shared<Circle>(is));
		}
		else if (shape == 'T')
		{
			m_calculatorItems.push_back(std::make_shared<Triangle>(is));
		}
		else
			throw(InvalidChar());

		numOfShapes++;
	}
	catch (exception &c)
	{
		cout << endl << c.what() << endl;
		if (fileOpened) {
			if (answer() == 'Y')
				return;
			else {
				m_file.close();
				fileOpened = false;
				run();
			}
		}
		help();
	}
}
//-----------------------------------------------------------
//print the list of the shapes that in the vector
void Calculator::printItemList() const
{
	int i = 0;
	cout << "\nThis is the shapes list:" << endl;
	for (auto& item : m_calculatorItems)
	{
		cout << i++ << ": ";
		item->printDetails();
		cout << endl;
	}

	cout << "The maximum number of shapes you can insert is: " << maxShapes << endl;
}

void Calculator::MaxShapes() 
{
	cout << "Enter the maximum number of shapes you want to create" << endl;
	try {
		const int index = Utils::readInt(std::cin);

		if (index > MAXSHAPE || index < MINSHAPE)						/*!isdigit(index)*/
			throw(OutOfRange());

		maxShapes = index;
	}
	catch(exception &c)
	{
		cout << endl << c.what() << endl;
		help();
	}
}

void Calculator::resize(std::istream &is)
{
	cout << "Enter a new maximum number of shapes you want to create" << endl;
	try {
		const int index = Utils::readInt(is);

		if (index < maxShapes)
			throw(SmallNum());
	}
	catch (exception &c)
	{
		cout << endl << c.what() << endl;
		if (resizeOrDelete() == 'R')
			resize(std::cin);
		else
			deleteItem();
	}
}

void Calculator::read()
{
	cout << "Enter the file address" << endl;
	try {
		string address;
		cin >> address;				//read the file address
		m_file.open(address);
		if (!m_file.is_open())		//if file does not open
			throw Failed();
		
		fileOpened = true;
	}

	catch (exception &c)
	{
		cout << endl << c.what() << endl;
		help();
	}
}

void Calculator::commandList(std::string command, std::istream &is)
{
	//string command;
	
	//exit from the calculator
	if (command == "exit")
	{
		exit();
		return;
	}
	//request for the list of option to action(-to requests)
	if (command == "help")
	{
		help();
		return;
	}
	//create a basic shape and put it in the calculator
	if (command == "cre")
	{
		createShape(is);
		return;
	}
	//calculate the area of a shape from the calculator, the shape is requested by number(-index)
	if (command == "area")
	{
		calculateArea();
		return;
	}
	//calculate the perimeter of a shape from the calculator, the shape is requested by number(-index)
	if (command == "per")
	{
		calculatePerimeter();
		return;
	}
	//create a new shape that consist of multiple of one shape, and put it in the calculator
	if (command == "mul")
	{
		m_calculatorItems.push_back(std::make_shared<Multiply>(is, *this));
		return;
	}
	//create a new shape that consist of add of one shape and another shape, and put it in the calculator
	if (command == "add")
	{
		m_calculatorItems.push_back(std::make_shared<Add>(is, *this));
		return;
	}
	//create a new shape that consist of subtraction of one shape from another shape, and put it in the calculator
	if (command == "sub")
	{
		m_calculatorItems.push_back(std::make_shared<Subtraction>(is, *this));
		return;
	}
	//Draws the shape (regardless of its actual size)
	if (command == "draw")
	{
		drawItem();
		return;
	}
	//Prints all indexes of the shapes that are equal in their area and perimeter to the selected shape
	if (command == "same")
	{
		findAllSameShapes();
		return;
	}
	//Deletes the required shape from the calculator and arranges the indexes of the other shapes
	if (command == "del")
	{
		deleteItem();
		return;
	}
	//Finds and prints the largest of the shapes in the calculator, according to the user selection
	if (command == "min")
	{
		findMin();
		return;
	}
	//Finds and prints the smallest of the shapes in the calculator, according to the user selection
	if (command == "max")
	{
		findMax();
		return;
	}
	if (command == "resize")
	{
		resize(is);
		return;
	}
	if (command == "read")
	{
		read();
		return;
	}
	else
		throw(WrongCommand());
}

char Calculator::answer()
{
	char ans;
	cout << "If you want to continue read from file press 'Y'\n"
		"If not press = 'N'\n";
	cin >> ans;
	if (ans == 'Y')
		return 'Y';
	return 'N';
}

char Calculator::resizeOrDelete()
{
	char ans;
	cout << "If you want to try another size press 'R'\n"
		"If you want to delete the last shapes press = 'D'\n";
	cin >> ans;
	if (ans == 'R')
		return 'R';
	return 'D';

}

