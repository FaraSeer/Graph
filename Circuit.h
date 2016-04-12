#pragma once

#include "Graph.h"
#include "AllUnits.h"

enum ComponentType { CTNone, CTSource, CTKey, CTWire };

class Component : public Vertex
{
public:
	Component(ComponentType _type, int _id) : Vertex(_id),
		m_Type(_type)
	{
		m_Unit = AllUnits::getPtr()->getUnitById(_id);
	}

	ComponentType getType() { return m_Type; }

	void CLK()
	{
		if (m_Unit->OFF()) {
			setColor(VCBlack);
		}
		else {
			setColor(VCWhite);
		}
	}

	Unit* getUnit() { return m_Unit; }

private:
	Unit*          m_Unit;
	ComponentType  m_Type;
};

class Circuit : public Unit
{
public:
	Circuit() : Unit(-1) 
	{ 
		m_nSources = 0; 
		m_nComponents = 0; 
	}

	static Circuit* getPtr();

	void addJunction(ComponentType _type1, int _id1, ComponentType _type2, int _id2);

	void CLK();

private:
	Graph m_Graph;
	static Circuit* m_myPtr;
	static const int MAX_SOURCES = 100;
	Component* m_Sources[MAX_SOURCES];
	int m_nSources;
	Component* m_Components[MAX_SOURCES];
	int m_nComponents;
};

class Junction
{
public:
	Junction(ComponentType _type1, int _id1, ComponentType _type2, int _id2)
	{
		Circuit::getPtr()->addJunction(_type1, _id1, _type2, _id2);
	}
};