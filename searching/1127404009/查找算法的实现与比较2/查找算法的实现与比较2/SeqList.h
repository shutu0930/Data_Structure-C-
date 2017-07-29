#pragma once
const int max_list=20;
#include "stdafx.h"
template<class SeqList_entry>
class SeqList
{
public:
	SeqList(void);
	int size()const;
	bool full()const;
	bool empty()const;
	void clear();
	void traverse(void (*visit)(SeqList_entry &));
	Error_code retrieve(int position,SeqList_entry &x)const;
	Error_code replace(int position,const SeqList_entry &x);
	Error_code remove(int position,SeqList_entry &x);
	Error_code insert(int position,const SeqList_entry &x);
	~SeqList(void);
protected:
	int count;
	SeqList_entry entry[max_list];

};
