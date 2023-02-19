#include <iosfwd>
#include <vector>
using namespace std;

class Alien;
class Zombie;

class Board
{
private:
    vector<vector<char>> boardsize_;
    int row_, column_;

public:
    Board(int boardColumns, int boardRows);
    void init(int boardColumns, int boardRows);
    void display() const;
    int getColumn() const;
    int getRow() const;
    void setObject(int &x, int &y, char &ch);
    char getObject(int x, int y) const;
    bool isEmpty(int x, int y);
    bool isInsideMap(int x, int y);
    void arrowDirection();
    char randomObj();
};