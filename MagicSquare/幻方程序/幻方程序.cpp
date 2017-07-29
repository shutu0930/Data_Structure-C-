// 幻方程序.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "../../c/utility.h"
#include "../../c/utility.cpp"
#include "square.h"
#include "square.cpp"
int main()
{
cout << "Magic Square Program" << endl << endl;
cout << "Enter a square of integers:" << endl;
Square s;
s.read();
if (s.is_magic()) cout << "That square is magic!" << endl;
else cout << "That square is not magic." << endl;
cout << endl << endl << "Generating a 5 x 5 magic square:" << endl;
cout << "--------------------------------" << endl << endl;
s.generate(5);
s.print();
cout << endl << endl << "Generating a 7 x 7 magic square:" << endl;
cout << "--------------------------------" << endl << endl;
s.generate(7);
s.print();
}
const int max_size = 9;
class Square {
public:
void read();
void print();
bool is_magic();
void generate(int n);
private:
int sum_row(int i);
int sum_col(int i);
int sum_maindiag();
int sum_other();
int size;
int grid[max_size][max_size];
};
void Square::generate(int n)
/* Pre: n is odd
Post: a magic n x n square is generated */
{
if (n % 2 == 0) {
cout << "Error: the side must be odd:" << endl;
}
size = n;
if (size < 0 || size > 9) {
cout << "Error: Side Size --- Out of range." << endl;
return;
}
for (int i = 0; i < size; i++)
for (int j = 0; j < size; j++)
grid[i][j] = 0;
//int count = 0;
//int row = n - 2;
//int col = n / 2 - 1;
//while (count < n * n) {
//if (grid[(row + 1) % n][(col + 1) % n] == 0) {
//row = (row + 1) % n;
//col = (col + 1) % n;

	int count=0;
	int row=1;
	int col=n/2-1;
	while(count<n*n)
	{
		if(grid[row][col]==0)
		{
			if(row-1<0)
			{
				row=n-1;
			}else
				row=(row-1)%n;
			
			if(col+1>n-1)
			{
				col=0;
			}else
				col=(col+1)%n;
		}else
		{
			
			if(row+1>n-1)
			{
				row=0;
			}else
				row=row+1;
		
		}
			
		count++;
		grid[row][col]=count;

	
	}

}
else {
row = (row + n - 1) % n;
}
count++;
grid[row][col] = count;
}
}
void Square::print()
/* Post: The square data is printed. */
{
for (int i = size - 1; i >= 0; i--) {
for (int j = 0; j < size; j++) {
if (grid[i][j] < 10) cout << " ";
cout << grid[i][j] << " ";
}
cout << endl;
}
}
void Square::read()
/* Post: the square data is read */
{
cout << "Enter the side size: " << flush;
cin >> size;
if (size < 0 || size > 9) {
cout << "Error: Out of range." << endl;
return;
}
cout << "Now type in the data, row by row." << endl;
for (int i = 0; i < size; i++)
for (int j = 0; j < size; j++)
cin >> grid[i][j];
}
int Square::sum_other()
/* Post: Returns the non-main diagonal sum */
{
int sum = 0;
for (int j = 0; j < size; j++) sum += grid[size - j - 1][j];
return sum;
}
int Square::sum_maindiag()
/* Post: Returns the main diagonal sum */
{
int sum = 0;
for (int j = 0; j < size; j++) sum += grid[j][j];
return sum;
}
int Square::sum_row(int i)
/* Pre: i is a valid row of the square
Post: Returns the row sum of the ith row */
{
int sum = 0;
for (int j = 0; j < size; j++) sum += grid[i][j];
return sum;
}
int Square::sum_col(int i)
/* Pre: i is a valid col of the square
Post: Returns the col sum of the ith col */
{
int sum = 0;
for (int j = 0; j < size; j++) sum += grid[j][i];
return sum;
}
bool Square::is_magic()
{
int number = sum_maindiag();
if (sum_other() != number) return false;
for (int i = 0; i < size; i++) {
if (sum_row(i) != number) return false;
if (sum_col(i) != number) return false;
}
return true;
}
