#pragma once
#include "AbstractNames.h"
class ClassNames
	:public AbstractNames
{
public:
	ClassNames() :AbstractNames({"First Class","Business Class","Economy Class"}) {}
	~ClassNames() = default;
private:
};