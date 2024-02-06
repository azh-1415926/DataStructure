#ifndef _LINK_LIST_H_
#define _LINK_LIST_H_

#include<iostream>

template<class T>
class linkList
{
private:
	struct Node
	{
		public:
		T data;
		Node *next;
		Node(const T& data=0,Node* next=nullptr):data(data),next(next){}
	};
	Node* m_Head;
	int m_Length;
public:
	linkList();
	linkList(T *pArray,int size);
	~linkList();
	inline bool empty() const { return m_Head->next==NULL; }
	void show() const;
	int indexOf(const T& data) const;
	T at(int pos=-1) const;
	bool insert(const T& data,int pos=-1);
	T erase(int pos=-1);
	linkList& split(linkList &list);
};

template<class T>
linkList<T>::linkList()
	: m_Head(new Node), m_Length(0)
{
}

template<class T>
linkList<T>::linkList(T *pArray,int size)
	: m_Head(new Node)
{
	Node* pList=m_Head;
	for(int i=0;i<size;++i)
	{
		pList->next=new Node(pArray[i]);
		pList=pList->next;
	}
	m_Length=size;
}

template <class T>
inline linkList<T>::~linkList()
{
	Node* pList=m_Head;
	Node* temp=nullptr;
	while(pList)
	{
		temp=pList;
		pList=pList->next;
		delete temp;
	}
}

template<class T>
void linkList<T>::show() const
{
	Node* pList=m_Head->next;
	if(pList==NULL)
		throw std::out_of_range("show() error,list is empty!");
	while(pList)
	{
		std::cout<<pList->data<<" ";
		pList=pList->next;
	}
	std::cout<<std::endl;
}

template<class T>
int linkList<T>::indexOf(const T& data) const
{
	Node* pList=m_Head->next;
	int i=0;
	while(pList)
	{
		if(pList->data==data)
			return i;
		pList=pList->next;
		++i;
	}
	return -1;
}

template<class T>
T linkList<T>::at(int pos) const
{
	if(pos==-1)
		pos=0;
	if(pos<-1||pos>=m_Length)
		throw std::out_of_range("at() error,out of range!");
	Node* pList=m_Head->next;
	int i=0;
	while(i++<pos&&pList)
		pList=pList->next;
	if(i<pos&&pList==NULL)
		throw std::out_of_range("at() error,out of range!");
	return pList->data;
}

template<class T>
bool linkList<T>::insert(const T& data,int pos)
{
	if(pos==-1)
		pos=0;
	if(pos<-1&&pos>m_Length)
		return false;
	Node* pList=m_Head;
	int i=0;
	while(i++<pos&&pList)
		pList=pList->next;
	if(i<pos&&pList==NULL)
		return false;
	Node* pTemp;
	pTemp=pList->next;
	pList->next=new Node(data);
	pList=pList->next;
	pList->next=pTemp;
	++m_Length;
	return true;
}

template<class T>
T linkList<T>::erase(int pos)
{
	if((pos<-1&&pos>=m_Length)||empty())
		throw std::out_of_range("erase() error,out of range!");
	if(pos==-1)
		pos=0;
	Node* pList=m_Head;
	int i=0;
	while(i++<pos&&pList)
		pList=pList->next;
	if(i<pos&&pList==nullptr)
		throw std::out_of_range("erase() error,out of range!");
	Node* pTemp;
	T e;
	pTemp=pList->next;
	e=pTemp->data;
	pList->next=pTemp->next;
	delete pTemp;
	--m_Length;
	return e;
}

template<class T>
linkList<T>& linkList<T>::split(linkList<T> &list)
{
	m_Length=m_Length+list.m_Length;
	Node* pList=m_Head;
	while(pList->next)
		pList=pList->next;
	for(int i=0;i<list.m_Length;++i)
	{
		pList->next=new Node(list.at(i));
		pList=pList->next;
	}
	return *this;
}

#endif