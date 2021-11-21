#include "../include/Vector3D.h"

namespace AMathEngine {
    // Default Constructor
    Vector3D::Vector3D() {
        vec = {0.0f, 0.0f, 0.0f};
        length = 3;
    }

    // Copy Constructor
    Vector3D::Vector3D(const Vector3D& a) {
        vec = a.vec;
        length = a.length;
    }

    // Move Constructor
    Vector3D::Vector3D(Vector3D&& a) {
        vec = a.vec;
        length = a.length;

        a.vec = {};
        a.length = 0;
    }

    // Constructor passed in 3 floats
    Vector3D::Vector3D(float x, float y, float z) {
        vec = {x, y, z};
        length = 3;
    }

    // Constructor passed in vector
    Vector3D::Vector3D(vector<float> a) {
        vec = a;
        length = 3;
    }

    // Destructor
    Vector3D::~Vector3D() {}

    // Cross Product
    Vector3D cross(const Vector3D& a, const Vector3D& b) {
        return (
            Vector3D(
                a[1]*b[2] - a[2]*b[1],
                a[2]*b[0] - a[0]*b[2],
                a[0]*b[1] - a[1]*b[0]
            )
        );
    }

    // Scalar Triple Product
    float scalar_triple_product(const Vector3D& a, const Vector3D& b, const Vector3D& c) {
        return (
            dot(a, cross(b, c))
        );        
    }
}