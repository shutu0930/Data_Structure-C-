#include<iostream>
#include<limits>
#include<cmath>
#include<cstdlib>
#include<cstddef>
#include<fstream>
#include<cctype>
#include<ctime>
using namespace std;
//-----------------------------------------------------------------------------------------------
enum Error_code{success,fail,Range_error,underflow,overflow,fatal,
				not_present,duplicate_error,entry_inserted,
				entry_found,internal_error};