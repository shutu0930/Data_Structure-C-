// 排序算法的比较与实现2.cpp : 定义控制台应用程序的入口点。
//

// 排序算法的实现和比较.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Random.h"
#include <time.h>
#include "Timer.h"
#include "List.h"
#include "Key.h"
#include "Record.h"
 // sortable list specification
#include "Sortable_list.h"

void write_entry(Record &c)
{
	cout << ((Key) c).the_key() << " ";
}

void help()
{
	cout << "User options are:\n"
	<< "[H]elp [Q]uit (re)[F]ill list \n"
	<< "write [D]ata write sorted [O]utput \n"
	<< "[0] insertion sort --- Project 2P1d\n"
	<< "[1] selection sort --- Project 3P1\n"
	<< "[2] shell sort --- Project 4P2\n"
	<< "[3] quick sort\n"
	<< "[4] heap sort\n"
	<< "[5] insertion, with binary search --- project 2P2\n"
	<< "[6] scan sort --- Project 2P3\n"
	<< "[7] bubble sort --- Project 2P4\n"
	<< "[8] merge sort --- Project 7P4\n"
	<< "[9] hybrid sort, many small insert sorts --- Project 8P3b\n"
	<< "[b] hybrid sort, one insert sort --- Project 8P3b\n"
	<< endl;
}
void intro()
{
	cout << "Testing program for sorting methods for a contiguous list."
	<< endl;
	help ();
}
void main()
{
	List<Record> s; 
	List<Record> t = s; // help out a poor old compiler
	intro();
	int n;
	Random dice;
	Error_code report;
	Record target;
	Sortable_list<Record> the_list;
	Sortable_list<Record> copy_list;
	char command = ' ';
	while (command != 'q' && command != 'Q') 
	{
		cout << "Enter a command of H, Q, F, O, D, "<< "0, 1, 2, 3, 4, 5, 6, 7, 8, 9, b: "<< flush;
		cin >> command;
		switch (command) 
		{
			case 'h': 
			case 'H':help();break;
			case 'd': 
			case 'D':{
						cout << "\nUnsorted list \n";
						the_list.traverse(write_entry);
						cout << endl;
						break;
					 }
			case 'o': 
			case 'O':cout << "\nLast sorted list \n";
					copy_list.traverse(write_entry);
					cout << endl;
					break;
			
			case '0': case '1': case '2': case '3': case '4': case '5':
			case '6': case '7': case '8': case '9': case 'b': case 'B': {
					copy_list = the_list;
					Key::comparisons = 0;
					Key::assignments = 0;
					Timer clock;
					switch (command) 
					{
						case '0':cout << "Insertion Sort ";
								copy_list.insertion_sort();
								break;
						
						case '1':
								cout << "Selection Sort ";
								copy_list.selection_sort();
								break;
						case '2':
								cout << " Shell Sort ";
								copy_list.shell_sort();
								break;
						case '3':
								cout << " Quick Sort ";
								copy_list.quick_sort();
								break;
						case '4':
								cout << " Heap Sort ";
								copy_list.heap_sort();
								break;
						case '5':
								cout << " Insertion Sort with bianry search ";
								copy_list.insertion_binary();
								break;
						case '6':
								cout << " Scan Sort ";
								copy_list.scan_sort();
								break;
						/*case '7':
								cout << " Bubble Sort ";
								copy_list.bubble_sort();
								break;*/
						case '8':
								cout << " Merge Sort ";
								copy_list.merge_sort();
								break;
						case '9':
								cout << " Hybrid Sort ";
								cout << "At what size list do you want to switch method: "
								<< flush;
								cin >> n;
								copy_list.hybrid(n);
								break;
						case 'b': case 'B':
								cout << " Hybrid Sort ";
								cout << "At what size list do you want to switch method: "
								<< flush;
								cin >> n;
								copy_list.quick_sort(n);
								break;
						}
					cout << "Time: " << clock.elapsed_time() << " seconds.\n"
					<< "Comparisons: " << Key::comparisons << "\n"
					<< "Assignments: " << Key::assignments
					<< endl;
					}
					break;
			case 'f': case 'F':
					the_list.clear();
					cout << "How many list entries would you like? "
					<< flush;
					cin >> n;
					for (int i = 0; i < n; i++) 
					{
						target = dice.random_integer(0, 10 * n);
						report = the_list.insert(i,target);
						if (report == overflow)
						{
							cout << "Available list space filled up at " << i
							<< " entries." << endl;
							break;
						}
						if (report != success) i--;
					}
					break;
		} // end of outer switch statement
	} // end of outer while statement
}


