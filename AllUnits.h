#pragma once

#include "Unit.h"
#include <list>

class AllUnits
{
public:
	static AllUnits* getPtr();


	void addUnit(Unit* _u);


	Unit* getUnitById(int _id);


private:
	static AllUnits* m_myPtr;
	std::list<Unit*> m_Units;
	std::list<Unit*>::iterator m_It;

};
