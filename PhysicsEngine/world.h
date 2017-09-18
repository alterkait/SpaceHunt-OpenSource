#ifndef _WORLD_HPP_
#define _WORLD_HPP_

#include <vector>
#include <string>

#include "Simulation.hpp"
class Simulation;
#include "Vehicle.hpp"
class Vehicle;

class World
{
    private:
        std::vector<Vehicle*> vehicles;
        unsigned long time_ms;
        Simulation *simulation; // A world must exist as part of a simulation
    public:
        World(Simulation *simulation);
        void attach_vehicle(Vehicle *vehicle);
        void debugging_message(std::string message);
};

#endif
