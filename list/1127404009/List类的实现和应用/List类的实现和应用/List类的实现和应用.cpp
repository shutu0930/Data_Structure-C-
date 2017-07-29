// SeqList类的实现和应用.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "SeqList.h"
#include "SeqList.cpp"
#include "Linklist.h"
#include "Linklist.cpp"
#include "DoubleLinkList.h"
#include "DoubleLinkList.cpp"
#include <iostream>
using namespace std;
void write_entry(char &c)
{
	cout<<c;
}
void main()
{
	int sg;
	cout<<"=================List类的实现与应用=================="<<"\n"
		<<"1.Test SeqList"<<"\t\t"<<"2.Test LinkList"<<"\n"
		<<"3.Test DoubleLinkList"<<endl;
	cout<<"Please input an order:";
	cin>>sg;
	switch(sg)
	{
	case 3:{
			cout<<"==============================================================="<<endl;
			char x;
			DoubleLinklist<char> c_list; // a SeqList of characters, initialized empty
			cout << "DoubleLinklist is empty, it has " << c_list.size() << " items.\n";
			cout << "Enter characters and the program adds them to the DoubleLinklist.\n";
			cout << "Use Enter key (newline) to terminate the input.\n";
			cout << "When DoubleLinklist Size is 3, the element will be inserted at the ";
			cout << "front of the DoubleLinklist.\n The others will appear at the back.\n";
			while (!c_list.full() && (x = cin.get()) != '\n')
			if (c_list.size() == 3) c_list.insert(0, x);
			else c_list.insert(c_list.size(), x);
			cout << "The DoubleLinklist has " << c_list.size() << " items.\n";
			cout << "The function c_list.full(), got " << c_list.full();
			if (c_list.full()) cout << " because the DoubleLinklist is full.\n";
			else cout << " because the DoubleLinklist is NOT full.\n";
			cout << "c_list.empty(), expecting 0, got " << c_list.empty() << ".\n";
			cout << "c_list.traverse(write_entry) output: ";
			c_list.traverse(write_entry);
			cout << "\n";
			c_list.clear();
			cout << "Cleared the DoubleLinklist, printing its contents:\n";
			c_list.traverse(write_entry);
			cout << "\n";
			cout << "Enter characters and the program adds them to the DoubleLinklist.\n";
			cout << "Use Enter key (newline) to terminate the input.\n";
			cout << "When DoubleLinklist Size is < 3, the element will be inserted at the ";
			cout << "front of the DoubleLinklist.\n The others will appear at the back.\n";
			while (!c_list.full() && (x = cin.get()) != '\n')
			if (c_list.size() < 3) c_list.insert(0, x);
			else c_list.insert(c_list.size(), x);
			c_list.traverse(write_entry);
			cout << "\n";
			break;
		   }
		   
	case 2:{
			cout<<"==============================================================="<<endl;
			char y;
			Linklist<char> b_list; // a SeqList of characters, initialized empty
			cout << "LinkList is empty, it has " << b_list.size() << " items.\n";
			cout << "Enter characters and the program adds them to the LinkList.\n";
			cout << "Use Enter key (newline) to terminate the input.\n";
			cout << "When LinkList Size is 3, the element will be inserted at the ";
			cout << "front of the LinkList.\n The others will appear at the back.\n";
			while (!b_list.full() && (y = cin.get()) != '\n')
			if (b_list.size() == 3) b_list.insert(0, y);
			else b_list.insert(b_list.size(), y);
			cout << "The LinkList has " << b_list.size() << " items.\n";
			cout << "The function b_list.full(), got " << b_list.full();
			if (b_list.full()) cout << " because the LinkList is full.\n";
			else cout << " because the DoubleLinklist is NOT full.\n";
			cout << "b_list.empty(), expecting 0, got " << b_list.empty() << ".\n";
			cout << "b_list.traverse(write_entry) output: ";
			b_list.traverse(write_entry);
			cout << "\n";
			b_list.clear();
			cout << "Cleared the LinkList, printing its contents:\n";
			b_list.traverse(write_entry);
			cout << "\n";
			cout << "Enter characters and the program adds them to the LinkList.\n";
			cout << "Use Enter key (newline) to terminate the input.\n";
			cout << "When LinkList Size is < 3, the element will be inserted at the ";
			cout << "front of the LinkList.\n The others will appear at the back.\n";
			while (!b_list.full() && (y = cin.get()) != '\n')
			if (b_list.size() < 3) b_list.insert(0, y);
			else b_list.insert(b_list.size(), y);
			b_list.traverse(write_entry);
			cout << "\n";
		   break;
		   }
	
	case 1:{
			cout<<"==============================================================="<<endl;
			int i=0;
			int position;
			char z;
			SeqList<char> a_list; // a SeqList of characters, initialized empty
			cout << "SeqList is empty, it has " << a_list.size() << " items.\n";
			cout << "Enter characters and the program adds them to the SeqList.\n";
			cout << "Use Enter key (newline) to terminate the input.\n";
			cout << "When SeqList Size is 3, the element will be inserted at the ";
			cout << "front of the SeqList.\n The others will appear at the back.\n";
			cin.get();
			while (a_list.full()!=true&&(z=cin.get())!='\n')
			{
				a_list.insert(i++, z);
				
			}
				
			cout << "The SeqList has " << a_list.size() << " items.\n";
			cout << "The function a_list.full(), got " << a_list.full();
			if (a_list.full()) cout << " because the SeqList is full.\n";
			else cout << " because the SeqList is NOT full.\n";
			cout << "a_list.empty(), expecting 0, got " << a_list.empty() << ".\n";
			cout << "a_list.traverse(write_entry) output: ";
			
			a_list.traverse(write_entry);
			cout << "\n";
			a_list.clear();
			cout << "Cleared the SeqList, printing its contents:\n";
			a_list.traverse(write_entry);
			cout << "\n";
			cout << "Enter a character and the program insert it to the SeqList.\n";
			cin>>z;
			cout << "Use Enter key (newline) to terminate the input.\n";
			cout<<"Enter the position it will be inserted:\n";
			cin>>position;
			while ((a_list.full()!=true) && position>=0)
				a_list.insert(position, z);
			a_list.traverse(write_entry);
			cout << "\n";
			break;
		   }
	default:break;
	}
	
}

