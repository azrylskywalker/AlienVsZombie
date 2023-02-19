// *********************************************************
// Course: TCP1101 PROGRAMMING FUNDAMENTALS
// Year: Trimester 1, 2022/23 (T2215)
// Lab: TT8L
// Names: AISYAH BINTI AHMAD KASSIM | ALIA MAISARA BINTI SHAHRIN | AZRYL SHAMIN BIN AZRIZAL
// IDs: 1211101007 | 1211104237 | 1211103145
// Emails: 1211101007@student.mmu.edu.my | 1211104237@student.mmu.edu.my | 1211103145@student.mmu.edu.my
// Phones: 0197345509  | 01127261835 | 01110169553
// *********************************************************

#include <iostream>
#include <vector>
#include <random>
#include <iomanip>
#include <cstdlib>

using namespace std;

#include "display.h"
#include "alien.h"
#include "zombie.h"

class Board;
class Alien;
class Zombie;

void displayMenu();
void changeGameSettings(int &boardRows, int &boardColumns, int &numOfZombies, bool &settingsDone);
void startGame(const int &boardColumns, const int &boardRows, const int &numOfZombies);
void gameDashboard(Zombie &bots, Alien &player, const int & numOfZombies);
void gameControl(Alien &player, Board &playingBoard, Zombie &bots, const int & numOfZombies);
void commandHelp();


int main()
{
    //cout << "\nAssignment (Part 1)" << endl;
    //cout << "\nLet's Get Started!\n" << endl;

    char choice;
    int numOfRows{19}, numOfColumns{3}, numOfZombies{1};
    bool done{0}, settingsDone{0};
    Alien player;
    Zombie bots;

    displayMenu();
    cin >> choice;
    switch (choice)
    {
    case '1':
        GameSettings:
        cout << "\nGame Settings\n";
        cout << "----------------\n";

        cout << "Board Columns : " << numOfRows << "\n";
        cout << "Board Rows : " << numOfColumns << "\n";
        cout << "Zombie Count : " << numOfZombies << "\n\n";

        char changeSettings;

        cout << "Do you wish to change the game settings? (y/n) => ";
        cin >> changeSettings;
        switch (changeSettings)
        {
        case 'y':
            while (!settingsDone)
            {
                changeGameSettings(numOfRows, numOfColumns, numOfZombies, settingsDone);
            }
            
            
            startGame(numOfRows, numOfColumns, numOfZombies);
        case 'n':
            startGame(numOfRows, numOfColumns, numOfZombies);
        default:
            cout << "Invalid selection, try again!";
            goto GameSettings;
        }

    case '2':
        // create a load game function
        break;

    case 'Q':
        done = true;
        break;

    default:
        cout << "\nInvalid selection, try again!" << endl;
        cout << endl;
        displayMenu();
    }
    system("pause");
}

void displayMenu()
{
    // system("cls");
    cout << endl;
    cout << "+---------------------------------------------+" << endl;
    cout << "|               ALIEN VS ZOMBIE               |" << endl;
    cout << "|=============================================|" << endl;
    cout << "| Select:                                     |" << endl;
    cout << "|    1 => New Game                            |" << endl;
    cout << "|    2 => Load Game                           |" << endl;
    cout << "|---------------------------------------------|" << endl;
    cout << "|    Q => Quit                                |" << endl;
    cout << "+---------------------------------------------+" << endl;
    cout << endl;
    cout << "Choice => ";
}

void changeGameSettings(int &boardRows, int &boardColumns, int &numOfZombies, bool &exit)
{
    // system("cls");
    cout << "\nBoard Settings\n";
    cout << "------------------\n";

    
    cout << "Enter rows => ";
    cin >> boardColumns;
    cout << endl;


    cout << "Enter columns => ";
    cin >> boardRows;
    cout << endl;


    cout << "\nZombie Settings\n";
    cout << "------------------\n";

    cout << "Enter number of zombies => ";
    cin >> numOfZombies;
    cout << endl;

    if(boardColumns%2 == 0 || boardRows%2 == 0 ){
        cout << "\nERROR ! Please make sure user enter an odd number for the rows and columns.\n\n";
    }
    else{
        exit = true;
    }


}

void startGame(const int &boardColumns, const int &boardRows, const int &numOfZombies)
{
    Board playingBoard = Board(boardColumns, boardRows);

    Alien player;
    player.initPos(playingBoard);

    Zombie bots;
    bots.zombiePos(playingBoard, numOfZombies);

    //bots.zombieAttributes(numOfZombies);

    while (true)
    {

        playingBoard.display();
        //gameDashboard(bots, player, numOfZombies);
        gameControl(player, playingBoard, bots, numOfZombies);
        playingBoard.display();
        bots.zombieTurns();
        bots.zombieMainMove(playingBoard, player, bots, numOfZombies);
   
    }
}

void gameDashboard(Zombie &bots, Alien &player, const int &numOfZombies)
{
    //if(player.getTurns() == 1){
    //    cout << "=>"
    //}
    player.alienStatus();
    bots.zombieStatus(numOfZombies);
    // This function display the status of entity on the board
}

void gameControl(Alien &player, Board &playingBoard, Zombie &bots, const int &numOfZombies)
{
    string userInput;
    cout << "Command> ";
    cin >> userInput;
    cout << "\n";


    if (userInput == "up" || "down" || "left" || "right")
    {
        player.move(userInput, playingBoard, bots, player, numOfZombies);
    }
    if (userInput == "arrow")
    {
        playingBoard.arrowDirection();
        gameControl(player, playingBoard, bots, numOfZombies);
    
    }
    if (userInput == "help")
    {
        commandHelp();
    }
    if (userInput == "save")
    {
    }
    if (userInput == "load")
    {
    }
    if (userInput == "quit")
    {
        exit(0);
    }
}



void commandHelp()
{
    cout << "Commands\n";
    cout << "1. up - Move Up.\n";
    cout << "2. down - Move down.\n";
    cout << "3. left - Move left.\n";
    cout << "4. right - Move right.\n";
    cout << "5. arrow - Change the direction of an arrow.\n";
    cout << "6. help - Display these user commands.\n";
    cout << "7. save - Save the game.\n";
    cout << "8. load - Load a game\n";
    cout << "9. quit - Quit the game.\n";
}

