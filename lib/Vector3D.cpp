#include "../include/Vector3D.h"

namespace A4DEngine {
    // Constructor
    Vector3D::Vector3D() : Vector3D{0.0, 0.0, 0.0} {}

    Vector3D::Vector3D(float aX, float aY, float aZ) {
        x = aX;
        y = aY;
        z = aZ;
    }

    // Copy Constructor
    Vector3D::Vector3D(const Vector3D& a) : Vector3D{a.x, a.y, a.z} {}

    // Move Constructor
    Vector3D::Vector3D(Vector3D&& a) : Vector3D{a.x, a.y, a.z} {}

    // Destructor
    Vector3D::~Vector3D() {}

    // Scalar Multiplication: v *= s
    Vector3D& Vector3D::operator*=(float s) {
        x *= s;
        y *= s;
        z *= s;
        return (*this); 
    }

    // Scalar Division: v /= s
    Vector3D& Vector3D::operator/=(float s) {
        x /= s;
        y /= s;
        z /= s;
        return (*this);    
    }

    // Vector Addition
    Vector3D& Vector3D::operator+=(const Vector3D& a) {
        x += a.x;
        y += a.y;
        z += a.z;
        return (*this);
    }

    // Vector Subtraction
    Vector3D& Vector3D::operator-=(const Vector3D& a) {
        x -= a.x;
        y -= a.y;
        z -= a.z;
        return (*this);
    }

    // returns Vector Magnitude
    float Vector3D::get_magnitude() const {
        return (sqrt(x*x + y*y + z*z));
    }

    // returns Normalized Vector
    Vector3D Vector3D::get_normalize_vector() const {
        float magnitude = get_magnitude();
        return (
            Vector3D(
                x/magnitude,
                y/magnitude,
                z/magnitude
            )
        );
    }

    // Sets Vector to Normalized Vector
    Vector3D Vector3D::normalize_vector() {
        Vector3D a = get_normalize_vector();
        x = a.x;
        y = a.y;
        z = a.z;
    }

    // Print out Vector
    void Vector3D::show(ostream& os) const {
        os << x << " " << y << " " << z << "\n";
    }

    // Scalar Multiplication
    Vector3D operator*(const Vector3D& v, float s) {
        return (
            Vector3D(
                v.x*s, v.y*s, v.z*s
            )
        );
    }

    // Scalar Division
    Vector3D operator/(const Vector3D& v, float s) {
        return (
            Vector3D(
                v.x/s, v.y/s, v.z/s
            )
        );
    }

    // Negate Vector
    Vector3D operator-(const Vector3D& v) {
        return (
            Vector3D(
                -v.x, -v.y, -v.z
            )
        );
    }

    // Vector Addition
    Vector3D operator+(const Vector3D& a, const Vector3D& b) {
        return (
            Vector3D(
                a.x + b.x, a.y + b.y, a.z + b.z
            )
        );
    }

    // Vector Subtraction
    Vector3D operator-(const Vector3D& a, const Vector3D& b) {
        return (
            Vector3D(
                a.x - b.x, a.y - b.y, a.z - b.z
            )
        );
    }
}