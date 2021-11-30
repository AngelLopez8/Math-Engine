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
            Vector<T> get_column_vector(int column) const;    // Returns Column Vector at given Column
            Vector<T> get_row_vector(int row) const;          // Return Row Vector at given Row
            Matrix<T> get_submatrix(int row, int col) const;   // returns submatrix from given row, col

            void print() {
                for (int i = 0; i < nElements; i++) {
                    if ((i+1)%nCols == 0) {
                        std::cout << matrixData[i] << "\n";
                    } else {
                        std::cout << matrixData[i] << " ";
                    }
                }
            }
            /***************************** Functions to Computate *****************************/
            T determinant() const;  // Return Matrix Determinant

            Matrix<T> transposed() const;   // Return Copy of Tranpose Matrix
            void transpose();   // Transpose Current Matrix

            Matrix<T> adjacented() const;     // Return Copy of Adjacency Matrix
            void adjacent();    // Turn current Matrix to Adjacency Matrix

            Matrix<T> inversed() const;     // Return Copy of Inversed Matrix
            void inverse();     // Turn current Matrix to Inverse Matrix

            /***************************** Overloaded Operators *****************************/
            bool operator==(const Matrix<T>& rhs);  // Overloaded == operator
            
            Matrix<T>& operator=(const Matrix<T>& rhs);     // Copy assignment operator
            Matrix<T>& operator=(Matrix<T>&& rhs);      // Move Assignment Operator
 
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
            template <class U> friend Vector<U> operator*(const Matrix<U>& lhs, const Vector<U>& rhs);  // Matrix * Vector    

        private:
            int get_linear_index(int row, int col) const; // Calculate index with given row and col
            bool is_square() const;   // Check if Square Matrix
    };
}

#endif