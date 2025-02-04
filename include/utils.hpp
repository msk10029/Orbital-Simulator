#ifndef UTILS_HPP
#define UTILS_HPP

#include <cmath>

struct Vector3D
{
    double x,y,z;
    //Constructor
    Vector3D(double x_val = 0.0, double y_val = 0.0, double z_val = 0.0) 
        : x(x_val), y(y_val), z(z_val) {}

    //Addition
    Vector3D operator+(const Vector3D &v)const{
        return {x + v.x, y+v.y, z+v.z};
    }

    //Substraction
    Vector3D operator-(const Vector3D &v)const{
        return {x - v.x, y - v.y, z - v.z};
    }

    //Multiplication scalar
    Vector3D operator*(double scalar) const{
        return {x*scalar, y*scalar, z*scalar};
    }

    //Devision scalar
    Vector3D operator/(double scalar) const{
        return {x/scalar, y/scalar, z/scalar};
    }

    // Magnitude of the vector
    double magnitude() const {
        return std::sqrt(x*x + y*y + z*z);
    }
};


#endif