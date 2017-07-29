#pragma once
const int max_list=20;
enum Error_code{success,overflow,underflow,range_error};
template<class Sequence_List_entry>
class Sequence_List
{
public:
	Sequence_List(void);
	int size()const;
	bool full()const;
	bool empty()const;
	void clear();
	void traverse(void (*visit)(Sequence_List_entry &));
	Error_code retrieve(int position,Sequence_List_entry &x)const;
	Error_code replace(int position,const Sequence_List_entry &x);
	Error_code remove(int position,Sequence_List_entry &x);
	Error_code insert(int position,const Sequence_List_entry &x);
	~Sequence_List(void);
protected:
	int count;
	Sequence_List_entry entry[max_list];

};
