#pragma once
#include "stdafx.h"
template<class Node_entry>
struct Node
{
	Node_entry entry;
	Node<Node_entry>*next;
	Node();
	Node(Node_entry,Node<Node_entry>*link=NULL);
};

template<class Linklist_entry>
class Linklist
{
public:
	Linklist(void);
	Linklist(const Linklist<Linklist_entry>&copy);
	void operator=(const Linklist<Linklist_entry>&copy);
	int size()const;
	bool full()const;
	bool empty()const;
	void clear();
	void traverse(void (*visit)(Linklist_entry &));
	Error_code retrieve(int position,Linklist_entry &x)const;
	Error_code replace(int position,const Linklist_entry &x);
	Error_code remove(int position,Linklist_entry &x);
	Error_code insert(int position,const Linklist_entry &x);
	~Linklist(void);
protected:
	int count;
	Node<Linklist_entry>*head;
	Node<Linklist_entry>*set_position(int position)const;

	

};