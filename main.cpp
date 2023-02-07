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
#include <random>
#include <iomanip>
#include <cstdlib>

using namespace std;


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

        char objects[] = {'h', 'p', 'r', '>', '<', '^', 'v', ' ', ' ', ' ', ' ', ' '};
        int noOfObjects = 12;

        static random_device device;
        uniform_int_distribution<int> random(0, noOfObjects-1);

        boardsize_.resize(row_);
        for (int i = 0; i < row_; ++i){
            boardsize_[i].resize(column_);
        }

        for (int i = 0; i < row_; ++i){
            for (int j = 0; j < column_; ++j){
                int objNo = random(device);
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
        return (x > 0 && x <= column_ && y > 0 && y <= row_);
    }

    void arrowDirection(){
        int row, column;
        string direction;
        char oldDirection, newDirection;

        cout << "Enter row, column, and direction: ";
        cin >> row >> column >> direction;

        oldDirection = getObject(column, row);

        if (direction == "right"){
            newDirection = '>';
        }else if(direction == "left"){
            newDirection = '<';
        }else if(direction == "up"){
            newDirection = '^';
        }else if(direction == "down"){
            newDirection = 'v';
        }

        setObject(column, row, newDirection);

        cout << "Arrow " << oldDirection << " is switched to " << newDirection << ".\n";
        system("pause");
    }

    
};

class Alien{
private:
    int life_ {100}, attack_ {0}, x_, y_;
    char heading_ {'A'}, trail_ {'.'};
    bool turns_ {1};

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
   
    void move(const string &input,Board &playingBoard){
        if (input == "up"){
            moveUp(playingBoard);
        }else if (input == "down"){
            moveDown(playingBoard);
        }else if (input == "left"){
            moveLeft(playingBoard);
        }else if(input == "right"){
            moveRight(playingBoard);
        }
    }

    void moveStep(int &oldPosX, int &oldPosY, int &newPosX, int &newPosY, Board &playingBoard){
        
        char obj = playingBoard.getObject(newPosX, newPosY);
        
        playingBoard.setObject(x_, y_, heading_);
        playingBoard.setObject(oldPosX, oldPosY, trail_);
        playingBoard.display();

        if (obj == '>' || '<' || '^' || 'v')
        {
            moveArrow(playingBoard, obj);
        }
    }

    void moveUp(Board &playingBoard){
        while (turns_){
            int oldPosX {x_}, oldPosY {y_};
            int newposX {x_}, newPosY {y_ + 1};

            moveObstacles(playingBoard, newposX, newPosY);

            if (turns_){
                y_++;
                moveStep(oldPosX, oldPosY,newposX, newPosY, playingBoard);
            }
        }
    }

    void moveDown(Board &playingBoard){
        while (turns_){
            int oldPosX {x_}, oldPosY {y_};
            int newposX {x_}, newPosY {y_ - 1};

            moveObstacles(playingBoard, newposX, newPosY);

            if (turns_){
                y_--;
                moveStep(oldPosX, oldPosY, newposX, newPosY, playingBoard);
            }
        }
    }

    void moveLeft(Board &playingBoard){
        while (turns_){
            int oldPosX {x_}, oldPosY {y_};
            int newposX {x_ - 1}, newPosY {y_};

            moveObstacles(playingBoard, newposX, newPosY);
            
            if(turns_){
                x_--;
                moveStep(oldPosX, oldPosY, newposX, newPosY, playingBoard);
            }
        }
    }

    void moveRight(Board &playingBoard){
        while (turns_){
            int oldPosX {x_}, oldPosY {y_};
            int newposX {x_ + 1}, newPosY {y_};

            moveObstacles(playingBoard, newposX, newPosY);

            if(turns_){
                x_++;
                moveStep(oldPosX, oldPosY, newposX, newPosY, playingBoard);
            }
        }
    }

    void moveObstacles(Board &playingBoard, int &newposX, int &newPosY){
        if (playingBoard.getObject(newposX, newPosY) == 'h'){ 
            healthObstacles();
        }else if(playingBoard.getObject(newposX, newPosY) == 'p'){
            podObstacles();
        }else if (playingBoard.getObject(newposX, newPosY) == 'r'){
            rockObstacles(playingBoard, newposX, newPosY);
        }else if(!playingBoard.isInsideMap(newposX, newPosY)){
            borderObstacles();
        }else if ((playingBoard.getObject(newposX, newPosY) == '>') || (playingBoard.getObject(newposX, newPosY) == '<') || playingBoard.getObject(newposX, newPosY) == '^' || playingBoard.getObject(newposX, newPosY) == 'v'){
            arrowObstacles();
        }else if(isdigit(playingBoard.getObject(newposX, newPosY))){
            attack(playingBoard, newposX, newPosY);
        }
    }

    void healthObstacles(){
        cout << "Alien finds a health pack.\n";
        cout << "Alien's life is increased by 20\n";

        life_ += 20;

        system("pause");
    }

    void podObstacles(){
        system("pause");
    }

    void rockObstacles(Board &playingBoard, int &x, int y){
        cout << "Alien stumbles upon a rock\n";

        char objects[] = {'h', 'p', ' ', '>', '<', '^', 'v', ' ', ' ', ' ', ' ', ' '};
        int noOfObjects = 12;

        static random_device device;
        uniform_int_distribution<int> random(0, noOfObjects-1);

        char newObj = objects[random(device)];

        switch (newObj){
        case 'h':
            cout << "Alien discovers a health pack beneath the rock.\n";
            break;
        case 'p':
            cout << "Alien discovers a pod beneath the rock.\n";
            break;
        case '>':
        case '<':
        case '^':
        case 'v':
            cout << "Alien discovers an arrow beneath the rock.\n";
            break;
        default:
            cout << "Alien discovers nothing beneath the rock.\n";
            break;
        }
        playingBoard.setObject(x, y, newObj);
        system("pause");

        turns_ = 0;
    }

    void borderObstacles(){
        cout << "Alien hits a border.\n";
        system("pause");

        turns_ = 0;
    }

    void arrowObstacles(){
        cout << "Alien finds an arrow\n";
        cout << "Alien's attack is increase by 20\n";

        attack_ += 20;

        system("pause");
    }

    void moveArrow(Board &playingBoard, const char &arrowObj){
        
        switch (arrowObj)
        {
        case '>':
            moveRight(playingBoard);
            break;
        case 'v':
            moveDown(playingBoard);
            break;
        case '<':
            moveLeft(playingBoard);
            break;
        case '^':
            moveUp(playingBoard);
            break;
        }
    }

    void attack(Board &playingBoard, int &newX, int &newY){
        
    }
};

class Zombie{
private:
    int life_, attack_, range_, x_, y_;
public:
    Zombie(){};

    int getX() const{
        return x_;
    }

    int getY() const{
        return y_;
    }

    void zombieStatus(int &zombies){

        for(int x=1; x<=zombies; x++){
            range_ = 1 + (rand() % 5);
            life_ = 100 + (rand() % 201);
            attack_ = 5 + (rand() % 30);
            cout << "Zombie " << x << " : Life " << life_ << ", Attack " << attack_ << ", Range " << range_ << endl; 
        };
    }

    void zombiePos(Board &playingBoard, int &zombies){

        char zombieNum_[9] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};

        for(int x=0; x<zombies; x++){
            playingBoard.setObject(x_, y_, zombieNum_[x]);
        };
    }

    //TODO : getY(), getX(), move(), and else
};

void displayMenu();
void showGameSettings(const int &rows, const int &columns, const int &zombies);
void changeGameSettings(int &rows, int &columns, int &zombies);
void startGame(const int &boardColumns, const int &boardRows, const int &numOfZombies, int &zombies);
void gameDashboard();
void gameControl(Alien &player, Board &playingBoard);
void commandHelp();





int main(){
    cout << "Assignment (Part 1)" << endl;
    cout << "Let's Get Started!" << endl;

    char choice;
    int numOfRows{3}, numOfColumns{19}, numOfZombies{1}, zombies;
    bool done{0};
    Alien player;
    Zombie bots;


    displayMenu();
    cin >> choice;
    
    switch (choice)
    {
    case '1':
        showGameSettings(numOfColumns, numOfRows, numOfZombies);
        changeGameSettings(numOfColumns, numOfRows, numOfZombies);
        startGame(numOfColumns, numOfRows, numOfZombies, zombies);
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

    cout << "\nGame Settings\n";
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
        void changeGameSettings(int &rows, int &columns, int &zombies);
        return;
    case 'n':
        break;
    default:
        cout << "Invalid selection, try again!";
    }
}

void changeGameSettings(int &rows, int &columns, int &zombies){
    cout << "Board Settings\n";
    cout << "------------------\n";

    cout << "Enter rows => ";
    cin >> rows;
    cout << "Enter columns => ";
    cin >> columns;

    cout << "\nZombie Settings\n";
    cout << "------------------\n";

    cout << "Enter number of zombies => ";
    cin >> zombies;
}


void startGame(const int &boardColumns, const int &boardRows, const int &numOfZombies, int &zombies){
    Board playingBoard = Board(boardColumns, boardRows);
    
    Alien player;
    player.initPos(playingBoard);

    Zombie bots;
    bots.zombiePos(playingBoard, zombies);

    while (true){
        
        playingBoard.display();
         //gameDashboard()
        gameControl(player, playingBoard);

    }
    
}
   



void gameDashboard(){
    // This function display the status of entity on the board

}

void gameControl(Alien &player, Board &playingBoard){
    string userInput;
    cout << "Command> ";
    cin >> userInput;

    if(userInput == "up" || "down" || "left" || "right"){
        player.move(userInput, playingBoard);
    }
    if(userInput == "arrow"){
        playingBoard.arrowDirection();
    }
    if(userInput == "help"){
        commandHelp();
    }
    if(userInput == "save"){
        
    }
    if(userInput == "load"){
        
    }
    if(userInput == "quit"){
        exit(0);
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





