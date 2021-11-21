#ifndef MATRIX_H
#define MATRIX_H

#include "../../Vector/include/Vector.h"

namespace AMathEngine {

    class Matrix {
        private:
            vector<Vector> M;
            int dimM, dimN;
        public:
            Matrix();                   // Default Constructor
            Matrix(const Matrix&);      // Copy Constructor
            Matrix(Matrix&&);           // Move Constructor
            Matrix(vector<Vector>);     // Constructor passed in vector
            ~Matrix();                  // Destructor

            Matrix& operator=(const Matrix&);   // Copy assignment operator
            Matrix& operator=(Matrix&&);        // Move assignment operator

            // Subscript Operators
            Vector& operator[](int);
            const Vector& operator[](int) const;

            int get_columns() const { return dimN; }  // returns # of column vectors
            int get_rows() const { return dimM; }   // returns # of row vectors
            void dimensions() const { std::cout << dimM << "x" << dimN << "\n"; }   // prints out matrix dimension

            // Overloaded Output Operator
            friend ostream& operator<<(ostream& out, const Matrix& A) {
                int rows = A.get_rows();
                int cols = A.get_columns();

                for (int i = 0; i < rows; i++) {
                    for (int j = 0; j < cols; j++)
                        out << A[j][i] << " ";
                    out << "\n";
                }

                return out;
            }
    };

    Matrix operator*(const Matrix&, float); // Vector Scalar Multiplication
    
    Matrix operator+(const Matrix&, const Matrix&);     // Matrix Addition
    Matrix operator-(const Matrix&, const Matrix&);     // Matrix Subtraction
    Matrix operator*(const Matrix&, const Matrix&);     // Matrix Multiplication

    Matrix transpose(const Matrix&);    // Matrix transpose
    Matrix get_submatrix(const Matrix&, int);    // returns subMatrix
    float determinant(const Matrix&);   // Matrix determinant
}

#endif