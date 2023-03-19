#pragma once
#include <Animal.h>

class QuadAABB
{
public:
	float left;
	float right;
	float top;
	float bottom;
	float width;
	float height;


	QuadAABB(float left, float right, float top, float bottom)
	{
		this->left = left;
		this->right = right;
		this->top = top;
		this->bottom = bottom;
		this->width = right - left;
		this->height = bottom - top;
	}

	QuadAABB()
	{
		this->left = this->right = this->top = this->bottom = this->width = this->height = 0;
	}

	bool IsContain(QuadAABB aabb)
	{
		return (aabb.left >= this->left && aabb.right <= this->right && aabb.bottom <= this->bottom && aabb.top >= this->top);
	}

	bool IsEqual(QuadAABB aabb)
	{
		return (aabb.left == this->left && aabb.right == this->right && aabb.bottom == this->bottom && aabb.top == this->top);
	}
	
	bool isIntersect(QuadAABB aabb)
	{
		int nleft = std::max(this->left, aabb.left);
		int nright = std::min(this->right, aabb.right);
		int ntop = std::max(this->top, aabb.top);
		int nbottom = std::min(this->bottom, aabb.bottom);

		if (nleft > nright || ntop > nbottom) return false;
		else return true;
	}

};