#pragma once
#include "FieldValidator.h"


template <class T>
class RangeValidator
	:public FieldValidator<T>
{
public:
	RangeValidator(int min, int max) :FieldValidator<T>("Out of Range"), m_min(min), m_max(max) {};
	~RangeValidator() = default;

	bool validate(const T&)const override;

private:
	int m_max;
	int m_min;
};

// ======================================== //
template <class T>
inline bool RangeValidator<T>::RangeValidator::validate(const T& value)const
{
	return (value <= m_max) && (value >= m_min);
}