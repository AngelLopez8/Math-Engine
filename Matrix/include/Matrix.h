#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>

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

            /***************************** Element Access Methods *****************************/
            T get_element(int row, int col);
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
            // T& operator[](int index);   // Overloaded [] operator
            // const T& operator[](int index); // Overloaed [] operator

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
            int get_linear_index(int row, int col);
    };
}

#endif