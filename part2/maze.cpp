// maze.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <iostream>
using namespace std;

int maze[8][13] = { {1, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1} ,
					{1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1} ,
					{1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1} ,
					{1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1} ,
					{1, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1} ,
					{1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0} ,
					{0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0} ,
					{0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1} };

void printMaze()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 13; j++)
			cout << maze[i][j] << " ";
		cout << endl;
	}
}

bool isValidNextUp(int row, int column)
{
	//not wall position and not boundary position, and not on path already, and not dead end
	int tempR = row - 1;
	return (tempR >= 0 && maze[tempR][column] == 1);
}

bool isValidNextRight(int row, int column)
{
	//not wall position and not boundary position, and not on path already, and not dead end
	int tempC = column + 1;
	return (tempC <= 12 && maze[row][tempC] == 1);
}

bool isValidNextDown(int row, int column)
{
	//not wall position and not boundary position, and not on path already, and not dead end
	int tempR = row + 1;
	return (tempR <= 7 && maze[tempR][column] == 1);
}

bool isValidNextLeft(int row, int column)
{
	//not wall position and not boundary position, and not on path already, and not dead end
	int tempC = column - 1;
	return (tempC >= 0 && maze[row][tempC] == 1);
}

void progressTo(int row, int column)
{
	maze[row][column] = 9; //path position
}

void goBackFrom(int row, int column)
{
	maze[row][column] = 2; //dead end position; better choice?
	//maze[row][column] = 1; //also work
}

bool success(int row, int column)
{
	return (row == 7 && column == 12);
}

bool tryWithBackTrack(int row, int column)
{
	progressTo(row, column);

	if (success(row, column)) //reach goal
		return true;
	else //not goal
	{
		if (isValidNextUp(row, column) && tryWithBackTrack(row - 1, column)) //recursive call
			return true; //from north position can reach goal
		else if (isValidNextRight(row, column) && tryWithBackTrack(row, column + 1)) 
			return true;
		else if (isValidNextDown(row, column) && tryWithBackTrack(row + 1, column))
			return true;
		else if (isValidNextLeft(row, column) && tryWithBackTrack(row, column - 1))
			return true;
		else //cannot reach goal from current (row, column)
		{
			goBackFrom(row, column); //lead to end position
			return false;
		}
	}
}

int main()
{	
	if (tryWithBackTrack(0, 0))
		printMaze();
	else
		cout << "No path exists!\n";
	return 0;
}