#include <iostream>
#include <vector>
#include <random>
#include <iomanip>
#include <cstdlib>
#include "display.h"
#include "alien.h"
#include "zombie.h"

using namespace std;

    int Alien::getX() const
    {
        return x_;
    }

    int Alien::getY() const
    {
        return y_;
    }

    void Alien::alienStatus()
    {
        cout << "Alien: Life: " << life_ << " Attack: " << attack_ << endl;
    }

    void Alien::lifeUpdate(int &damage)
    {
        life_ = life_ - damage;
    }

    void Alien::initPos(Board &playingBoard)
    {

        x_ = playingBoard.getColumn() / 2 + 1;
        y_ = (playingBoard.getRow() / 2) + 1;

        playingBoard.setObject(x_, y_, heading_);
    }

    void Alien::move(const string &input, Board &playingBoard, Zombie &bots, Alien &player, const int &numOfZombies)
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

    void Alien::moveStep(int &oldPosX, int &oldPosY, int &newPosX, int &newPosY, Board &playingBoard , Zombie &bots, Alien player, const int &numOfZombies)
    {
        char obj = playingBoard.getObject(newPosX, newPosY);

        playingBoard.setObject(x_, y_, heading_);
        playingBoard.setObject(oldPosX, oldPosY, trail_);

        if (obj == '>' || '<' || '^' || 'v')
        {
            moveArrow(playingBoard, player, obj, bots, numOfZombies);
        }
    }

    void Alien::moveUp(Board &playingBoard, Zombie &bots, Alien &player, const int &numOfZombies)
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

    void Alien::moveDown(Board &playingBoard, Zombie &bots, Alien &player, const int &numOfZombies)
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

    void Alien::moveLeft(Board &playingBoard, Zombie &bots, Alien &player, const int &numOfZombies)
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

    void Alien::moveRight(Board &playingBoard , Zombie &bots, Alien &player, const int &numOfZombies)
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

    void Alien::moveObstacles(Board &playingBoard, int &newposX, int &newPosY, Zombie &bots, Alien &player, const int &numOfZombies)
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

    void Alien::healthObstacles(Board &playingBoard, Zombie &bots, Alien &player, const int &numOfZombies)
    {
        cout << "Alien finds a health pack.\n";
        cout << "Alien's life is increased by 20\n\n";

        life_ += 20;
        cout << "Alien: \nLife: " << life_ << " Attack: " << attack_ << "\n\n";

        playingBoard.display();

        system("pause");
    }

    void Alien::podObstacles(Board &playingBoard, Zombie &bots, Alien &player, int &xPos, int &yPos, const int &numOfZombies)
    {
        playingBoard.display();
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

    void Alien::rockObstacles(Board &playingBoard, Zombie &bots, Alien &player, int &x, int y, const int &numOfZombies)
    {
        cout << "Alien stumbles upon a rock\n";

        char objects[] = {'h', 'p', ' ', '>', '<', '^', 'v', ' ', ' ', ' ', ' ', ' '};
        int noOfObjects = 12;

        static random_device device;
        uniform_int_distribution<int> random(0, noOfObjects - 1);

        char newObj = objects[random(device)];

        playingBoard.display();

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

    void Alien::borderObstacles(Board &playingBoard, Zombie &bots, Alien &player, const int &numOfZombies)
    {
        playingBoard.display();
        cout << "Alien hits a border.\n\n";
        system("pause");

        turns_ = 0;
    }

    void Alien::arrowObstacles(Board &playingBoard,  Alien &player, Zombie &bots, const int &numOfZombies)
    {
        playingBoard.display();
        cout << "Alien finds an arrow\n";
        cout << "Alien's attack is increase by 20\n\n";

        attack_ += 20;
        cout << "Alien: \nLife: " << life_ << " Attack: " << attack_ << "\n\n";

        system("pause");
    }

    void Alien::moveArrow(Board &playingBoard, Alien &player, const char &arrowObj, Zombie &bots, const int &numOfZombies)
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

    void Alien::attack(Board &playingBoard, int &newX, int &newY, Zombie &bots)
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

    bool Alien::setTurns(){
        return turns_ = 1;
    }

    bool Alien::getTurns(){
        return turns_;
    }