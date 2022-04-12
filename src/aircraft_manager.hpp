#pragma once

#include "aircraft.hpp"

#include <memory>
#include <vector>

class AircraftManager : public GL::DynamicObject
{
private:
    std::vector<std::unique_ptr<Aircraft>> aircrafts;

public:
    void move() override;
    void add(std::unique_ptr<Aircraft> aircraft);
};