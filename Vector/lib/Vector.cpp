#include "../include/Vector.h"

namespace AMathEngine {

    // Default Constructor
    Vector::Vector() {
        vec = {};       // set to empty vector
        length = 0;     // initiate length to 0
    }

    /* Copy Constructor
        
    */
    Vector::Vector(const Vector& a) : vec{a.vec}, length{a.length} {}

    /* Move Constructor
    */
    Vector::Vector(Vector&& a) {
        vec = a.vec;
        length = a.length;
        
        a.vec = {};
        a.length = 0;
    }

    /* Constructor passed in array
    */
    Vector::Vector(vector<float> v) {
        vec = v;
        length = v.size();
    }

    // Destructor
    Vector::~Vector() {}

    /* Copy assignment operator
    */
    Vector& Vector::operator=(const Vector& a) {
        if (this != &a)
        {
            length = a.length;
            vec = a.vec;
      }
      return *this;
    }
    
    /* Move Assignment Operator
    */
    Vector& Vector::operator=(Vector&& a) {
        if (this != &a)
        {            
            vec = a.vec;
            length = a.length;
            
            a.vec = {};
            a.length = 0;
        }
        return *this;
    }

    /* Subscript Operators
    */
    float& Vector::operator[](int index) {
        return vec.at(index);
    }

    const float& Vector::operator[](int index) const {
        return vec.at(index);
    }

    /* Vector Scalar Multiplication
     * Parameter: float s -> scalar
     * Multiply each element in vector by the passed in scalar
    */
    Vector& Vector::operator*=(float s) {
        for (int i = 0; i < length; i++) {
            vec[i] *= s;
        }
        return (*this);
    }

    /* Vector Addition
     * Parameter: Vector a -> Vector Instance
     * Iterate through passed in Vector elements and add to respective element
     * in current vector
    */
    Vector& Vector::operator+=(const Vector& a) {
        for (int i = 0; i < length; i++) {
            vec[i] += a[i];
        }
        return (*this);
    }

    /* Vector Subtraction
     * Parameter: Vector a -> Vector Instance
     * Iterate through passed in Vector elements and subtract to respective element
     * in current vector
    */
    Vector& Vector::operator-=(const Vector& a) {
        for (int i = 0; i < length; i++) {
            vec[i] -= a[i];
        }
        return (*this);
    }

    /* Vector Scalar Multiplication
    */
    Vector operator*(const Vector& a, float s) {
        vector<float> newVec;

        for (int i = 0; i < a.get_length(); i++) {
            newVec.push_back(a[i]*s);
        }

        return(
            Vector(newVec)
        );
    }

    /* Vector Addition
    */
    Vector operator+(const Vector& a, const Vector& b) {
        vector<float> newVec;

        for (int i = 0; i < a.get_length(); i++) {
            newVec.push_back(a[i]+b[i]);
        }

        return (
            Vector(newVec)
        );
    }

    /* Vector Subtraction
    */
    Vector operator-(const Vector& a, const Vector& b) {
        vector<float> newVec;

        for (int i = 0; i < a.get_length(); i++) {
            newVec.push_back(a[i]-b[i]);
        }

        return (
            Vector(newVec)
        );
    }

    /* Dot Product
    */
    float dot(const Vector& a, const Vector& b) {
        int len = a.get_length();
        float sum = 0;

        for (int i = 0; i < len; i++) {
            sum += a[i]*b[i];
        }
        return sum;
    }

    /* Vector Magnitude
    */
    float magnitude(const Vector& a) {
        int len = a.get_length();
        float sum = 0;

        for (int i = 0; i < len; i++) {
            sum += (a[i]*a[i]);
        }
        return sqrt(sum);
    }

    /* returns angle between vectors
    */
    float find_angle(const Vector& a, const Vector& b) {
        float dotAB = dot(a, b);
        float magA = magnitude(a);
        float magB = magnitude(b);

        return (
            acos(dotAB/(magA*magB)) * (180/M_PI)
        );
    }
}