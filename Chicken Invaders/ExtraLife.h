#pragma once
#include "PowerUp.h"

class ExtraLife : public PowerUp
{
public:
	ExtraLife(const powerUp_pkg& x);

private:
	static bool m_registerit;
};