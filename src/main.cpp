#include <iostream>
#include "orbit_propagator.hpp"
#include "perturbation.cpp"
#include "orbit_propagator.cpp"
#include "opengl_visualizer.hpp"

int main(int argc, char** argv) {
    Vector3D initial_position = {7000.0, 0.0, 0.0};  // km
    Vector3D initial_velocity = {0.0, 7.5, 0.0};    // km/s
    double timestep = 10.0;
    int num_steps = 1000;
    double satellite_mass = 500;
    double satellite_area = 0.01;

    Orbit_propagator simulator(initial_position, initial_velocity, timestep, satellite_mass, satellite_area);
    
    std::vector<Vector3D> orbit_points;
    
    for (int i = 0; i < num_steps; ++i) {
        Vector3D pos = simulator.getposition();
        orbit_points.push_back(pos);
        simulator.propagateRK4(1);
    }

    initOpenGL(argc, argv);
    setOrbitData(orbit_points);
    startRendering();

    return 0;
}


