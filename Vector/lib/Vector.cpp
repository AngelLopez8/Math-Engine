#include "../include/Vector.h"

namespace AMathEngine {

    /******************************************************
                Constructor / Destructor Functions
    ******************************************************/
    /* Default Constructor */
    template <class T>
    Vector<T>::Vector() {
        length = 1;     // initiate length to 1
        data = new T[length];       // set to empty array size 1
        data[0] = 0.0;
    }

    /*  Constructor: Create empty Vector of given length 
     * @param lengh value
    */
   template <class T>
    Vector<T>::Vector(int len) {
        length = len;
        data = new T[length];
        for (int i = 0; i < length; i++)
            data[i] = 0.0;
    }

    /*  Constructor: Create new Vector of given data
     * @param lengh value
    */
   template <class T>
    Vector<T>::Vector(int len, const T* inputData) {
        length = len;
        data = new T[length];
        for (int i = 0; i < length; i++)
            data[i] = inputData[i];
    }

    /* Copy Constructor 
     * @param Vector Object
    */
    template <class T>
    Vector<T>::Vector(const Vector<T>& inputVector) : length{inputVector.length} {
        this->data = new T[this->length];
        for (int i = 0; i < length; i++)
            this->data[i] = inputVector.data[i];
    }

    /* Move Constructor 
     * @param Vector Object
    */
   template <class T>
    Vector<T>::Vector(Vector<T>&& inputVector) {
        this->length = inputVector.length;
        this->data = new T[this->length];

        for (int i = 0; i < this->length; i++)
            this->data[i] = inputVector.data[i];
        
        delete[] inputVector.data;
        inputVector.data = nullptr;
        inputVector.length = 0;
    }

    /* Destructor */
    template <class T>
    Vector<T>::~Vector() {
        if (data != nullptr)  {
            delete[] data;     
            data = nullptr;
        }  
    }

    /******************************************************
                    Configuration Functions
    ******************************************************/
   /* Resize Vector
    * 1) delete current data
    * 2) If data == nullptr return false otherwise continue
    * 3) create new array empty of new length
    * 4) return true
    * @param new length value
    * @return boolean value of resize result
   */
    template <class T>
    bool Vector<T>::resize(int len) {
        length = len;
        delete[] data;
        data = new T[length];
        if (data != nullptr) {
            for (int i = 0; i < length; i++)
                data[i] = 0.0;
            return true;
        } else {
            return false;
        }
    }

    /******************************************************
                    Element Access Functions
    ******************************************************/
   /* Get Length of Current Vector
    * @param None
    * @return Vector length
   */
    template <class T>
    int Vector<T>::get_length() const { 
        return length; 
    }

    /******************************************************
                    Functions to Computate
    ******************************************************/
    /* Vector Magnitude
     * @param None
     * @return Magnitude of Current Vector
    */
    template <class T>
    T Vector<T>::magnitude() const {
        T sum = 0.0;
        for (int i = 0; i < length; i++) {
            sum += data[i]*data[i];
        }
        return (
            sqrt(sum)
        );
    }
    
    /* Copy of Normalized Vector
     * @param None
     * @return Normalize Vector
    */
    template <class T>
    Vector<T> Vector<T>::normalized() const {
        T mag = magnitude();
        mag = 1.0/mag;

        Vector<T> newVec(this->length);
        for (int i = 0; i < this->length; i++)
            newVec[i] = this->data[i] * mag;
        
        return (
            newVec
        );
    }

    /* Set Vector to Normalized Vector
     * @param None
     * @return None
    */
    template <class T>
    void Vector<T>::normalize() {
        T mag = magnitude();
        mag = 1.0/mag;

        for (int i = 0; i < length; i++)
            data[i] = data[i]*mag;
    }

    /******************************************************
                  Overloaded Operators Functions
    ******************************************************/
    /* Overloaded (==) equal to Operator
     * @param Vector Object
     * @return boolean result of Vector compare
    */
    template <class T>
    bool Vector<T>::operator==(const Vector<T>& rhs) {
        // Check if the matrices are the same dimension, if not return false
        if (this->length != rhs.length)
            return false;
        
        // Check if elements are equal
        bool flag = true;
        for (int i = 0; i < this->length; i++) {
            if (this->data[i] != rhs.data[i])
                flag = false;
        }
        return flag;
    }

    /* Copy assignment operator 
     * @param Vector Object
     * @return Current Vector Object
    */
    template <class T>
    Vector<T>& Vector<T>::operator=(const Vector<T>& rhs) {
        if (this != &rhs)
        {
            this->length = rhs.length;
            delete[] this->data;
            this->data = new T[this->length];

            for (int i = 0; i < this->length; i++)
                this->data[i] = rhs.data[i];
      }
      return (*this);
    }
    
    /* Move Assignment Operator 
     * @param Vector Object
     * @return Current Vector Object
    */
    template <class T>
    Vector<T>& Vector<T>::operator=(Vector<T>&& rhs) {
        if (this != &rhs)
        {            
            this->length = rhs.length;
            delete[] this->data;
            this->data = new T[this->length];

            for (int i = 0; i < this->length; i++)
                this->data[i] = rhs.data[i];
            
            delete[] rhs.data;
            rhs.data = nullptr;
            rhs.length = 0;
        }
        return (*this);
    }

    /* Vector Scalar Multiplication
     *  - Iterate through Vector and multiply each element by given scalar value
     * @param scalar value
     * @return Current Vector Object
    */
    template <class T>
    Vector<T>& Vector<T>::operator*=(float s) {
        for (int i = 0; i < length; i++) {
            data[i] *= s;
        }
        return (*this);
    }

    /* Vector Addition
     * @param Vector Object
     * @return Current Vector Object
    */
    template <class T>
    Vector<T>& Vector<T>::operator+=(const Vector<T>& rhs) {
        if (this->length != rhs.length) {
            throw std::invalid_argument("Number of rows in current Vector must equal rows in Vector 'a'.");
        }

        for (int i = 0; i < this->length; i++) {
            this->data[i] += rhs.data[i];
        }
        return (*this);
    }

    /* Vector Subtraction
     * @param Vector Object
     * @return Current Vector Object
    */
    template <class T>
    Vector<T>& Vector<T>::operator-=(const Vector<T>& rhs) {
        if (this->length != rhs.length) {
            throw std::invalid_argument("Number of rows in current Vector must equal rows in Vector 'a'.");
        }

        for (int i = 0; i < this->length; i++) {
            this->data[i] -= rhs.data[i];
        }
        return (*this);
    }

    /* Subscript Operators 
     * @param index value
     * @return element at index location
    */
    template <class T>
    T& Vector<T>::operator[](int index) {
        return data[index];
    }

    template <class T>
    const T& Vector<T>::operator[](int index) const {
        return data[index];
    }

    /******************************************************
              Overloaded Operators Functions (friends)
    ******************************************************/

    /* Vector Scalar Multiplication
     * @param Vector Object, Scalar Value
     * @return new Vector Object
    */
    template <class T>
    Vector<T> operator*(const Vector<T>& a, float s) {
        Vector<T> newVec(a.length);

        for (int i = 0; i < a.length; i++) {
            newVec.data[i] = a.data[i]*s;
        }

        return(
            newVec
        );
    }

    /* Vector Scalar Multiplication
     * @param Scalar Value, Vector Object
     * @return new Vector Object
    */
    template <class T>
    Vector<T> operator*(float s, const Vector<T>& a) {
        Vector<T> newVec(a.length);

        for (int i = 0; i < a.length; i++) {
            newVec.data[i] = a.data[i]*s;
        }

        return(
            newVec
        );
    }

    /* Vector Addition
     * @param Vector Object, Vector Object
     * @return new Vector Object
    */
    template <class T>
    Vector<T> operator+(const Vector<T>& lhs, const Vector<T>& rhs) {
        if (lhs.length != rhs.length) {
            throw std::invalid_argument("Number of rows in Vector 'a' must equal rows in Vector 'b'.");
        }

        Vector<T> newVec(lhs.length);

        for (int i = 0; i < lhs.length; i++) {
            newVec.data[i] = lhs.data[i]+rhs.data[i];
        }
        
        return(
            newVec
        );
    }

    /* Vector Subtraction
     * @param Vector Object, Vector Object
     * @return new Vector Object
    */
    template <class T>
    Vector<T> operator-(const Vector<T>& lhs, const Vector<T>& rhs) {
        if (lhs.length != rhs.length) {
            throw std::invalid_argument("Number of rows in Vector 'a' must equal rows in Vector 'b'.");
        }

        Vector<T> newVec(lhs.length);

        for (int i = 0; i < lhs.length; i++) {
            newVec.data[i] = lhs.data[i]-rhs.data[i];
        }
        
        return(
            newVec
        );
    }

    /******************************************************
                        Friend Functions
    ******************************************************/

    /* Dot Product
     * @param Vector Object, Vector Object
     * @return sum of vector product
    */
    template <class T>
    T dot(const Vector<T>& lhs, const Vector<T>& rhs) {
        if (lhs.length != rhs.length) {
            throw std::invalid_argument("Number of rows in Vector 'a' must equal rows in Vector 'b'.");
        }

        int len = lhs.get_length();
        T sum = 0;

        for (int i = 0; i < len; i++) {
            sum += lhs[i]*rhs[i];
        }
        return sum;
    }

    /* Find Angle
     *  - 1) Find Dot Product of Vector a and b
     *  - 2) Find magnitudes of Vectors a and b
     *  - 3) Calculate the quotient by dividing the dot product by the 
     *       product of both magnitudes
     *  - 4) Multiply the solution of arccos on quotient with (180/PI) to 
     *       change radians to degrees 
     * @param Vector Object, Vector Object
     * @return Angle between Vectors
    */
    template <class T>
    T find_angle(const Vector<T>& lhs, const Vector<T>& rhs) {
        T dotAB = dot(lhs, rhs);
        T magA = magnitude(lhs);
        T magB = magnitude(rhs);
        T quot = dotAB/(magA*magB);

        return (
            acos(quot) * (180/M_PI)
        );
    }

    template class Vector<float>;
}