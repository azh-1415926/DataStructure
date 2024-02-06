#ifndef _LINK_LIST_H_
#define _LINK_LIST_H_

#include<iostream>

template<class Type>
class linkList
{
private:
	struct Node
	{
		public:
		Type data;
		Node *next;
		Node(const Type& data=0,Node* next=nullptr):data(data),next(next){}
	};
	Node* m_Head;
	int m_Length;
public:
	linkList();
	linkList(Type *pArray,int size);
	~linkList();
	inline bool empty() const { return m_Head->next==NULL; }
	void show() const;
	int indexOf(const Type& data) const;
	Type at(int pos=-1) const;
	bool insert(const Type& data,int pos=-1);
	Type erase(int pos=-1);
	linkList& split(linkList &list);
};

template<class Type>
linkList<Type>::linkList()
	: m_Head(new Node), m_Length(0)
{
}

template<class Type>
linkList<Type>::linkList(Type *pArray,int size)
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

template <class Type>
inline linkList<Type>::~linkList()
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

template<class Type>
void linkList<Type>::show() const
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

template<class Type>
int linkList<Type>::indexOf(const Type& data) const
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

template<class Type>
Type linkList<Type>::at(int pos) const
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

template<class Type>
bool linkList<Type>::insert(const Type& data,int pos)
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

template<class Type>
Type linkList<Type>::erase(int pos)
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
	Type e;
	pTemp=pList->next;
	e=pTemp->data;
	pList->next=pTemp->next;
	delete pTemp;
	--m_Length;
	return e;
}

template<class Type>
linkList<Type>& linkList<Type>::split(linkList<Type> &list)
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