#include <iosfwd>

class Board;
class Zombie;


class Alien{
private:
    int life_{100}, attack_{0}, x_, y_;
    char heading_{'A'}, trail_{'.'};
    bool turns_{1};

public:
    Alien(){};
    int getX() const;
    int getY() const;
    void alienStatus();
    void lifeUpdate(int &damage);
    void initPos(Board &playingBoard);
    void move(const std::string &input, Board &playingBoard, Zombie &bots, Alien &player, const int &numOfZombies);
    void moveStep(int &oldPosX, int &oldPosY, int &newPosX, int &newPosY, Board &playingBoard , Zombie &bots, Alien player, const int &numOfZombies);
    void moveUp(Board &playingBoard, Zombie &bots, Alien &player, const int &numOfZombies);
    void moveDown(Board &playingBoard, Zombie &bots, Alien &player, const int &numOfZombies);
    void moveLeft(Board &playingBoard, Zombie &bots, Alien &player, const int &numOfZombies);
    void moveRight(Board &playingBoard , Zombie &bots, Alien &player, const int &numOfZombies);
    void moveObstacles(Board &playingBoard, int &newposX, int &newPosY, Zombie &bots, Alien &player, const int &numOfZombies);
    void healthObstacles(Board &playingBoard, Zombie &bots, Alien &player, const int &numOfZombies);
    void podObstacles(Board &playingBoard, Zombie &bots, Alien &player, int &xPos, int &yPos, const int &numOfZombies);
    void rockObstacles(Board &playingBoard, Zombie &bots, Alien &player, int &x, int y, const int &numOfZombies);
    void borderObstacles(Board &playingBoard, Zombie &bots, Alien &player, const int &numOfZombies);
    void arrowObstacles(Board &playingBoard,  Alien &player, Zombie &bots, const int &numOfZombies);
    void moveArrow(Board &playingBoard, Alien &player, const char &arrowObj, Zombie &bots, const int &numOfZombies);
    void attack(Board &playingBoard, int &newX, int &newY, Zombie &bots);
    bool setTurns();
    bool getTurns();
};