#pragma once
#include "AbstractNames.h"
class CurrencyNames : 
	public AbstractNames
{
public:
	CurrencyNames() :AbstractNames({ "NIS","Euro","Dollar"}) {}
	~CurrencyNames() = default;
private:
};