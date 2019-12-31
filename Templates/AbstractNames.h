#pragma once
#include <vector>
#include <string>
//abstract base class for names
class AbstractNames
{
public:
	//get a vector of strings as const& for efficiency
	AbstractNames(const std::vector<std::string>& v) :m_names(v) {}
	std::string getName(int num);
	virtual ~AbstractNames() = 0 {} //we make this pure so the class can be abstract
private:
	const std::vector<std::string> m_names;  //this is a static non changed vector, so const
};

//get index, return string
std::string AbstractNames::getName(int num)
{
	//if the user enters 0 or less or greater then vec size
	//we return the number he gave us
	if ((num <= 0) || (num > (int)m_names.size()))
		return std::to_string(num); 
	return m_names[num-1];  //if the number is good we return the correct name
}