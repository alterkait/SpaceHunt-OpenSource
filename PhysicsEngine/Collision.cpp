#include "Precompiled.h"

CollisionCallBack Dispatch[Shape::eCount][Shape::eCount] =
{
  {
      CircleToCircle, CircleToPolygon
  },
  {
    PolygonToCircle, PolygonToPolygon
  },
};

void CircleToCircle (Manifold *m, Body *a, Body *b)
{
  Circle *A = reinterpret_cast<Circle *>;
  Circle *B = reinterpret_cast<Circle *>;
  
  Vec2 normal = b->position - a->position;
  
    if(dist_sqr >= radius * radius)
      {
        return 0;
      }
  real distance;
  distance = std::sqrt (dist_sqrt);
    
    if(distance == 0.f)
      {
        m->normal = Vec2 (1, 0);
      } 
        else
        {
          m -> normal;
          m -> normal = normal / distance; 
        }
}


