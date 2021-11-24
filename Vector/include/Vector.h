#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <math.h>

# define M_PI   3.14159265358979323846  /* pi */

using std::ostream;

namespace AMathEngine {
    template <class T>
    class Vector {
        protected:
            T* data;
            int length;
        public:
            /***************************** Constructors *****************************/
            Vector();   // Default Constructor
            Vector(int len);    // Empty Vector of given length
            Vector(int len, const T* inputData);    // New Vector of given data
            Vector(const Vector<T>& inputVector);   // Copy Constructor
            Vector(Vector<T>&& inputVector);    // Move Constructor
            
            ~Vector();  // Destructor

            /***************************** Configuration Methods *****************************/
            bool resize(int len);   // Change Vector length

            /***************************** Element Access Methods *****************************/
            int get_length() const;  // returns vector length

            void print() const {
                for (int i = 0; i < length; i++)
                    std::cout << data[i] << " ";
                std::cout << std::endl;
            }

            /***************************** Overloaded Operators *****************************/
            Vector<T>& operator=(const Vector<T>&);     // Copy assignment operator
            Vector<T>& operator=(Vector<T>&&);      // Move Assignment Operator
            
            Vector<T>& operator*=(float);   // Vector Scalar Multiplication

            Vector<T>& operator+=(const Vector<T>&);    // Vector Addition
            Vector<T>& operator-=(const Vector<T>&);    // Vector Subtraction

            // Subscript Operators
            T& operator[](int); 
            const T& operator[](int) const;

            /***************************** Overloaded Operators (friends) *****************************/
            template <class U> friend Vector<U> operator*(const Vector<U>&, float);     // Vector Scalar Multiplication
            template <class U> friend Vector<U> operator+(const Vector<U>&, const Vector<U>&);  // Vector Addition
            template <class U> friend Vector<U> operator-(const Vector<U>&, const Vector<U>&);  // Vector Subtraction

            /***************************** Friend Functions *****************************/
            template <class U> friend U dot(const Vector<U>&, const Vector<U>&);    // Dot Product
            template <class U> friend U magnitude(const Vector<U>&);    // Vector Magnitude
            template <class U> friend U find_angle(const Vector<U>&, const Vector<U>&);     // returns angle between vectors

            template <class U> friend Vector<U> normalize(const Vector<U>&);    // Normalize Vector
    };
}

#endif