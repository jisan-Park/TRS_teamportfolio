#pragma once
#include "line.h"
class topLine :
	public line
{
public:
	virtual void collison(characterInfo &info);
};

