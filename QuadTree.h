#pragma once
#include <memory>
#include <utility>
#include <vector>
#include "QuadTreeNode.h"
#include <algorithm>
#include<cmath>
#include "QuadAABB.h"
#include <Animal.h>
#include <Vector2D.h>

using std::vector;


template<typename T>class QuadTree
{
public:


	QuadTree(int max_deep = 31)
	{
		this->max_deep = max_deep;

		QuadAABB aabb(EnvironmentConstants::LOWER_BOUND, EnvironmentConstants::UPPER_BOUND, EnvironmentConstants::LOWER_BOUND, EnvironmentConstants::UPPER_BOUND);

		this->_root = new QuadTreeNode<T>(aabb);
	}

	QuadTree(shared_ptr<vector<shared_ptr<Animal>>> animals, int max_deep = 31)
	{
		this->max_deep = max_deep;

		QuadAABB aabb(EnvironmentConstants::LOWER_BOUND, EnvironmentConstants::UPPER_BOUND, EnvironmentConstants::LOWER_BOUND, EnvironmentConstants::UPPER_BOUND);

		this->_root = new QuadTreeNode<T>(aabb);

		//身体半径
		for (auto& animal : *animals)
			add(animal,QuadAABB(animal->GetPosition().GetX() - animal->GetCollisionRadius(), animal->GetPosition().GetX() + animal->GetCollisionRadius(),
							    animal->GetPosition().GetY() - animal->GetCollisionRadius(), animal->GetPosition().GetY() + animal->GetCollisionRadius()));

	}
	

	void add(T data,QuadAABB aabb)
	{
		add(this->_root, data, aabb, 1);
	}

	void find(QuadAABB aabb, vector<T>& list,bool accuracy = false)
	{
		vector<QuadAABB> aabbList;
		find(this->_root, aabb, list, aabbList);
		if (accuracy)
		{
			for (int i = list.size() - 1; i >= 0; i--)
			{
				if (!aabbList[i].isIntersect(aabb))
				{
					list.erase(list.begin() + i);
				}
				if (aabb.IsEqual(aabbList[i]))
				{
					list.erase(list.begin() + i);
				}
			}
		}
	}
	 
	//输入的是Probe radius 
	shared_ptr<Animal> ProbedNearestAnimal (shared_ptr<Animal> data)
	{
		vector<shared_ptr<Animal>>list;
		int radius = AnimalConstants::PROBE_RADIUS;
		find((QuadAABB(data->GetPosition().GetX() - radius, data->GetPosition().GetX() + radius,
			data->GetPosition().GetY() - radius, data->GetPosition().GetY() + radius)), list, false);

		shared_ptr<Animal> NearestData = nullptr;
		float Distance = 1e9;
		
		for(int i = 0; i < list.size(); i++)
		{
			if (list[i] == data) 
				continue;
			
			if (Distance > Vector2D::GetDistance(data->GetPosition(), list[i]->GetPosition()))
			{
				NearestData = list[i];
				Distance = Vector2D::GetDistance(data->GetPosition(), list[i]->GetPosition());
			}
		}

		return NearestData;
	}

	//输入的是身体半径
	vector<shared_ptr<Animal>> GetCollision(shared_ptr<Animal> data)
	{
		vector<shared_ptr<Animal>>list;
		find(QuadAABB(data->GetPosition().GetX() - data->GetCollisionRadius(), data->GetPosition().GetX() + data->GetCollisionRadius(),
			data->GetPosition().GetY() - data->GetCollisionRadius(), data->GetPosition().GetY() + data->GetCollisionRadius()), list, true);

		return list;
	}


	~QuadTree()
	{
		delete _root;
	}

private:
	void add(QuadTreeNode<T>* node, T data, QuadAABB aabb, int deep)
	{
		QuadAABB naabb = node->aabb;
		if (deep < max_deep)
		{
			if (node->childList == nullptr)
			{
				node->childList = new QuadTreeNode<T>*[4];
				int nwidth = naabb.width / 2;
				int nheight = naabb.height / 2;
				node->childList[0] = new QuadTreeNode<T>(QuadAABB(naabb.left, naabb.left + nwidth, naabb.top, naabb.top + nheight));
				node->childList[1] = new QuadTreeNode<T>(QuadAABB(naabb.left + nwidth, naabb.right, naabb.top, naabb.top + nheight));
				node->childList[2] = new QuadTreeNode<T>(QuadAABB(naabb.left, naabb.left + nwidth, naabb.top + nheight, naabb.bottom));
				node->childList[3] = new QuadTreeNode<T>(QuadAABB(naabb.left + nwidth, naabb.right, naabb.top + nheight, naabb.bottom));
			}
			for (int i = 0; i < 4; i++)
			{
				QuadTreeNode<T>* child = node->childList[i];
				if (child->aabb.IsContain(aabb))
				{
					add(child, data, aabb, deep + 1);
				}
			}
		}
		node->dataList.push_back(data);
		node->aabbList.push_back(aabb);
	}

	void find(QuadTreeNode<T>* node, QuadAABB aabb, vector<T>& list, vector<QuadAABB>& aabbList)
	{
		if (node->aabbList.size() > 0)
		{
			for (auto x : node->dataList)
			{
				list.push_back(x);
			}
			for (auto x : node->aabbList)
			{
				aabbList.push_back(x);
			}
		}
		if (node->childList == nullptr)
		{
			return;
		}

		for (int i = 0; i < 4; i++)
		{
			QuadTreeNode<T>* child = node->childList[i];
			if (child->aabb.IsContain(aabb))
			{
				find(child, aabb, list, aabbList);
			}
		}
	}


private:
	int max_deep;
	QuadTreeNode<T>* _root;
};