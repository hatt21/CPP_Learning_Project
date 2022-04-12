#include "aircraft_manager.hpp"

void AircraftManager::move()
{
    for (auto it = aircrafts.begin(); it != aircrafts.end(); it++)
    {
        if (!(*it)->move())
        {
            it = aircrafts.erase(it);
        }
    }
}

void AircraftManager::add(std::unique_ptr<Aircraft> aircraft)
{
    aircrafts.emplace_back(std::move(aircraft));
}