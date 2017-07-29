#include "Linklist.h"

template <class Node_entry>
Node<Node_entry>::Node()
{
	next =NULL;
}

template <class Node_entry>
Node<Node_entry>::Node(Node_entry data,Node<Node_entry> *link= NULL)
{
	entry = data;
	next = link;
}

template <class Linklist_entry>
Linklist<Linklist_entry> :: Linklist( )
/* Post: The Linklist is initialized to be empty. */
{
	count = 0;
	head = NULL;
}

template <class Linklist_entry>
Linklist<Linklist_entry> :: Linklist(const Linklist<Linklist_entry> &copy)
/* Post: The Linklist is initialized to copy the parameter copy. */
{
	count=copy.count;
	Node<Linklist_entry> *new_node, *old_node = copy.head;
	if (old_node == NULL) head = NULL;
	else 
	{
		new_node = head = new Node<Linklist_entry>(old_node->entry);
		while (old_node->next != NULL) 
		{
			old_node = old_node->next;
			new_node->next = new Node<Linklist_entry>(old_node->entry);
			new_node = new_node->next;
		}
	}
}
template <class Linklist_entry>
void Linklist<Linklist_entry> :: operator=(const Linklist<Linklist_entry> &copy)
/* Post: The Linklist is assigned to copy a parameter */
{
	Linklist new_copy(copy);
	clear( );
	count = new_copy.count;
	head = new_copy.head;
	new_copy.count = 0;
	new_copy.head = NULL;
}

template <class Linklist_entry>
Linklist<Linklist_entry> :: ~Linklist( )
/* Post: The Linklist is empty: all entries have been removed. */
{
	clear( );
}
template <class Linklist_entry>
void Linklist<Linklist_entry>::clear( )
/* Post: The Linklist is cleared. */
{
	Node<Linklist_entry> *p, *q;
	for (p = head; p; p=q) 
	{
		q = p->next;
		delete p;
	}
	count = 0;
	head = NULL;
}
template <class Linklist_entry>
int Linklist<Linklist_entry>::size( )const
/* Post: The function returns the number of entries in the Linklist. */
{
	return count;
}
template <class Linklist_entry>
bool Linklist<Linklist_entry>::empty( )const
/* Post: The function returns true or false according as the Linklist is empty or not. */
{
	return count <= 0;
}
template <class Linklist_entry>
bool Linklist<Linklist_entry> :: full( ) const
/* Post: The function returns 1 or 0 according as the Linklist is full or not. */
{
	return false;
}
template <class Linklist_entry>
Error_code Linklist<Linklist_entry> :: replace(int position, const Linklist_entry &x)
/* Post: If 0<=position < n; where n is the number of entries in the Linklist, the function succeeds:
The entry in position is replaced by x, all other entries remain unchanged. Otherwise
the function fails with an error code of range_error. */
{
	Node<Linklist_entry> *current;
	if (position < 0||position>=count) return range_error;
	current = set_position(position);
	current->entry = x;
	return success;
}

template <class Linklist_entry>
Error_code Linklist<Linklist_entry> :: retrieve(int position, Linklist_entry &x)const
/* Post: If the Linklist is not full and 0  position < n; where n is the number of entries in the Linklist,
the function succeeds: The entry in position is copied to x. Otherwise the function fails
with an error code of range_error. */
{
	Node<Linklist_entry> *current;
	if (position < 0 || position>=count) return range_error;
	current=set_position(position);
	x=current->entry;
	return success;
}


template <class Linklist_entry>
Error_code Linklist<Linklist_entry> :: remove(int position, Linklist_entry &x)
/* Post: If 0<=position < n; where n is the number of entries in the Linklist, the function succeeds:
The entry in position is removed from the Linklist, and the entries in all later positions have
their position numbers decreased by 1. The parameter x records a copy of the entry
formerly in position. Otherwise the function fails with a diagnostic error code. */
{
	Node<Linklist_entry> *prior, *current;
	if (count == 0) return fail;
	if (position < 0 || position >= count) return range_error;
	if (position > 0) 
	{
		prior = set_position(position-1);
		current = prior->next;
		prior->next=current->next;
	}
	else {
		current = head;
		head = head->next;
	}
	x=current->entry;
	delete current;
	count--;
	return success;
}
template <class Linklist_entry>
void Linklist<Linklist_entry> :: traverse(void (*visit)(Linklist_entry &))
/* Post: The action specified by function (*visit) has been performed on every entry of the Linklist,
beginning at position 0 and doing each in turn. */
{
	Node<Linklist_entry> *q;
	for (q = head; q; q = q->next)
	(*visit)(q->entry);
}
template <class Linklist_entry>
Node<Linklist_entry>*Linklist<Linklist_entry>::set_position(int position) const
{
	Node<Linklist_entry>*q=head;
	for(int i=0;i<position;i++)q=q->next;
	return q;
}
template <class Linklist_entry>
Error_code Linklist<Linklist_entry>::insert(int position, const Linklist_entry &x)
{
	if(position<0||position>count)
		return rangeerror;
	Node<Linklist_entry>*new_node,*previous,*following;
	if(position>0)
	{
		previous=set_position(position-1);
		following=previous->next;
	
	}else following=head;
	new_node=new Node<Linklist_entry>(x,following);
	if(new_node==NULL)
		return overflow;
	if(position==0)
		head=new_node;
	else
		previous->next=new_node;
	count++;
	return success;
}