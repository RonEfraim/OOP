#include "Form.h"
#include <algorithm>
#include "Utilities.h"
void Form::addField(BaseField* field)
{
	m_fields.push_back(field);
}

void Form::addValidator(FormValidator* validator_form)
{
	m_formValidators.push_back(validator_form);
}
bool Form::validateForm() const
{
	//return true if all fields are valid and if all formValidators are valid
	if (validateAllFields() &&
		std::all_of(m_formValidators.cbegin(), m_formValidators.cend(),
			[](const auto validator)->bool {return validator->validate(); }))
	{
		change_color(BLUE);
		return true;
	}
	else
	{
		change_color(RED);
		return false;
	}
	
}

bool Form::validateAllFields() const
{
	//return true if all fields are valid
	return std::all_of(m_fields.cbegin(), m_fields.cend(),
		[](const auto field)->bool {return field->validate(); });
}

void Form::fillForm()
{
	static bool first = true;


	if (first)
	{
		for (auto& field : m_fields)
		{
			if (field->empty() || !field->validate())
				field->readData();

		}
		first = false;
	}
	else
	{
		//checking if there is still a field invalid
		if (!validateAllFields())
		{
			for (auto& field : m_fields)
			{
				if (field->empty() || !field->validate())
					field->readData();
			}
		}
		//if all the fields themselves are valid, we can check the formValidatora
		else
		{
			//for each for validator
			for (const auto vali : m_formValidators)
			{
				// if it is invalid
				if (!vali->validate())
					//refill the connected fields
					vali->refill_fields();
			}
		}
	}
	

}
//---------------------------------------------------------//
std::ostream& operator<<(std::ostream & os, const Form & form)
{
	change_color(WHITE);
	for (const BaseField* field : form.m_fields)
	{
		field->print(os);
		os << '\n';
	}

	

	//go through form validators only if all fields are valid
	if (form.validateAllFields()) {
		change_color(RED);
		for (const auto vali : form.m_formValidators)
		{
			if (!vali->validate())
				os << vali->getErrMsg() << std::endl;
		}
		change_color(WHITE);
	}


	return os;
}