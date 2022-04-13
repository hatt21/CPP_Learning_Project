#include "aircraft_manager.hpp"

void AircraftManager::move()
{
    aircrafts.erase(std::remove_if(aircrafts.begin(), aircrafts.end(),
                                   [](const auto& aircraft) { return !(aircraft)->move(); }),
                    aircrafts.end());
}

void AircraftManager::add(std::unique_ptr<Aircraft> aircraft)
{
    aircrafts.emplace_back(std::move(aircraft));
}

void AircraftManager::count_aircrafts(int num_airline) const
{
    std::cout << "Airline " << airlines[num_airline] << " contains "
              << std::count_if(aircrafts.begin(), aircrafts.end(),
                               [num_airline](const auto& aircraft)
                               { return aircraft->get_num_airline() == num_airline; })
              << " plane(s)" << std::endl;
}
