#ifndef ORBIT_PROPAGATOR_HPP
#define ORBIT_PROPAGATOR_HPP

#include "utils.hpp"
#include "perturbation.hpp"

class Orbit_propagator{
    public:
        Orbit_propagator(Vector3D position, Vector3D velocity, double timestep, double mass, double area);
        void propagateEuler(int steps);
        void propagateRK4(int steps);
        Vector3D getposition() const;
        Vector3D getVelocity() const;

    private:
        Vector3D position;
        Vector3D velocity;
        double dt;
        double mass;
        double area;

        Vector3D computeacceleration(Vector3D pos, Vector3D vel);  
};

#endif