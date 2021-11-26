#include "../include/Matrix.h"

namespace AMathEngine {

    /******************************************************
                Constructor / Destructor Functions
    ******************************************************/
    /* Default Constructor */
    template <class T>
    Matrix<T>::Matrix() {
        nRows = 1;
        nCols = 1;
        nElements = 1;
        matrixData = new T[nElements];
        matrixData[0] = 0.0;
    }

    /* Constructor Empty Matrix (All Elements 0.0)
     * @param
    */
    template <class T>
    Matrix<T>::Matrix(int numRows, int numCols) {
        nRows = numRows;
        nCols = numCols;
        nElements = nRows*nCols;
        matrixData = new T[nElements];
        for (int i = 0; i < nElements; i++)
            matrixData[i] = 0.0;
    }

    /* Constructor from const array
     * @param
    */
    template <class T>
    Matrix<T>::Matrix(int numRows, int numCols, const T* inputData) {
        nRows = numRows;
        nCols = numCols;
        nElements = nRows*nCols;
        matrixData = new T[nElements];
        for (int i = 0; i < nElements; i++)
            matrixData[i] = inputData[i];
    }

    /* Copy Constructor
     * @param Matrix Object
    */
    template <class T>
    Matrix<T>::Matrix(const Matrix<T>& inputMatrix) 
        : nRows(inputMatrix.nRows), nCols(inputMatrix.nCols), nElements(inputMatrix.nElements) {
        matrixData = new T[nElements];
        for (int i = 0; i < nElements; i++)
            matrixData[i] = inputMatrix.matrixData[i];
    }

    /* Move Constructor
     * @param Matrix Object
    */
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

    /* Destructor */
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
    /* Resize Matrix to given dimensions
     * @param number of rows, number of columns
     * @return boolean result of resize
    */
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

    /* Reset Matrix to Identity Matrix
     * @param None
     * @return None
    */
    template <class T>
    void Matrix<T>::set_to_identity() {
        for (int i = 0; i < nElements; i++) {
            int currRow = (i/nCols);
            int currCol = (i%nCols);
            if (currRow == currCol) matrixData[i] = 1;
            else matrixData[i] = 0;
        }
    }

    /******************************************************
                    Element Access Functions
    ******************************************************/
    /* Access Element at Given Row and Column
     * @param Row value, Column value
     * @return value at given location
    */
    template <class T>
    T Matrix<T>::get_element(int row, int col) const{
        int index = get_linear_index(row, col);
        if (index >= 0)
            return matrixData[index];
        else
            return 0.0;
    }

    /* Set element at given row and column to given value
     * @param Row value, Column Value, element value
     * @return boolean result of set item
    */
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

    /* Get Number of Rows
     * @param None
     * @return number of rows
    */
    template <class T>
    int Matrix<T>::get_num_rows() const { return nRows; }

    /* Get Number of Columns
     * @param None
     * @return number of columns
    */
    template <class T>
    int Matrix<T>::get_num_cols() const { return nCols; }

    /******************************************************
                  Overloaded Operators Functions
    ******************************************************/
    /* Overloaded (==) equal to Operator
     * @param Matrix Object
     * @return boolean result of Matrix compare
    */
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

    /* Copy assignment operator 
     * @param Matrix Object
     * @return Current Matrix Object
    */
    template <class T>
    Matrix<T>& Matrix<T>::operator=(const Matrix<T>& A) {
        if (this != &A)
        {
            nRows = A.nRows;
            nCols = A.nCols;
            nElements = nRows*nCols;
            delete[] matrixData;
            matrixData = new T[nElements];
            for (int i = 0; i < nElements; i++)
                matrixData[i] = A.matrixData[i];
      }
      return (*this);
    }
    
    /* Move Assignment Operator 
     * @param Matrix Object
     * @return Current Matrix Object
    */
    template <class T>
    Matrix<T>& Matrix<T>::operator=(Matrix<T>&& A) {
        if (this != &A)
        {            
            nRows = A.nRows;
            nCols = A.nCols;
            nElements = nRows*nCols;
            delete[] matrixData;
            matrixData = new T[nElements];
            for (int i = 0; i < nElements; i++)
                matrixData[i] = A.matrixData[i];
            
            delete[] A.matrixData;
            A.matrixData = nullptr;
            A.nRows = 0; A.nCols = 0;
        }
        return (*this);
    }

    /******************************************************
                        The + Operator
    ******************************************************/
    /* Matrix Addition: Matrix + Matrix
     * @param Matrix Object, Matrix Object
     * @return new Matrix Object
    */
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

    /* Add scalar value to each Matrix Element: scalar + Matrix
     * @param scalar value, Matrix Object
     * @return new Matrix Object
    */
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

    /* Add scalar value to each Matrix Element: Matrix + scalar
     * @param Matrix Object, scalar value
     * @return new Matrix Object
    */
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
    /* Matrix Subtraction: Matrix - Matrix
     * @param Matrix Object, Matrix Object
     * @return new Matrix Object
    */
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

    /* Subtract scalar value to each Matrix Element: scalar - Matrix
     * @param Matrix Object, scalar value
     * @return new Matrix Object
    */
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

    /* Subtract scalar value to each Matrix Element: Matrix - scalar
     * @param Matrix Object, scalar value
     * @return new Matrix Object
    */
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
    /* Matrix Multiplication: Matrix*Matrix
     * @param Matrix Object, Matrix Object
     * @return new Matrix Object
    */
    template <class T>
    Matrix<T> operator*(const Matrix<T>& lhs, const Matrix<T>& rhs) {
        int LnumRows = lhs.nRows;
        int LnumCols = lhs.nCols;
        int RnumRows = rhs.nRows;
        int RnumCols = rhs.nCols;

        if (LnumCols == RnumRows) {
            T* tempData = new T[LnumRows*RnumCols];

            /* figure out issue later*/
            // for (int i = 0; i < LnumRows; i++) {
            //     Vector<T> aRow = get_row_vector(lhs, i);
            //     for (int j = 0; j < RnumCols; j++) {
            //         Vector<T> bCol = get_column_vector(rhs, j);
            //         int index = lhs.get_linear_index(i, j);
            //         tempData[index] = dot(aRow, bCol);
            //     }
            // }

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

    /* Matrix & Scalar Multiplication: scalar*Matrix
     * @param Scalar value, Matrix Object
     * @return new Matrix Object
    */
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

    /* Matrix & Scalar Multiplication: Matrix*scalar
     * @param Matrix Object, Scalar value
     * @return new Matrix Object
    */
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
    /* Calculate Linear Index with given row and column
     * @param row value, column value
     * @return linear index value
    */
    template <class T>
    int Matrix<T>::get_linear_index(int row, int col) const {
        if ((row < nRows) && (row >= 0) && (col < nCols) && (col >= 0))
            return (row*nCols) + col;
        else
            return -1;
    }

    /* Check if Matrix is a Square Matrix
     * @param None
     * @return boolean result
    */
    template <class T>
    bool Matrix<T>::is_square() const { return nRows == nCols; }

    /******************************************************
                    Calculations/Artithmetic
    ******************************************************/
    /* Calculate Determinant of Matrix
     * @param Matrix Object
     * @return determinant value
    */
    template <class T>
    T determinant(const Matrix<T>& A) {
        T det;
        if (A.get_num_rows() == 2 && A.get_num_cols() == 2) {
            return (
                A.get_element(0, 0)*A.get_element(1, 1)
                - A.get_element(1, 0)*A.get_element(0, 1)
            );
        }
        if (A.get_num_rows() == A.get_num_cols()) {
            for (int i = 0; i < A.get_num_cols(); i++) {
                Matrix<T> tempMatrix = get_submatrix(A, i);
                if (i%2 == 0) {
                    det += A.get_element(0, i)*(determinant(tempMatrix));
                } else {
                    det -= A.get_element(0, i)*(determinant(tempMatrix));
                }
            }
        }
        return det;
    }

    /* Transpose Matrix
     * @param Matrix Object
     * @return Transpose Matrix
    */
    template <class T>
    Matrix<T> transpose(const Matrix<T>& A) {
        int newRows = A.get_num_cols();
        int newCols = A.get_num_rows();
        int length = newRows * newCols;
        T* newData = new T[length];

        for (int i = 0; i < length; i++) {
            int currRow = (i/newCols);
            int currCol = (i%newCols);
            newData[i] = A.get_element(currCol, currRow);
        }

        return (
            Matrix<T>(
                newRows, newCols, newData
            )
        );
    }

    /* Adjacent Matrix
     *  - Used to find Inverse Matrix
     * @param Matrix Object
     * @return Adjacent Matrix
    */
    template <class T>
    Matrix<T> adjacent(const Matrix<T>& A) {
        Matrix<T> AT = transpose(A);
        int newRows = A.get_num_rows();
        int newCols = A.get_num_cols();
        int newElements = newRows*newCols;
        T* newData = new T[newElements];

        for (int i = 0; i < newElements; i++) {
            Matrix<T> subMatrix = get_submatrix(A, i);
            T det = determinant(subMatrix);
            if (i%2 == 0) newData[i] = det;
            else newData[i] = -1*det;
        }

        return (
            Matrix<T>(
                newRows, newCols, newData
            )
        );
    }

    /* Inverse Matrix
     * @param Matrix Object
     * @return Inverse Matrix
    */
    template <class T>
    Matrix<T> inverse(const Matrix<T>& A) {
        T det = determinant(A);
        if (A.is_square() && det != 0)  {
            Matrix<T> Adj = adjacent(A);
            Matrix<T> Inv = (1/det)*Adj;

            return (
                Inv
            );
        } else {
            return (
                Matrix<T>(1)
            );
        }
    }

    /******************************************************
                        Helper Functions
    ******************************************************/
    /* Return Vector with column vector values
     * @param Matrix Object, column value
     * @return Column Vector Object
    */
    template <class T>
    Vector<T> get_column_vector(Matrix<T>& A, int column) {
        int numRows = A.get_num_rows();

        T* newData = new T[numRows];

        for (int i = 0; i < numRows; i++)
            newData[i] = A.get_element(i, column);
        
        return (
            Vector<T>(numRows, newData)
        );
    }

    /* Return Vector with row vector value
     * @param Matrix Object, row value
     * @return Row Vector Object
    */
    template <class T>
    Vector<T> get_row_vector(Matrix<T>& A, int row) {
        int numCols = A.get_num_cols();

        T* newData = new T[numCols];

        for (int i = 0; i < numCols; i++)
            newData[i] = A.get_element(row, i);
        
        return (
            Vector<T>(numCols, newData)
        );
    }

    /* Return SubMatrix of Matrix with given index
     *  - Used to calculate Determinant
     * @param Matrix Object, index value
     * @return SubMatrix
    */
    template <class T>
    Matrix<T> get_submatrix(const Matrix<T>& A, int index) {
        int newRows = A.get_num_rows() - 1;
        int newCols = A.get_num_cols() - 1;
        int newLength = newRows * newCols;
        T* newData = new T[newLength];

        int rowIgnore = (index/A.get_num_cols());
        int colIgnore = (index%A.get_num_cols());
        int indexCount = 0;
        for (int i = 0; i < (A.get_num_rows()*A.get_num_cols()); i++) {
            int currentRow = (i/A.get_num_cols());
            int currentCol = (i%A.get_num_cols());
            if ((currentRow != rowIgnore) && (currentCol != colIgnore)) {
                newData[indexCount] = A.get_element(currentRow, currentCol);
                indexCount++;
            }
        }

        return (
            Matrix<T>(
                newRows, newCols, newData
            )
        );
    }

    template class Matrix<float>;
}