#pragma once

#include "CsDeclares.h"


class Visitor {
public:
	virtual void VisitStr(StrElement& SElem) = 0;
	virtual void VisitInt(IntElement& IElem) = 0;
	virtual void VisitDouble(DoubleElement& DElem) = 0;
};