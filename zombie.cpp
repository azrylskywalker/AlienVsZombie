#include <iostream>
#include <vector>
#include <random>
#include <iomanip>
#include <cstdlib>
#include "display.h"
#include "alien.h"
#include "zombie.h"

using namespace std;

Zombie::Zombie(){};

int Zombie::getX() const
{
    return x_;
}

int Zombie::getY() const
{
    return y_;
}

int Zombie::zombieTurns(){
       return turns_ = 1;
}

void Zombie::setPosX(const int &index, int &xcoord){ 
        
    zombies_[index][0] = xcoord;
}

int Zombie::getPosX(int &i){
   return x_ = zombies_[i][0];
}

void Zombie::setPosY(const int &index, int &ycoord){ 
        
    zombies_[index][1] = ycoord;
}

int Zombie::getPosY(int &i){

   return y_ = zombies_[i][1];
}

void Zombie::setAttack(const int &index, const int &attack){ 
        
    zombies_[index][2] = attack;
}

void Zombie::getAttack(){
    attack_ = zombies_[zombieIndex_][2];
}

void Zombie::setLife(const int &index, const int &life){ 
        
    zombies_[index][3] = life;
}

void Zombie::lifeUpdate(const int &index, int &damage){
    zombies_[index][3] -= damage;
}

int Zombie::getLife(Board &playingBoard, const int &index){
    return life_ = zombies_[index][3];
}

void Zombie::setRange(const int &index, const int &range){ 
        
    zombies_[index][4] = range;
}

void Zombie::getRange(){
    range_ = zombies_[zombieIndex_][4];
}

    //int getAttack()
    //{
    //    return attack_;
    //}

void Zombie::zombieAttributes(const int &numOfZombies)
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

void Zombie::zombieStatus(const int &numOfZombies)
{
    for (int i = 1; i <= numOfZombies; i++)
    cout << "Zombie " << i << " : Life " << zombies_[i-1][3] << ", Attack " << zombies_[i-1][2] << ", Range " << zombies_[i-1][4] << endl;
    cout << endl;
}

void Zombie::zombiePos(Board &playingBoard, const int &numOfZombies)
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

void Zombie::savePos(){
    zombies_[zombieIndex_][0] = x_;
    zombies_[zombieIndex_][1] = y_;
}

void Zombie::zombieMainMove(Board &playingBoard, Alien &player, Zombie &bots, const int &numOfZombies)
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
            playingBoard.display();
        }
        turns_ = 0;
    }

}


void Zombie::zombieMove(Board &playingBoard)
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

void Zombie::zombieUp(Board &playingBoard)
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

void Zombie::zombieDown(Board &playingBoard)
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

    void Zombie::zombieLeft(Board &playingBoard)
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

    void Zombie::zombieRight(Board &playingBoard)
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