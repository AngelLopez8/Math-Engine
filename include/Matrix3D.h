#ifndef MATRIX3D_H
#define MATRIX3D_H

#include "Matrix.h"

namespace A4DEngine {
    class Matrix3D : public Matrix {
        public:
            Vector3D M[3];

            // Constructor
            Matrix3D();
            Matrix3D(float, float, float, float, float, float, float, float, float);
            Matrix3D(Vector3D, Vector3D, Vector3D);

            // Copy Constructor
            Matrix3D(const Matrix3D&);

            // Move Constructor
            Matrix3D(Matrix3D&&);

            // Assignement operator
            Matrix3D& operator=(const Matrix3D&);

            // Destructor
            virtual ~Matrix3D() {}

            // Overloading Operator [] to access vector
            Vector3D& operator[](int);
            const Vector3D& operator[](int) const;

            // Overloading Operator () to access element
            float& operator()(int, int);
            const float& operator()(int, int) const;

            // Print out Matrix
            void show(ostream&) const;

            // Matrix Addition
            Matrix3D& operator+=(const Matrix3D&);
            
            // Matrix Subtraction
            Matrix3D& operator-=(const Matrix3D&);
            
            // Scalar and Matrix Multiplication
            Matrix3D& operator*=(float);

            // Matrix Multiplication
            Matrix3D& operator*=(const Matrix3D&);
    };

    // Matrix Addition
    Matrix3D operator+(const Matrix3D&, const Matrix3D&);

    // Matrix Subtraction
    Matrix3D operator-(const Matrix3D&, const Matrix3D&);

    // Scalar and Matrix Multiplication
    Matrix3D operator*(const Matrix3D&, float);

    // Vector and Matrix Multiplication 
    Vector3D operator*(const Matrix3D&, const Vector3D&);

    // Matrix Multiplication 
    Matrix3D operator*(const Matrix3D&, const Matrix3D&);

    // Returns Identity Matrix
    Matrix3D get_identity();

    // Returns Transpose Matrix
    Matrix3D get_transpose(const Matrix3D&);

    // Returns Matrix Determinant
    float get_determinant(const Matrix3D&);

    // Returns Adjugate Matrix
    Matrix3D get_adjugate(const Matrix3D&);

    // Returns Inverse Matrix
    Matrix3D get_inverse(const Matrix3D&);

    // Make Rotation X
    Matrix3D make_rotation_x(float);

    // Make Rotation Y
    Matrix3D make_rotation_y(float);

    // Make Rotation Z
    Matrix3D make_rotation_z(float);

    // Make Rotation
    Matrix3D make_rotation(float, const Vector3D&);

    // Make Reflection
    Matrix3D make_reflection(const Vector3D&);

    // Make Involution
    Matrix3D make_involution(const Vector3D&);

    // Make Scale
    Matrix3D make_scale(float, float, float);

    // Make Scale
    Matrix3D make_scale(float, const Vector3D&);

    // Make Skew
    Matrix3D make_skew(float, const Vector3D&, const Vector3D&);
}

#endif