
#include "globals.h"
#include <conio.h>
#include <fstream>
#include <iostream>
#include <string>

#define PStarShip 50

using namespace std;
enum background {SPACE = 1, STATIC, UNBREAKABLE};
enum directions {LEFT = -1, UP = -1, RIGHT = 1, DOWN = 1, NOT = 0};
enum PLaser {PLASERBREAK};
enum moves {MDOWN = 0, MUP, MLEFT, MRIGHT};

int map_id, Enemy::position, spawn_pos::s_no;

map_id = 1;
Enemy::position = 0;
spawn_pos::s_no = 0;

spawn_pos::s_no() 
{
  y = 0;
  x = BW * 3;
  
  cout << X << " ";
  s_no++;
}

EnemyTank::EnemyTank(int inte)
{
    Enemy::x = sp.x;
    Enemy::y = sp.y;
    CoolDown = 0;
    storeCooltime = 5000;
    intelligence = inte;
    tmpstorex = storex = 300; tmpstorey = storey = 300;

    clip.x = 0 * TW; clip.y = 1 * TH;
    clip.w = TW; clip.h = TH;
  
      for(int i = 0; i < 3; ++i)
        {
          if(i == 0) priority[i] = 100;
            else priority[i] = 350;
        }
  
}
