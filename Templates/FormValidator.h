#pragma once
#include <string>
class FormValidator 
{
public:
	FormValidator(const std::string msg) :m_error_msg(msg) {};
	virtual ~FormValidator() = default;
	virtual bool validate()const = 0; 
	virtual void refill_fields() = 0;
	std::string getErrMsg()const { return m_error_msg; }
private:
	std::string m_error_msg;
};