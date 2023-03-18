#pragma once
#include <memory>
#include <utility>
#include <vector>
#include <QuadTreeNode.h>
#include <Animal.h>

using std::make_shared;
using std::vector;

template<typename T>class QuadTree
{
private:
	void add(shared_ptr<QuadTreeNode<T>> node,T data,QuadAABB aabb,int deep)
	{
		QuadAABB naabb = node->aabb;
		if (deep < max_deep)
		{
			if (node->childList == nullptr)
			{
				//参数没有调好
				int nwidth = naabb.width / 2;
				int nheight = naabb.height / 2;
				node->childList->push_back(make_shared<QuadTreeNode<T>>(new QuadTreeNode<T>(QuadAABB(naabb.left, naabb.left + nwidth, naabb.top, naabb.bottom))));
				node->childList->push_back(make_shared<QuadTreeNode<T>>(new QuadTreeNode<T>(QuadAABB(naabb.left, naabb.left + nwidth, naabb.top, naabb.bottom))));
				node->childList->push_back(make_shared<QuadTreeNode<T>>(new QuadTreeNode<T>(QuadAABB(naabb.left, naabb.left + nwidth, naabb.top, naabb.bottom))));
				node->childList->push_back(make_shared<QuadTreeNode<T>>(new QuadTreeNode<T>(QuadAABB(naabb.left, naabb.left + nwidth, naabb.top, naabb.bottom))));
			}

			for (int i = 0; i < 4; i++)
			{
				shared_ptr<QuadTreeNode<T>> child = node->childList[i];
				if (child->aabb.IsContain(aabb))
				{
					add(child, data, aabb, deep + 1);
					return;
				}
			}
		}
		node->dataList.push_back(data);
		node->aabbList.push_back(aabb);
	}

	void find(shared_ptr<QuadTreeNode<T>> node, QuadAABB aabb, vector<T>& list, vector<QuadAABB>& aabbList)
	{
		if (node->addList.size() > 0)
		{
			list.insert(list.end(), node->dataList.begin(), node->dataList->addList.end());
			aabbList.insert(aabbList.end(), node->aabbList.begin(), node->aabbList.end());
		}
		if (node->childList == nullptr)
		{
			return;
		}

		for (int i = 0; i < 4; i++)
		{
			shared_ptr<QuadTreeNode<T>> child = node->childList[i];
			if (child->aabb.IsContain(aabb))
			{
				find(child, aabb, list, aabbList);
			}
		}
	}

public:
	QuadTree(int max_deep = 31)
	{
		this->max_deep = max_deep;
		int size = 2;
		for (int i = 2; i < max_deep; i++)
			size *= 2;
		this->_root = make_shared<QuadTreeNode<T>>(new QuadAABB(-size / 2, size / 2, size / 2, -size / 2));
	}

	QuadTree(shared_ptr<vector<shared_ptr<Animal>>> animals)
	{
		QuadTree();

		
		for (shared_ptr<Animal>& animal : *animals)
		{
			int radius = AnimalConstants::PROBE_RADIUS;
			int nleft = max(0.0, animal->GetPosition().GetX() - radius);
			int nright = min(UPPER_BOUND, animal->GetPosition().GetX() + radius);
			int ntop = max(0.0, animal->GetPosition().GetY() - radius);
			int nbottom = min(UPPER_BOUND, animal->GetPosition().GetY() + radius);
			
			add(*animal, QuadAABB(nleft, nright, ntop, nbottom));
		}
	}

	void add(T data,QuadAABB aabb)
	{
		add(_root, data, aabb, 1);
	}

	void find(QuadAABB aabb, vector<T>& list,bool accuracy = false)
	{
		vector<QuadAABB> aabbList;
		find(_root, aabb, list, aabbList);
		if (accuracy)
		{
			for (int i = list.size() - 1; i >= 0; i--)
			{
				if (!aabbList[i].isIntersect(aabb))
				{
					list.erase(list.begin() + i);
				}
			}
		}
	}


	vector<T> DoCollisions(QuadAABB aabb, T data)
	{
		vector<T>list;
		find(_root,list, true);
		return list;
	}






private:
	int max_deep;
	shared_ptr<QuadTreeNode<T>> _root;
};