
#include <list>
#include <queue>
#include <stdio.h>

enum ComponentType  { CTNone, CTSource, CTKey, CTWire };
enum VertexColor { VCWhite, VCGray, VCBlack };

class Vertex
{
public:
	Vertex(int _id):
		m_Id(_id)
	{
		m_Color = VCWhite;
	}

	int         getId()   { return m_Id; }

	VertexColor getColor() { return m_Color; }
	void        setColor(VertexColor _c) { m_Color = _c; }

private:
	int         m_Id;
	VertexColor m_Color;

};

class Component: public Vertex
{
public:
	Component(ComponentType _type, int _id): Vertex(_id),
		m_Type(_type)
	{
		m_isOpened = false;
	}

	ComponentType getType() { return m_Type; }

	void close() { m_isOpened = false; }
	void open()  { m_isOpened = true; }

	bool isOpened() { return m_isOpened; }

private:
	ComponentType  m_Type;
	bool           m_isOpened;
};

class Graph
{
public:
	Graph()
	{
		m_nVertices = 0;
	}

	void addEdge(Vertex* _v1, Vertex* _v2)
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

	void BFS(Vertex* _s, bool _needClear = true)
	{
		if (_needClear) {
			for (int i = 0; i < m_nVertices; i++)
			{
				for (int j = 0; j < m_Vertices[i]; j++)
				{
					m_AdjacencyList[i][j]->setColor(VCWhite);
				}
			}
		}

		_s->setColor(VCGray);

		m_Queue.push(_s);
		Vertex* u = NULL;
		while (m_Queue.empty() == false) 
		{
			u = m_Queue.front();
			m_Queue.pop();
			int row = findRowNumber(u->getId());
			printf("#--------\nScanning vertex: %d\n", u->getId());
			for (int i = 1; i < m_Vertices[row]; i++)
			{
				Vertex* v = m_AdjacencyList[row][i];
				if (v->getColor() == VCWhite) {
					printf("Visiting vertex: %d\n", v->getId());
					v->setColor(VCGray);
					m_Queue.push(v);
				}
			}
			u->setColor(VCBlack);
		}
	}

	int findRowNumber(int _id)
	{
		for (int i = 0; i < m_nVertices; i++)
		{
			if (m_AdjacencyList[i][0]->getId() == _id) {
				return i;
			}
		}
		return -1;
	}

	Vertex* getVertexById(int _id)
	{
		for (int i = 0; i < m_nVertices; i++)
		{
			if (m_AdjacencyList[i][0]->getId() == _id) {
				return m_AdjacencyList[i][0];
			}
		}
		return NULL;
	}

private:
	static const int MAX_VERTICES = 100;
	static const int MAX_ADJACENT_VERTICES = 100;
	Vertex* m_AdjacencyList[MAX_VERTICES][MAX_ADJACENT_VERTICES];
	int m_Vertices[MAX_VERTICES];
	int m_nVertices;

	std::queue<Vertex*> m_Queue;
};

class Circuit
{
public:
	Circuit()
	{
		m_nSources = 0;
	}

	static Circuit* getPtr()
	{
		if (m_myPtr == NULL) {
			m_myPtr = new Circuit;
		}
		return m_myPtr;
	}

	void addJunction(ComponentType _type1, int _id1, ComponentType _type2, int _id2)
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

	void clk()
	{
		bool isFirst = true;
		for (int i = 0; i < m_nSources; i++)
		{
			m_Graph.BFS(m_Sources[i], isFirst);
			isFirst = false;
		}
	}

private:
	Graph m_Graph;
	static Circuit* m_myPtr;
	static const int MAX_SOURCES = 100;
	Component* m_Sources[MAX_SOURCES];
	int m_nSources;
};

Circuit* Circuit::m_myPtr = NULL;

class Junction
{
public:
	Junction(ComponentType _type1, int _id1, ComponentType _type2, int _id2)
	{
		Circuit::getPtr()->addJunction(_type1, _id1, _type2, _id2); 
	}

private:

};



int main()
{
	new Junction(CTSource, 1, CTWire, 2);
	new Junction(CTWire, 1, CTWire, 3);
	new Junction(CTWire, 1, CTWire, 4);
	new Junction(CTWire, 2, CTSource, 6);
	new Junction(CTWire, 2, CTWire, 5);
	new Junction(CTWire, 2, CTWire, 3);

	Circuit::getPtr()->clk();
}
