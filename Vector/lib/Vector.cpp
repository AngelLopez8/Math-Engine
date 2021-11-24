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
    Vector<T>::Vector(const Vector<T>& a) : length{a.length} {
        data = new T[length];
        for (int i = 0; i < length; i++)
            data[i] = a.data[i];
    }

    /* Move Constructor 
     * @param Vector Object
    */
   template <class T>
    Vector<T>::Vector(Vector<T>&& a) {
        length = a.length;
        data = new T[length];

        for (int i = 0; i < length; i++)
            data[i] = a.data[i];
        
        delete[] a.data;
        a.data = nullptr;
        a.length = 0;
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
                  Overloaded Operators Functions
    ******************************************************/

    /* Copy assignment operator 
     * @param Vector Object
     * @return Current Vector Object
    */
    template <class T>
    Vector<T>& Vector<T>::operator=(const Vector<T>& a) {
        if (this != &a)
        {
            length = a.length;
            delete[] data;
            data = new T[length];
            for (int i = 0; i < length; i++)
                data[i] = a.data[i];
      }
      return (*this);
    }
    
    /* Move Assignment Operator 
     * @param Vector Object
     * @return Current Vector Object
    */
    template <class T>
    Vector<T>& Vector<T>::operator=(Vector<T>&& a) {
        if (this != &a)
        {            
            length = a.length;
            delete[] data;
            data = new T[length];

            for (int i = 0; i < length; i++)
                data[i] = a.data[i];
            
            delete[] a.data;
            a.data = nullptr;
            a.length = 0;
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
    Vector<T>& Vector<T>::operator+=(const Vector<T>& a) {
        for (int i = 0; i < length; i++) {
            data[i] += a[i];
        }
        return (*this);
    }

    /* Vector Subtraction
     * @param Vector Object
     * @return Current Vector Object
    */
    template <class T>
    Vector<T>& Vector<T>::operator-=(const Vector<T>& a) {
        for (int i = 0; i < length; i++) {
            data[i] -= a[i];
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
        T* newData = new T[a.length];
        int newLength = a.length;

        for (int i = 0; i < newLength; i++) {
            newData[i] = a[i]*s;
        }

        Vector<T> newVec (newLength, newData);
        delete[] newData;

        return(
            newVec
        );
    }

    /* Vector Addition
     * @param Vector Object, Vector Object
     * @return new Vector Object
    */
    template <class T>
    Vector<T> operator+(const Vector<T>& a, const Vector<T>& b) {
        T* newData = new T[a.length];
        int newLength = a.length;

        for (int i = 0; i < newLength; i++) {
            newData[i] = a[i]+b[i];
        }

        Vector<T> newVec (newLength, newData);
        delete[] newData;
        
        return(
            newVec
        );
    }

    /* Vector Subtraction
     * @param Vector Object, Vector Object
     * @return new Vector Object
    */
    template <class T>
    Vector<T> operator-(const Vector<T>& a, const Vector<T>& b) {
        T* newData = new T[a.length];
        int newLength = a.length;

        for (int i = 0; i < newLength; i++) {
            newData[i] = a[i]-b[i];
        }

        Vector<T> newVec (newLength, newData);
        delete[] newData;
        
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
    T dot(const Vector<T>& a, const Vector<T>& b) {
        int len = a.get_length();
        T sum = 0;

        for (int i = 0; i < len; i++) {
            sum += a[i]*b[i];
        }
        return sum;
    }

    /* Vector Magnitude
     *  - 1) Find the sum of each element squared
     *  - 2) Return Square Root of Sum
     * @param Vector Object
     * @return magnitude of Vector
    */
    template <class T>
    T magnitude(const Vector<T>& a) {
        int len = a.get_length();
        T sum = 0;

        for (int i = 0; i < len; i++) {
            sum += (a[i]*a[i]);
        }
        return sqrt(sum);
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
    T find_angle(const Vector<T>& a, const Vector<T>& b) {
        T dotAB = dot(a, b);
        T magA = magnitude(a);
        T magB = magnitude(b);
        T quot = dotAB/(magA*magB);

        return (
            acos(quot) * (180/M_PI)
        );
    }

    /* Normalize Vector
     *  - Multiply vector by 1 over the vector magnitude
     * @param Vector Object
     * @return Normalized Vector
    */
    template <class T>
    Vector<T> normalize(const Vector<T>& a) {
        T mag = 1.0f/magnitude(a);

        int newLength = a.length;
        T* newData = new T[newLength];
    
        for (int i = 0; i < a.length; i++)
            newData[i] = a[i]*mag;

        return (
            Vector<T>(a.length, newData)
        );
    }

    template class Vector<float>;
}