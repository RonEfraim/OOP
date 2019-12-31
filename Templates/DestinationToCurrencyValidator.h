#pragma once
#include "FormValidator.h"
template <class Destination, class Currency>
class DestinationToCurrencyValidator
	: public FormValidator
{
public:
	DestinationToCurrencyValidator(Destination* first, Currency* second)
		:FormValidator("Destination and currency don't match"), m_first(first), m_second(second) { ; }
	~DestinationToCurrencyValidator() = default;

	void refill_fields()override;
	bool validate()const override;
private:
	Destination* m_first;
	Currency* m_second;
};
template<class Destination, class Currency>
inline void DestinationToCurrencyValidator<Destination, Currency>::refill_fields()
{
	m_first->readData();
	m_second->readData();
}
template<class Destination,class Currency>
bool DestinationToCurrencyValidator<Destination, Currency>::validate()const
{
	//bceuase ValuesToNames has a cas to int operator, we can
	//use it as an int
	bool result = true;
	int dest = m_first->getData();
	int currency = m_second->getData();

	switch (dest)
	{
	case 1:  //rome
	case 2:  //prague
		result = (currency == 1 || currency == 2); //Nis or Euro == true
		break;

	case 3:
		result = (currency == 1 || currency == 3); //Nis or Dollar
		break;
	default:
		break;
	}
	return result;

}
