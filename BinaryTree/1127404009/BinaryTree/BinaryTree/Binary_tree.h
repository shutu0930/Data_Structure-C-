#pragma once
#include"Binary_node.h"
#include"utility.h"
#include"exqueue.h"
template <class Entry>
class Binary_tree
{
public:
	// Add methods here.
	void double_traverse(void (*visit)(Entry &));
	void bracketed_print();
	void interchange();
	void level_traverse(void (*visit)(Entry &));
	int width();
	int leaf_count() const;

	Binary_tree();
	bool empty() const;
	void preorder(void (*visit)(Entry &));
	void inorder(void (*visit)(Entry &));
	void postorder(void (*visit)(Entry &));
	void recursive_inorder(Binary_node<Entry> *, void (*visit)(Entry &));
	void recursive_preorder(Binary_node<Entry> *, void (*visit)(Entry &));
	void recursive_postorder(Binary_node<Entry> *, void (*visit)(Entry &));

	Error_code remove(Entry &);
	int size() const;
	void clear();
	int height() const;
	void insert(const Entry &);
	Binary_tree (const Binary_tree<Entry> &original);
	Binary_tree & operator =(const Binary_tree<Entry> &original);
	~Binary_tree();
	void recursive_double_traverse(Binary_node<Entry> *sub_root, void (*visit)(Entry &));
	void recursive_bracketed(Binary_node<Entry> *sub_root);
	void recursive_interchange(Binary_node<Entry> *sub_root);
	int recursive_leaf_count(Binary_node<Entry> *sub_root) const;
	void swap();

	void recursive_insert(Binary_node<Entry> *&sub_root, const Entry &x);
	int recursive_size(Binary_node<Entry> *sub_root) const;
	int recursive_height(Binary_node<Entry> *sub_root) const;
	void recursive_clear(Binary_node<Entry> *&sub_root);
	Binary_node<Entry> *recursive_copy(Binary_node<Entry> *sub_root);
	void recursive_swap(Binary_node<Entry> *sub_root);
	Binary_node<Entry> *&find_node(Binary_node<Entry> *&,const Entry &) const;
	Error_code remove_root(Binary_node<Entry> *&sub_root);
protected:
	// Add auxiliary function prototypes here.
	Binary_node<Entry> *root;
};