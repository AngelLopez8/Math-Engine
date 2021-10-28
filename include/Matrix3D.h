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
}

#endif