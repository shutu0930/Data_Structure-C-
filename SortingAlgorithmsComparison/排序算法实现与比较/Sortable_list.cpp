#include "Sortable_list.h"

template <class Record>
void Sortable_list<Record>::merge(int low, int high)
{
	Record *temp = new Record[high - low + 1];
	int index = 0;
	int index1 = low, mid = (low + high) / 2, index2 = mid + 1;
	while (index1 <= mid && index2 <= high) 
	{
		if (entry[index1] < entry[index2])
		temp[index++] = entry[index1++];
		else
		temp[index++] = entry[index2++];
	}
	while (index1 <= mid)
		temp[index++] = entry[index1++];
	while (index2 <= high)
		temp[index++] = entry[index2++];
	for (index = low; index <= high; index++)
		entry[index] = temp[index -low];
	delete []temp;
}
template <class Record>
void Sortable_list<Record>::recursive_merge_sort(int low, int high)
/*Post: The entries of the sortable list between index low and high have been rearranged so that
their keys are sorted into nondecreasing order.
Uses: The contiguous List implementation of Chapter 6.*/
{
	if (high > low) 
	{
		recursive_merge_sort(low, (high + low) / 2);
		recursive_merge_sort((high + low) / 2 + 1, high);
		merge(low, high);
	}
}
template <class Record>
void Sortable_list<Record>::merge_sort()
/*Post: The entries of the sortable list have been rearranged so that their keys are sorted into nondecreasing order.
Uses: The contiguous List implementation of Chapter 6.*/
{
	recursive_merge_sort(0, size() - 1);
}
template <class Record>
int Sortable_list<Record>::partition(int low, int high)
/*Pre: low and high are valid positions of the Sortable_list,
with low <= high.
Post: The center (or left center) entry in the range between indices low and high of the Sortable_list
has been chosen as a pivot. All entries of the Sortable_list between indices low and high, inclusive, have been
rearranged so that those with keys less than the pivot come before the pivot and the remaining entries come
after the pivot. The final position of the pivot is returned.
Uses: swap(int i, int j) (interchanges entries in positions i and j of a Sortable_list),the contiguous List implementation of ?list_ch?, and
methods for the class Record.*/
{
	Record pivot;
	int i, // used to scan through the list
	last_small; // position of the last key less than pivot
	swap(low, (low + high) / 2);
	pivot = entry[low]; // First entry is now pivot.
	last_small = low;
	for (i = low + 1; i <= high; i++)
	/*At the beginning of each iteration of this loop, we have the following conditions:
	If low < j <= last_small then entry[j].key < pivot.If last_small < j < i then entry[j].key >= pivot.*/
	if (entry[i] < pivot) 
	{
		last_small = last_small + 1;
		swap(last_small, i); // Move large entry to right, small to left.
	}
	swap(low, last_small); // Put the pivot into its proper position.
	return last_small;
}
template <class Record>
void Sortable_list<Record>::recursive_quick_sort(int low, int high)
/*Pre: low and high are valid positions in the Sortable_list.
Post: The entries of the Sortable_list have been rearranged so that their keys are sorted into nondecreasing order.
Uses: The contiguous List implementation of ?list_ch?,recursive_quick_sort, and partition.*/
{
	int pivot_position;
	if (low < high) 
	{ // Otherwise, no sorting is needed.
		pivot_position = partition(low, high);
		recursive_quick_sort(low, pivot_position - 1);
		recursive_quick_sort(pivot_position + 1, high);
	}
}

template <class Record>
void Sortable_list<Record>::quick_sort()
/*Post: The entries of the Sortable_list have been rearranged so that their keys are sorted into nondecreasing order.
Uses: The contiguous List implementation of ?list_ch?,recursive_quick_sort.*/
{
	recursive_quick_sort(0, count - 1);
}


template <class Record>
void Sortable_list<Record>::insert_heap(const Record &current,int low, int high)
/*Pre: The entries of the Sortable_list between indices low + 1 and high,inclusive, form a heap. The entry in position low will be discarded.
Post: The entry current has been inserted into the Sortable_list and the entries rearranged
so that the entries between indices low and high, inclusive,form a heap.
Uses: The class Record, and the contiguous List implementation of ?list_ch?.*/
{
	int large; // position of child of entry[low] with the larger key
	large = 2 * low + 1;// large is now the left child of low.
	while (large <= high) 
	{
		if (large < high && entry[large] < entry[large + 1])
		large++; // large is now the child of low with the largest key.
		if (current >= entry[large])
		break; // current belongs in position low.
		else { // Promote entry[large] and move down the tree.
			entry[low] = entry[large];
			low = large;
			large = 2 * low + 1;
		}
	}
	entry[low] = current;
}
template <class Record>
void Sortable_list<Record>::build_heap()
/*Post: The entries of the Sortable_list have been rearranged so that it becomes a heap.
Uses: The contiguous List implementation of ?list_ch?, and insert_heap.*/
{
	int low; // All entries beyond the position low form a heap.
	for (low = count / 2 - 1; low >= 0; low--) 
	{
		Record current = entry[low];
		insert_heap(current, low, count - 1);
	}
}
template <class Record>
void Sortable_list<Record>::heap_sort()
/*Post: The entries of the Sortable_list have been rearranged so that their keys are sorted into nondecreasing order.
Uses: The contiguous List implementation of ?list_ch?,build_heap, and insert_heap.*/
{
	Record current; // temporary storage for moving entries
	int last_unsorted; // Entries beyond last_unsorted have been sorted.
	build_heap(); // First phase: Turn the list into a heap.
	for (last_unsorted = count - 1; last_unsorted > 0; last_unsorted--) 
	{
		current = entry[last_unsorted]; // Extract last entry from the list.
		entry[last_unsorted] = entry[0]; // Move top of heap to the end
		insert_heap(current, 0, last_unsorted - 1); // Restore the heap
	}
}

template <class Record>
void Sortable_list<Record>::insertion_sort(int low,int high)
/*Post: The entries of the Sortable_list between low and high have been rearranged so that the keys in all the
entries are sorted into nondecreasing order.
Uses: Methods for the class Record; the contiguous List implementation of Chapter 6. */
{
	int first_unsorted; // position of first unsorted entry
	int position; // searches sorted part of list
	Record current; // holds the entry temporarily removed from list
	for (first_unsorted = low + 1; first_unsorted <= high; first_unsorted++)
	if (entry[first_unsorted] < entry[first_unsorted - 1]) 
	{
		position = first_unsorted;
		current = entry[first_unsorted];
		do {
			entry[position] = entry[position - 1];
			position--; // position is empty.
		} while (position > low && entry[position - 1] > current);
		entry[position] = current;
	}
}

template <class Record>
void Sortable_list<Record>::recursive_hybrid(int low, int high, int offset)
/*Pre: low and high are valid positions in the Sortable_list.
Post: The entries of the Sortable_list have been rearranged so that their keys are sorted into nondecreasing order.
Uses: The contiguous List implementation of ?list_ch?,recursive_quick_sort, and partition.*/
{
	int pivot_position;
	if (low + offset < high) 
	{ // Otherwise, no sorting is needed.
		pivot_position = partition(low, high);
		recursive_hybrid(low, pivot_position - 1, offset);
		recursive_hybrid(pivot_position + 1, high, offset);
	}
	else insertion_sort(low, high);
}
template <class Record>
void Sortable_list<Record>::hybrid(int offset)
/*
Post: The entries of the Sortable_list have been rearranged so that their keys are sorted into nondecreasing order.
Uses: The contiguous List implementation of Chapter 6,recursive_quick_sort.*/
{
	recursive_hybrid(0, count - 1, offset);
}
template <class Record>
void Sortable_list<Record>::recursive_quick_sort(int low, int high,int offset)
/*Pre: low and high are valid positions in the Sortable_list.
Post: The entries of the Sortable_list have been rearranged so that their keys are sorted into nondecreasing order.
Uses: The contiguous List implementation of ?list_ch?,recursive_quick_sort, and partition.*/
{
	int pivot_position;
	if (low + offset < high) 
	{ // Otherwise, no sorting is needed.
		pivot_position = partition(low, high);
		recursive_quick_sort(low, pivot_position - 1, offset);
		recursive_quick_sort(pivot_position + 1, high, offset);
	}
}
template <class Record>
void Sortable_list<Record>::quick_sort(int offset)
/*Post: The entries of the Sortable_list have been rearranged sothat their keys are sorted into nondecreasing order.
Uses: The contiguous List implementation of ?list_ch?,recursive_quick_sort.*/
{
	recursive_quick_sort(0, count - 1, offset);
	insertion_sort();
}

