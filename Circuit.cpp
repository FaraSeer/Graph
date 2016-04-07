#include "Circuit.h"

Circuit* Circuit::m_myPtr = NULL;

Circuit* Circuit::getPtr()
{
	if (m_myPtr == NULL) {
		m_myPtr = new Circuit;
	}
	return m_myPtr;
}

void Circuit::addJunction(ComponentType _type1, int _id1, ComponentType _type2, int _id2)
{
	Component* v1 = (Component*)m_Graph.getVertexById(_id1);
	if (v1 == NULL) {
		v1 = new Component(_type1, _id1);
		if (_type1 == CTSource) {
			m_Sources[m_nSources] = v1;
			m_nSources++;
		}
	}
	Component* v2 = (Component*)m_Graph.getVertexById(_id2);
	if (v2 == NULL) {
		v2 = new Component(_type2, _id2);
		if (_type2 == CTSource) {
			m_Sources[m_nSources] = v2;
			m_nSources++;
		}
	}
	m_Graph.addEdge(v1, v2);
}

void Circuit::clk()
{
	bool isFirst = true;
	for (int i = 0; i < m_nSources; i++)
	{
		m_Graph.BFS(m_Sources[i], isFirst);
		isFirst = false;
	}
}
