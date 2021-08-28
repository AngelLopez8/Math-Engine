#include "Matrix3D.hpp"

Matrix3D::Matrix3D(float n00, float n01, float n02, float n10, float n11, float n12, float n20, float n21, float n22) {
    M[0] = Vector3D(n00, n10, n20);
    M[1] = Vector3D(n01, n11, n21);
    M[2] = Vector3D(n02, n12, n22);
}

Matrix3D::Matrix3D(const Vector3D& a, const Vector3D& b, const Vector3D& c) {
    M[0] = a;
    M[1] = b;
    M[2] = c;
}

// row = i, col = j
float& Matrix3D::operator()(int i, int j) {
    return (M[j][i]);
}

const float& Matrix3D::operator()(int i, int j) const {
    return (M[j][i]);
}

Vector3D& Matrix3D::operator[](int j) { return M[j]; }

const Vector3D& Matrix3D::operator[](int j) const { return M[j]; }

Matrix3D operator*(const Matrix3D& A, const Matrix3D& B) {
    return (
        Matrix3D(
            Vector3D(
                (A[0][0] * B[0][0]) + (A[1][0] * B[0][1]) + (A[2][0] * B[0][2]),
                (A[0][1] * B[0][0]) + (A[1][1] * B[0][1]) + (A[2][1] * B[0][2]),
                (A[0][2] * B[0][0]) + (A[1][2] * B[0][1]) + (A[2][2] * B[0][2])
            ),
            Vector3D(
                (A[0][0] * B[1][0]) + (A[1][0] * B[1][1]) + (A[2][0] * B[1][2]),
                (A[0][1] * B[1][0]) + (A[1][1] * B[1][1]) + (A[2][1] * B[1][2]),
                (A[0][2] * B[1][0]) + (A[1][2] * B[1][1]) + (A[2][2] * B[1][2])
            ),
            Vector3D(
                (A[0][0] * B[2][0]) + (A[1][0] * B[2][1]) + (A[2][0] * B[2][2]),
                (A[0][1] * B[2][0]) + (A[1][1] * B[2][1]) + (A[2][1] * B[2][2]),
                (A[0][2] * B[2][0]) + (A[1][2] * B[2][1]) + (A[2][2] * B[2][2])
            )
        )
    );
}

Vector3D operator*(const Matrix3D& M, const Vector3D& v) {
    return (
        Vector3D(
            (M[0][0] * v[0]) + (M[1][0] * v[1]) + (M[2][0] * v[2]),
            (M[0][1] * v[0]) + (M[1][1] * v[1]) + (M[2][1] * v[2]),
            (M[0][2] * v[0]) + (M[1][2] * v[1]) + (M[2][2] * v[2])
        )
    );
}

float Determinant(const Matrix3D& M) {
    return (
        (M[0][0] * (M[1][1] * M[2][2] - M[1][2] * M[2][1]))-
        (M[0][1] * (M[1][0] * M[2][2] - M[1][2] * M[2][0]))+
        (M[0][2] * (M[1][0] * M[2][1] - M[1][1] * M[2][0]))
    );
}

Matrix3D Inverse(const Matrix3D& M) {
    const Vector3D a = M[0];
    const Vector3D b = M[1];
    const Vector3D c = M[2];

    Vector3D r0 = Cross(b, c);
    Vector3D r1 = Cross(c, a);
    Vector3D r2 = Cross(a, b);

    float invDet = 1.0F / Dot(r2, c);

    return (
        Matrix3D(
            r0[0] * invDet, r0[1] * invDet, r0[2] * invDet,
            r1[0] * invDet, r1[1] * invDet, r1[2] * invDet,
            r2[0] * invDet, r2[1] * invDet, r2[2] * invDet
        )
    );
}

std::ostream& operator<<(std::ostream& out, const Matrix3D& M) {
    out << "|" << M[0][0] << " " << M[1][0] << " " << M[2][0] << "|" << "\n"
        << "|" << M[0][1] << " " << M[1][1] << " " << M[2][1] << "|" << "\n"
        << "|" << M[0][2] << " " << M[1][2] << " " << M[2][2] << "|" << "\n";
    return out;
}