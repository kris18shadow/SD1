#include <iostream>

//Stack element:
template<typename T>
struct Box
{
	Box<T>* pNext;
	T data;
};

//linked stack:
template<typename T>
class Stack
{
private:
	Box<T>* pTop;
	int length;
public:
	Stack<T>();
	~Stack<T>();

	void push(const T& elem);
	void pop();

	bool isEmpty() const;
	int getLength() const;
	T peek() const;	
};

template<typename T>
Stack<T>::Stack()
{
	pTop = NULL;
	length = 0;
}

template<typename T>
Stack<T>::~Stack()
{
	while(pTop)
	{
		Box<T>* prev = pTop->pNext;
		delete pTop;
		pTop = prev;
	}

}

template<typename T>
void Stack<T>::push(const T& elem)
{
	Box<T>* pn = new Box<T>;
	pn->data = elem;
	pn->pNext = pTop;
	pTop = pn;

	length++;
}

template<typename T>
void Stack<T>::pop()
{
	if(isEmpty())
		throw "The stack is empty!\n";

	Box<T>* prev = pTop->pNext;
	delete pTop;
	pTop = prev;

	length--;
}

template<typename T>
bool Stack<T>::isEmpty() const
{
	return pTop == NULL;
}

template<typename T>
int Stack<T>::getLength() const
{
	return length;
}

template<typename T>
T Stack<T>::peek() const
{
	if(isEmpty())
		throw "The stack is empty!\n";

	return pTop->data;
}