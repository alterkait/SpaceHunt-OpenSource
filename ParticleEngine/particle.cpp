#include "Particle.h"

namespace particles
{
  ParticleData::ParticleData(int maxSize) : count(maxSize), countAlive(0) 
  {
    pos = new sf::Vector2f[maxSize];
    vel = new sf::Vector2f[maxSize];
    acc = new sf::Vector2f[maxSize];
    time = new sf::Vector3f[maxSize];
    size = new sf::Vector3f[maxSize];
    angle = new sf::Vector3f[maxSize];
    col = new sf::Color[maxSize];
    startCol = new sf::Color[maxSize];
    endCol = new sf::Color[maxSize];
    texCoords = new sf::IntRect[maxSize];
    frame = new int[maxSize];
    frameTimer = new float[maxSize];
  }
      ParticleData::~ParticleData() {
        delete pos;
        delete vel;
        delete acc;
        delete time;
        delete size;
        delete angle;
        delete col;
        delete startCol;
        delete endCol;
        delete texCoords;
        delete frame;
        delete frameTimer;
}
  
  void ParticleData::kill(int id) 
  {
	if (countAlive > 0) 
    {
      swapData(id, countAlive - 1);
      countAlive--;
	  }
}
