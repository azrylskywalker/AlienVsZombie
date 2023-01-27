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

void displayMenu();
void showGameSettings(const int &rows, const int &columns, const int &zombies);
void changeGameSettings(int &rows, int &columns, int &zombies);
void createGameBoard(const int &boardColumns, const int &boardRows);
void startGame(const int &boardColumns, const int &boardRows, const int &numOfzZombies);
void gameDashboard();
void gameControl();
void commandHelp();


class Board{
private:
    vector<vector<char>> boardsize_;
    int row_, column_;

public:

    Board(int boardColumns, int boardRows){

        init(boardColumns, boardRows);
    }

    void init(int boardColumns, int boardRows){
        row_ = boardRows;
        column_ = boardColumns;

        char objects[] = {'h', 'p', 'r', '>', '<', '^', 'v', ' ', ' ', ' '};
        int noOfObjects = 10;

        boardsize_.resize(row_);
        for (int i = 0; i < row_; ++i){
            boardsize_[i].resize(column_);
        }

        for (int i = 0; i < row_; ++i){
            for (int j = 0; j < column_; ++j){
                int objNo = rand() % noOfObjects;
                boardsize_[i][j] = objects[objNo];
            }
        }
    }

    void display() const{

    // system("cls");
        cout << setw(15);
        cout << " .: Alien vs Zombie :." << endl;

        for (int i = 0; i < row_; ++i){
            cout << "   ";
            for (int j = 0; j < column_; ++j){
                cout << "+-";
            }
            cout << "+" << endl;

            cout << setw(2) << (row_ - i) << " ";

            for (int j = 0; j < column_; ++j){
                cout << "|" << boardsize_[i][j];
            }
            cout << "|" << endl;
        }

        cout << "   ";

        for (int j = 0; j < column_; ++j){
            cout << "+-";
        }

        cout << "+" << endl;
        cout << "   ";

        for (int j = 0; j < column_; ++j){
            int digit = (j + 1) / 10;
            cout << " ";
            if (digit == 0)
                cout << " ";
            else
                cout << digit;
        }

        cout << endl;
        cout << "   ";

        for (int j = 0; j < column_; ++j){
            cout << " " << (j + 1) % 10;
        }

        cout << "\n\n";
    }

    int getColumn() const{
        return column_;
    }

    int getRow() const {
        return row_;
    }

    void setObject(int &x, int &y, char &ch){
        boardsize_[-(y - row_)][x - 1] = ch;
    }

    char getObject(int x, int y) const{

        return boardsize_[-(y - row_)][x - 1];
    }

    bool isEmpty(int x, int y){
        return isspace(boardsize_[-(y - row_)][x - 1]); 
    }

    bool isInsideMap(int x, int y){
        return !isspace(boardsize_[-(y - row_)][x - 1]);
    }

};

class Alien{
private:
    int life_ {100}, attack_ {0}, x_, y_;
    char heading_ {'A'};

public:
    Alien(){};

    int getX() const{
        return x_;
    }

    int getY() const{
        return y_;
    }

    void alienStatus(){
        cout << "Alien: Life: " << life_ << "Attack: " << attack_;
    }

    void initPos(Board &playingBoard){

        x_ = playingBoard.getColumn() / 2;
        y_ = (playingBoard.getRow() / 2) + 1;

        playingBoard.setObject(x_, y_, heading_);
    }

    void move(const string &input){
        int oldPosX = x_;
        int oldPosY = y_;

        
        
    }


};

class Zombie{
private:
    int life_, attack_, range_, x_, y_;
public:
    Zombie(){};

    //TODO : getY(), getX(), move(), and else
};


int main(){
    cout << "Assignment (Part 1)" << endl;
    cout << "Let's Get Started!" << endl;

    char choice;
    int numOfRows{3}, numOfColumns{19}, numOfZombies{1};
    bool done{0};

    //TODO : once finished, create a proper randomnizer

    displayMenu();
    cin >> choice;
    switch (choice)
    {
    case '1':
        startGame(numOfColumns, numOfRows, numOfZombies);
        break;
    case '2':
        //create a load game function

        break;
    case '3':
        showGameSettings(numOfRows, numOfColumns, numOfZombies);
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

void displayMenu(){
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

void showGameSettings(const int &rows, const int &columns, const int &zombies){

    cout << "Game Settings\n";
    cout << "----------------\n";

    cout << "Board Rows : " << rows << "\n";
    cout << "Board Columns : " << columns << "\n";
    cout << "Zombie Count : " << zombies << "\n\n";

    char changeSettings;

    cout << "Do you wish to change the game settings? (y/n) => ";
    cin >> changeSettings;
    switch (changeSettings)
    {
    case 'y':
        cout << "not yet implement ";
        break;
    case 'n':
        break;
    default:
        cout << "Invalid selection, try again!";
    }
}

void changeGameSettings(int &rows, int &columns, int &zombies){
    cout << "Board Settings\n";
    cout << "------------------";

    cout << "Enter rows => ";
    cin >> rows;
    cout << "Enter columns => ";
    cin >> columns;

    cout << "Zombie Settings\n";
    cout << "------------------";

    cout << "Enter number of zombies => ";
    cin >> zombies;
}

void createGameBoard(const int &boardColumns, const int &boardRows){
    Board playingBoard = Board(boardColumns, boardRows);
    Alien player;

    player.initPos(playingBoard);
    playingBoard.display();
}

void startGame(const int &boardColumns, const int &boardRows, const int &numOfZombies){
    createGameBoard(boardColumns, boardRows);
    //gameDashboard()
    gameControl();

}

void gameDashboard(){
    // This function display the status of entity on the board

}

void gameControl(){
    string userInput;
    cout << "Command> ";
    cin >> userInput;

    if(userInput == "up" || "down" || "left" || "right"){
        cout << "allowed!";
    }else if(userInput == "arrow"){
        
    }else if(userInput == "help"){
        commandHelp();
    }else if(userInput == "save"){
        
    }else if(userInput == "load"){
        
    }else if(userInput == "quit"){
        
    }else{
        cout << "Invalid selection, try again!";
    }
}



void commandHelp(){
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





