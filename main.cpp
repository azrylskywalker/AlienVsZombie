// ********************************************************* 
// Course: TCP1101 PROGRAMMING FUNDAMENTALS 
// Year: Trimester 1, 2022/23 (T2215) 
// Lab: TT8L 
// Names: AISYAH BINTI AHMAD KASSIM | ALIA MAISARA BINTI SHAHRIN | AZRYL SHAMIN BIN AZRIZAL 
// IDs: 1211101007 | 1211104237 | 1211103145 
// Emails: 1211101007@student.mmu.edu.my | 1211104237@student.mmu.edu.my | 1211103145@student.mmu.edu.my 
// Phones: 0197345509 | MEMBER_PHONE_2 | MEMBER_PHONE_3 
// ********************************************************* 

// TODO: Fill in the missing information above and delete this line.

#include "pf/helper.h"
#include <iostream>
using namespace std;

int main()
{
    cout << "Assignment (Part 1)" << endl;
    cout << "Let's Get Started!" << endl;
    pf::Pause();
}

//test

//cuba check guys
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>
using namespace std;

class Board
{
private:
    vector<vector<char>> boardsize_;
    int row_, column_;

public:
    Board(int boardColumns = 5, int boardRows = 10);
    void init(int boardColumns, int boardRows);
    void display() const;
};

Board::Board(int boardColumns, int boardRows)
{
    cout << endl;
    cout << "Board Settings" << endl;
    cout << "----------------" << endl;

    cout << "Enter rows => ";
    cin >> boardRows;
    cout << "Enter columns => ";
    cin >> boardColumns;

    init(boardColumns, boardRows);
}

void Board::init(int boardColumns, int boardRows)
{
    row_ = boardRows;
    column_ = boardColumns;

    char objects[] = {'h', 'p', 'r', '>', '<', '^', 'v', ' ', ' ', ' '};
    int noOfObjects = 10;

    boardsize_.resize(row_);
    for (int i = 0; i < row_; ++i)
    {
        boardsize_[i].resize(column_);
    }

    for (int i = 0; i < row_; ++i)
    {
        for (int j = 0; j < column_; ++j)
        {
            int objNo = rand() % noOfObjects;
            boardsize_[i][j] = objects[objNo];
        }
    }
}

void Board::display() const
{

    //system("cls");
    cout << setw(15);
    cout << " .: Alien vs Zombie :." << endl;

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
    cout << endl
         << endl;
}

void gameBoardDisplay()
{
    Board board;
    board.display();
}

int main()
{
    char choices;

    cout << "Default Game Settings" << endl;
    cout << "------------------------" << endl;

    cout << "Board Rows    : 5" << endl;
    cout << "Board Columns : 9" << endl;
    cout << "Zombie Count  : 1" << endl;

    cout << "Do you wish to change the game settings (y/n)? => ";
    cin >> choices;

    if (choices == 'y')
    {
        srand(time(NULL));
        gameBoardDisplay();
    }

    if (choices == 'n')
    {
        srand(time(NULL));
        gameBoardDisplay();
    }

    else
    {
        cout << "Please only choose 'y' or 'n'." << endl;
    }

}