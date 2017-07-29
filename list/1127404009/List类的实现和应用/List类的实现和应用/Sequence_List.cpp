#include "Sequence_List.h"

template<class Sequence_List_entry>
Sequence_List<Sequence_List_entry>::Sequence_List(void)
/* Post: The List is initialized to be empty. */
{
	count = 0;
}

template<class Sequence_List_entry>
int Sequence_List<Sequence_List_entry>::size()const
{
	return count;
}

template<class Sequence_List_entry>
bool Sequence_List<Sequence_List_entry>::full() const
/* Post: The function returns true or false according as the List is full or not. */
{
	return count >= max_list;
}

template<class Sequence_List_entry>
bool Sequence_List<Sequence_List_entry>::empty() const
/* Post: The function returns true or false according as the List is empty or not. */
{
	return count <= 0;

}

template<class Sequence_List_entry>
void Sequence_List<Sequence_List_entry>::clear()
/* Post: The List is cleared. */
{
	count = 0;
}

template<class Sequence_List_entry>
Error_code Sequence_List<Sequence_List_entry> :: replace(int position, const Sequence_List_entry &x)
/* Post: If 0<=position < n; where n is the number of entries in the List, the function succeeds:
The entry in position is replaced by x, all other entries remain unchanged. Otherwise
the function fails with an error code of range_error. */
{
	if (position<0||position >=count) return range_error;
	entry[position]=x;
	return success;
}

template<class Sequence_List_entry>
Error_code Sequence_List<Sequence_List_entry> :: retrieve(int position, Sequence_List_entry &x) const
/* Post: If the List is not full and 0  position < n; where n is the number of entries in the List,
the function succeeds: The entry in position is copied to x. Otherwise the function fails
with an error code of range_error. */
{
	if (position < 0 || position >= count) return range_error;
	x = entry[position];
	return success;
}

template<class Sequence_List_entry>
Error_code Sequence_List<Sequence_List_entry> :: remove(int position, Sequence_List_entry &x)
/* Post: If 0<=position < n; where n is the number of entries in the List, the function succeeds:
The entry in position is removed from the List, and the entries in all later positions have
their position numbers decreased by 1. The parameter x records a copy of the entry
formerly in position. Otherwise the function fails with a diagnostic error code. */
{
	if (count == 0) return underflow;
	if (position < 0 || position >= count) return range_error;
	x=entry[position];
	count--;
	while (position<count) 
	{
		entry[position] = entry[position+1];
		position++;
	}
	return success;
}

template<class Sequence_List_entry>
Error_code Sequence_List<Sequence_List_entry>::insert(int position, const Sequence_List_entry &x)
{
	if(full())
		return overflow;
	if(position<0||position>count)
		return range_error;
	for(int i=count-1;i>=position;i--)
		entry[i+1]=entry[i];
	entry[position]=x;
	count++;
	return success;

}

template<class Sequence_List_entry>
void Sequence_List<Sequence_List_entry>::traverse(void (*visit)(Sequence_List_entry &))
{
	for(int i=0;i<count;i++)
		(*visit)(entry[i]);

}
