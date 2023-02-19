#include <iostream>
#include <vector>
#include <random>
#include <iomanip>
#include <cstdlib>
#include "display.h"
#include "alien.h"
#include "zombie.h"

using namespace std;

Board::Board(int boardColumns, int boardRows)
{

    init(boardColumns, boardRows);
}

void Board::init(int boardColumns, int boardRows)
{
    row_ = boardRows;
    column_ = boardColumns;

    char objects[] = {'h', 'p', 'r', '>', '<', '^', 'v', ' ', ' ', ' ', ' ', ' '};
    int noOfObjects = 12;

    static random_device random;
    uniform_int_distribution<int> obj(0, 11);

    boardsize_.resize(row_);
    for (int i = 0; i < row_; ++i)
    {
        boardsize_[i].resize(column_);
    }

    for (int i = 0; i < row_; ++i)
    {
        for (int j = 0; j < column_; ++j)
        {
            int objNo = obj(random);
            boardsize_[i][j] = objects[objNo];
        }
    }
}

void Board::display() const
{

    // system("cls");
    cout << setw(15);
    cout << "\n .: Alien vs Zombie :." << endl;

    for (int i = 0; i < row_; ++i)
    {
        cout << "   ";
        for (int j = 0; j < column_; ++j)
        {
            cout << "+-";
        }
        cout << "+" << endl;

        cout << setw(2) << (row_ - i) << " ";

        for (int j = 0; j < column_; ++j)
        {
            cout << "|" << boardsize_[i][j];
        }
        cout << "|" << endl;
    }

    cout << "   ";

    for (int j = 0; j < column_; ++j)
    {
        cout << "+-";
    }

    cout << "+" << endl;
    cout << "   ";

    for (int j = 0; j < column_; ++j)
    {
        int digit = (j + 1) / 10;
        cout << " ";
        if (digit == 0)
            cout << " ";
        else
            cout << digit;
    }

    cout << endl;
    cout << "   ";

    for (int j = 0; j < column_; ++j)
    {
       cout << " " << (j + 1) % 10;
    }

    cout << "\n\n";
}

int Board::getColumn() const
{
    return column_;
}

int Board::getRow() const
{
    return row_;
}

void Board::setObject(int &x, int &y, char &ch)
{
    boardsize_[-(y - row_)][x - 1] = ch;
}

char Board::getObject(int x, int y) const
{
    return boardsize_[-(y - row_)][x - 1];
}

bool Board::isEmpty(int x, int y)
{
    return isspace(boardsize_[-(y - row_)][x - 1]);
}

bool Board::isInsideMap(int x, int y)
{
    return (x > 0 && x <= column_ && y > 0 && y <= row_);
}

void Board::arrowDirection()
{
    int row, column;
    string direction;
    char oldDirection, newDirection;

    cout << "Enter row, column, and direction: ";
    cin >> row >> column >> direction;

    oldDirection = getObject(column, row);

    if (direction == "right")
    {
        newDirection = '>';
    }
    else if (direction == "left")
    {
        newDirection = '<';
    }
    else if (direction == "up")
    {
        newDirection = '^';
    }
    else if (direction == "down")
    {
        newDirection = 'v';
    }

    setObject(column, row, newDirection);

    cout << "\nArrow " << oldDirection << " is switched to " << newDirection << ".\n\n";
    system("pause");

}

char Board::randomObj(){
    char objects[] = {'h', 'p', 'r', '>', '<', '^', 'v', ' ', ' ', ' ', ' ', ' '};
    int noObj = 12;

    static random_device random;
    uniform_int_distribution<int> obj(0, noObj);

    return objects[obj(random)];
}