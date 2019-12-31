#pragma once

template<class AbstractNAMES>
class ValuesToNames
{
public:
	ValuesToNames() = default;
	~ValuesToNames() = default;
	
	friend std::ostream& operator<<(std::ostream& os, const ValuesToNames& name)
	{
		AbstractNAMES names;
		os << names.getName(name.m_index);  //getting the wanted name by index
		return os;
	}
	friend std::istream& operator>>(std::istream& is, ValuesToNames& name)
	{
		is >> name.m_index;
		return is;
	}
	operator int() { return m_index; }   //we cast to int so we dont need to implement all operators
	operator int()const { return m_index; } //for the times we need to cast a const object
private:
	int m_index;  //index that user gives us that coordinates to name
};
