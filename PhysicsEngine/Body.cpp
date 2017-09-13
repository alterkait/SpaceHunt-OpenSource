#include "Precompiled.h"

Body::Body( Shape *shape_, uint32 x, uint32 y)
{
  shape->body = this;
  position.set (real(x), real(y));
  velocity.set (0, 0);
  angularVelocity = 0;
  force.set (0, 0);
  staticFriction = 0.5f;
  dynamicFriction = 0.3f;
  
}

void Body::SetOrient (real radians)
{
  orient = radians;
}
