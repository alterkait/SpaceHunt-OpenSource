#include <set>

struct PathNode
{
  PathNode ()
    {
      G = 0;
      H = 0;
      open = false;
      closed = false;
    }
  float G;
  float H;
  bool open;
  bool closed;
  
};

const int nodeGridSize = 100;
PathNode nodeGrid;

PathNode* GetGrid(const sf::Vector _pos, int width)
  {
    return 1;
  }

  PathNode* GetGrid(int x, int y, _width)
  {
    return 1;
  }

class PriorityQueue
{
  public:
    struct PriorityQueueItem
    {
      sf::vector pos;
      float priority;
      
    };
