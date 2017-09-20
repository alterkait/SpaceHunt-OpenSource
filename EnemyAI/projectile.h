#pragma once

#include "ProjectileGeneration.h"

UCLASS()
{
GENERATED_BODY()
}

public:
  Projectile();
  virtual void BeginPlay() override;
  virtual void Tick(float DeltaSeconds) override;
  void LaunchProjectile (float speed);
  
private:
  ProjectileComponent* ProjectileMovement = nullptr;
