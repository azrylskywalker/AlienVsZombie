// *********************************************************
// Course: TCP1101 PROGRAMMING FUNDAMENTALS
// Year: Trimester 1, 2022/23 (T2215)
// Lab: TT8L
// Names: AISYAH BINTI AHMAD KASSIM | ALIA MAISARA BINTI SHAHRIN | AZRYL SHAMIN BIN AZRIZAL
// IDs: 1211101007 | 1211104237 | 1211103145
// Emails: 1211101007@student.mmu.edu.my | 1211104237@student.mmu.edu.my | 1211103145@student.mmu.edu.my
// Phones: 0197345509  | MEMBER_PHONE_2 | 01110169553
// *********************************************************

#include "pf/helper.h"
#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

void pause();
void clearScreen();
void createGameBoard();
void displayMenu();
void showGameSettings();

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

    // system("cls");
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
    cout << "Assignment (Part 1)" << endl;
    cout << "Let's Get Started!" << endl;

    char choice;
    int numOfRows{3}, numOfColumns{19}, numOfZombies{1};
    bool done{0};

    displayMenu();
    cin >> choice;
    switch (choice)
    {
    case '1':
        cout << "Option 1 not yet implemented." << endl;
        break;
    case '2':
        cout << "Option 2 Not yet implemented." << endl;
        break;
    case '3':
        cout << "Option 3 Not yet implemented." << endl;
        break;
    case 'Q':
        done = true;
        break;
    default:
        cout << "Invalid selection, try again!" << endl;
        cout << endl;
        break;
    }
    system("pause");
    // CreateGameBoard();
}

void displayMenu()
{
    system("cls");
    cout << "+---------------------------------------------+" << endl;
    cout << "|               ALIEN VS ZOMBIE               |" << endl;
    cout << "|=============================================|" << endl;
    cout << "| Select:                                     |" << endl;
    cout << "|    1 => New Game                            |" << endl;
    cout << "|    2 => Load Game                           |" << endl;
    cout << "|---------------------------------------------|" << endl;
    cout << "|    3 => Settings                            |" << endl;
    cout << "|---------------------------------------------|" << endl;
    cout << "|    Q => Quit                                |" << endl;
    cout << "+---------------------------------------------+" << endl;
    cout << endl;
    cout << "Choice => ";
}

void createGameBoard()
{
}

void showGameSettings(const int &rows, const int &columns, const int &zombies)
{

    cout << "Game Settings\n";
    cout << "----------------\n";

    cout << "Board Rows : " << rows << "\n";
    cout << "Board Columns : " << columns << "\n";
    cout << "Zombie Count : " << zombies << "\n";

    char changeSettings;

    cout << "Do you wish to change the game settings? (y/n) => ";
    cin >> changeSettings;
    switch (changeSettings)
    {
    case 'y':
        cout << "not yet implement ";
        break;
    case 'n':
        cout << "TO DO";
        break;
    default:
        cout << "Invalid selection, try again!";
    }
}

void changeGameSettings(){

}