#pragma once
#include <string>
template<typename T>
class FieldValidator
{
public:
	FieldValidator(const std::string& s) :m_error_msg(s) {}
	virtual bool validate(const T&)const = 0;
	std::string getErrorMsg()const { return m_error_msg; }
	~FieldValidator() = default;
private:
	const std::string m_error_msg;
};