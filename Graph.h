#pragma once

#include <queue>
#include <stdio.h>

enum VertexColor { VCWhite, VCGray, VCBlack };

class Vertex
{
public:
	Vertex(int _id) :
		m_Id(_id)
	{
		m_Color = VCWhite;
	}

	int         getId() { return m_Id; }

	VertexColor getColor() { return m_Color; }
	void        setColor(VertexColor _c) { m_Color = _c; }

private:
	int         m_Id;
	VertexColor m_Color;
};


class Graph
{
public:
	Graph(){ m_nVertices = 0; }

	void addEdge(Vertex* _v1, Vertex* _v2);

	void BFS(Vertex* _s, bool _needClear = true);

	int findRowNumber(int _id);

	Vertex* getVertexById(int _id);

private:
	static const int MAX_VERTICES = 100;
	static const int MAX_ADJACENT_VERTICES = 100;
	Vertex* m_AdjacencyList[MAX_VERTICES][MAX_ADJACENT_VERTICES];
	int m_Vertices[MAX_VERTICES];
	int m_nVertices;

	std::queue<Vertex*> m_Queue;
};
