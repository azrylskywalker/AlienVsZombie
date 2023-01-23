// *********************************************************
// Course: TCP1101 PROGRAMMING FUNDAMENTALS
// Year: Trimester 1, 2022/23 (T2215)
// Lab: TT8L
// Names: AISYAH BINTI AHMAD KASSIM | MEMBER_NAME_2 | AZRYL SHAMIN BIN AZRIZAL
// IDs: MEMBER_ID_1 | MEMBER_ID_2 | 1211103145
// Emails: MEMBER_EMAIL_1 | MEMBER_EMAIL_2 | 1211103145@student.mmu.edu.my
// Phones: MEMBER_PHONE_1 | MEMBER_PHONE_2 | 01110169553
// *********************************************************

#include "pf/helper.h"
#include <iostream>

using namespace std;

void pause();
void clearScreen();
void createGameBoard();
void displayMenu();


int main()
{
    cout << "Assignment (Part 1)" << endl;
    cout << "Let's Get Started!" << endl;

    char choice;
    int numOfRows{3}, numOfColumns {19}, numOfZombies {1};
    bool done {0};

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

void pause()
{
    cout << "Pausing Now" << endl;
    pf::Pause();
    cout << endl;
}

void clearScreen()
{
    cout << "Pausing and Clearing Screen Now" << endl;
    pf::Pause();
    pf::ClearScreen();
    cout << endl;
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



void showGameSettings(const int &rows, const int &columns, const int &zombies){

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
