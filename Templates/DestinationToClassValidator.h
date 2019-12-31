#pragma once
#include "FormValidator.h"
template <class Destination, class Class>
class DestinationToClassValidator
	: public FormValidator
{
public:
	DestinationToClassValidator(Destination* first, Class* second)
		:FormValidator("Destination and class don't match"), m_first(first), m_second(second) {}
	~DestinationToClassValidator() = default;


	void refill_fields()override;
	bool validate()const override;
private:
	Destination* m_first;
	Class* m_second;
};
template<class Destination, class Class>
inline void DestinationToClassValidator<Destination, Class>::refill_fields()
{
	m_first->readData();
	m_second->readData();
}
// ======================================== //
template<class Destination, class Class>
inline bool DestinationToClassValidator<Destination, Class>::validate()const
{
	//bceuase ValuesToNames has a cas to int operator, we can
	//use it as an int
	bool result = true;
	int dest = m_first->getData();
	int Airclass = m_second->getData();

	switch (dest)
	{
	case 1:  //ROME
	case 2:  //PRAGUE
		result = (Airclass == 1 || Airclass == 2); //first or business class allowed
		break;
	case 4: //India
	case 5: //Thailand
		result = (Airclass == 2 || Airclass == 3); //first or economy class
		break;

	default:
		break;
	}
	return result;
}
