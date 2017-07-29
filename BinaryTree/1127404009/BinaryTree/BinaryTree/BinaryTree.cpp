// BinaryTree.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <string.h>
#include <iostream>
using namespace std;
#include "Queue.cpp"
#include "exqueue.cpp"
#include"Binary_tree.cpp"
#include"utility.h"

void help()
/* PRE: None.
POST: Instructions for the tree operations have been printed.
*/
{
	cout << "[S]ize [I]nsert [H]eight \n"
	"[C]ontents [L]eafs \n"
	"[P]reorder P[O]storder I[N]order \n[?]help [Q]uit\n" << endl;
}
char get_command()
/* PRE: None.
POST: A character command belonging to the set of legal commands for
the tree demonstration has been returned.
*/
{
	char c, d;
	help();
	cout << "Input command and press <Enter>:";
	while (1) 
	{
		do
		{
			cin.get(c);
		} while (c == '\n');
		do
		{
			cin.get(d);
		} while (d != '\n');
		c = tolower(c);
		if(strchr("cl?siponqh",c) != NULL)
			return c;
		cout << "Please enter a valid command or ? for help:" << endl;
		help();
	}
}
void write_ent(char &x)
{
	cout << x;
}
char get_char()
{
	char c;
	cin >>c;
	return c;
}
int do_command(char c, Binary_tree<char> &test_tree)
/* PRE: The tree has been created and command is a valid tree
operation.
POST: The command has been executed.
USES: All the functions that perform tree operations.
*/
{
	char x;
	switch (c) 
	{
	case '?': 
		help();
		break;
	case 's':
		cout << "The size of the tree is " << test_tree.size() << "\n";
		break;
	case 'i':
		cout << "Enter new character to insert:";
		x = get_char();
		test_tree.insert(x);
		break;
	case 'h':
		cout << "The height of the tree is " << test_tree.height() << "\n";
		break;
	case 'c':
		test_tree.bracketed_print();
		break;
	case 'l':
		cout << "The leaf count of the tree is "
		<< test_tree.leaf_count() << "\n";
		break;
	case 'p':
		test_tree.preorder(write_ent);
		cout << endl;
		break;
	case 'o':
		test_tree.postorder(write_ent);
		cout << endl;
		break;
	case 'n':
		test_tree.inorder(write_ent);
		cout << endl;
		break;
	case 'q':
		cout << "Tree demonstration finished.\n";
		return 0;
	}
	return 1;
}

int _tmain(int argc, _TCHAR* argv[])
{
	Binary_tree<char> test_tree;
	cout << "Program for a binary search tree of char entries."
	<< endl << endl;
	while (do_command(get_command(), test_tree));
}

