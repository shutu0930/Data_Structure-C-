// Life Game(revised).cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "../../c/utility.h"
#include "life.h"
#include "../../c/utility.cpp"
#include "life.cpp"
int main() // Program to play Conway's game of Life.
/*
Pre: The user supplies an initial configuration of living cells.
Post: The program prints a sequence of pictures showing the changes in
the configuration of living cells according to the rules for
the game of Life.
Uses: The class Life and methods initialize(), print(), and update();
the functions instructions(), user_says_yes().
*/{
	Life configuration;
	instructions();
	configuration.initialize();
	configuration.print(cout);
	bool command;
	do {
		configuration.update();
		configuration.print(cout);
		cout << "Continue viewing without changes? " << endl;
		
		if (!(command = user_says_yes())) {
			cout << "Do you want to quit? " << flush;
			if (user_says_yes()) command = false;
			else {
				cout << "Do you want help? " << flush;
				if (user_says_yes()) instructions();
					cout << "Do you want to make any changes? " << flush;
				if (user_says_yes()) configuration.edit();
					command = true;
				}
		}
	} while (command);
		cout << "Do you want to save the final position to file? " << flush;
		if (user_says_yes()) {
			char name[1000];
			cout << "Give the save file name: " << flush;
			cin >> name;
			ofstream f(name);
			configuration.print(f);
	}
}
const int maxrow = 20, maxcol = 60; // grid dimensions
class Life {
public:
	void initialize();
	void print(ostream &f);
	void update();
	void edit();
private:
	int grid[maxrow + 2][maxcol + 2]; // Allow two extra rows and columns.
	int neighbor_count(int row, int col);
	bool step_mode;
};
void Life::edit()
/* Post: User has edited configuration, and/or step mode */
{
	cout << "Do you want to switch the step mode? " << flush;
	if (user_says_yes()) step_mode = !step_mode;
	cout << "Do you want to change the configuration? " << flush;
	if (!user_says_yes()) return;
	int row, col;
	cout << "List the coordinates for cells to change." << endl;
	cout << "Terminate the list with the the special pair -1 -1" << endl;
	cin >> row >> col;
	while (row != -1 || col != -1) {
	if (row >= 1 && row <= maxrow)
	if (col >= 1 && col <= maxcol)
	grid[row][col] = 1 - grid[row][col];
	else
	cout << "Column " << col << " is out of range." << endl;
	else
	cout << "Row " << row << " is out of range." << endl;
	cin >> row >> col;
	}
}
void Life::print(ostream &f)
/*
Pre: The Life object contains a configuration.
Post: The configuration is written to stream f for the user.
*/
{
	int row, col;
	f << "The current Life configuration is:" << endl;
	for (row = 1; row <= maxrow; row++) {
	for (col = 1; col <= maxcol; col++)
	if (grid[row][col] == 1) f << '*';
	else f << ' ';
	f << endl;
	}
	f << endl;
}
int Life::neighbor_count(int row, int col)
/*
Pre: The Life object contains a configuration, and the coordinates
row and col define a cell inside its hedge.
Post: The number of living neighbors of the specified cell is returned.
*/
{
	int i, j;
	int count = 0;
	for (i = row - 1; i <= row + 1; i++)
	for (j = col - 1; j <= col + 1; j++)
	count += grid[i][j]; // Increase the count if neighbor is alive.
	count -= grid[row][col]; // A cell is not its own neighbor.
	return count;
}
void Life::update()
/*
Pre: The Life object contains a configuration.
Post: The Life object contains the next generation of configuration.
*/
{
	int row, col;
	int new_grid[maxrow + 2][maxcol + 2];
	for (row = 1; row <= maxrow; row++)
	for (col = 1; col <= maxcol; col++)
	switch (neighbor_count(row, col)) {
	case 2:
	new_grid[row][col] = grid[row][col]; // Status stays the same.
	break;
	case 3:
	if (step_mode &&grid[row][col] == 0)
	cout << "Vivify cell " << row << " " << col << endl;
	new_grid[row][col] = 1; // Cell is now alive.
	break;
	default:
	if (step_mode && grid[row][col] == 1)
	cout << "Kill cell " << row << " " << col << endl;
	new_grid[row][col] = 0; // Cell is now dead.
	}
	for (row = 1; row <= maxrow; row++)
	for (col = 1; col <= maxcol; col++)
	grid[row][col] = new_grid[row][col];
}
void Life::initialize()
/*
Pre: None.
Post: The Life object contains a configuration specified by the user.
*/
{
step_mode = false;
int row, col;
char c;
bool from_file = false;
ifstream f;
for (row = 0; row <= maxrow+1; row++)
for (col = 0; col <= maxcol+1; col++)
grid[row][col] = 0;
cout << "Do you want to read input from a prepared file? " << flush;
if (user_says_yes()) {
cout << "Enter input file name: " << flush;
char name[1000];
cin >> name;
f.open(name);
from_file = true;
while (f.get() != '\n');
}
else {
while (cin.get() != '\n');
cout << "Enter a picture of the initial configuration." << endl;
cout << "Please enter nonblanks to signify living cells,\n";
cout << "and blanks to signify empty cells.\n";
cout << "Enter a return (newline) to terminate a row of input.\n";
cout << "Enter a character $ if all input is complete before the "
<< "last row." << endl;
}
for (row = 1; row <= maxrow; row++) {
if (!from_file) cout << row << " : " << flush;
for (col = 1; col <= maxcol; col++) {
if (from_file) f.get(c);
else cin.get(c);
if (c == '\n' || c == '$') break;
if (c != ' ') grid[row][col] = 1;
else grid[row][col] = 0;
}
if (c == '$') break;
if (from_file) while (c != '\n') f.get(c);
else while (c != '\n') cin.get(c);
}
}
void instructions()
/*
Pre: None.
Post: Instructions for using the Life program have been printed.
*/
{
cout << "Welcome to Conway's game of Life." << endl;
cout << "This game uses a grid of size "
<< maxrow << " by " << maxcol << " in which" << endl;
cout << "each cell can either be occupied by an organism or not." << endl;
cout << "The occupied cells change from generation to generation" << endl;
cout << "according to the number of neighboring cells which are alive."
<< endl;
}