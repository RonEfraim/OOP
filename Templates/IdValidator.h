#pragma once
#include "FieldValidator.h"
class IdValidator 
	: public FieldValidator<uint32_t>
{
public:
	IdValidator() :FieldValidator("Wrong control digit") {};
	~IdValidator() = default;
	bool validate(const uint32_t&)const override;
};

bool IdValidator::validate(const uint32_t& id)const
{
	std::string s = std::to_string(id);
	if (s.size() != 9)
		return false;
	int counter = 0;
	int incnum;
	for (unsigned int i = 0; i < s.size(); i++)
	{
		incnum = ((int)s[i] - 48)*((i % 2) + 1);
		counter += (incnum > 9) ? incnum - 9 : incnum;
	}
	return (counter % 10 == 0);
}