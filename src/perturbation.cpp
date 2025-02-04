#include "../include/perturbation.hpp"
#include <cmath>

Vector3D computeJ2Perturbation(Vector3D pos){
    double r = pos.magnitude();
    double z = pos.z;
    double fac = -1.5 * J2 * mu * (R_E*R_E)/(pow(r,5));

    double ax = pos.x * fac * (1-5*(z*z) / (r*r));
    double ay = pos.y * fac * (1-5*(z*z) / (r*r));
    double az = pos.z * fac * (3-5*(z*z) / (r*r));

    return Vector3D(ax, ay, az);
}

double computeDensity(double altitude)
{
    if(altitude<0) return 0;
    return rho0*exp(-altitude/H);
}

Vector3D computeDrag(Vector3D pos, Vector3D vel, double mass, double area){
    double r = pos.magnitude();
    double altitude = r - R_E;

    double rho = computeDensity(altitude);
    double v_mag = vel.magnitude();

    return vel*(-0.5 * Cd * area * rho * v_mag / mass);

}