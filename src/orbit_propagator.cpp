#include "../include/perturbation.hpp"
#include "../include/orbit_propagator.hpp"
#include <iostream>
#include <fstream>
#include <cmath>

Orbit_propagator::Orbit_propagator(Vector3D position, Vector3D velocity, double timestep, double mass, double area) : 
position(position), velocity(velocity), dt(timestep), mass(mass), area(area) {}

Vector3D Orbit_propagator::computeacceleration(Vector3D pos, Vector3D vel){
    double r = pos.magnitude();
    Vector3D gravity_acc =  pos*(-mu/(r*r*r));
    Vector3D j2_acc = computeJ2Perturbation(pos); 
    Vector3D drag_acc = computeDrag(position,velocity, mass, area);
    return gravity_acc + j2_acc+ drag_acc;
}

Vector3D Orbit_propagator::getposition() const{
    return this->position;
}

Vector3D Orbit_propagator::getVelocity() const{
    return this->velocity;
}

void Orbit_propagator::propagateEuler(int steps){
    std::ofstream file("data/euler_results.csv");
    file << "time,x,y,z\n";  // CSV Header

    for(int i = 0; i<steps; i++){
        Vector3D accel = computeacceleration(position,velocity);

        velocity = velocity + accel*dt;
        position = position + velocity*dt;

        // std::cout << "Step " << i+1 << " | X: " << position.x << " km, Y: " << position.y << " km, Z: " << position.z << " km\n" << std::endl;
        file << i * dt << "," << position.x << "," << position.y << "," << position.z << "\n"; // Save data
        // std::cout<<"Hello"<< std::endl;

    }
    file.close();
}

void Orbit_propagator::propagateRK4(int steps){

    std::ofstream file("data/RK4_results.csv");
    file << "time,x,y,z\n";  // CSV Header

    for (int i = 0; i < steps; ++i) {

        Vector3D k1_v = computeacceleration(position,velocity);
        Vector3D k1_r = velocity;

        Vector3D k2_v = computeacceleration(position + k1_r * (dt / 2), velocity + k1_v * (dt / 2));
        Vector3D k2_r = velocity + k1_v * (dt / 2);

        Vector3D k3_v = computeacceleration(position + k2_r * (dt / 2), velocity + k2_v * (dt / 2));
        Vector3D k3_r = velocity + k2_v * (dt / 2);

        Vector3D k4_v = computeacceleration(position + k3_r * dt, velocity + k3_v * dt);
        Vector3D k4_r = velocity + k3_v * dt;

        velocity = velocity + (k1_v + k2_v * 2 + k3_v * 2 + k4_v) * (dt / 6);
        position = position + (k1_r + k2_r * 2 + k3_r * 2 + k4_r) * (dt / 6);

        file << i * dt << "," << position.x << "," << position.y << "," << position.z << "\n";
    }
    file.close();

}