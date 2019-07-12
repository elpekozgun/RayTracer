#ifndef VERTEXLIST_H
#define VERTEXLIST_H

#include <vector>
#include <map>
#include "IEntity.h"
#include "../Core/Vector3.h"

class VertexList : public IEntity
{
	public:
		std::map<int,Vector3> vertexList;

		virtual eEntityType GetType() override;
};



#endif 

