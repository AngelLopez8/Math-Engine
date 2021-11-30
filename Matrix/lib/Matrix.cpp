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
        this->matrixData = new T[this->nElements];
        for (int i = 0; i < this->nElements; i++)
            this->matrixData[i] = inputMatrix.matrixData[i];
    }

    /* Move Constructor
     * @param Matrix Object
    */
    template <class T>
    Matrix<T>::Matrix(Matrix<T>&& inputMatrix) 
        : nRows(inputMatrix.nRows), nCols(inputMatrix.nCols), nElements(inputMatrix.nElements) {
        this->matrixData = new T[this->nElements];
        for (int i = 0; i < this->nElements; i++)
            this->matrixData[i] = inputMatrix.matrixData[i];

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
        if ((numRow <= 0) || (numCols <= 0))
            return false;
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

    /* Get Column Vector
     * @param column value
     * @return Vector Object
    */
    template <class T>
    Vector<T> Matrix<T>::get_column_vector(int column) const{
        if ((column < 0) || (column >= nCols)) {
            throw std::invalid_argument("Column out of range.");
        }
        Vector<T> colVector(nRows);

        for (int i = 0; i < nRows; i++)
            colVector[i] = get_element(i, column);
        
        return colVector;
    }

    /* Get Row Vector
     * @param row value
     * @return Vector Object
    */
    template <class T>
    Vector<T> Matrix<T>::get_row_vector(int row) const {
        if ((row < 0) || (row >= nRows)) {
            throw std::invalid_argument("Row out of range.");
        }
        Vector<T> rowVector(nRows);

        for (int i = 0; i < nRows; i++)
            rowVector[i] = get_element(row, i);
        
        return rowVector;
    }

    /* Get SubMatrix
     * @param row value, col value
     * @return Matrix Object
    */
    template <class T>
    Matrix<T> Matrix<T>::get_submatrix(int row, int col) const {
        if ((row <= 0) || (row >= nRows) || (col <= 0) || (row >= nCols)) {
            throw std::invalid_argument("Row/Column out of range.");
        }
        Matrix<T> subMatrix(nRows-1, nCols-1);

        int count = 0;
        for (int i = 0; i < nRows; i++) {
            for (int j = 0; j < nCols; j++) {
                if ((i != row) && (j != col)) {
                    subMatrix.matrixData[count] = this->get_element(i, j);
                    count++;
                }
            }
        }

        return subMatrix;
    }

    /******************************************************
     *               Functions to Computate
    ******************************************************/
    /* Calculate Determinant
     * @param None
     * @return Determinant result
    */
    template <class T>
    T Matrix<T>::determinant() const {
        if (!is_square()) {
            throw std::invalid_argument("Must be a Square Matrix (Number of Rows must equal Number of Columns).");
        }

        T det;

        if (nRows == 2) {
            det = (matrixData[0]*matrixData[3] - matrixData[1]*matrixData[2]);
        } else {
            T sum = static_cast<T>(0.0);
            T sign = static_cast<T>(1.0);
            for (int i = 0; i < nCols; i++) {
                Matrix<T> subMatrix = this->get_submatrix(0, i);

                sum += sign*this->get_element(0, i)*subMatrix.determinant();
                sign = -sign;
            }
            det = sum;
        }

        return det;
    }

    /* Get transpose of current Matrix
     * @param None
     * @return Matrix Object
    */
    template <class T>
    Matrix<T> Matrix<T>::transposed() const {
        T* newData = new T[nElements];

        for (int i = 0; i < nElements; i++) {
            int currRow = (i/nRows);
            int currCol = (i%nRows);

            newData[i] = get_element(currCol, currRow);
        }

        Matrix<T> newMatrix(nCols, nRows, newData);
        delete[] newData;

        return (
            newMatrix
        );
    }

    /* Turn current Matrix to Tranpose of itself
     * @param None
     * @return None
    */
    template <class T>
    void Matrix<T>::transpose() {
        T* newData = new T[nElements];

        for (int i = 0; i < nElements; i++) {
            int currRow = (i/nRows);
            int currCol = (i%nRows);

            newData[i] = get_element(currCol, currRow);
        }

        for (int i = 0; i < nElements; i++) {
            matrixData[i] = newData[i];
        }
        
        delete[] newData;
    }

    /* Get Adjacency Matrix of current Matrix
     * @param None
     * @return Matrix Object
    */
    template <class T>
    Matrix<T> Matrix<T>::adjacented() const {
        if (!is_square()) {
            throw std::invalid_argument("Must be a Square Matrix (Number of Rows must equal Number of Columns).");
        }

        if (nRows == 2) {
            Matrix<T> Adj(2, 2);
            T det = this->determinant();
            det = 1.0/det;
            Adj.matrixData[0] = matrixData[3];
            Adj.matrixData[1] = -1*matrixData[1];
            Adj.matrixData[2] = -1*matrixData[2];
            Adj.matrixData[3] = matrixData[0];

            return Adj;
        }

        Matrix<T> AT = transposed();
        Matrix<T> newMatrix(nRows, nCols);

        T sign = static_cast<T>(1.0);
        for (int i = 0; i < nCols; i++) {
            for (int j = 0; j < nRows; j++) { 
                Matrix<T> subMatrix = AT.get_submatrix(i, j);
                T det = subMatrix.determinant();
                det = det*sign;
                newMatrix.set_element(i, j, det);
                sign = -sign;
            }
        }

        return (
            newMatrix
        );
    }

    /* Turn current Matrix into Ajacency Matrix
     * @param None
     * @return None
    */
    template <class T>
    void Matrix<T>::adjacent() {

        Matrix<T> Adj = this->adjacented();

        for (int i = 0; i < nElements; i++) {
            matrixData[i] = Adj.matrixData[i];
        }
    }

    /* Get inverse of current Matrix
     * @param None
     * @return Matrix Object
    */
    template <class T>
    Matrix<T> Matrix<T>::inversed() const {
        T det = determinant();
        if (det == 0) {
            throw std::invalid_argument("Determinant = 0, inverse matrix does not exist.");
        }
        det = static_cast<T>(1.0)/det;
        Matrix<T> Inv = this->adjacented();

        for (int i = 0; i < nElements; i++)
            Inv.matrixData[i] = Inv.matrixData[i]*det;

        return Inv;
    }
    
    /* Turn current Matrix to inverse of itself
     * @param None
     * @return None
    */
    template <class T>
    void Matrix<T>::inverse() {
        T det = determinant();
        if (det == 0) {
            throw std::invalid_argument("Determinant = 0, inverse matrix does not exist.");
        }
        det = static_cast<T>(1.0)/det;
        this->adjacent();

        for (int i = 0; i < nElements; i++)
            matrixData[i] = matrixData[i]*det;
    }

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
    Matrix<T>& Matrix<T>::operator=(const Matrix<T>& rhs) {
        if (this != &rhs)
        {
            this->nRows = rhs.nRows;
            this->nCols = rhs.nCols;
            this->nElements = this->nRows*this->nCols;
            delete[] this->matrixData;
            this->matrixData = new T[this->nElements];
            for (int i = 0; i < this->nElements; i++)
                this->matrixData[i] = rhs.matrixData[i];
      }
      return (*this);
    }
    
    /* Move Assignment Operator 
     * @param Matrix Object
     * @return Current Matrix Object
    */
    template <class T>
    Matrix<T>& Matrix<T>::operator=(Matrix<T>&& rhs) {
        if (this != &rhs)
        {            
            this->nRows = rhs.nRows;
            this->nCols = rhs.nCols;
            this->nElements = this->nRows*this->nCols;
            delete[] this->matrixData;
            this->matrixData = new T[this->nElements];
            for (int i = 0; i < this->nElements; i++)
                this->matrixData[i] = rhs.matrixData[i];
            
            delete[] rhs.matrixData;
            rhs.matrixData = nullptr;
            rhs.nRows = 0; rhs.nCols = 0;
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
        if ((lhs.nRows != rhs.nRows) || (lhs.nCols != rhs.nCols)) {
            throw std::invalid_argument("Dimensions do not match.");
        }

        Matrix<T> newMatrix(lhs.nRows, lhs.nCols);
        
        for (int i = 0; i < lhs.nRows; i++)
            for (int j = 0; j < lhs.nCols; j++) {
                T sum = lhs.get_element(i, j) + rhs.get_element(i, j);
                newMatrix.set_element(i, j, sum);
            }

        return newMatrix;
    }

    /* Add scalar value to each Matrix Element: scalar + Matrix
     * @param scalar value, Matrix Object
     * @return new Matrix Object
    */
    template <class T>
    Matrix<T> operator+(const T& lhs, const Matrix<T>& rhs) {
        Matrix<T> newMatrix(rhs.nRows, rhs.nCols);
        
        for (int i = 0; i < rhs.nRows; i++)
            for (int j = 0; j < rhs.nCols; j++) {
                T sum = lhs + rhs.get_element(i, j);
                newMatrix.set_element(i, j, sum);
            }

        return newMatrix;
    }

    /* Add scalar value to each Matrix Element: Matrix + scalar
     * @param Matrix Object, scalar value
     * @return new Matrix Object
    */
    template <class T>
    Matrix<T> operator+(const Matrix<T>& lhs, const T& rhs) {
        Matrix<T> newMatrix(lhs.nRows, lhs.nCols);
        
        for (int i = 0; i < lhs.nRows; i++)
            for (int j = 0; j < lhs.nCols; j++) {
                T sum = lhs.get_element(i, j) + rhs;
                newMatrix.set_element(i, j, sum);
            }

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
        if ((lhs.nRows != rhs.nRows) || (lhs.nCols != rhs.nCols)) {
            throw std::invalid_argument("Dimensions do not match.");
        }
        
        Matrix<T> newMatrix(lhs.nRows, lhs.nCols);
        
        for (int i = 0; i < lhs.nRows; i++)
            for (int j = 0; j < lhs.nCols; j++) {
                T sum = lhs.get_element(i, j) - rhs.get_element(i, j);
                newMatrix.set_element(i, j, sum);
            }

        return newMatrix;
    }

    /* Subtract scalar value to each Matrix Element: scalar - Matrix
     * @param Matrix Object, scalar value
     * @return new Matrix Object
    */
    template <class T>
    Matrix<T> operator-(const T& lhs, const Matrix<T>& rhs) {
        Matrix<T> newMatrix(rhs.nRows, rhs.nCols);
        
        for (int i = 0; i < rhs.nRows; i++)
            for (int j = 0; j < rhs.nCols; j++) {
                T sum = lhs - rhs.get_element(i, j);
                newMatrix.set_element(i, j, sum);
            }

        return newMatrix;
    }

    /* Subtract scalar value to each Matrix Element: Matrix - scalar
     * @param Matrix Object, scalar value
     * @return new Matrix Object
    */
    template <class T>
    Matrix<T> operator-(const Matrix<T>& lhs, const T& rhs) {
        Matrix<T> newMatrix(lhs.nRows, lhs.nCols);
        
        for (int i = 0; i < lhs.nRows; i++)
            for (int j = 0; j < lhs.nCols; j++) {
                T sum = lhs.get_element(i, j) - rhs;
                newMatrix.set_element(i, j, sum);
            }

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
            Matrix<T> newMatrix(LnumRows, RnumCols);

            for (int i = 0; i < LnumRows; i++) {
                for (int j = 0; j < RnumCols; j++) {
                    Vector<T> rowVector = lhs.get_row_vector(i);
                    Vector<T> colVector = rhs.get_column_vector(j);
                    T sum = dot(rowVector, colVector);
                    newMatrix.set_element(i, j, sum);
                }
            }

            return newMatrix;
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
        Matrix<T> newMatrix(rhs.nRows, rhs.nCols);
        
        for (int i = 0; i < rhs.nRows; i++)
            for (int j = 0; j < rhs.nCols; j++) {
                T sum = lhs * rhs.get_element(i, j);
                newMatrix.set_element(i, j, sum);
            }

        return newMatrix;
    }

    /* Matrix & Scalar Multiplication: Matrix*scalar
     * @param Matrix Object, Scalar value
     * @return new Matrix Object
    */
    template <class T>
    Matrix<T> operator*(const Matrix<T>& lhs, const T& rhs) {
        Matrix<T> newMatrix(lhs.nRows, lhs.nCols);
        
        for (int i = 0; i < lhs.nRows; i++)
            for (int j = 0; j < lhs.nCols; j++) {
                T sum = lhs.get_element(i, j) * rhs;
                newMatrix.set_element(i, j, sum);
            }

        return newMatrix;
    }

    /* Matrix & Vector Multiplication: Matrix*Vector
     * @param Matrix Object, Vector Object
     * @return Vector of product sum
    */
    template <class T>
    Vector<T> operator*(const Matrix<T>& lhs, const Vector<T>& rhs) {
        if (lhs.nCols != rhs.get_length()) {
            throw std::invalid_argument("Number of Columns in Matrix must equal number of rows in vector.");
        }
        Vector<T> newVec(lhs.nRows);

        for (int i = 0; i < lhs.nRows; i++) {
            T sum = 0.0;
            for (int j = 0; j < lhs.nCols; j++) {
                sum += lhs.get_element(i, j) * rhs[j];
            }
            newVec[i] = sum;
        }
        return (
            newVec
        );
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

    template class Matrix<float>;
}