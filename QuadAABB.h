#pragma once

class QuadAABB
{
public:
	int left;
	int right;
	int top;
	int bottom;
	int width;
	int height;


	QuadAABB(int left, int right, int top, int bottom)
	{
		this->left = left;
		this->right = right;
		this->top = top;
		this->bottom = bottom;
		this->width = right - left;
		this->height = top - bottom;
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
		return (aabb.left == this->left && aabb.right == this->rigth && aabb.bottom == this->bottom && aabb.top == this->top);
	}
	
	bool isIntersect(QuadAABB aabb)
	{
		int flag = 0;
		if (aabb.left <= this->right && aabb.bottom >= this->top) flag = 1;
		if (aabb.right >= this->left && aabb.bottom >= this->top) flag = 1;
		if (aabb.left <= this->right && aabb.top >= this->bottom) flag = 1;
		if (aabb.right <= this->left && aabb.top >= this->bottom) flag = 1;
		if (flag) return true;
		else return false;
	}
};