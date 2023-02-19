#include <iosfwd>
#include <vector>
using namespace std;

class Board;
class Alien;

class Zombie
{
private:
    int life_, attack_, range_, x_, y_, zombieIndex_, numOfZombies_;
    char zombie_;
    char zombieNum_[9] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
    bool turns_{0};
    vector<int> xCoord_, yCoord_, vecAttack_, vecLife_, vecRange_;
    int zombies_[9][5];

public:
    Zombie();
    int getX() const;
    int getY() const;
    int zombieTurns();
    void setPosX(const int &index, int &xcoord);
    int getPosX(int &i);
    void setPosY(const int &index, int &ycoord);
    int getPosY(int &i);
    void setAttack(const int &index, const int &attack);
    void getAttack();
    void setLife(const int &index, const int &life);
    void lifeUpdate(const int &index, int &damage);
    int getLife(Board &playingBoard, const int &index);
    void setRange(const int &index, const int &range);
    void getRange();
    void zombieAttributes(const int &numOfZombies);
    void zombieStatus(const int &numOfZombies);
    void zombiePos(Board &playingBoard, const int &numOfZombies);
    void savePos();
    void zombieMainMove(Board &playingBoard, Alien &player, Zombie &bots, const int &numOfZombies);
    void zombieMove(Board &playingBoard);
    void zombieUp(Board &playingBoard);
    void zombieDown(Board &playingBoard);
    void zombieLeft(Board &playingBoard);
    void zombieRight(Board &playingBoard);
    void zombieAttack(Board &playingBoard, Alien &player);


};