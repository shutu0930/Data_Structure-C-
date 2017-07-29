#include "Chain_List.h"

template <class Chain_List_entry>
Chain_List<Chain_List_entry> :: Chain_List( )
/* Post: The Chain_List is initialized to be empty. */
{
	count = 0;
	head = NULL;
}

template <class Chain_List_entry>
Chain_List<Chain_List_entry> :: Chain_List(const Chain_List<Chain_List_entry> &copy)
/* Post: The Chain_List is initialized to copy the parameter copy. */
{
	count=copy.count;
	Node<Chain_List_entry> *new_node, *old_node = copy.head;
	if (old_node == NULL) head = NULL;
	else 
	{
		new_node = head = new Node<Chain_List_entry>(old_node->entry);
		while (old_node->next != NULL) 
		{
			old_node = old_node->next;
			new_node->next = new Node<Chain_List_entry>(old_node->entry);
			new_node = new_node->next;
		}
	}
}
template <class Chain_List_entry>
void Chain_List<Chain_List_entry> :: operator=(const Chain_List<Chain_List_entry> &copy)
/* Post: The Chain_List is assigned to copy a parameter */
{
	Chain_List new_copy(copy);
	clear( );
	count = new_copy.count;
	head = new_copy.head;
	new_copy.count = 0;
	new_copy.head = NULL;
}

template <class Chain_List_entry>
Chain_List<Chain_List_entry> :: ~Chain_List( )
/* Post: The Chain_List is empty: all entries have been removed. */
{
	clear( );
}
template <class Chain_List_entry>
void Chain_List<Chain_List_entry>::clear( )
/* Post: The Chain_List is cleared. */
{
	Node<Chain_List_entry> *p, *q;
	for (p = head; p; p=q) 
	{
		q = p->next;
		delete p;
	}
	count = 0;
	head = NULL;
}
template <class Chain_List_entry>
int Chain_List<Chain_List_entry>::size( )const
/* Post: The function returns the number of entries in the Chain_List. */
{
	return count;
}
template <class Chain_List_entry>
bool Chain_List<Chain_List_entry>::empty( )const
/* Post: The function returns true or false according as the Chain_List is empty or not. */
{
	return count <= 0;
}
template <class Chain_List_entry>
bool Chain_List<Chain_List_entry> :: full( ) const
/* Post: The function returns 1 or 0 according as the Chain_List is full or not. */
{
	return false;
}
template <class Chain_List_entry>
Error_code Chain_List<Chain_List_entry> :: replace(int position, const Chain_List_entry &x)
/* Post: If 0<=position < n; where n is the number of entries in the Chain_List, the function succeeds:
The entry in position is replaced by x, all other entries remain unchanged. Otherwise
the function fails with an error code of range_error. */
{
	Node<Chain_List_entry> *current;
	if (position < 0||position>=count) return range_error;
	current = set_position(position);
	current->entry = x;
	return success;
}

template <class Chain_List_entry>
Error_code Chain_List<Chain_List_entry> :: retrieve(int position, Chain_List_entry &x)const
/* Post: If the Chain_List is not full and 0  position < n; where n is the number of entries in the Chain_List,
the function succeeds: The entry in position is copied to x. Otherwise the function fails
with an error code of range_error. */
{
	Node<Chain_List_entry> *current;
	if (position < 0 || position>=count) return range_error;
	current=set_position(position);
	x=current->entry;
	return success;
}


template <class Chain_List_entry>
Error_code Chain_List<Chain_List_entry> :: remove(int position, Chain_List_entry &x)
/* Post: If 0<=position < n; where n is the number of entries in the Chain_List, the function succeeds:
The entry in position is removed from the Chain_List, and the entries in all later positions have
their position numbers decreased by 1. The parameter x records a copy of the entry
formerly in position. Otherwise the function fails with a diagnostic error code. */
{
	Node<Chain_List_entry> *prior, *current;
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
template <class Chain_List_entry>
void Chain_List<Chain_List_entry> :: traverse(void (*visit)(Chain_List_entry &))
/* Post: The action specified by function (*visit) has been performed on every entry of the Chain_List,
beginning at position 0 and doing each in turn. */
{
	Node<Chain_List_entry> *q;
	for (q = head; q; q = q->next)
	(*visit)(q->entry);
}
template <class Chain_List_entry>
Node<Chain_List_entry>*Chain_List<Chain_List_entry>::set_position(int position) const
{
	Node<Chain_List_entry>*q=head;
	for(int i=0;i<position;i++)q=q->next;
	return q;
}
template <class Chain_List_entry>
Error_code Chain_List<Chain_List_entry>::insert(int position, const Chain_List_entry &x)
{
	if(position<0||position>count)
		return range_error;
	Node<Chain_List_entry>*new_node,*previous,*following;
	if(position>0)
	{
		
	
	}

}