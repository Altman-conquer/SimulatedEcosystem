#pragma once
#include <stdexcept>
#include <Utility>
#include <xutility>
#include <map>

using std::make_pair;
using std::pair;
using std::iterator;

template<class K, class V>
class AVLTreeNode {

	template<class _K, class _V>
	friend class AVLTree;

public:
	// Universal reference constructor. Aiming at using perfect forwarding to construct the node.
	// std::forward takes two template parameters. It cannot deduce the first parameter. 
	template<typename _K = K, typename _V = V>
	AVLTreeNode(_K&& _key, _V&& _value) :
		first(_key), second(_value),
		left(nullptr), right(nullptr), parent(nullptr), balance_factor(0), is_valid(true) {}

	template<typename _V = V>
	AVLTreeNode& operator=(_V&& _value)
	{
		second = _value;
		return *this;
	}

	~AVLTreeNode()
	{
		delete left;
		left = nullptr;

		delete right;
		right = nullptr;
	}

	AVLTreeNode* GetRight() { return right; }

	AVLTreeNode* GetLeft() { return left; }

public:
	int GetBalanceFactor() const
	{
		auto dfs = [&](AVLTreeNode* current)  -> int
		{
			if (current == nullptr)
				return 0;
		};
	}

	K first;
	V second;

	AVLTreeNode* left;
	AVLTreeNode* right;
	AVLTreeNode* parent;

	int balance_factor; // height(right) - height(left)

private:
	bool is_valid;
};

template<class K, class V>
class AVLTree {

	typedef AVLTreeNode<K, V> Node;

public:
	AVLTree() :root(nullptr) {}

	~AVLTree()
	{
		delete root;
		root = nullptr;
	}

	class AVLTreeIterator : public std::iterator<std::forward_iterator_tag, Node> {
	public:
		AVLTreeIterator(Node* _current) :current(_current)
		{
			while (current != nullptr && current->GetLeft() != nullptr)
			{
				current = current->GetLeft();
			}
		}

		// Dereference operator
		Node& operator*() { return *current; }

		Node* operator->() { return current; }

		// Increment operator (prefix)
		AVLTreeIterator& operator++() { next(); return *this; }

		// Increment operator (postfix)
		AVLTreeIterator operator++(int) { AVLTreeIterator temp = *this; next(); return temp; }

		// Equality operator
		bool operator==(const AVLTreeIterator& other) { return current == other.current; }

		// Inequality operator
		bool operator!=(const AVLTreeIterator& other) { return current != other.current; }

	private:
		// Move current pointer to the next node. (In-order traversal)
		void next()
		{
			if (current->GetRight() != nullptr)
			{
				current = current->GetRight();
				while (current->GetLeft() != nullptr)
					current = current->GetLeft();
			}
			else
			{
				Node* parent = current->parent;
				while (parent != nullptr && current == parent->GetRight())
				{
					current = parent;
					parent = parent->parent;
				}
				current = parent;
			}
		}

		Node* current;
	};

	template<typename _K = K, typename _V = V>
	bool insert(_K&& _key, _V&& _value)
	{
		return _insert(_key, _value) == nullptr;
	}

	template<typename _K = K>
	bool erase(_K&& _key)
	{
		Node* current = _find(_key);
		if (current == nullptr)
			return false;
		current->is_valid = false;
		return true;
	}
	
	template<typename _K = K>
	AVLTreeIterator find(_K&& _key)
	{
		Node* current = _find(_key);
		return AVLTreeIterator(current);
	}

	AVLTreeIterator begin() { return AVLTreeIterator(root); }

	AVLTreeIterator end() { return AVLTreeIterator(nullptr); }

	template<typename _K = K, typename _V = V>
	V& operator[](_K&& _key)
	{
		Node* temp = _find(_key);
		if (temp != nullptr)
			return temp->second;
		return _insert(_key, V())->second;
	}

private:

	template<typename _K = K, typename _V = V>
	Node* _insert(_K&& _key, _V&& _value)
	{
		if (root == nullptr)
		{
			root = new Node(_key, _value);
			return root;
		}

		// Insert node like in BST
		Node* current = root, * parent = nullptr;
		while (current != nullptr)
		{
			parent = current;
			if (_key < current->first)
				current = current->left;
			else if (_key > current->first)
				current = current->right;
			else // Key already exists
			{
				current->second = _value;
				break;
			}
		}

		// Insert the node
		current = new Node(_key, _value);
		current->parent = parent;
		if (_key < parent->first)
			parent->left = current;
		else
			parent->right = current; // guaranteed to be greater than the value of the parent

		// Check if the tree is balanced or not
		while (parent != nullptr)
		{
			// Update balance factor of parents
			if (parent->left == current)
				parent->balance_factor--;
			else
				parent->balance_factor++;

			if (parent->balance_factor == 1 || parent->balance_factor == -1) // The height might be changed, we need to go up and update.
			{
				current = current->parent;
				parent = parent->parent;
			}
			else if (parent->balance_factor == 0) // already balance because max height is not changed
			{
				break;
			}
			else if (parent->balance_factor == 2 || parent->balance_factor == -2) // The tree is unbalanced
			{
				if (parent->balance_factor == 2)
				{
					if (current->balance_factor == 1)
						RotateL(current);
					else
						RotateRL(current);
				}
				else
				{
					if (current->balance_factor == -1)
						RotateR(current);
					else
						RotateLR(current);
				}
				break;
			}
			else {
				throw std::logic_error("The tree is wrong");
			}
		}
		return current;
	}

	template<typename _K = K>
	Node* _find(_K&& _key)
	{
		Node* current = root;
		while (current != nullptr)
		{
			if (current->first == _key)
				return current;
			else if (current->first > _key)
				current = current->left;
			else
				current = current->right;
		}
		return current;
	}

	void RotateL(Node* current)
	{
		Node* parent = current->parent, * lchild = current->left;

		current->parent = parent->parent;
		if (parent != root)
		{
			if (parent->parent->left == parent)
				parent->parent->left = current;
			else
				parent->parent->right = current;
		}
		else
		{
			root = current;
		}

		current->left = parent;
		parent->parent = current;

		parent->right = lchild;
		if (lchild != nullptr)
			lchild->parent = parent;

		current->balance_factor = 0;
		parent->balance_factor = 0;

	}

	void RotateR(Node* current)
	{
		Node* parent = current->parent, * rchild = current->right;

		current->parent = parent->parent;
		if (parent != root)
		{
			if (parent->parent->left == parent)
				parent->parent->left = current;
			else
				parent->parent->right = current;
		}
		else
		{
			root = current;
		}

		current->right = parent;
		parent->parent = current;

		parent->left = rchild;
		if (rchild != nullptr)
			rchild->parent = parent;

		current->balance_factor = 0;
		parent->balance_factor = 0;
	}

	void RotateLR(Node* current)
	{
		Node* parent = current->parent, * rchild = current->right;

		int balance_factor = rchild->balance_factor;

		RotateL(rchild);
		RotateR(rchild);

		rchild->balance_factor = 0;
		if (balance_factor == -1)
		{
			parent->balance_factor = 1;
			current->balance_factor = 0;
		}
		else if (balance_factor == 1)
		{
			parent->balance_factor = 0;
			current->balance_factor = -1;
		}
		else if (balance_factor == 0)
		{
			parent->balance_factor = 0;
			current->balance_factor = 0;
		}
		else
		{
			throw std::logic_error("The tree is wrong");
		}
	}

	void RotateRL(Node* current)
	{
		Node* parent = current->parent, * lchild = current->left;

		int bf = lchild->balance_factor;

		RotateR(lchild);
		RotateL(lchild);

		lchild->balance_factor = 0;
		if (bf == 1)
		{
			parent->balance_factor = -1;
			current->balance_factor = 0;
		}
		else if (bf == -1)
		{
			parent->balance_factor = 0;
			current->balance_factor = 1;
		}
		else if (bf == 0)
		{
			parent->balance_factor = 0;
			current->balance_factor = 0;
		}
		else
		{
			throw std::logic_error("The tree is wrong");
		}
	}

	Node* root;
};
