#pragma once
#include "stdafx.h"
template<class DNode_entry>
struct DNode
{
	DNode_entry entry;
	DNode<DNode_entry>*next;
	DNode<DNode_entry>*back;
	DNode();
	DNode(DNode_entry,DNode<DNode_entry>*link_back=NULL,DNode<DNode_entry>*link_next=NULL);
};

template<class DoubleLinklist_entry>
class DoubleLinklist
{
public:
	

	DoubleLinklist(void);
	DoubleLinklist(const DoubleLinklist<DoubleLinklist_entry> &copy);
	int size() const;
	bool full() const;
	bool empty() const;
	void clear();
	void operator=(const DoubleLinklist<DoubleLinklist_entry> &copy);
	Error_code replace(int position, const DoubleLinklist_entry &x);
	Error_code retrieve(int position, DoubleLinklist_entry &x) const;
	Error_code remove(int position, DoubleLinklist_entry &x);
	Error_code insert(int position,const DoubleLinklist_entry &x);
	void traverse(void (*visit)(DoubleLinklist_entry &));
	~DoubleLinklist(void);
protected:
	int count;
	mutable int current_position;
	mutable DNode<DoubleLinklist_entry>*current;
	void set_position(int position)const;
};
