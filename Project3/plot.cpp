#include "grid.h"
#include <iostream>
#include <string>
#include <cctype>
#include <cassert>
using namespace std;

const int HORIZ = 0;
const int VERT = 1;

const int FG = 0; //foreground
const int BG = 1; //background

void plotHorizontalLine(int row, int col, int distance, char ch, int fgbg);
void plotVerticalLine(int row, int col, int distance, char ch, int fgbg);
void plotRectangle(int row, int col, int height, int width, char ch, int fgbg); //Unused warmup function

bool plotLine(int row, int col, int distance, int dir, char plotChar, int fgbg);
bool inGrid(int row, int col, int distance, int dir);

int performCommands(string commandString, char& plotChar, int& mode, int& badPos);
bool checkSyntax(string commandString, int& badPos);

int main()
{
	setSize(20, 30);
	char currentChar = '*';
	int currentMode = FG;
	for (;;)
	{
		cout << "Enter a command string: ";
		string cmd;
		getline(cin, cmd);
		if (cmd == "")
			break;
		int position;
		int status = performCommands(cmd, currentChar, currentMode, position);
		switch (status)
		{
		case 0:
			draw();
			break;
		case 1:
			cout << "Syntax error at position " << position + 1 << endl;
			break;
		case 2:
			cout << "Cannot perform command at position " << position + 1 << endl;
			break;
		default:
			// It should be impossible to get here.
			cerr << "performCommands returned " << status << "!" << endl;
		}
	}
}

/*
Sets chars in grid to form line segment w/ start point (r,c)
Returns true if successfully plots line, false if not
False if dir isn't horiz/vert, fgbg isn't fg/bg, every pos in line isn't in grid, isn't a printable char
*/
bool plotLine(int row, int col, int distance, int dir, char plotChar, int fgbg) {
	if (dir != 0 && dir != 1) //if dir isn't horiz and isn't vertical
		return false;
	if (fgbg != 0 && fgbg != 1) //if fbgb isn't foreground and isn't background
		return false;
	if (!inGrid(row, col, distance, dir)) //if point(s) in line not in grid
		return false;
	if (!isprint(plotChar)) //if isprint(ch) is false
		return false;

	//Only draws line if none of above return false
	if (dir == 0) //horizontal line
		plotHorizontalLine(row, col, distance, plotChar, fgbg);
	else if (dir == 1) //vertical line
		plotVerticalLine(row, col, distance, plotChar, fgbg);

	return true;
}

/* Function for parsing the entered command string and calling the plotLine function
 returns 0 if successful, 1 if command is syntactically invalid, 2 if plotted line is out of grid */
int performCommands(string commandString, char& plotChar, int& mode, int& badPos) {
	int row = 1;
	int col = 1;

	if (!checkSyntax(commandString, badPos)) //If there are syntax errors, return and report syntax error
		return 1;

	//If the commandString is empty, terminate the program
	if (commandString == "")
		return 0;
	else {
		int index = 0;

		while (index < commandString.size()) {
			//For C/c ==> clear grid, set position to (1,1), set char to *, set mode to fg
			if (commandString[index] == 'C' || commandString[index] == 'c') {
				clearGrid();
				plotChar = '*';
				row = 1;
				col = 1;
				mode = FG;

				index++;
			}
			//For F/f ==> set mode to FG, set char to char ==> move onto next char in string
			else if (commandString[index] == 'F' || commandString[index] == 'f') {
				index++;
				mode = FG;
				plotChar = commandString[index];
				index++;
			}
			//For B/b ==> set mode to BG, set char to char ==> move onto next char in string
			else if (commandString[index] == 'B' || commandString[index] == 'b') {
				index++;
				mode = BG;
				plotChar = commandString[index];
				index++;
			}
			//For H/h ==> draw line if within bounds, return index of bad command if out of bounds
			else if (commandString[index] == 'H' || commandString[index] == 'h') {
				int firstLetter = index;
				index++;
				bool isNegative = false;
				if (commandString[index] == '-') { //Check for optional - sign
					isNegative = true;
					index++;
				}
				char digit1 = commandString[index];
				int distance = (int)digit1 - 48; //Subtracts 48 bc ASCII value
				//Checks if there is a second digit
				if (index < commandString.size() - 1 && isdigit(commandString[index + 1])) {
					index++;
					char digit2 = commandString[index];
					distance = distance * 10 + (int)digit2 - 48;
				}
				if (isNegative)
					distance = distance * -1;
				if (plotLine(row, col, distance, HORIZ, plotChar, mode)) {
					index++;
					col = col + distance; //Moves position of start point after line plotted
				}
				else { //plotLine failed, out of bounds error
					badPos = firstLetter;
					return 2;
				}
			} //end of H/h loop
			//For H/h ==> draw line if within bounds, return index of bad command if out of bounds
			else if (commandString[index] == 'V' || commandString[index] == 'v') {
				int firstLetter = index;
				index++;
				bool isNegative = false;
				if (commandString[index] == '-') { //Check for optional - sign
					isNegative = true;
					index++;
				}
				char digit1 = commandString[index];
				int distance = (int)digit1 - 48; //Subtracts 48 bc ASCII value
				//Checks if there is a second digit
				if (index < commandString.size() - 1 && isdigit(commandString[index + 1])) {
					index++;
					char digit2 = commandString[index];
					distance = distance * 10 + (int)digit2 - 48;
				}
				if (isNegative)
					distance = distance * -1;
				if (plotLine(row, col, distance, VERT, plotChar, mode)) {
					index++;
					row = row + distance; //Move start position after line is plotted
				}
				else { //plotLine failed, out of bounds error
					badPos = firstLetter;
					return 2;
				}
			} //end of V/v loop
		} //end of while loop
	} //end of big else

	return 0; //returns if all cmds are successful
}

//Checks the commandString for syntax errors, returns true if there are no errors and false if there are errors
//Changes badPos to the index of the first syntax error if there is an error, leave badPos unchanged if there are no syntax errors
bool checkSyntax(string commandString, int& badPos) {
	int index = 0;

	//Loops through all char in commandString
	while (index < commandString.size()) {
		//All C/c commands are valid
		if (commandString[index] == 'C' || commandString[index] == 'c')
			index++;
		//F/f and B/b commands are invalid if not followed by a printable character
		else if (commandString[index] == 'F' || commandString[index] == 'f' || commandString[index] == 'B' || commandString[index] == 'b') {
			index++;
			if (index < commandString.size()) {
				if (!isprint(commandString[index])) { //Not printable, syntax error
					badPos = index;
					return false;
				}
				index++; //Character is valid, move on to next index
			}
			else { //No character follows, syntax error
				badPos = index;
				return false;
			}
		} //end of F/f if
		//H/h and V/v commands are invalid if not followed by one/two digits (can have optional - before digit/s)
		else if (commandString[index] == 'H' || commandString[index] == 'h' || commandString[index] == 'V' || commandString[index] == 'v') {
			index++;
			if (index < commandString.size()) {
				if (commandString[index] == '-') { //If - not followed by digit, syntax error
					index++;
					if (!isdigit(commandString[index])) {
						badPos = index;
						return false;
					}
				}
				if (isdigit(commandString[index])) {
					index++;
					if (index < commandString.size() && isdigit(commandString[index])) //Accounts for second digit
						index++;
				}
				else { //Character that follows isn't - or digit
					badPos = index;
					return false;
				}
			}
			else { //if H/h, V/v are the last number, a number can't follow it and there is a syntax error
				badPos = index;
				return false;
			}
		} //end of H/h, V/v if
		else { //Syntax error if not a C, F, B, H, or V command
			badPos = index;
			return false;
		}
	} //end of while loop

	return true;
}
//Checks that all points in the to-draw line are within the grid limits
bool inGrid(int row, int col, int distance, int dir) {
	if (distance >= 0) {
		if (dir == HORIZ) {
			for (int c = col; c <= col + distance; c++) {
				if (c > getCols() || c <= 0)
					return false;
			}
			if (row > getRows() || row <= 0)
				return false;
		} //end of horiz if
		else if (dir == VERT) {
			for (int r = row; r <= row + distance; r++) {
				if (r > getRows() || r <= 0)
					return false;
			}
			if (col > getCols() || col <= 0)
				return false;
		} //end of vertical if
	}
	else { //distance is negative
		if (dir == HORIZ) {
			for (int c = col; c >= col + distance; c--) {
				if (c > getCols() || c <= 0)
					return false;
			}
			if (row > getRows() || row <= 0)
				return false;
		}
		else if (dir == VERT) {
			for (int r = row; r >= row + distance; r--) {
				if (r > getRows() || r <= 0)
					return false;
			}
			if (col > getCols() || col <= 0)
				return false;
		} //end of vertical if
	}

	return true;
}

//From start point (r, c) for distance, draw ch through the row (row, ...)
void plotHorizontalLine(int row, int col, int distance, char ch, int fgbg) {
	//row = up down, col = left right
	if (distance >= 0) { //distance is positive, go right
		for (int i = col; i <= (col + distance); i++) {
			if (row <= getRows() && row > 0 && i <= getCols() && i > 0) {
				if (fgbg == FG) //sets all char if foreground
					setChar(row, i, ch);
				else { //sets char if the spot contains ' ' if background
					if (getChar(row, i) == ' ')
						setChar(row, i, ch);
				}
			}
		}
	}
	else { //distance is negative, go left
		for (int i = col; i >= (col + distance); i--) {
			if (row <= getRows() && row > 0 && i <= getCols() && i > 0) {
				if (fgbg == 0)  //sets all char if foreground
					setChar(row, i, ch);
				else { //sets char if the spot contains ' ' if background
					if (getChar(row, i) == ' ')
						setChar(row, i, ch);
				}
			}
		}
	}
}

//From start point (r, c) for distance, draw ch through the col (..., col)
void plotVerticalLine(int row, int col, int distance, char ch, int fgbg) {
	if (distance >= 0) { //distance is positive, go down
		for (int i = row; i <= (row + distance); i++) {
			if (i <= getRows() && i > 0 && col <= getCols() && col > 0) {
				if (fgbg == 0) //foreground
					setChar(i, col, ch);
				else { //background
					if (getChar(i, col) == ' ')
						setChar(i, col, ch);
				}
			}
		}
	}
	else { //distance is negative, go up
		for (int i = row; i >= (row + distance); i--) {
			if (i <= getRows() && i > 0 && col <= getCols() && col > 0) {
				if (fgbg == 0) //foreground
					setChar(i, col, ch);
				else {
					if (getChar(i, col) == ' ')
						setChar(i, col, ch);
				}
			}
		}
	}
}

//Plots rectangle of char ch with given height, width starting at (row, col)
void plotRectangle(int row, int col, int height, int width, char ch, int fgbg) {
	if (height > 0 && width > 0) {
		plotHorizontalLine(row, col, width, ch, fgbg);
		plotHorizontalLine(row + height, col, width, ch, fgbg);
		plotVerticalLine(row, col, height, ch, fgbg);
		plotVerticalLine(row, col + width, height, ch, fgbg);
	}
}