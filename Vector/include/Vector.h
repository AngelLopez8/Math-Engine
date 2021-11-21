#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <math.h>
#include <vector>

#include "Exception.h"

# define M_PI   3.14159265358979323846  /* pi */

using std::ostream;
using std::vector;

namespace AMathEngine {
    class Vector {
        protected:
            vector<float> vec;
            int length;
        public:
            Vector();               // Default Constructor
            Vector(const Vector&);  // Copy Constructor
            Vector(Vector&&);       // Move Constructor
            Vector(vector<float>);  // Constructor passed in array
            ~Vector();              // Destructor

            Vector& operator=(const Vector&);   // Copy assignment operator
            Vector& operator=(Vector&&); // Move Assignment Operator
            
            Vector& operator*=(float);     // Vector Scalar Multiplication

            Vector& operator+=(const Vector&);     // Vector Addition
            Vector& operator-=(const Vector&);     // Vector Subtraction

            // Subscript Operators
            float& operator[](int); 
            const float& operator[](int) const;

            int get_length() const { return length; }   // returns vector length

            // Overloaded Output Operator
            friend ostream& operator<<(ostream& out, const Vector& a) {
                for (int i = 0; i < a.length; i++) {
                    out << a.vec[i] << "\n";
                }
                return out;
            }
    };

    Vector operator*(const Vector&, float);             // Vector Scalar Multiplication
    Vector operator+(const Vector&, const Vector&);     // Vector Addition
    Vector operator-(const Vector&, const Vector&);     // Vector Subtraction

    float dot(const Vector&, const Vector&);    // Dot Product
    float magnitude(const Vector&);             // Vector Magnitude
    float find_angle(const Vector&, const Vector&);  // returns angle between vectors
}

#endif