#pragma once
#include <string>
#include <iostream>
//an abstract base class for all template fields
class BaseField {
public:
	BaseField(const std::string& msg) :m_valid_field(false), m_filled(false) , m_msg(msg) {}
	virtual bool validate()const = 0;
	virtual void readData() = 0;
	virtual void print(std::ostream& os)const = 0;
	bool empty()const { return !m_filled; } //return true if not filled
	bool isValid()const { return m_valid_field; }
	void setValidity(bool b) { m_valid_field = b; }

	//virtual destructor because this class inherits
	virtual ~BaseField() = default;
protected:
	//TODO, still unused
	bool m_valid_field;        
	const std::string m_msg; //message unchanged, we keep const
	bool m_filled;  //tells me if this field is empty
};