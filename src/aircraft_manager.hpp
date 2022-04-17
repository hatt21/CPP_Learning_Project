#pragma once

#include "aircraft.hpp"

#include <algorithm>
#include <memory>
#include <numeric>
#include <vector>

class AircraftManager : public GL::DynamicObject
{
private:
    std::vector<std::unique_ptr<Aircraft>> aircrafts;
    const std::string airlines[8] = { "AF", "LH", "EY", "DL", "KL", "BA", "AY", "EY" };
    int crash_counter             = 0;

public:
    void move() override;
    void add(std::unique_ptr<Aircraft> aircraft);
    void count_aircrafts(int num_airline) const;
    int get_required_fuel() const;
    void print_crash_counter() const;
};