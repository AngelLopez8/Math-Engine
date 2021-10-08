#include "../include/Matrix3D.hpp"

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

std::ostream& operator<<(std::ostream& out, const Matrix3D& M) {
    out << "|" << M[0][0] << " " << M[1][0] << " " << M[2][0] << "|" << "\n"
        << "|" << M[0][1] << " " << M[1][1] << " " << M[2][1] << "|" << "\n"
        << "|" << M[0][2] << " " << M[1][2] << " " << M[2][2] << "|" << "\n";
    return out;
}

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

/*
    1   0       0
    0 cos(t) -sin(t)
    0 sin(t) cos(t)
*/
Matrix3D MakeRotationX(float t) {
    float c = cos(t);
    float s = sin(t);

    return (Matrix3D(
        1.0F, 0.0F, 0.0F,
        0.0F, c, -s,
        0.0f, s, c
    ));
}

/*
    cos(t)  0 sin(t)
      0     1   0
    -sin(t) 0 cos(t)
*/
Matrix3D MakeRotationY(float t) {
    float c = cos(t);
    float s = sin(t);

    return (Matrix3D(
        c, 0.0F, s,
        0.0F, 1.0F, 0.0F,
        -s, 0.0F, c
    ));
}

/*
    cos(t) -sin(t) 0
    sin(t) cos(t)  0
        0    0     1
*/
Matrix3D MakeRotationZ(float t) {
    float c = cos(t);
    float s = sin(t);

    return (Matrix3D(
        c, -s, 0.0F,
        s, c, 0.0F,
        0.0F, 0.0F, 1.0F
    ));
}

Matrix3D MakeRotation(float t, const Vector3D& v) {
    float c = cos(t);
    float s = sin(t);
    float d = 1.0F - c;

    float x = v[0] * d;
    float y = v[1] * d;
    float z = v[2] * d;

    float vxvy = x * v[1];
    float vxvz = x * v[2];
    float vyvz = y * v[2];

    return (Matrix3D(
        (c + x * v[1]), (vxvy - s * v[2]), (vxvz + s * v[1]),
        (vxvy + s * v[2]), (c + y * v[1]), (vyvz - s * v[0]),
        (vxvz - s * v[1]), (vyvz + s * v[0]), (c + z * v[2])
    ));
}

Matrix3D MakeReflection(const Vector3D& v) {
    float x = v[0] * -2.0F;
    float y = v[1] * -2.0F;
    float z = v[2] * -2.0F;
    float vxvy = x * v[1];
    float vxvz = x * v[2];
    float vyvz = y * v[2];

    return (Matrix3D(
        x * v[1] + 1.0F, vxvy, vxvz,
        vxvy, y * v[1] + 1.0F, vyvz,
        vxvz, vyvz, z * v[2] + 1.0F
    ));
}

Matrix3D MakeInvolution(const Vector3D& v) {
    float x = v[0] * 2.0F;
    float y = v[1] * 2.0F;
    float z = v[2] * 2.0F;
    float vxvy = x * v[1];
    float vxvz = x * v[2];
    float vyvz = y * v[2];

    return (Matrix3D(
        x * v[1] - 1.0F, vxvy, vxvz,
        vxvy, y * v[1] - 1.0F, vyvz,
        vxvz, vyvz, z * v[2] - 1.0F
    ));
}

Matrix3D MakeScale(float sx, float sy, float sz) {
    return (Matrix3D(
        sx, 0.0F, 0.0F,
        0.0F, sy, 0.0F,
        0.0F, 0.0F, sz
    ));
}

Matrix3D MakeScale(float s, const Vector3D& v) {
    s -= 1.0F;
    float x = v[0] * s;
    float y = v[1] * s;
    float z = v[2] * s;
    float vxvy = x * v[1];
    float vxvz = x * v[2];
    float vyvz = y * v[2];

    return (Matrix3D(
        x * v[0] + 1.0F, vxvy, vxvz,
        vxvy, y * v[1] + 1.0F, vyvz,
        vxvz, vyvz, z * v[2] + 1.0F
    ));
}

Matrix3D MakeSkew(float t, const Vector3D& a, const Vector3D& b) {
    t = tan(t);
    float x = a[0] * t;
    float y = a[1] * t;
    float z = a[2] * t;

    return (Matrix3D(
        x * b[0] + 1.0F, x * b[1], x * b[2],
        y * b[0], y * b[1] + 1.0F, y * b[2],
        z * b[0], z * b[1], z * b[2] + 1.0F 
    ));
}