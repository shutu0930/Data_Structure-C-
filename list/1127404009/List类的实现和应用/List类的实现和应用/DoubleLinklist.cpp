#include "DoubleLinklist.h"

template <class DoubleLinklist_entry>
DNode<DoubleLinklist_entry>::DNode()
{
	next = back = NULL;
}

template <class DoubleLinklist_entry>
DNode<DoubleLinklist_entry>::DNode(DoubleLinklist_entry data,DNode<DoubleLinklist_entry> *link_back = NULL,
DNode<DoubleLinklist_entry> *link_next = NULL)
{
	entry = data;
	back = link_back;
	next = link_next;
}

template <class DoubleLinklist_entry>
DoubleLinklist<DoubleLinklist_entry>::DoubleLinklist()
{
	count = 0;
	current = NULL;
	current_position = -1;
}

template <class DoubleLinklist_entry>
void DoubleLinklist<DoubleLinklist_entry>::clear()
{
	DNode<DoubleLinklist_entry> *p, *q;
	if (current == NULL) return;
	for (p=current->back; p; p=q) 
	{
		q = p->back;
		delete p;
	}
	for (p=current; p; p=q) 
	{
		q = p->next;
		delete p;
	}
	count = 0;
	current = NULL;
	current_position = -1;
}

template <class DoubleLinklist_entry>
int DoubleLinklist<DoubleLinklist_entry>::size() const
{
	return count;
}

template <class DoubleLinklist_entry>
bool DoubleLinklist<DoubleLinklist_entry>::empty() const
{
	return count <= 0;
}

template <class DoubleLinklist_entry>
bool DoubleLinklist<DoubleLinklist_entry>::full() const
{
	return false;
}

template <class DoubleLinklist_entry>
void DoubleLinklist<DoubleLinklist_entry>::traverse(void (*visit)(DoubleLinklist_entry &))
{
	DNode<DoubleLinklist_entry> *to_visit = current;
	if (to_visit != NULL) 			// Ignore empty DoubleLinklists.
	for ( ; to_visit->back; to_visit = to_visit->back)
	// Find the beginning of DoubleLinklist.
	;
	for ( ; to_visit; to_visit = to_visit->next)
	(*visit)(to_visit->entry);
}

template <class DoubleLinklist_entry>
Error_code DoubleLinklist<DoubleLinklist_entry>::insert(int position, const DoubleLinklist_entry &x)
{
	DNode<DoubleLinklist_entry> *new_DNode, *following, *preceding;
	if (position < 0 || position>count) return rangeerror;
	if (position == 0) 
	{
		if (count == 0) following = NULL;
		else 
		{
			set_position(0);
			following = current;
		}
		preceding = NULL;
	}
	else 
	{
		set_position(position - 1);
		preceding = current;
		following = preceding->next;
	}
	new_DNode = new DNode<DoubleLinklist_entry>(x, preceding, following);
	if (new_DNode == NULL) return overflow;
	if (preceding != NULL) preceding->next = new_DNode;
	if (following != NULL) following->back = new_DNode;
	current = new_DNode;
	current_position = position;
	count++;
	return success;
}

template <class DoubleLinklist_entry>
Error_code DoubleLinklist<DoubleLinklist_entry>::retrieve(int position,DoubleLinklist_entry &x) const
{
	if (position < 0 || position >= count) return range_error;
	set_position(position);
	x = current->entry;
	return success;
}

template <class DoubleLinklist_entry>
Error_code DoubleLinklist<DoubleLinklist_entry>::replace(int position, const DoubleLinklist_entry &x)
{
	if (position < 0 || position >= count) return range_error;
	set_position(position);
	current->entry = x;
	return success;
}

template <class DoubleLinklist_entry>
Error_code DoubleLinklist<DoubleLinklist_entry>::remove(int position, DoubleLinklist_entry &x)
{
	DNode<DoubleLinklist_entry> *old_DNode, *neighbor;
	if (count == 0) return fail;
	if (position < 0 || position >= count) return range_error;
	set_position(position);
	old_DNode = current;
	if (neighbor = current->back) neighbor->next = current->next;
	if (neighbor = current->next) 
	{
		neighbor->back = current->back;
		current = neighbor;
	}
	else 
	{
		current = current->back;
		current_position--;
	}
	x = old_DNode->entry;
	delete old_DNode;
	count--;
	return success;
}

template <class DoubleLinklist_entry>
void DoubleLinklist<DoubleLinklist_entry>::set_position(int position) const
{
	if (current_position <= position)
	for ( ; current_position != position; current_position++)
	current = current->next;
	else
	for ( ; current_position != position; current_position--)
	current = current->back;
}
// ~DoubleLinklist: a destructor to clear the DoubleLinklist.
/*
Post: The DoubleLinklist is empty: all entries have been removed.
*/
template <class DoubleLinklist_entry>
DoubleLinklist<DoubleLinklist_entry>::	~DoubleLinklist()
{
	clear();
}
// DoubleLinklist: a copy constructor
/*
Post: The DoubleLinklist is initialized to copy the parameter copy.
*/
template <class DoubleLinklist_entry>
DoubleLinklist<DoubleLinklist_entry>::DoubleLinklist(const DoubleLinklist<DoubleLinklist_entry> &copy)
{
	count = copy.count;
	current_position = copy.current_position;
	DNode<DoubleLinklist_entry> *new_DNode, *old_DNode = copy.current;
	if (old_DNode == NULL) current = NULL;
	else 
	{
		new_DNode = current = new DNode<DoubleLinklist_entry>(old_DNode->entry);
		while (old_DNode->next != NULL) 
		{
			old_DNode = old_DNode->next;
			new_DNode->next = new DNode<DoubleLinklist_entry>(old_DNode->entry, new_DNode);
			new_DNode = new_DNode->next;
		}
		old_DNode = copy.current;
		new_DNode = current;
		while (old_DNode->back != NULL) 
		{
			old_DNode = old_DNode->back;
			new_DNode->back= new DNode<DoubleLinklist_entry>(old_DNode->entry,
			NULL, new_DNode);
			new_DNode = new_DNode->back;
		}
	}
}
// DoubleLinklist: overloaded assignment
/*
Post: The DoubleLinklist is assigned to copy a parameter
*/
template <class DoubleLinklist_entry>
void DoubleLinklist<DoubleLinklist_entry>::operator =(const DoubleLinklist<DoubleLinklist_entry> &copy)
{
	DoubleLinklist new_copy(copy);
	clear();
	count = new_copy.count;
	current_position = new_copy.current_position;
	current = new_copy.current;
	new_copy.count = 0;
	new_copy.current_position = 0;
	new_copy.current = NULL;
}
