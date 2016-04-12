
#include "AllUnits.h"

AllUnits* AllUnits::m_myPtr = NULL;

AllUnits* AllUnits::getPtr()
{
	if (m_myPtr == NULL) {
		m_myPtr = new AllUnits;
	}
	return m_myPtr;
}

void AllUnits::addUnit(Unit* _u)
{
	for (m_It = m_Units.begin(); m_It != m_Units.end(); ++m_It)
	{
		if ((*m_It)->getId() == _u->getId()) return;
	}
	m_Units.push_back(_u);
}

Unit* AllUnits::getUnitById(int _id)
{
	for (m_It = m_Units.begin(); m_It != m_Units.end(); ++m_It)
	{
		if ((*m_It)->getId() == _id) return *m_It;
	}
	return NULL;
}

void AllUnits::clk()
{
	for (m_It = m_Units.begin(); m_It != m_Units.end(); ++m_It)
	{
		(*m_It)->CLK();
	}
}



