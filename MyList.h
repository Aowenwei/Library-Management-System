#pragma once
#ifndef MYLIST_H_
#define MYLIST_H_
#include<cassert>
#include<iostream>
#include<functional>

using std::cin;
using std::cout;
using std::endl;

template<class Type >struct Node {
	Type val;
	Node<Type>* prev, * pnext;
	Node() : prev(nullptr), pnext(nullptr), val() {}
};

//迭代器
template<class Type> class Iterator {
public:
	Node<Type>* current;
	Iterator() :current(nullptr) {}//默认构造函数
	Iterator(Node<Type>* node) :current(node) {}
	Iterator(const Iterator& itr) :current(itr.current) {}

	//重载操作符
	Iterator& operator++() { current = current->pnext; return *this; }
	Iterator& operator++(int) {
		Iterator old = *this;
		++(*this);  //利用了重载的前置++
		return old;
	}
	Iterator& operator--() { current = current->prev; return *this; }
	Iterator& operator--(int) {
		Iterator old = current;
		--(*this);
		return old;
	}
	Type& operator *() { return current->val; }
	const Type& operator *()const { return current->val; }

	//重载判断
	bool operator!=(const Iterator& rhs) { return (current != rhs.current); }
	bool operator==(const Iterator& rhs) { return (current == rhs.current); }
};

template<class Type >class MyList {
private:
	size_t len;
	Node<Type>* phead;
	using Func = std::function<void ()>;			    //函数
public:
	typedef Iterator<Type> iterator;							//简化迭代器的写法
	MyList(Type* p = nullptr) :len(0) {
		phead = new Node<Type>;
		phead->pnext = phead->prev = nullptr;
	}								//构造函数
	MyList(const MyList& list);								    //拷贝构造函数
	iterator begin();											//返回头节点
	iterator end();												//返回尾节点
	void Clear();												//删除链表  
	bool pop_front();										    //头删
	bool pop_back();										    //尾删
	int Length()const;                                          //链表长度
	bool push_back(const Type& pdata);                          //尾插法
	bool push_front(const Type& pdata);                         //头插法
	iterator erase(iterator itr);								//清除itr的current指向的节点
	bool CreatList(const Type& pdata);						    //创建链表
	bool IsEmpty() const { return phead->pnext == nullptr; }
	MyList& operator=(const MyList& rhs);                       //重载 = 运算符
	friend std::ostream& operator<<(std::ostream& os, const MyList& rhs) {
		if (rhs.IsEmpty()) {
			os << "Null Data.\n";
		}
		else {
			Node<Type>* p = rhs.phead;
			while (p) {
				os << p->val << ' ';
				p = p->pnext;
			}
		}
		return os;
	}
	void TraverList(Func fun = NULL)const;
	~MyList();
};
#endif // !MYLIST_H_

//拷贝双向链表
template<class Type> MyList<Type>::MyList(const MyList<Type>& rhs) :len(0)
{
	phead = new Node<Type>;
	phead->pnext = nullptr;
	Node<Type>* cur_phead = phead, * current = rhs.phead->pnext;
	while (current)
	{
		cur_phead->pnext = new Node<Type>;
		cur_phead = cur_phead->pnext;
		cur_phead->val = current->val;
		cur_phead->pnext = nullptr;
		current = current->pnext;
	}
}

template<class Type> Iterator<Type> MyList<Type>::begin()
{
	return iterator(phead->pnext);
}

template<class Type> Iterator<Type> MyList<Type>::end()
{
	return nullptr;
};
//重载 = 
template<class Type> MyList<Type>& MyList<Type>::operator=(const MyList<Type>& rhs)
{
	if (this != &rhs) {
		Clear();
		Node<Type>* pNew = nullptr, * ptem = rhs.phead;
		while (ptem) //遍历传入的链表
		{
			pNew = new Node<Type>;//创建新节点
			pNew->val = rhs.phead->val;//进行赋值
			ptem = ptem->pnext;
		}
	}
	return *this;
}

template<class Type> bool MyList<Type>::push_front(const Type& pdata)
{
	Node<Type>* pNew = new Node<Type>;
	assert(pNew);
	pNew->val = pdata;
	if (phead->pnext == nullptr) {
		phead->pnext = pNew;
		pNew->prev = phead;
		pNew->pnext = nullptr;
		++len;
		return true;                    //添加完毕
	}
	else {
		pNew->pnext = phead->pnext;
		phead->pnext->prev = pNew;
		phead->pnext = pNew;
		pNew->prev = phead;
		++len;
		return true;
	}
	return false;                       //操作失败
}

template<class Type> Iterator<Type> MyList<Type>::erase(iterator itr)
{
	if (itr != end()) {
		Node<Type>* cur = itr.current;
		Node<Type>* prev = cur->prev;
		Node<Type>* next = cur->pnext;

		prev->pnext = next;
		next->prev = prev;

		delete cur;
		cur = nullptr;
		itr = iterator(next);
	}
	return itr;
}

template<class Type> bool MyList<Type>::CreatList(const Type& pdata)
{
	Node<Type>* pNew = nullptr, * temp = phead;
	pNew = new Node<Type>;
	if (pNew == nullptr) return false;
	pNew->val = pdata;
	pNew->pnext = nullptr;
	pNew->prev = temp;
	temp->pnext = pNew;
	temp = pNew;
	++len;
	return true;
}

template<class Type> bool MyList<Type>::push_back(const Type& pdata)
{
	//链表为空， 调用头插法，成功返回true
	if (phead->pnext == nullptr) {
		push_front(pdata);
		return true;
	}
	//迭代至末尾
	Node<Type>* p = phead;
	while (p->pnext) p = p->pnext;
	//创建新的节点
	Node<Type>* pNew = new Node<Type>;
	if (pNew == nullptr) {
		return false;
	}
	//完成尾插操作
	pNew->val = pdata;
	p->pnext = pNew;
	pNew->prev = p;
	//p = pNew;
	pNew->pnext = nullptr;
	++len;
	return true;
}

template<class Type> bool MyList<Type>::pop_front()
{
	if (phead->pnext == nullptr) {
		return false;
	}
	Node<Type>* p = phead->pnext;
	phead->pnext = phead->pnext->pnext;
	delete p;
	p = nullptr;
	--len;
	return true;
}

template<class Type> bool MyList<Type>::pop_back()
{
	if (phead->pnext == nullptr) {
		fprintf(stderr, "There is no list.\n");
		return false;
	}
	Node<Type>* temp = phead, * temp1 = nullptr;
	while (temp->pnext) //指针移动到尾节点
	{
		temp = temp->pnext;
	}
	//获取尾节点的前一个节点
	temp1 = temp->prev;
	//释放节点
	delete temp;
	temp = nullptr;
	temp1->pnext = nullptr;
	return true;
}

template<class Type> void MyList<Type>::Clear()
{
	if (phead->pnext != nullptr) {
		Node<Type>* p = phead;
		while (p)
		{
			phead = phead->pnext;
			delete p;
			p = nullptr;
			p = phead;
		}
	}
	--len;
	delete phead;
	phead = nullptr;
}

template<class Type> int MyList<Type>::Length()const
{
	int len = 0;
	Node<Type>* p = phead->pnext;
	while (p)
	{
		++len;
		p = p->pnext;
	}
	return len;
}

template<class Type> void MyList<Type>::TraverList(Func fun)const {
	assert(phead->pnext);
	Node<Type>* p = phead->pnext;
	while (p)
	{
		std::cout << p->val << ' ';
		//fun(p);
		p = p->pnext;
	}
	std::cout << "\n";
}

template<class Type> MyList<Type>::~MyList()
{
	Clear();
	std::cout << "Destructor is completed\n";
}
