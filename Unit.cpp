
#include "Unit.h"
#include "AllUnits.h"

Unit::Unit(int _id)
{
	AllUnits::getPtr()->addUnit(this);
}

int Unit::getId() { return m_Id; }

