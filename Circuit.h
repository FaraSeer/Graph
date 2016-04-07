#pragma once

#include "Graph.h"

enum ComponentType { CTNone, CTSource, CTKey, CTWire };

class Component : public Vertex
{
public:
	Component(ComponentType _type, int _id) : Vertex(_id),
		m_Type(_type)
	{
		m_isOpened = false;
	}

	ComponentType getType() { return m_Type; }

	void close() { m_isOpened = false; }
	void open() { m_isOpened = true; }

	bool isOpened() { return m_isOpened; }

private:
	ComponentType  m_Type;
	bool           m_isOpened;
};

class Circuit
{
public:
	Circuit(){ m_nSources = 0; }

	static Circuit* getPtr();

	void addJunction(ComponentType _type1, int _id1, ComponentType _type2, int _id2);

	void clk();

private:
	Graph m_Graph;
	static Circuit* m_myPtr;
	static const int MAX_SOURCES = 100;
	Component* m_Sources[MAX_SOURCES];
	int m_nSources;
};


class Junction
{
public:
	Junction(ComponentType _type1, int _id1, ComponentType _type2, int _id2)
	{
		Circuit::getPtr()->addJunction(_type1, _id1, _type2, _id2);
	}
};