#pragma once

template <class Elem>
class Link {
public:
	Elem value;
	Link* next;
	Link* prev;
	
	Link(const Elem& element   , Link* preVal = nullptr, Link* nextVal = nullptr) {
		value = element;
		next = nextVal;
		prev = preVal;
	}
    Link(Link* preVal = nullptr, Link* nextVal = nullptr) {
		next = nextVal;
		prev = preVal;
	}


};


template <class T>
class List
{
public:
	List();
	~List();

	int size() const;
	bool isEmpty() const;

	T get(int index) const;
	T get_first() const;
	T get_last() const;

	bool insert(int index, T t);
	bool insert_first(T t);
	bool append_last(T t);
	bool erase(int index);

private:
	int count;
	Link<T>* head;

private:
	Link<T>* getLinkNode(int index) const;
};

template<class T>
 List<T>::List() :count(0) {
	head = new Link<T>();
	head->prev = head->next = head;
}

template<class T>
List<T>::~List() {
	{
		// delete all
		Link<T>* temp;
		Link<T>* node = head->next;
		while (node != head)
		{
			temp = node;
			node = node->next;
			delete temp;
		}

		// delete head
		delete head;
		head = NULL;
	}
}

template<class T>
int List<T>::size() const
{
	return count;
}

template<class T>
bool List<T>::isEmpty() const 
{
	return count == 0;
}

template<class T>
Link<T>* List<T>::getLinkNode(int index) const
{
	if (index < 0 || index >= count)
	{
		cout << "get node failed! the index in out of bound!" << endl;
		return NULL;
	}

	if (index <= count / 2)
	{
		int i = 0;
		Link<T>* temp = head->next;
		while (i++ < index) {
			temp = temp->next;
		}

		return temp;
	}

	int j = 0;
	int rindex = count - index - 1;
	Link<T>* temp = head->prev;
	while (j++ < rindex) {
		temp = temp->prev;
	}
	return temp;
}


template<class T>
T List<T>::get(int index) const
{
	return getLinkNode(index)->value;
}


template<class T>
T List<T>::get_first() const
{
	return getLinkNode(0)->value;
}


template<class T>
T List<T>::get_last() const
{
	return getLinkNode(count - 1)->value;
}



template<class T>
bool List<T>::insert(int index, T t)
{
	if (index < 0 || index >= count) return false;
	if (index == 0)
		return insert_first(t);
	Link<T>* temp = getLinkNode(index);
	Link<T>* elem = new Link<T>(t, temp->prev, temp);
	temp->prev->next = elem;
	temp->prev = elem;
	count++;
	return true;
}


template<class T>
bool List<T>::insert_first(T t)
{
	Link<T>* TEMP = new Link<T>(t, head, head->next);
	head->next->prev = TEMP;
	head->next = TEMP;
	count++;
	return true;
}

template<class T>
bool List<T>::append_last(T t)
{
	Link<T>* temp = new Link<T>(t, head->prev, head);
	head->prev->next = temp;
	head->prev = temp;
	count++;
	return 0;
}

template<class T>
bool List<T>::erase(int index)
{
	if (index < 0 || index >= count) return false;
	Link<T>* temp = getLinkNode(index);
	temp->next->prev = temp->prev;
	temp->prev->next = temp->next;
	delete temp;
	count--;
	return 0;
}

