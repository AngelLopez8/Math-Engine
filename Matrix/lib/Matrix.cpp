#include "../include/Matrix.h"

namespace AMathEngine {

    /******************************************************
                Constructor / Destructor Functions
    ******************************************************/
    // Default Constructor
    template <class T>
    Matrix<T>::Matrix() {
        nRows = 1;
        nCols = 1;
        nElements = 1;
        matrixData = new T[nElements];
        matrixData[0] = 0.0;
    }

    // Constructor Empty Matrix (All Elements 0.0)
    template <class T>
    Matrix<T>::Matrix(int numRows, int numCols) {
        nRows = numRows;
        nCols = numCols;
        nElements = nRows*nCols;
        matrixData = new T[nElements];
        for (int i = 0; i < nElements; i++)
            matrixData[i] = 0.0;
    }

    // Constructor from const array
    template <class T>
    Matrix<T>::Matrix(int numRows, int numCols, const T* inputData) {
        nRows = numRows;
        nCols = numCols;
        nElements = nRows*nCols;
        matrixData = new T[nElements];
        for (int i = 0; i < nElements; i++)
            matrixData[i] = inputData[i];
    }

    // Copy Constructor
    template <class T>
    Matrix<T>::Matrix(const Matrix<T>& inputMatrix) 
        : nRows(inputMatrix.nRows), nCols(inputMatrix.nCols), nElements(inputMatrix.nElements) {
        matrixData = new T[nElements];
        for (int i = 0; i < nElements; i++)
            matrixData[i] = inputMatrix.matrixData[i];
    }

    // Move Constructor
    template <class T>
    Matrix<T>::Matrix(Matrix<T>&& inputMatrix) 
        : nRows(inputMatrix.nRows), nCols(inputMatrix.nCols), nElements(inputMatrix.nElements) {
        matrixData = new T[nElements];
        for (int i = 0; i < nElements; i++)
            matrixData[i] = inputMatrix.matrixData[i];

        delete[] inputMatrix.matrixData;
        inputMatrix.matrixData = nullptr;
        inputMatrix.nRows = 0;
        inputMatrix.nCols = 0;
        inputMatrix.nElements = 0;
    }

    // Destructor
    template <class T>
    Matrix<T>::~Matrix() {
        if (matrixData != nullptr)  {
            delete[] matrixData;     
            matrixData = nullptr;
        }  
    }

    /******************************************************
                    Configuration Functions
    ******************************************************/
    template <class T>
    bool Matrix<T>::resize(int numRows, int numCols) {
        nRows = numRows;
        nCols = numCols;
        nElements = nRows*nCols;
        delete[] matrixData;
        matrixData = new T[nElements];
        if (matrixData != nullptr) {
            for (int i = 0; i < nElements; i++)
                matrixData[i] = 0.0;
            return true;
        } else {
            return false;
        }
    }

    /******************************************************
                    Element Access Functions
    ******************************************************/
    template <class T>
    T Matrix<T>::get_element(int row, int col) {
        int index = get_linear_index(row, col);
        if (index >= 0)
            return matrixData[index];
        else
            return 0.0;
    }

    template <class T>
    bool Matrix<T>::set_element(int row, int col, T elementValue) {
        int index = get_linear_index(row, col);
        if (index >= 0) {
            matrixData[index] = elementValue;
            return true;
        } else {
            return false;
        }
    }

    template <class T>
    int Matrix<T>::get_num_rows() const { return nRows; }
    
    template <class T>
    int Matrix<T>::get_num_cols() const { return nCols; }

    /******************************************************
                  Overloaded Operators Functions
    ******************************************************/
   template <class T>
   bool Matrix<T>::operator==(const Matrix<T>& rhs) {
        // Check if the matrices are the same dimension, if not return false
        if ((this->nRows != rhs.nRows) && (this->nCols != rhs.nCols))
            return false;
        
        // Check if elements are equal
        bool flag = true;
        for (int i = 0; i < this->nElements; i++) {
            if (this->matrixData[i] != rhs.matrixData[i])
                flag = false;
        }
        return flag;
   }

    /******************************************************
                        The + Operator
    ******************************************************/
    // Matrix + Matrix
    template <class T>
    Matrix<T> operator+(const Matrix<T>& lhs, const Matrix<T>& rhs) {
        int numRows = lhs.nRows;
        int numCols = lhs.nCols;
        int numElements = numRows*numCols;
        T *tempData = new T[numElements];
        for (int i = 0; i < numElements; i++)
            tempData[i] = lhs.matrixData[i] + rhs.matrixData[i];

        Matrix<T> newMatrix(numRows, numCols, tempData);
        delete [] tempData;
        return newMatrix;
    }

    // Scalar + Matrix
    template <class T>
    Matrix<T> operator+(const T& lhs, const Matrix<T>& rhs) {
        int numRows = rhs.nRows;
        int numCols = rhs.nCols;
        int numElements = numRows*numCols;
        T *tempData = new T[numElements];
        for (int i = 0; i < numElements; i++)
            tempData[i] = lhs + rhs.matrixData[i];
        
        Matrix<T> newMatrix(numRows, numCols, tempData);
        delete[] tempData;
        return newMatrix;
    }

    // Matrix + Scalar
    template <class T>
    Matrix<T> operator+(const Matrix<T>& lhs, const T& rhs) {
        int numRows = lhs.nRows;
        int numCols = lhs.nCols;
        int numElements = numRows*numCols;
        T *tempData = new T[numElements];
        for (int i = 0; i < numElements; i++)
            tempData[i] = lhs.matrixData[i] + rhs;
        
        Matrix<T> newMatrix(numRows, numCols, tempData);
        delete[] tempData;
        return newMatrix;
    }

    /******************************************************
                        The - Operator
    ******************************************************/
    // Matrix - Matrix
    template <class T>
    Matrix<T> operator-(const Matrix<T>& lhs, const Matrix<T>& rhs) {
        int numRows = lhs.nRows;
        int numCols = lhs.nCols;
        int numElements = numRows*numCols;
        T *tempData = new T[numElements];
        for (int i = 0; i < numElements; i++)
            tempData[i] = lhs.matrixData[i] - rhs.matrixData[i];

        Matrix<T> newMatrix(numRows, numCols, tempData);
        delete [] tempData;
        return newMatrix;
    }

    // Scalar - Matrix
    template <class T>
    Matrix<T> operator-(const T& lhs, const Matrix<T>& rhs) {
        int numRows = rhs.nRows;
        int numCols = rhs.nCols;
        int numElements = numRows*numCols;
        T *tempData = new T[numElements];
        for (int i = 0; i < numElements; i++)
            tempData[i] = lhs - rhs.matrixData[i];
        
        Matrix<T> newMatrix(numRows, numCols, tempData);
        delete[] tempData;
        return newMatrix;
    }

    // Matrix - Scalar
    template <class T>
    Matrix<T> operator-(const Matrix<T>& lhs, const T& rhs) {
        int numRows = lhs.nRows;
        int numCols = lhs.nCols;
        int numElements = numRows*numCols;
        T *tempData = new T[numElements];
        for (int i = 0; i < numElements; i++)
            tempData[i] = lhs.matrixData[i] - rhs;
        
        Matrix<T> newMatrix(numRows, numCols, tempData);
        delete[] tempData;
        return newMatrix;
    }

    /******************************************************
                        The * Operator
    ******************************************************/
    // Matrix * Matrix
    template <class T>
    Matrix<T> operator*(const Matrix<T>& lhs, const Matrix<T>& rhs) {
        int LnumRows = lhs.nRows;
        int LnumCols = lhs.nCols;
        int RnumRows = rhs.nRows;
        int RnumCols = rhs.nCols;

        if (LnumCols == RnumRows) {
            T* tempData = new T[LnumRows*RnumCols];

            // Loop through each Row of the lhs
            for (int LRow = 0; LRow < LnumRows; LRow++) {
                // Loop through each Column of the rhs
                for (int RCol = 0; RCol < RnumCols; RCol++) {
                    T elementSum = 0.0;
                    // Loop through each element of this lhs row
                    for (int LCol = 0; LCol < LnumCols; LCol++) {
                        int LIndex = (LRow * LnumCols) + LCol;
                        int RIndex = (LCol * RnumCols) + RCol;

                        elementSum += (lhs.matrixData[LIndex] * rhs.matrixData[RIndex]);
                    }
                    int resultIndex = (LRow*RnumCols) + RCol;
                    tempData[resultIndex] = elementSum;
                }
            }
            Matrix<T> Result(LnumRows, RnumCols, tempData);
            delete[] tempData;
            return Result;
        } else {
            return Matrix<T>(1, 1); // return 1x1 Matrix
        }
    }

    // Scalar * Matrix
    template <class T>
    Matrix<T> operator*(const T& lhs, const Matrix<T>& rhs) {
        int numRows = rhs.nRows;
        int numCols = rhs.nCols;
        int numElements = numRows*numCols;
        T *tempData = new T[numElements];
        for (int i = 0; i < numElements; i++)
            tempData[i] = lhs*rhs.matrixData[i];
        
        Matrix<T> newMatrix(numRows, numCols, tempData);
        delete[] tempData;
        return newMatrix;
    }

    // Matrix * Scalar
    template <class T>
    Matrix<T> operator*(const Matrix<T>& lhs, const T& rhs) {
        int numRows = lhs.nRows;
        int numCols = lhs.nCols;
        int numElements = numRows*numCols;
        T *tempData = new T[numElements];
        for (int i = 0; i < numElements; i++)
            tempData[i] = lhs.matrixData[i]*rhs;
        
        Matrix<T> newMatrix(numRows, numCols, tempData);
        delete[] tempData;
        return newMatrix;
    }

    /******************************************************
                        Private Functions
    ******************************************************/
    template <class T>
    int Matrix<T>::get_linear_index(int row, int col) {
        if ((row > nRows) && (row >= 0) && (col < nCols) && (col >= 0))
            return (row*nCols) + col;
        else
            return -1;
    }

    template class Matrix<float>;
}