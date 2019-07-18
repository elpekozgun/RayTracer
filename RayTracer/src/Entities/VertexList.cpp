#include "VertexList.h"



eEntityType VertexList::GetType()
{
	return eEntityType::vertexlist;
}

VertexList::VertexList()
{
	vertexList = std::map<int,Vector3>();
}

VertexList::~VertexList()
{
	std::cout << "Vertex list deleted" << std::endl;
}
