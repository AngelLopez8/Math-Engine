#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>

#include "../../Vector/include/Vector.h"

namespace AMathEngine {
    template <class T>
    class Matrix {
        private:
            T* matrixData;
            int nRows, nCols, nElements;
        public:
            /***************************** Constructors *****************************/
            Matrix();   // Default Constructor
            Matrix(int numRows, int numCols);   // Create empty matrix of numRows x numCols
            Matrix(int numRows, int numCols, const T* inputData);   // Copy elements from array into new matrix of numRows x numCols
            Matrix(const Matrix<T>& inputMatrix);   // Copy Constructor
            Matrix(Matrix<T>&& inputMatrix);    // Move Constructor

            ~Matrix();// Destructor

            /***************************** Configuration Methods *****************************/
            bool resize(int numRows, int numCols);  // Change Matrix dimensions

            void set_to_identity(); // Set Matrix to Identity Matrix

            /***************************** Element Access Methods *****************************/
            T get_element(int row, int col) const;
            bool set_element(int row, int col, T elementValue);
            int get_num_rows() const;
            int get_num_cols() const;

            void print() {
                for (int i = 0; i < nElements; i++) {
                    if ((i+1)%nCols == 0) {
                        std::cout << matrixData[i] << "\n";
                    } else {
                        std::cout << matrixData[i] << " ";
                    }
                }
            }

            /***************************** Overloaded Operators *****************************/
            bool operator==(const Matrix<T>& rhs);  // Overloaded == operator
            
            Matrix<T>& operator=(const Matrix<T>&);     // Copy assignment operator
            Matrix<T>& operator=(Matrix<T>&&);      // Move Assignment Operator
 
            /***************************** Overloaded +, -, and * operators (friends) *****************************/
            template <class U> friend Matrix<U> operator+(const Matrix<U>& lhs, const Matrix<U>& rhs);  // Matrix + Matrix
            template <class U> friend Matrix<U> operator+(const U& lhs, const Matrix<U>& rhs);  // Scalar + Matrix
            template <class U> friend Matrix<U> operator+(const Matrix<U>& lhs, const U& rhs);  // Matrix + Scalar

            template <class U> friend Matrix<U> operator-(const Matrix<U>& lhs, const Matrix<U>& rhs);  // Matrix - Matrix
            template <class U> friend Matrix<U> operator-(const U& lhs, const Matrix<U>& rhs);  // Scalar - Matrix
            template <class U> friend Matrix<U> operator-(const Matrix<U>& lhs, const U& rhs);  // Matrix - Scalar

            template <class U> friend Matrix<U> operator*(const Matrix<U>& lhs, const Matrix<U>& rhs);  // Matrix * Matrix
            template <class U> friend Matrix<U> operator*(const U& lhs, const Matrix<U>& rhs);  // Scalar * Matrix
            template <class U> friend Matrix<U> operator*(const Matrix<U>& lhs, const U& rhs);  // Matrix * Scalar        

        private:
            int get_linear_index(int row, int col) const; // Calculate index with given row and col
            bool is_square() const;   // Check if Square Matrix
    };

    /***************************** Calculations/Artithmetic *****************************/
    template <class T>
    T determinant(const Matrix<T>& A);    // Calculate and return the determinant

    template <class T>
    Matrix<T> transpose(const Matrix<T>& A);    // Tranpose Matrix

    template <class T>
    Matrix<T> adjacent(const Matrix<T>& A);     // Adjacent Matrix

    template <class T>
    Matrix<T> inverse(const Matrix<T>& A);      // Inverse Matrix

    /***************************** Helper Functions *****************************/
    template <class T>
    Vector<T> get_column_vector(const Matrix<T>& A, int column);  // return column vector at given column

    template <class T>
    Vector<T> get_row_vector(const Matrix<T>& A, int row);    // returns row vector at given row

    template <class T>
    Matrix<T> get_submatrix(const Matrix<T>& A, int index);   // returns submatrix from given index
}

#endif