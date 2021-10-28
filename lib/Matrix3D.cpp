#include "../include/Matrix3D.h"

namespace A4DEngine {

    // Default Constructor
    Matrix3D::Matrix3D() 
        : Matrix3D{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0} {}

    // Constructor takes 9 floats
    Matrix3D::Matrix3D(float n00, float n01, float n02, float n10, float n11, float n12, float n20, float n21, float n22) {
        M[0].x = n00, M[0].y = n01, M[0].z = n02;
        M[1].x = n10, M[1].y = n11, M[1].z = n12;
        M[2].x = n20, M[2].y = n21, M[2].z = n22;
    }

    // Constructor takes 3 vectors
    Matrix3D::Matrix3D(Vector3D a, Vector3D b, Vector3D c) {
        M[0] = a;
        M[1] = b;
        M[2] = c;
    }

    // Copy Constructor
    Matrix3D::Matrix3D(const Matrix3D& A) : Matrix3D{A[0], A[1], A[2]} {}

    // Move Constructor
    Matrix3D::Matrix3D(Matrix3D&& A) : Matrix3D{A[0], A[1], A[2]}  {}

    // Assignment operator
    Matrix3D& Matrix3D::operator=(const Matrix3D& A) {
        M[0] = A[0];
        M[1] = A[1];
        M[2] = A[2];
        return (*this);
    }

    // Overloading Operator [] to access vector
    Vector3D& Matrix3D::operator[](int i) {
        return (M[i]);
    }
    const Vector3D& Matrix3D::operator[](int i) const {
        return (M[i]);
    }

    // Overloading Operator () to access element
    float& Matrix3D::operator()(int i, int j) {
        return (M[i][j]);
    }
    const float& Matrix3D::operator()(int i, int j) const {
        return (M[i][j]);
    }

    // Matrix Addition
    Matrix3D& Matrix3D::operator+=(const Matrix3D& A) {
        M[0] += A[0];
        M[1] += A[1];
        M[2] += A[2];
        return (*this);
    }

    // Matrix Subtraction
    Matrix3D& Matrix3D::operator-=(const Matrix3D& A) {
        M[0] -= A[0];
        M[1] -= A[1];
        M[2] -= A[2];
        return (*this);
    }

    // Scalar and Matrix Multiplication
    Matrix3D& Matrix3D::operator*=(float s) {
        M[0] *= s;
        M[1] *= s;
        M[2] *= s;
        return (*this);
    }

    // Matrix Multiplication
    Matrix3D& Matrix3D::operator*=(const Matrix3D& A) {
        const Vector3D a = M[0];
        const Vector3D b = M[1];
        const Vector3D c = M[2];

        M[0].x = (a.x*A[0].x + a.y*A[1].x + a.z*A[2].x);
        M[0].y = (a.x*A[0].y + a.y*A[1].y + a.z*A[2].y);
        M[0].z = (a.x*A[0].z + a.y*A[1].z + a.z*A[2].z);

        M[1].x = (b.x*A[0].x + b.y*A[1].x + b.z*A[2].x);
        M[1].y = (b.x*A[0].y + b.y*A[1].y + b.z*A[2].y);
        M[1].z = (b.x*A[0].z + b.y*A[1].z + b.z*A[2].z);

        M[2].x = (c.x*A[0].x + c.y*A[1].x + c.z*A[2].x);
        M[2].y = (c.x*A[0].y + c.y*A[1].y + c.z*A[2].y);
        M[2].z = (c.x*A[0].z + c.y*A[1].z + c.z*A[2].z);

        return (*this);
    }

    // Print out Matrix
    void Matrix3D::show(ostream& out) const {
        out << M[0].x << " " << M[0].y << " " << M[0].z << "\n"
            << M[1].x << " " << M[1].y << " " << M[1].z << "\n"
            << M[2].x << " " << M[2].y << " " << M[2].z << "\n\n";
    }

    // Matrix Addition
    Matrix3D operator+(const Matrix3D& A, const Matrix3D& B) {
        return (
            Matrix3D(
                A[0] + B[0],
                A[1] + B[1],
                A[2] + B[2]
            )
        );
    }

    // Matrix Subtraction
    Matrix3D operator-(const Matrix3D& A, const Matrix3D& B) {
        return (
            Matrix3D(
                A[0] - B[0],
                A[1] - B[1],
                A[2] - B[2]
            )
        );
    }

    // Scalar and Matrix Multiplication
    Matrix3D operator*(const Matrix3D& A, float s) {
        return (
            Matrix3D(
                Vector3D(
                    A[0]*s
                ),
                Vector3D(
                    A[1]*s
                ),
                Vector3D(
                    A[2]*s
                )
            )
        );
    }

    // Vector and Matrix Multiplication
    Vector3D operator*(const Matrix3D& A, const Vector3D& v) {
        return (
            Vector3D(
                A[0].x*v.x + A[0].y*v.y + A[0].z*v.z,
                A[1].x*v.x + A[1].y*v.y + A[1].z*v.z,
                A[2].x*v.x + A[2].y*v.y + A[2].z*v.z
            )
        );
    }

    // Matrix Multiplication
    Matrix3D operator*(const Matrix3D& A, const Matrix3D& B) {
        return (
            Matrix3D(
                Vector3D(
                    A[0].x*B[0].x + A[0].y*B[1].x + A[0].z*B[2].x,
                    A[0].x*B[0].y + A[0].y*B[1].y + A[0].z*B[2].y,
                    A[0].x*B[0].z + A[0].y*B[1].z + A[0].z*B[2].z
                ),
                Vector3D(
                    A[1].x*B[0].x + A[1].y*B[1].x + A[1].z*B[2].x,
                    A[1].x*B[0].y + A[1].y*B[1].y + A[1].z*B[2].y,
                    A[1].x*B[0].z + A[1].y*B[1].z + A[1].z*B[2].z
                ),
                Vector3D(
                    A[2].x*B[0].x + A[2].y*B[1].x + A[2].z*B[2].x,
                    A[2].x*B[0].y + A[2].y*B[1].y + A[2].z*B[2].y,
                    A[2].x*B[0].z + A[2].y*B[1].z + A[2].z*B[2].z
                )
            )
        );
    }

    // Returns Identity Matrix
    Matrix3D get_identity() {
        return (
            Matrix3D(
                Vector3D(1.0, 0.0, 0.0),
                Vector3D(0.0, 1.0, 0.0),
                Vector3D(0.0, 0.0, 1.0)
            )
        );
    }

    // Returns Transpose Matrix
    Matrix3D get_transpose(const Matrix3D& A) {
        return (
            Matrix3D(
                Vector3D(A[0].x, A[1].x, A[2].x),
                Vector3D(A[0].y, A[1].y, A[2].y),
                Vector3D(A[0].z, A[1].z, A[2].z)
            )
        );
    }

    // Returns Adjugate Matrix
    Matrix3D get_adjugate(const Matrix3D& A) {
        Matrix3D T = get_transpose(A);

        return (
            Matrix3D(
                Vector3D(
                    (T[1].y*T[2].z - T[1].z*T[2].y),
                    -(T[1].x*T[2].z - T[1].z*T[2].x),
                    (T[1].x*T[2].y - T[1].y*T[2].x)
                ),
                Vector3D(
                    -(T[0].y*T[2].z - T[0].z*T[2].y),
                    (T[0].x*T[2].z - T[0].z*T[2].x),
                    -(T[0].x*T[2].y - T[0].y*T[2].x)
                ),
                Vector3D(
                    (T[0].y*T[1].z - T[0].z*T[1].y),
                    -(T[0].x*T[1].z - T[0].z*T[1].x),
                    (T[0].x*T[1].y - T[0].y*T[1].x)
                )
            )
        );
    }

    // Returns Matrix Determinant
    float get_determinant(const Matrix3D& A) {
        return (
            A[0].x*(A[1].y*A[2].z - A[1].z*A[2].y)
            - A[0].y*(A[1].x*A[2].z - A[1].z*A[2].x)
            + A[0].z*(A[1].x*A[2].y - A[1].y*A[2].x)
        );
    }

    // Returns Inverse Matrix
    Matrix3D get_inverse(const Matrix3D& A) {
        Matrix3D AdjMatrix = get_adjugate(A);
        float det = 1.0/get_determinant(A);

        Matrix3D InverseMatrix = AdjMatrix*det;

        return InverseMatrix;
    }
}