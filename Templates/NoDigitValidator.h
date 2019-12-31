#pragma once
#include <algorithm>
#include "FieldValidator.h"
class NoDigitValidator
	:public FieldValidator<std::string>
{
public:
	NoDigitValidator() :FieldValidator("Can't contain digits") {}
	~NoDigitValidator() = default;

	bool validate(const std::string&)const override;
private:

};
//===============================================//
bool NoDigitValidator::validate(const std::string& s)const
{
	//if any of the chars are a digit, we return false
	if (std::any_of(s.begin(), s.end(), ::isdigit))
		return false;
	return true;
}