#pragma once
#include "QuadAABB.h"
#include <list>
#include <memory>
#include <utility>
#include <vector>

using std::shared_ptr;
using std::vector;

template<typename T>
class QuadTreeNode
{
public:
	//иообвСср
	static const int LT = 0;
	static const int RT = 1;
	static const int LB = 2;
	static const int RB = 3;

	std::list<T> dataList;

	std::list<QuadAABB> aabbList;

	QuadAABB aabb;

	QuadTreeNode(QuadAABB aabb) : childList(nullptr) { this->aabb = aabb; }

	QuadTreeNode<T>** childList;

	~QuadTreeNode()
	{
		delete childList;
	}
};