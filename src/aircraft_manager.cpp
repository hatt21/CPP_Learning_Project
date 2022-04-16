#include "aircraft_manager.hpp"

void AircraftManager::move()
{
    std::sort(aircrafts.begin(), aircrafts.end(),
              [](auto& a, auto& b)
              {
                  if (!a->has_terminal() && b->has_terminal())
                  {
                      return false;
                  }
                  if (a->has_terminal() && !b->has_terminal())
                  {
                      return true;
                  }
                  return a->get_fuel() < b->get_fuel();
              });
    aircrafts.erase(std::remove_if(aircrafts.begin(), aircrafts.end(),
                                   [](const auto& aircraft)
                                   {
                                       try
                                       {
                                           return !aircraft->move();
                                       } catch (AircraftCrash& err)
                                       {
                                           std::cerr << err.what() << std::endl;
                                           return true;
                                       }
                                   }),
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

int AircraftManager::get_required_fuel() const
{
    return std::reduce(aircrafts.begin(), aircrafts.end(), 0,
                       [](int sum, auto& aircraft)
                       {
                           if (aircraft->is_low_on_fuel() && aircraft->get_is_at_terminal())
                           {
                               return sum + (3000 - aircraft->get_fuel());
                           }
                           return sum;
                       });
}
