#include "aircraft_factory.hpp"

std::unique_ptr<Aircraft> AircraftFactory::create_aircraft(Airport& airport, const AircraftType& type)
{
    assert(&airport); // make sure the airport is initialized before creating aircraft
    assert(&type);

    int num_airline           = std::rand() % 8;
    std::string flight_number = airlines[num_airline] + std::to_string(1000 + (rand() % 9000));
    while (flight_numbers.find(flight_number) != flight_numbers.end())
    {
        flight_number = airlines[std::rand() % 8] + std::to_string(1000 + (rand() % 9000));
    }
    flight_numbers.emplace(flight_number);
    const float angle       = (rand() % 1000) * 2 * 3.141592f / 1000.f; // random angle between 0 and 2pi
    const Point3D start     = Point3D { std::sin(angle), std::cos(angle), 0 } * 3 + Point3D { 0, 0, 2 };
    const Point3D direction = (-start).normalize();

    return std::make_unique<Aircraft>(type, flight_number, start, direction, *(&airport.get_tower()),
                                      num_airline);
}

std::unique_ptr<Aircraft> AircraftFactory::create_random_aircraft(Airport& airport)
{
    assert(&airport);
    return create_aircraft(airport, *(aircraft_types[rand() % 3]));
}