#ifndef VECTOR3D_HPP
#define VECTOR3D_HPP

#include <iostream>
#include <math.h>

class Vector3D {
    float x, y, z;
public:
    // Constructors
    Vector3D() = default;
    Vector3D(float, float, float);
    
    // Overloaded Operators
    float& operator[](int);
    const float& operator[](int) const;

    // Vector Operations
    Vector3D& operator+=(const Vector3D&);  // Addition
    Vector3D& operator-=(const Vector3D&);  // Subtraction
    Vector3D& operator*=(float);            // Multiplication
    Vector3D& operator/=(float);            // Division

    // Friend functions
    friend Vector3D operator+(const Vector3D&, const Vector3D&);
    friend Vector3D operator-(const Vector3D&, const Vector3D&);
    friend Vector3D operator*(const Vector3D&, float);
    friend Vector3D operator/(const Vector3D&, float);
    friend Vector3D operator-(const Vector3D&);

    friend float Magnitude(const Vector3D&);
    friend float Dot(const Vector3D&, const Vector3D&);;
    friend Vector3D Normalize(const Vector3D&);
    friend Vector3D Cross(const Vector3D&, const Vector3D&);
    friend Vector3D Project(const Vector3D&, const Vector3D&);
    friend Vector3D Reject(const Vector3D&, const Vector3D&);

    friend std::ostream& operator<<(std::ostream&, const Vector3D&);
};

#endif