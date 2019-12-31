#pragma once
#include "AbstractNames.h"
class DestinationNames :
	public AbstractNames
{
public:
	DestinationNames() :AbstractNames({ "Rome","Prague","New York","India","Thailand" }) {};
	~DestinationNames() = default;
private:
};