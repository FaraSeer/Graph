#include "Graph.h"

void Graph::addEdge(Vertex* _v1, Vertex* _v2)
{
	if (m_nVertices == 0) {
		m_AdjacencyList[0][0] = _v1;
		m_AdjacencyList[0][1] = _v2;
		m_Vertices[0] = 2;
		m_AdjacencyList[1][0] = _v2;
		m_AdjacencyList[1][1] = _v1;
		m_Vertices[1] = 2;
		m_nVertices = 2;
		return;
	}
	bool isNew1 = true;
	bool isNew2 = true;
	for (int i = 0; i < m_nVertices; i++)
	{
		if (m_AdjacencyList[i][0]->getId() == _v1->getId()) {
			isNew1 = false;
			m_AdjacencyList[i][m_Vertices[i]] = _v2;
			m_Vertices[i]++;
			continue;
		}
		if (m_AdjacencyList[i][0]->getId() == _v2->getId()) {
			isNew2 = false;
			m_AdjacencyList[i][m_Vertices[i]] = _v1;
			m_Vertices[i]++;
			continue;
		}
	}
	if (isNew1 == true) {
		m_AdjacencyList[m_nVertices][0] = _v1;
		m_AdjacencyList[m_nVertices][1] = _v2;
		m_Vertices[m_nVertices] = 2;
		m_nVertices++;
	}
	if (isNew2 == true) {
		m_AdjacencyList[m_nVertices][0] = _v2;
		m_AdjacencyList[m_nVertices][1] = _v1;
		m_Vertices[m_nVertices] = 2;
		m_nVertices++;
	}
}

void Graph::clean()
{
	for (int i = 0; i < m_nVertices; i++)
	{
		for (int j = 0; j < m_Vertices[i]; j++)
		{
			m_AdjacencyList[i][j]->setColor(VCWhite);
		}
	}
}

void Graph::BFS(Vertex* _s)
{
	_s->setColor(VCGray);

	m_Queue.push(_s);
	Vertex* u = NULL;
	while (m_Queue.empty() == false)
	{
		u = m_Queue.front();
		m_Queue.pop();
		int row = findRowNumber(u->getId());
		printf("\tScanning vertex: %d\n", u->getId());
		for (int i = 1; i < m_Vertices[row]; i++)
		{
			Vertex* v = m_AdjacencyList[row][i];
			if (v->getColor() == VCWhite) {
				printf("\t\tVisiting vertex: %d\n", v->getId());
				v->setColor(VCGray);
				m_Queue.push(v);
			}
		}
		u->setColor(VCBlack);
	}
}

void Graph::DFS(Vertex* _s)
{
	_s->setColor(VCGray);
	int row = findRowNumber(_s->getId());
	printf("\tScanning vertex: %d\n", _s->getId());
	for (int i = 1; i < m_Vertices[row]; i++)
	{
		Vertex* v = m_AdjacencyList[row][i];
		if (v->getColor() == VCWhite) {
			printf("\t\tVisiting vertex: %d\n", v->getId());
			DFS(v);
		}
		_s->setColor(VCBlack);
	}
}

int Graph::findRowNumber(int _id)
{
	for (int i = 0; i < m_nVertices; i++)
	{
		if (m_AdjacencyList[i][0]->getId() == _id) {
			return i;
		}
	}
	return -1;
}

Vertex* Graph::getVertexById(int _id)
{
	for (int i = 0; i < m_nVertices; i++)
	{
		if (m_AdjacencyList[i][0]->getId() == _id) {
			return m_AdjacencyList[i][0];
		}
	}
	return NULL;
}
