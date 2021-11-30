#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <stdexcept>
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
                    std::cout << data[i] << "\n";
                std::cout << std::endl;
            }
            /***************************** Functions to Computate *****************************/
            T magnitude() const;
            Vector<T> normalized() const;
            void normalize();

            /***************************** Overloaded Operators *****************************/
            bool operator==(const Vector<T>& rhs);  // Overloaded == operator

            Vector<T>& operator=(const Vector<T>& rhs);     // Copy assignment operator
            Vector<T>& operator=(Vector<T>&& rhs);      // Move Assignment Operator
            
            Vector<T>& operator*=(float s);   // Vector Scalar Multiplication

            Vector<T>& operator+=(const Vector<T>& rhs);    // Vector Addition
            Vector<T>& operator-=(const Vector<T>& rhs);    // Vector Subtraction

            // Subscript Operators
            T& operator[](int index); 
            const T& operator[](int index) const;

            /***************************** Overloaded Operators (friends) *****************************/
            template <class U> friend Vector<U> operator*(const Vector<U>& a, float s);     // Vector Scalar Multiplication
            template <class U> friend Vector<U> operator*(float s, const Vector<U>& a);     // Vector Scalar Multiplication

            template <class U> friend Vector<U> operator+(const Vector<U>& lhs, const Vector<U>& rhs);  // Vector Addition
            template <class U> friend Vector<U> operator-(const Vector<U>& lhs, const Vector<U>& rhs);  // Vector Subtraction

            /***************************** Friend Functions *****************************/
            template <class U> friend U dot(const Vector<U>& lhs, const Vector<U>& rhs);    // Dot Product
            template <class U> friend U find_angle(const Vector<U>& lhs, const Vector<U>& rhs);     // returns angle between vectors
    };
}

#endif