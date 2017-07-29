#pragma once
#include "Record.h"
#include "List.h"
template <class Record>
class Sortable_list: public List<Record>{
public:
	void insertion_sort();
	void insertion_binary();
	void selection_sort();
	void shell_sort();
	void quick_sort();
	void heap_sort();
	void scan_sort();
	void bubble_sort();
private:
	void sort_interval(int start, int increment);
	void swap(int low, int high);
	int max_key(int low, int high);
	int partition(int low, int high);
	void recursive_quick_sort(int low, int high);
	void insert_heap(const Record &current, int low, int high);
	void build_heap();
public:
	void merge_sort(); // Section 7, Project P4
private:
	void merge(int low, int high);
	void recursive_merge_sort(int low, int high);
public:
	void quick_sort(int offset); // Section 8, Project P3b
private:
	void recursive_quick_sort(int low, int high, int offset);
public:
	void hybrid(int offset); // Section 8, Project P3a
private:
	void recursive_hybrid(int low, int high, int offset);
	void insertion_sort(int low,int high);
};

