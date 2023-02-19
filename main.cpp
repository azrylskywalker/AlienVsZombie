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

class Board;
class Alien;
class Zombie;

class Board
{
private:
    vector<vector<char>> boardsize_;
    int row_, column_;

public:
    Board(int boardColumns, int boardRows)
    {

        init(boardColumns, boardRows);
    }

    void init(int boardColumns, int boardRows)
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

    void display(Zombie &bots, Alien &player, const int &numOfZombies) const
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

        gameDashboard(bots, player, numOfZombies);
    }

    int getColumn() const
    {
        return column_;
    }

    int getRow() const
    {
        return row_;
    }

    void setObject(int &x, int &y, char &ch)
    {
        boardsize_[-(y - row_)][x - 1] = ch;
    }

    char getObject(int x, int y) const
    {
        return boardsize_[-(y - row_)][x - 1];
    }

    bool isEmpty(int x, int y)
    {
        return isspace(boardsize_[-(y - row_)][x - 1]);
    }

    bool isInsideMap(int x, int y)
    {
        return (x > 0 && x <= column_ && y > 0 && y <= row_);
    }

    void arrowDirection()
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

    char randomObj(){
        char objects[] = {'h', 'p', 'r', '>', '<', '^', 'v', ' ', ' ', ' ', ' ', ' '};
        int noObj = 12;

        static random_device random;
        uniform_int_distribution<int> obj(0, noObj);

        return objects[obj(random)];
    }
};

class Zombie
{
private:
    int life_, attack_, range_, x_, y_, zombieIndex_, numOfZombies_;
    char zombie_;
    char zombieNum_[9] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
    bool turns_{0};
    vector<int> xCoord_, yCoord_, vecAttack_, vecLife_, vecRange_;
    int zombies_[9][5];

    //index 0, 1 = x, y . ,,,,,

public:
    Zombie(){};

    int getX() const
    {
        return x_;
    }

    int getY() const
    {
        return y_;
    }

    int zombieTurns(){
        return turns_ = 1;
    }

    void setPosX(const int &index, int &xcoord){ 
        
        zombies_[index][0] = xcoord;
    }

    int getPosX(int &i){
       return x_ = zombies_[i][0];
    }

    void setPosY(const int &index, int &ycoord){ 
        
        zombies_[index][1] = ycoord;
    }

    int getPosY(int &i){

       return y_ = zombies_[i][1];
    }

    void setAttack(const int &index, const int &attack){ 
        
        zombies_[index][2] = attack;
    }

    void getAttack(){
        attack_ = zombies_[zombieIndex_][2];
    }

    void setLife(const int &index, const int &life){ 
        
        zombies_[index][3] = life;
    }

    void lifeUpdate(const int &index, int &damage){
        zombies_[index][3] -= damage;
    }

    int getLife(Board &playingBoard, const int &index){
        return life_ = zombies_[index][3];
    }

    void setRange(const int &index, const int &range){ 
        
        zombies_[index][4] = range;
    }

    void getRange(){
        range_ = zombies_[zombieIndex_][4];
    }

    //int getAttack()
    //{
    //    return attack_;
    //}

    void zombieAttributes(const int &numOfZombies)
    {
        for (int x = 1; x <= numOfZombies; x++)
        {
            srand(time(NULL));
            range_ = 1 + (rand() % 5);
            setRange((x - 1), range_);
            life_ = 100 + (rand() % 201);
            setLife((x - 1), life_);
            attack_ = 5 + (rand() % 30);
            setAttack((x - 1), attack_);
        }
    }

    void zombieStatus(const int &numOfZombies)
    {
        for (int i = 1; i <= numOfZombies; i++)
        cout << "Zombie " << i << " : Life " << zombies_[i-1][3] << ", Attack " << zombies_[i-1][2] << ", Range " << zombies_[i-1][4] << endl;
        cout << endl;
    }

    void zombiePos(Board &playingBoard, const int &numOfZombies)
    {
        static random_device random;
        uniform_int_distribution<int> column(0, playingBoard.getColumn() - 1);
        uniform_int_distribution<int> row(0, playingBoard.getRow() - 1);

        numOfZombies_ = numOfZombies;


        for (int x = 0; x < numOfZombies; x++)
        {
            x_ = column(random);
            y_ = row(random);

            while (playingBoard.getObject(x_, y_) == 'A')
            {
                x_ = column(random);
                y_ = row(random);
            }

            setPosX(x, x_);
            setPosY(x, y_);
           
            //check the box first bfr place on board

            playingBoard.setObject(x_, y_, zombieNum_[x]);
        };

        zombieAttributes(numOfZombies);
    }

    void savePos(){
        zombies_[zombieIndex_][0] = x_;
        zombies_[zombieIndex_][1] = y_;
    }

    void zombieMainMove(Board &playingBoard, Alien &player, Zombie &bots, const int &numOfZombies)
    {
        if (turns_)
        {
            for (int x = 0; x < numOfZombies; x++)
            {
                zombie_ = zombieNum_[x];

                zombieIndex_ = x;

                getPosX(zombieIndex_);
                getPosY(zombieIndex_);

                 //get obstacles. if obstacle find empty

                zombieMove(playingBoard);
                zombieAttack(playingBoard, player);
                playingBoard.display(bots, player, numOfZombies);
            }
            turns_ = 0;
        }

    }


    void zombieMove(Board &playingBoard)
    {
        int noOfMoves = 4;
        char zombie_;
    
        srand(time(NULL));
        int moves = rand() % 4 + 1;

        switch (moves)
        {
        case 1:
            zombieUp(playingBoard);
            break;

        case 2:
            zombieDown(playingBoard);
            break;

        case 3:
            zombieLeft(playingBoard);
            break;

        case 4:
            zombieRight(playingBoard);
            break;
        }
    }

    void zombieUp(Board &playingBoard)
    {
        getPosX(zombieIndex_);
        getPosY(zombieIndex_);

        int oldZomPosX{x_}, oldZomPosY{y_};
        int newZomPosX{x_}, newZomPosY{y_ + 1};

        int x_ = newZomPosX;
        int y_ = newZomPosY;

        char newObj = playingBoard.randomObj();

        if (playingBoard.getObject(newZomPosX, newZomPosY) != 'A' || playingBoard.getObject(newZomPosX, newZomPosY) == zombie_ )
        {
            playingBoard.setObject(newZomPosX, newZomPosY, zombie_);
            playingBoard.setObject(oldZomPosX, oldZomPosY, newObj);

            
        }

        else{
            zombieMove(playingBoard);
        }
        cout << "Zombie " << zombie_ << " moves up.\n";

        system("pause");

        savePos();

    }

    void zombieDown(Board &playingBoard)
    {
        getPosX(zombieIndex_);
        getPosY(zombieIndex_);

        int oldZomPosX{x_}, oldZomPosY{y_};
        int newZomPosX{x_}, newZomPosY{y_ - 1};

        //getPosX();
        //getPosY();

        int x_ = newZomPosX;
        int y_ = newZomPosY;

        char newObj = playingBoard.randomObj();

        if (playingBoard.getObject(newZomPosX, newZomPosY) != 'A' || zombie_ )
        {
            playingBoard.setObject(newZomPosX, newZomPosY ,zombie_);
            playingBoard.setObject(oldZomPosX, oldZomPosY, newObj);
        }

         else{
            zombieMove(playingBoard);
        }
            cout << "Zombie " << zombie_ << " moves down.\n";

            system("pause");

            savePos();
        
    }

    void zombieLeft(Board &playingBoard)
    {
        getPosX(zombieIndex_);
        getPosY(zombieIndex_);

        int oldZomPosX{x_}, oldZomPosY{y_};
        int newZomPosX{x_ - 1}, newZomPosY{y_};

        int x_ = newZomPosX;
        int y_ = newZomPosY;

        char newObj = playingBoard.randomObj();

        if (playingBoard.getObject(newZomPosX, newZomPosY) != 'A' || zombie_ )
        {
            playingBoard.setObject(newZomPosX, newZomPosY, zombie_);
            playingBoard.setObject(oldZomPosX, oldZomPosY, newObj);
        }

         else{
            zombieMove(playingBoard);
        }
        cout << "Zombie " << zombie_ << " moves left.\n";

        system("pause");

        savePos();
        
    }

    void zombieRight(Board &playingBoard)
    {
        getPosX(zombieIndex_);
        getPosY(zombieIndex_);

        int oldZomPosX{x_}, oldZomPosY{y_};
        int newZomPosX{x_ + 1}, newZomPosY{y_};

        int x_ = newZomPosX;
        int y_ = newZomPosY;

        char newObj = playingBoard.randomObj();

        if (playingBoard.getObject(newZomPosX, newZomPosY) != 'A' || zombie_ )
        {
            playingBoard.setObject(newZomPosX, newZomPosY, zombie_);
            playingBoard.setObject(oldZomPosX, oldZomPosY, newObj);
        }

         else{
            zombieMove(playingBoard);
        }
        cout << "Zombie " << zombie_ << " moves right.\n";

        system("pause");

        savePos();
        
    }

    void zombieAttack(Board &playingBoard, Alien &player);
};

class Alien
{
private:
    int life_{100}, attack_{0}, x_, y_;
    char heading_{'A'}, trail_{'.'};
    bool turns_{1};

public:
    Alien(){};

    int getX() const
    {
        return x_;
    }

    int getY() const
    {
        return y_;
    }

    void alienStatus()
    {
        cout << "Alien: Life: " << life_ << " Attack: " << attack_ << endl;
    }

    void lifeUpdate(int &damage)
    {
        life_ = life_ - damage;
    }

    void initPos(Board &playingBoard)
    {

        x_ = playingBoard.getColumn() / 2 + 1;
        y_ = (playingBoard.getRow() / 2) + 1;

        playingBoard.setObject(x_, y_, heading_);
    }

    void move(const string &input, Board &playingBoard, Zombie &bots, Alien &player, const int &numOfZombies)
    {
        if (input == "up")
        {
            moveUp(playingBoard, bots, player, numOfZombies);
        }
        else if (input == "down")
        {
            moveDown(playingBoard, bots, player, numOfZombies);
        }
        else if (input == "left")
        {
            moveLeft(playingBoard, bots, player, numOfZombies);
        }
        else if (input == "right")
        {
            moveRight(playingBoard, bots, player, numOfZombies);
        }
    }

    void moveStep(int &oldPosX, int &oldPosY, int &newPosX, int &newPosY, Board &playingBoard , Zombie &bots, Alien player, const int &numOfZombies)
    {
        char obj = playingBoard.getObject(newPosX, newPosY);

        playingBoard.setObject(x_, y_, heading_);
        playingBoard.setObject(oldPosX, oldPosY, trail_);

        if (obj == '>' || '<' || '^' || 'v')
        {
            moveArrow(playingBoard, player, obj, bots, numOfZombies);
        }
    }

    void moveUp(Board &playingBoard, Zombie &bots, Alien &player, const int &numOfZombies)
    {
        while (turns_)
        {
            int oldPosX{x_}, oldPosY{y_};
            int newposX{x_}, newPosY{y_ + 1};

            moveObstacles(playingBoard, newposX, newPosY, bots, player, numOfZombies);

            if (turns_)
            {
                y_++;
                moveStep(oldPosX, oldPosY, newposX, newPosY, playingBoard, bots, player, numOfZombies);
            }
        }
    }

    void moveDown(Board &playingBoard, Zombie &bots, Alien &player, const int &numOfZombies)
    {
        while (turns_)
        {
            int oldPosX{x_}, oldPosY{y_};
            int newposX{x_}, newPosY{y_ - 1};

            moveObstacles(playingBoard, newposX, newPosY, bots, player, numOfZombies);

            if (turns_)
            {
                y_--;
                moveStep(oldPosX, oldPosY, newposX, newPosY, playingBoard, bots, player, numOfZombies);
            }
        }
    }

    void moveLeft(Board &playingBoard, Zombie &bots, Alien &player, const int &numOfZombies)
    {
        while (turns_)
        {
            int oldPosX{x_}, oldPosY{y_};
            int newposX{x_ - 1}, newPosY{y_};

            moveObstacles(playingBoard, newposX, newPosY, bots, player, numOfZombies);

            if (turns_)
            {
                x_--;
                moveStep(oldPosX, oldPosY, newposX, newPosY, playingBoard, bots, player, numOfZombies);
            }
        }
    }

    void moveRight(Board &playingBoard , Zombie &bots, Alien &player, const int &numOfZombies)
    {
        while (turns_)
        {
            int oldPosX{x_}, oldPosY{y_};
            int newposX{x_ + 1}, newPosY{y_};

            moveObstacles(playingBoard, newposX, newPosY, bots, player, numOfZombies);

            if (turns_)
            {
                x_++;
                moveStep(oldPosX, oldPosY, newposX, newPosY, playingBoard, bots, player, numOfZombies);
            }
        }
    }

    void moveObstacles(Board &playingBoard, int &newposX, int &newPosY, Zombie &bots, Alien &player, const int &numOfZombies)
    {
        if (playingBoard.getObject(newposX, newPosY) == 'h')
        {
            healthObstacles(playingBoard, bots, player, numOfZombies);
        }
        else if (playingBoard.getObject(newposX, newPosY) == 'p')
        {
            podObstacles(playingBoard, bots, player, newposX, newPosY, numOfZombies);
        }
        else if (playingBoard.getObject(newposX, newPosY) == 'r')
        {
            rockObstacles(playingBoard, bots, player, newposX, newPosY, numOfZombies);
        }
        else if (!playingBoard.isInsideMap(newposX, newPosY))
        {
            borderObstacles(playingBoard, bots, player, numOfZombies);
        }
        else if ((playingBoard.getObject(newposX, newPosY) == '>') || (playingBoard.getObject(newposX, newPosY) == '<') || playingBoard.getObject(newposX, newPosY) == '^' || playingBoard.getObject(newposX, newPosY) == 'v')
        {
            arrowObstacles(playingBoard, player, bots, numOfZombies);
        }
        else if (isdigit(playingBoard.getObject(newposX, newPosY)))
        {   
            attack(playingBoard, newposX, newPosY, bots);
        }
        
    }

    void healthObstacles(Board &playingBoard, Zombie &bots, Alien &player, const int &numOfZombies)
    {
        cout << "Alien finds a health pack.\n";
        cout << "Alien's life is increased by 20\n\n";

        life_ += 20;
        cout << "Alien: \nLife: " << life_ << " Attack: " << attack_ << "\n\n";

        playingBoard.display(bots, player, numOfZombies);

        system("pause");
    }

    void podObstacles(Board &playingBoard, Zombie &bots, Alien &player, int &xPos, int &yPos, const int &numOfZombies)
    {
        playingBoard.display(bots, player, numOfZombies);
        int podDamage = 20;
        int minDistance;
        int zombieIndex;
        
        for (int i = 0; i < numOfZombies; i++){
            int zombieX = bots.getPosX(i);
            int zombieY = bots.getPosY(i);

            int distance = sqrt ((pow((zombieX-xPos),2.0)) + (pow((zombieY-yPos),2.0)));

            if (i == 0 )
            {
                zombieIndex = i+1;
                minDistance = distance;
            }else if (distance < minDistance)
            {
                zombieIndex = i+1;
                minDistance = distance;
            }
            
        }

        cout << "Minimum distance " << minDistance << "zombie" << zombieIndex;

        bots.lifeUpdate((zombieIndex - 1), podDamage);

        //bots.setLife(zombieIndex, zombieLifeUpdate);
        system("pause");
    }

    void rockObstacles(Board &playingBoard, Zombie &bots, Alien &player, int &x, int y, const int &numOfZombies)
    {
        cout << "Alien stumbles upon a rock\n";

        char objects[] = {'h', 'p', ' ', '>', '<', '^', 'v', ' ', ' ', ' ', ' ', ' '};
        int noOfObjects = 12;

        static random_device device;
        uniform_int_distribution<int> random(0, noOfObjects - 1);

        char newObj = objects[random(device)];

        playingBoard.display(bots, player, numOfZombies);

        switch (newObj)
        {
        case 'h':
            cout << "Alien discovers a health pack beneath the rock.\n\n";
            break;
        case 'p':
            cout << "Alien discovers a pod beneath the rock.\n\n";
            break;
        case '>':
        case '<':
        case '^':
        case 'v':
            cout << "Alien discovers an arrow beneath the rock.\n\n";
            break;
        default:
            cout << "Alien discovers nothing beneath the rock.\n\n";
            break;
        }
        playingBoard.setObject(x, y, newObj);
        system("pause");

        turns_ = 0;
    }

    void borderObstacles(Board &playingBoard, Zombie &bots, Alien &player, const int &numOfZombies)
    {
        playingBoard.display(bots, player, numOfZombies);
        cout << "Alien hits a border.\n\n";
        system("pause");

        turns_ = 0;
    }

    void arrowObstacles(Board &playingBoard,  Alien &player, Zombie &bots, const int &numOfZombies)
    {
        playingBoard.display(bots, player, numOfZombies);
        cout << "Alien finds an arrow\n";
        cout << "Alien's attack is increase by 20\n\n";

        attack_ += 20;
        cout << "Alien: \nLife: " << life_ << " Attack: " << attack_ << "\n\n";

        system("pause");
    }

    void moveArrow(Board &playingBoard, Alien &player, const char &arrowObj, Zombie &bots, const int &numOfZombies)
    {

        switch (arrowObj)
        {
        case '>':
            moveRight(playingBoard, bots, player, numOfZombies);
            break;
        case 'v':
            moveDown(playingBoard, bots, player, numOfZombies);
            break;
        case '<':
            moveLeft(playingBoard, bots, player, numOfZombies);
            break;
        case '^':
            moveUp(playingBoard, bots, player,  numOfZombies);
            break;
        }
    }

    void attack(Board &playingBoard, int &newX, int &newY, Zombie &bots)
    {
        char zombie = playingBoard.getObject(newX, newY);
        int zombieIndex = (int)zombie - 1;
        int zombieLife = bots.getLife(playingBoard, zombieIndex);

        bots.lifeUpdate(zombieIndex, attack_);

        if (bots.getLife(playingBoard, zombieIndex) <= 0)
        {
            char newObj = playingBoard.randomObj();
            playingBoard.setObject(newX, newY, newObj);
        }else{
            turns_ = 0;
        }

    }

    bool setTurns(){
        return turns_ = 1;
    }

    bool getTurns(){
        return turns_;
    }
};


void Zombie::zombieAttack(Board &playingBoard, Alien &player){

    int newZomPosX{x_}, newZomPosY{y_};

    getAttack();
    int attackValue = attack_;
        //int i = range_;
    for(int i = 1; i<range_;i++){
        if (playingBoard.getObject(x_ + i, y_) == 'A' || playingBoard.getObject(x_ - i, y_) == 'A' || playingBoard.getObject(x_, y_+i) == 'A' || playingBoard.getObject(x_ , y_-i) == 'A')
        {
            player.lifeUpdate(attackValue);
            cout << "\nZombie " << zombie_ <<  " has attacked Alien.\n" ; 
            break;
        }else{
            cout << "\nZombie " << zombie_ << " failed to attack\n";
            break;
        }
    }
}



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

        playingBoard.display(bots, player, numOfZombies);
        //gameDashboard(bots, player, numOfZombies);
        gameControl(player, playingBoard, bots, numOfZombies);
        playingBoard.display(bots, player, numOfZombies);
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


