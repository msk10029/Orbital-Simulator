#ifndef PERTURBATION_HPP
#define PERTURBATION_HPP

#include "utils.hpp"

const double J2 = 1.08263e-3;  // Earth's J2 coefficient
const double R_E = 6378.1363;  // Earth's radius in km
const double Cd = 2.2;  // Drag coefficient
const double rho0 = 1.225e-9;  // Density at sea level (kg/km^3)
const double H = 60.0;  // Scale height (km)
const double mu = 398600.0;  // Earth's gravitational parameter (km³/s²)

Vector3D computeJ2Perturbation(Vector3D pos);
Vector3D computeDrag(Vector3D pos, Vector3D vel, double mass, double area);
double computeDensity(double altitude);

#endif