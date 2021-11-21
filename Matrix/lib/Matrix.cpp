#include "../include/Matrix.h"

namespace AMathEngine {

    // Default Constructor
    Matrix::Matrix() {
        M = {};
        dimM = 0; dimN = 0;
    }

    // Copy Constructor
    Matrix::Matrix(const Matrix& A) : M{A.M}, dimM(A.dimM), dimN(A.dimN) {}

    // Move Constructor
    Matrix::Matrix(Matrix&& A) {
        M = A.M;
        dimM = A.dimM; dimN = A.dimN;

        M = {};
        dimM = 0; dimN = 0;
    }

    // Constructor passed in vector
    Matrix::Matrix(vector<Vector> V) : M{V} {
        dimM = V[0].get_length();
        dimN = V.size();
    }

    // Destructor
    Matrix::~Matrix() {
    }

    // Copy assignment operator
    Matrix& Matrix::operator=(const Matrix& A) {
        if (this != &A) {
            M = A.M;
            dimM = A.dimM; dimN = A.dimN;
        }
        return *this;
    }

    // Move assignment operator
    Matrix& Matrix::operator=(Matrix&& A) {
        if (this != &A) {
            M = A.M;
            dimM = A.dimM; dimN = A.dimN;

            A.M = {};
            A.dimM = 0; A.dimN = 0;
        }
        return *this;
    }

    // Subscript Operators
    Vector& Matrix::operator[](int index) {
        return M.at(index);
    }

    const Vector& Matrix::operator[](int index) const {
        return M.at(index);
    }

    // Vector Scalar Multiplication
    Matrix operator*(const Matrix& A, float s) {
        vector<Vector> newMatrix;

        for (int i = 0; i < A.get_columns(); i++) {
            newMatrix.push_back(A[i]*s);
        }

        return (
            Matrix(newMatrix)
        );
    }

    // Matrix Addition
    Matrix operator+(const Matrix& A, const Matrix& B) {
        vector<Vector> newMatrix;

        for (int i = 0; i < A.get_columns(); i++) {
            newMatrix.push_back(A[i] + B[i]);
        }

        return (
            Matrix(newMatrix)
        );
    }

    // Matrix Subtraction
    Matrix operator-(const Matrix& A, const Matrix& B) {
        vector<Vector> newMatrix;

        for (int i = 0; i < A.get_columns(); i++) {
            newMatrix.push_back(A[i] - B[i]);
        }

        return (
            Matrix(newMatrix)
        );
    }

    // Matrix Multiplication
    Matrix operator*(const Matrix& A, const Matrix& B) {
        int colsA = A.get_columns();
        int rowsB = B.get_rows();

        vector<Vector> newMatrix;
        Matrix AT = transpose(A);

        int colsAT = AT.get_columns();
        int colsB = B.get_columns();

        for (int i = 0; i < colsAT; i++) {
            vector<float> tempVec;
            for (int j = 0; j < colsB; j++) {
                tempVec.push_back(dot(AT[i], B[j]));
            }
            Vector newVec(tempVec);
            newMatrix.push_back(newVec);
        }

        Matrix newMatrixClass = Matrix(newMatrix);

        return (
            transpose(newMatrixClass)
        );
    }

    // Matrix transpose
    Matrix transpose(const Matrix& A) {
        vector<Vector> newMatrix;
        int colLen = A.get_columns();
        int rowLen = A.get_rows();

        for (int i = 0; i < rowLen; i++) {
            vector<float> vec;
            for (int j = 0; j < colLen; j++) {
                vec.push_back(A[j][i]);
            }
            Vector newVec(vec);
            newMatrix.push_back(newVec);
        }

        return (
            Matrix(newMatrix)
        );
    }

    // Returns subMatrix
    Matrix get_submatrix(const Matrix& A, int index) {
        vector<Vector> newMatrix;
        for (int i = 0; i < A.get_columns(); i++) {
            if (index != i) {
                vector<float> newVec;
                for (int j = 1; j < A[i].get_length(); j++) {
                    newVec.push_back(A[i][j]);
                }
                newMatrix.push_back(newVec);
            }
        }

        return Matrix(newMatrix);
    }

    // Matrix Determinant
    float determinant(const Matrix& A) {       
        // Base Case
        if (A.get_columns() == 2) {
            return (
                A[0][0]*A[1][1] - A[0][1]*A[1][0]
            );
        }

        int det = 0;

        for (int i = 0; i < A.get_columns(); i++) {
            Matrix subMatrix = get_submatrix(A, i);
            if (i % 2 == 0) {
                det += A[i][0]*determinant(subMatrix);
            } else {
                det -= A[i][0]*determinant(subMatrix);
            }
        }

        return det;
    }
}