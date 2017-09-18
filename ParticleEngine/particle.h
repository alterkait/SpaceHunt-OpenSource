#pragma once

#include <SFML/Graphics.hpp>

namespace particles 
{

class ParticleData 
{
public:
	explicit ParticleData(int maxCount);
	~ParticleData();

	ParticleData(const ParticleData &) = delete;
	ParticleData &operator=(const ParticleData &) = delete;

	void kill(int id);
	void swapData(int id1, int id2);
  }
  }
