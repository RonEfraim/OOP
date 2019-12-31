#pragma once
#include "BaseField.h"
#include "FormValidator.h"

#include <vector>
class Form
{
public:
	Form()  = default;
	~Form() = default;

	void fillForm();
	void addField(BaseField*);
	void addValidator(FormValidator*);
	bool validateForm()const ;
	bool validateAllFields()const;
	friend std::ostream& operator<<(std::ostream& os, const Form& form); 
private:
	std::vector<BaseField*> m_fields; 
	std::vector<FormValidator*> m_formValidators; 
	bool m_all_fields_valid = false;
};