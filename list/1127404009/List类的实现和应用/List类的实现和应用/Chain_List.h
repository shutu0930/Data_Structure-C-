#pragma once
enum Error_code{success,overflow,underflow,range_error};
template<class Node_entry>
struct Node
{
	Node_entry entry;
	Node<Node_entry>*next;
	Node();
	Node(Node_entry,Node<Node_entry>*link=NULL);
};

template<class Chain_List_entry>
class Chain_List
{
public:
	Chain_List(void);
	Chain_List(const Chain_List<Chain_List_entry>&copy);
	void operator=(const Chain_List<Chain_List_entry>&copy);
	int size()const;
	bool full()const;
	bool empty()const;
	void clear();
	void traverse(void (*visit)(Chain_List_entry &));
	Error_code retrieve(int position,Chain_List_entry &x)const;
	Error_code replace(int position,const Chain_List_entry &x);
	Error_code remove(int position,Chain_List_entry &x);
	Error_code insert(int position,const Chain_List_entry &x);
	~Chain_List(void);
protected:
	int count;
	Node<Chain_List_entry>*head;
	Node<Chain_List_entry>*set_position(int position)const;

	

};