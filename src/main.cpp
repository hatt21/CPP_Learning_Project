#include "tower_sim.hpp"

void test_generic_points()
{
    Point<3, int> p1 { 1, 2, 3 };
    Point<3, int> p2 { 1, 2, 3 };
    auto p3 = p1 + p2;
    p1 += p2;
    p1 *= 3; // ou 3.f, ou 3.0 en fonction du type de Point
    std::cout << p3.x() << std::endl;

    /*Point2D p4 { 1., 2., 3. };
    std::cout << p4.x() << std::endl;*/

    /*Point3D p4 { 1., 2. };
    std::cout << p4.x() << std::endl;*/

    /*Point<5, float> p4 { 1.2, 2.3, 3.4, 4.5, 5.6 ,6.6};
    std::cout << p4.x() << std::endl;*/

    Point<5, float> p4 { 1.2, 2.3, 3.4, 4.5, 5.6 };
    std::cout << p4.x() << std::endl;
}

int main(int argc, char** argv)
{
    TowerSimulation simulation { argc, argv };
    simulation.launch();
    // test_generic_points();

    return 0;
}