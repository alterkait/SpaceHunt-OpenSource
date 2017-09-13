#ifndef BODY_H
#define BODY_H

struct Shape;

struct Body
{
  Body( Shape *shape_, uint32 x, uint32 y);
  void ApplyForce( const Vec2& f)
    {
      force += f;
    }
      void ApplyImpulse( const Vec2& impulse, const Vec2& contactVector )
      {
        velocity += im * impulse;
        angularVelocity += iI * Cross( contactVector, impulse );
      }
      
      real staticFriction;
      real dynamicFriction;
      
      Shape *shape;
};

#endif 
