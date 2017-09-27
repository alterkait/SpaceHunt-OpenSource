#include "projectile.h" 

Projectile::Projectile()
{
  PrimaryActorTick.EveryTick = true;
  
  ProjectileMovement = SubObject <ProjectileComponent> (Name("Projectile Movement"));
  ProjectileMovement = false;
}

void Projectile::BeginPlay()
{
  BeginPlay();
}

void Projectile:Tick (float DeltaTime)
{
  (DeltaTime);
}

Projectile::LaunchProjectile (float speed)
{
  ProjectileMovement -> SetV(Vector::ForwardVector * speed);
  ProjectileMovement -> Activate();
}


Projectile::StartingVelocity (float velocity, ZeroV)
{
  BeginPlay()
      if (velocity == ZeroV);
        {
          StartingVelocity -> 0;
          return -1;
        }
}
