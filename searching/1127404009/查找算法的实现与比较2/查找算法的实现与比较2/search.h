//--------------------------------------------------------------------------------------------------
Error_code sequential_search(const List<Record> &the_list,const Key &target,int &position)
{
	int s=the_list.size();
	for(position=0;position<s;position++)
	{
		Record data;
		the_list.retrieve(position,data);
		if(data==target)return success;
	}
	return not_present;
}
//---------------------------------------------------------------------------------------------------
void print_out(char *comment, float t, int comp_ct, int searches)
{
	float average;
	cout << comment << " Search Statistics: " << endl;
	cout<<"Total numbers of key comparisons is "<<comp_ct<<endl;
	cout << " Time for " << searches << " searches was " << t << endl;
	average = (( float ) comp_ct) / (( float ) searches);
	cout << " Average number of comparisons per search was " << average<< endl;
}
//---------------------------------------------------------------------------------------------------
void test_search(int searches,List<Record>&the_list)
{
	int list_size=the_list.size();
	if(searches<=0||list_size<0)
	{
		cout<<"Exiting test:"<<endl
			<<"the number of searches must be positive"<<endl
			<<"the number of list entries must exceed 0."<<endl;
		return;
	}
	int i,target,found_at;
	Key::comparisons=0;
	Random number;
	Timer clock;
	for(i=0;i<searches;i++)
	{
		target=2*number.random_integer(0,list_size-1)+1;
		if(sequential_search(the_list,target,found_at)==not_present)
			cout<<"Error:Failed to find expected target:"<<target<<endl;
	}
	print_out("Successful",clock.elapsed_time(),Key::comparisons,searches);

	Key::comparisons=0;
	clock.reset();
	for(i=0;i<searches;i++)
	{
		target=2*number.random_integer(0,list_size);
		if(sequential_search(the_list,target,found_at)==success)
			cout<<"Error:Found unexpected target "<<target<<"at"<<found_at<<endl;
	}
	print_out("Unsuccessful",clock.elapsed_time(),Key::comparisons,searches);
}
//-------------------------------------------------------


/*
# include<iostream>
# include"Random.h"
# include"Timer.h"
# include"utility.h"
# include"Ord_list.h"
using namespace std;
*/

Error_code sequential_search(const Ordered_list &the_list,const Key &target,int &position)
{
	int s=the_list.size();
	for(position=0;position<s;position++)
	{
		Record data;
		the_list.retrieve(position,data);
		if(data==target)return success;
	}
	return not_present;
}
//-----------------------------------------------------------

//-------------------------------------------------------
void test_search(int searches, Ordered_list &the_list)
{
	int list_size = the_list.size();

	if (searches <= 0 || list_size < 0)
	{
		cout << " Exiting test: " << endl
		 	 << " The number of searches must be positive." << endl
			 << " The number of list entries must exceed 0." << endl;
		return;
	}

	int i, target, found_at;
	Key::comparisons = 0;
	Random number;
	Timer clock;

	for (i = 0; i < searches; i++)
	{
		target = 2 * number.random_integer(0, list_size - 1) + 1;
		if (sequential_search(the_list, target, found_at) == not_present)
			cout << "Error: Failed to find expected target " << target << endl;
	}

	print_out("Successful", clock.elapsed_time(), Key::comparisons, searches);
	//unsuccessful
	Key::comparisons = 0;
	clock.reset();

	for (i = 0; i < searches; i++) 
	{
		target = 2 * number.random_integer(0, list_size);
		if (sequential_search(the_list, target, found_at) == success)
			cout << "Error: Found unexpected target " << target
				 << " at " << found_at << endl;
	}

	print_out("Unsuccessful", clock.elapsed_time(),Key::comparisons, searches);
}
//---------------------------------------------------------
Error_code binary_search_1 (const Ordered_list &the_list,const Key &target, int &position)
{
	Record data;
	int bottom = 0, top = the_list.size() - 1;

	while (bottom < top) 
	{
		int mid = (bottom + top) / 2;
		the_list.retrieve(mid, data);
		if (data < target)
			bottom = mid + 1;
		else
			top = mid;
	}

	if (top < bottom) return not_present;

	else
	{
		position = bottom;
		the_list.retrieve(bottom, data);
		if (data == target) return success;
		else return not_present;
	}
}
//------------------------------------------------------------------------
Error_code binary_search_2(const Ordered_list &the_list,const Key &target, int &position)
{
	Record data;
	int bottom = 0, top = the_list.size() - 1;

	while (bottom <= top)
	{
		position = (bottom + top) / 2;
		the_list.retrieve(position, data);
		if (data == target) return success;
		if (data < target) bottom = position + 1;
		else top = position - 1;
	}
	return not_present;
}
//------------------------------------------------------------------------
void test_b1_search(int searches,Ordered_list &the_list)
{
	int list_size=the_list.size();

	if(searches<=0||list_size<0)
	{
		cout<<"Exiting test:"<<endl
			<<"the number of searches must be positive"<<endl
			<<"the number of list entries must exceed 0."<<endl;
		return;
	}

	int i,target,found_at;
	Random number;
	Key::comparisons = 0;
	Timer clock;

	for (i = 0; i < searches; i++) 
	{
		target = 2 * number.random_integer(0, list_size - 1) + 1;
		if (binary_search_1(the_list, target, found_at) == not_present)
			cout << "Error: Failed to find expected target " << target<< endl;
	}

	print_out("Successful", clock.elapsed_time(),Key::comparisons, searches);
	//Unsuccessful:
	Key::comparisons = 0;
	clock.reset();
	for (i = 0; i < searches; i++) 
	{
		target = 2 * number.random_integer(0, list_size - 1);
		if (binary_search_1(the_list, target, found_at) == success)
			cout << "Error: Found unexpected target " << target	<< " at " << found_at << endl;
	}
	print_out("Unsuccessful", clock.elapsed_time(), Key::comparisons,searches);
}
//------------------------------------------------------------------------
void test_b2_search(int searches,Ordered_list &the_list)
{
	int list_size=the_list.size();

	if(searches<=0||list_size<0)
	{
		cout<<"Exiting test:"<<endl
			<<"the number of searches must be positive"<<endl
			<<"the number of list entries must exceed 0."<<endl;
		return;
	}

	int i,target,found_at;
	Random number;
	Key::comparisons = 0;
	Timer clock;

	for (i = 0; i < searches; i++) 
	{
		target = 2 * number.random_integer(0, list_size - 1) + 1;
		if (binary_search_2(the_list, target, found_at) == not_present)
			cout << "Error: Failed to find expected target " << target<< endl;
	}
	print_out("Successful", clock.elapsed_time(),Key::comparisons, searches);
	//Unsuccessful
	Key::comparisons = 0;
	clock.reset();
	for (i = 0; i < searches; i++) 
	{
		target = 2 * number.random_integer(0, list_size);
		if (binary_search_2(the_list, target, found_at) == success)
			cout << "Error: Found unexpected target " << target	<< " at " << found_at << endl;
	}
	print_out("Unsuccessful", clock.elapsed_time(), Key::comparisons,searches);
}