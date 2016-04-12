
#include "AllUnits.h"
#include "Unit.h"

Unit::Unit(int _id):
	m_Id(_id)
{
	AllUnits::getPtr()->addUnit(this);
	m_Status = ST_OFF;
}


