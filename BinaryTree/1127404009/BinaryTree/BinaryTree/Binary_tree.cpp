#include "StdAfx.h"
#include "Binary_tree.h"

template <class Entry>
Binary_tree<Entry>::Binary_tree()
/*
Post: An empty binary tree has been created.
*/
{
	root = NULL;
}

template <class Entry>
bool Binary_tree<Entry>::empty() const
/*
Post: A result of true is returned if the binary tree is empty.
Otherwise, false is returned.
*/
{
	return root == NULL;
}

template <class Entry>
void Binary_tree<Entry>::inorder(void (*visit)(Entry &))
/*
Post: The tree has been been traversed in infix
order sequence.
Uses: The function recursive_inorder
*/
{
	recursive_inorder(root, visit);
}
template <class Entry>
void Binary_tree<Entry>::preorder(void (*visit)(Entry &))
/*
Post: The binary tree is traversed in prefix order,
applying the operation *visit at each entry.
*/
{
	recursive_preorder(root, visit);
}
template <class Entry>
void Binary_tree<Entry>::postorder(void (*visit)(Entry &))
/*
Post: The binary tree is traversed in postfix order,
applying the operation *visit at each entry.
*/
{
	recursive_postorder(root, visit);
}
template <class Entry>
void Binary_tree<Entry>::recursive_inorder(Binary_node<Entry> *sub_root,
void (*visit)(Entry &))
/*
Pre: sub_root is either NULL or points to a subtree of
the Binary_tree.
Post: The subtree has been been traversed in inorder sequence.
Uses: The function recursive_inorder recursively
*/
{
	if (sub_root != NULL) 
	{
		recursive_inorder(sub_root->left, visit);
		(*visit)(sub_root->data);
		recursive_inorder(sub_root->right, visit);
	}
}
template <class Entry>
void Binary_tree<Entry>::recursive_preorder(Binary_node<Entry> *sub_root,void (*visit)(Entry &))
/*
Pre: sub_root is either NULL or points to a subtree of
the Binary_tree.
Post: The subtree has been been traversed in preorder sequence.
Uses: The function recursive_preorder recursively
*/
{
	if (sub_root != NULL) 
	{
		(*visit)(sub_root->data);
		recursive_preorder(sub_root->left, visit);
		recursive_preorder(sub_root->right, visit);
	}
}
template <class Entry>
void Binary_tree<Entry>::recursive_postorder(Binary_node<Entry> *sub_root,
void (*visit)(Entry &))
/*
Pre: sub_root is either NULL or points to a subtree of
the Binary_tree.
Post: The subtree has been been traversed in postorder sequence.
Uses: The function recursive_postorder recursively
*/
{
	if (sub_root != NULL)
	{
		recursive_postorder(sub_root->left, visit);
		recursive_postorder(sub_root->right, visit);
		(*visit)(sub_root->data);
	}
}
template <class Entry>
void Binary_tree<Entry>::recursive_insert(Binary_node<Entry> *&sub_root,
const Entry &x)
/*
Pre: sub_root is either NULL or points to a subtree of
the Binary_tree.
Post: The Entry has been inserted into the subtree in such a way
that the properties of a binary search tree have been preserved.
Uses: The functions recursive_insert, recursive_height
*/
{
	if (sub_root == NULL) 
		sub_root = new Binary_node<Entry>(x);
	else
		if (recursive_height(sub_root->right) < recursive_height(sub_root->left))
			recursive_insert(sub_root->right, x);
		else
			recursive_insert(sub_root->left, x);
}
template <class Entry>
int Binary_tree<Entry>::recursive_size(Binary_node<Entry> *sub_root) const
/*
Post: The number of entries in the subtree rooted at
sub_root is returned.
*/
{
	if (sub_root == NULL) return 0;
	return 1 + recursive_size(sub_root->left) + recursive_size(sub_root->right);
}
template <class Entry>
int Binary_tree<Entry>::recursive_height(Binary_node<Entry> *sub_root) const
/*
Post: The height of the subtree rooted at
sub_root is returned.
*/
{
	if (sub_root == NULL) 
		return 0;
	int l = recursive_height(sub_root->left);
	int r = recursive_height(sub_root->right);
	if (l > r) 
		return 1 + l;
	else
		return 1 + r;
}
template <class Entry>
void Binary_tree<Entry>::recursive_clear(Binary_node<Entry> *&sub_root)
/*
Post: The subtree rooted at
sub_root is cleared.
*/
{
	Binary_node<Entry> *temp = sub_root;
	if (sub_root == NULL) 
		return;
	recursive_clear(sub_root->left);
	recursive_clear(sub_root->right);
	sub_root = NULL;
	delete temp;
}
template <class Entry>
Binary_node<Entry> *Binary_tree<Entry>::recursive_copy(
Binary_node<Entry> *sub_root)
/*
Post: The subtree rooted at
sub_root is copied, and a pointer to
the root of the new copy is returned.
*/
{
	if (sub_root == NULL) 
		return NULL;
	Binary_node<Entry> *temp = new Binary_node<Entry>(sub_root->data);
	temp->left = recursive_copy(sub_root->left);
	temp->right = recursive_copy(sub_root->right);
	return temp;
}
template <class Entry>
void Binary_tree<Entry>::recursive_swap(Binary_node<Entry> *sub_root)
/*
Post: In the subtree rooted at
sub_root all pairs of left and right
links are swapped.
*/
{
	if (sub_root == NULL)
		return;
	Binary_node<Entry> *temp = sub_root->left;
	sub_root->left = sub_root->right;
	sub_root->right = temp;
	recursive_swap(sub_root->left);
	recursive_swap(sub_root->right);
}
template <class Entry>
Binary_node<Entry> *&Binary_tree<Entry>::find_node(
Binary_node<Entry> *&sub_root, const Entry &x) const
/*
Post: If the subtree rooted at
sub_root contains x as a entry, a pointer
to the subtree node storing x is returned.
Otherwise NULL is returned.
*/
{
	if (sub_root == NULL || sub_root->data == x) 
		return sub_root;
	else 
	{
		Binary_node<Entry> *&temp = find_node(sub_root->left, x);
		if (temp != NULL) 
			return temp;
		else 
			return find_node(sub_root->right, x);
	}
}
template <class Entry>
Error_code Binary_tree<Entry>::remove_root(Binary_node<Entry> *&sub_root)
/*
Pre: sub_root is either NULL or points to a subtree of
the Binary_tree
Post: If sub_root is NULL, a code of not_present is returned.
Otherwise the root of the subtree is removed in such a way
that the properties of a binary search tree are preserved.
The parameter sub_root is reset as
the root of the modified subtree and
success is returned.
*/
{
	if (sub_root == NULL)
		return not_present;
	Binary_node<Entry> *to_delete = sub_root;
	// Remember node to delete at end.
	if (sub_root->right == NULL)
		sub_root = sub_root->left;
	else if (sub_root->left == NULL)
		sub_root = sub_root->right;
	else 
	{ // Neither subtree is empty
		to_delete = sub_root->left; // Move left to find predecessor
		Binary_node<Entry> *parent = sub_root; // parent of to_delete
		while (to_delete->right != NULL)
		{ //to_delete is not the predecessor
			parent = to_delete;
			to_delete = to_delete->right;
		}
		sub_root->data = to_delete->data; // Move from to_delete to root
		if (parent == sub_root) sub_root->left = to_delete->left;
		else parent->right = to_delete->left;
	}
	delete to_delete; // Remove to_delete from tree
	return success;
}
template <class Entry>
Error_code Binary_tree<Entry>::remove(Entry &x)
/*
Post: An entry of the binary tree with Key matching x is
removed. If there is no such entry a code of not_present
is returned.
*/
{
	Binary_node<Entry> *&found = find_node(root, x);
	return remove_root(found);
}
template <class Entry>
void Binary_tree<Entry>::insert(const Entry &x)
/*
Post: The Entry x is added to the binary tree.
*/
{
	recursive_insert(root, x);
}

template <class Entry>
int Binary_tree<Entry>::size() const
/*
Post: The number of entries in the binary tree is returned.
*/
{
	return recursive_size(root);
}
template <class Entry>
int Binary_tree<Entry>::height() const
/*
Post: The height of the binary tree is returned.
*/
{
	return recursive_height(root);
}
template <class Entry>
void Binary_tree<Entry>::clear()
/*
Post: All entries of the binary tree are removed.
*/
{
	recursive_clear(root);
}
template <class Entry>
Binary_tree<Entry>::~Binary_tree()
/*
Post: All entries of the binary tree are removed.
All dynamically allocated memory in the structure
is deleted.
*/
{
	clear();
}
template <class Entry>
Binary_tree<Entry>::Binary_tree (const Binary_tree<Entry> &original)
/*
Post: A new binary tree is initialized to copy original.
*/
{
	root = recursive_copy(original.root);
}
template <class Entry>
Binary_tree<Entry> &Binary_tree<Entry>::operator =(const Binary_tree<Entry> &original)
/*
Post: The binary tree is reset to copy original.
*/
{
	Binary_tree<Entry> new_copy(original);
	clear();
	root = new_copy.root;
	new_copy.root = NULL;
	return *this;
}
template <class Entry>
void Binary_tree<Entry>::swap()
/*
Post: All left and right subtrees are switched
in the binary tree.
*/
{
	recursive_swap(root);
}
template <class Entry>
void Binary_tree<Entry>::recursive_double_traverse
(Binary_node<Entry> *sub_root, void (*visit)(Entry &))
/*
Post: The subtree rooted at sub_root is
doubly traversed.
*/
{
	if (sub_root != NULL)
	{
		(*visit)(sub_root->data);
		recursive_double_traverse(sub_root->left, visit);
		(*visit)(sub_root->data);
		recursive_double_traverse(sub_root->right, visit);
	}
}
template <class Entry>
void Binary_tree<Entry>::double_traverse(void (*visit)(Entry &))
/*
Post: The tree is doubly traversed.
*/
{
	recursive_double_traverse(root, visit);
}
template <class Entry>
void Binary_tree<Entry>::recursive_bracketed(Binary_node<Entry> *sub_root)
/*
Post: The subtree rooted at sub_root is
printed with brackets.
*/
{
	if (sub_root != NULL) 
	{
		if (sub_root->left == NULL && sub_root->right == NULL)
			cout << sub_root->data;
		else
		{
			cout << "(" << sub_root->data << ":";
			recursive_bracketed(sub_root->left);
			cout << ",";
			recursive_bracketed(sub_root->right);
			cout << ")";
		}
	}
}
template <class Entry>
void Binary_tree<Entry>::bracketed_print()
/*
Post: The tree is printed with brackets.
*/
{
	recursive_bracketed(root);
	cout << endl;
}
template <class Entry>
void Binary_tree<Entry>::recursive_interchange(Binary_node<Entry> *sub_root)
/*
Post: In the subtree rooted at
sub_root all pairs of left and right
links are swapped.
*/
{
	if (sub_root != NULL)
	{
		Binary_node<Entry> *tmp = sub_root->left;
		sub_root->left = sub_root->right;
		sub_root->right = tmp;
		recursive_interchange(sub_root->left);
		recursive_interchange(sub_root->right);
	}
}
template <class Entry>
void Binary_tree<Entry>::interchange()
/*
Post: In the tree all pairs of left and right
links are swapped round.
*/
{
	recursive_interchange(root);
}
template <class Entry>
void Binary_tree<Entry>::level_traverse(void (*visit)(Entry &))
/*
Post: The tree is traversed level by level,
starting from the top. The operation
*visit is applied to all entries.
*/
{
	Binary_node<Entry> *sub_root;
	if (root != NULL)
	{
		Queue<Binary_node<Entry> *> waiting_nodes;
		waiting_nodes.append(root);
		do 
		{
			waiting_nodes.retrieve(sub_root);
			(*visit)(sub_root->data);
			if (sub_root->left) waiting_nodes.append(sub_root->left);
				if (sub_root->right) waiting_nodes.append(sub_root->right);
					waiting_nodes.serve();
		} while (!waiting_nodes.empty());
	}
}
template <class Entry>
int Binary_tree<Entry>::width()
/*
Post: The width of the tree is returned.
*/
{
	if (root == NULL) return 0;
	Extended_queue<Binary_node<Entry> *> current_level;
	current_level.append(root);
	int max_level = 0;
	while (current_level.size() != 0) 
	{
		if (current_level.size() > max_level)
		max_level = current_level.size();
		Extended_queue<Binary_node<Entry> *> next_level;
		do 
		{
			Binary_node<Entry> *sub_root;
			current_level.retrieve(sub_root);
			if (sub_root->left) next_level.append(sub_root->left);
			if (sub_root->right) next_level.append(sub_root->right);
			current_level.serve();
		} while (!current_level.empty());
		current_level = next_level;
	}
	return max_level;
}
template <class Entry>
int Binary_tree<Entry>::recursive_leaf_count(Binary_node<Entry> *sub_root) const
/*
Post: The number of leaves in the subtree
rooted at sub_root is returned.
*/
{
	if (sub_root == NULL) return 0;
	if (sub_root->left == NULL && sub_root->right == NULL) 
		return 1;
	return recursive_leaf_count(sub_root->left)+ recursive_leaf_count(sub_root->right);
}
template <class Entry>
int Binary_tree<Entry>::leaf_count() const
/*
Post: The number of leaves in the tree is returned.
*/
{
	return recursive_leaf_count(root);
}