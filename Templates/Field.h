#pragma once
#include "BaseField.h"
#include "FieldValidator.h"
#include <vector>
#include "Utilities.h"
template<class T>
class Field :public BaseField {
public:
	
	Field(const std::string& msg):BaseField(msg) { ; } 
	~Field() = default;

	bool validate()const override; 
	void readData()override;   
	void addValidator(FieldValidator<T>*);
	void print(std::ostream& os)const override;  
	T getData()const {return m_data;}
private:
	std::vector<FieldValidator<T>*> m_validators;  
	T m_data;
};


template<class T>
inline void Field<T>::addValidator(FieldValidator<T>* validatorinput)
{
	m_validators.push_back(validatorinput);
}


template<class T>
inline bool Field<T>::validate() const
{
	//if all are valid we return true, else false
	return std::all_of(m_validators.cbegin(), m_validators.cend(), 
		[this](const auto vali)->bool {return vali->validate(m_data); });
}

template<class T>
inline void Field<T>::readData()
{
	//asking user to input
	std::cout << m_msg << " "  ;
	//getting user input
	std::cin >> m_data;
	m_filled = true;  //setting field as filled
}


template<class T>
void Field<T>::print(std::ostream& os)const
{
	//printing the question and the given answer
	os << m_msg + " = " << m_data;  

	
	for(const FieldValidator<T>* validator : m_validators)
	{
		//if the field doesnt pass this validator
		if (!validator->validate(m_data)) {
			change_color(RED);
			//we get its error message and add it to os
			os << "\t" << validator->getErrorMsg() << std::endl;
			change_color(WHITE);
		}
	}
	
}