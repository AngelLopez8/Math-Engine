#include "../include/Vector.h"

namespace AMathEngine {

    /* Default Constructor */
    Vector::Vector() {
        vec = {};       // set to empty vector
        length = 0;     // initiate length to 0
    }

    /* Copy Constructor 
     * @param Vector Object
    */
    Vector::Vector(const Vector& a) : vec{a.vec}, length{a.length} {}

    /* Move Constructor 
     * @param Vector Object
    */
    Vector::Vector(Vector&& a) {
        vec = a.vec;
        length = a.length;
        
        a.vec = {};
        a.length = 0;
    }

    /* Constructor passed in array 
     * @param vector of floats
    */
    Vector::Vector(vector<float> v) {
        vec = v;
        length = v.size();
    }

    /* Destructor */
    Vector::~Vector() {}

    /* Copy assignment operator 
     * @param Vector Object
     * @return Current Vector Object
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
     * @param Vector Object
     * @return Current Vector Object
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
     * @param index value
     * @return element at index location
    */
    float& Vector::operator[](int index) {
        return vec.at(index);
    }

    const float& Vector::operator[](int index) const {
        return vec.at(index);
    }

    /* Vector Scalar Multiplication
     *  - Iterate through Vector and multiply each element by given scalar value
     * @param scalar value
     * @return Current Vector Object
    */
    Vector& Vector::operator*=(float s) {
        for (int i = 0; i < length; i++) {
            vec[i] *= s;
        }
        return (*this);
    }

    /* Vector Addition
     * @param Vector Object
     * @return Current Vector Object
    */
    Vector& Vector::operator+=(const Vector& a) {
        for (int i = 0; i < length; i++) {
            vec[i] += a[i];
        }
        return (*this);
    }

    /* Vector Subtraction
     * @param Vector Object
     * @return Current Vector Object
    */
    Vector& Vector::operator-=(const Vector& a) {
        for (int i = 0; i < length; i++) {
            vec[i] -= a[i];
        }
        return (*this);
    }

    /* Vector Scalar Multiplication
     * @param Vector Object, Scalar Value
     * @return new Vector Object
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
     * @param Vector Object, Vector Object
     * @return new Vector Object
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
     * @param Vector Object, Vector Object
     * @return new Vector Object
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
     * @param Vector Object, Vector Object
     * @return sum of vector product
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
     *  - 1) Find the sum of each element squared
     *  - 2) Return Square Root of Sum
     * @param Vector Object
     * @return magnitude of Vector
    */
    float magnitude(const Vector& a) {
        int len = a.get_length();
        float sum = 0;

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
    float find_angle(const Vector& a, const Vector& b) {
        float dotAB = dot(a, b);
        float magA = magnitude(a);
        float magB = magnitude(b);
        float quot = dotAB/(magA*magB);

        return (
            acos(quot) * (180/M_PI)
        );
    }

    /* Normalize Vector
     *  - Multiply vector by 1 over the vector magnitude
     * @param Vector Object
     * @return Normalized Vector
    */
    Vector normalize(const Vector& a) {
        float mag = 1.0f/magnitude(a);

        return (
            a*mag
        ); 
    }
}