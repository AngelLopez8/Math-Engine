#include "../include/Vector3D.h"

namespace AMathEngine {

    /******************************************************
                Constructor / Destructor Functions
    ******************************************************/
    /* Default Constructor */
    template <class T>
    Vector3D<T>::Vector3D() {
        length = 3;
        data = new T[length];
        data[0] = data[1] = data[2] = 0.0;
    }

    /* Constructor
     * @param 3 float values
    */
    template <class T>
    Vector3D<T>::Vector3D(float x, float y, float z) {
        length = 3;
        data = new T[length];
        data[0] = x;
        data[1] = y;
        data[2] = z;
    }


    /* Copy Constructor 
     * @param Vector Object
    */
    template <class T>
    Vector3D<T>::Vector3D(const Vector3D& inputVector) {
        this->length = inputVector.length;
        this->data = new T[this->length];
        this->data[0] = inputVector.data[0];
        this->data[1] = inputVector.data[1];
        this->data[2] = inputVector.data[2];
    }

    /* Move Constructor 
     * @param Vector Object
    */
    template <class T>
    Vector3D<T>::Vector3D(Vector3D<T>&& inputVector) {
        this->length = inputVector.length;
        this->data = new T[this->length];
        this->data[0] = inputVector.data[0];
        this->data[1] = inputVector.data[1];
        this->data[2] = inputVector.data[2];

        delete[] inputVector.data;
        inputVector.data = nullptr;
        inputVector.length = 0;
    }

    /* Destructor */
    template <class T>
    Vector3D<T>::~Vector3D() {
        if (data != nullptr) {
            delete[] data;
            data = nullptr;
        }
    }

    /******************************************************
                        Friend Functions
    ******************************************************/

    /* Cross Product
     * Returns a Perpendicular Vector to the two Vectors
     * @param Vector Object, Vector Object
     * @return new Vector Object
    */
    template <class T>
    Vector3D<T> cross(const Vector3D<T>& lhs.data, const Vector3D<T>& rhs.data) {
        return (
            Vector3D<T>(
                lhs.data[1]*rhs.data[2] - lhs.data[2]*rhs.data[1],
                -1*(lhs.data[0]*rhs.data[2] - lhs.data[2]*rhs.data[0]),
                lhs.data[0]*rhs.data[1] - lhs.data[1]*rhs.data[0]
            )
        );
    }

    /* Scalar Triple Product 
     * Used to find the volume of a parallelepiped
     * @param Vector Object, Vector Object, Vector Object
     * @return 
    */
    template <class T>
    T scalar_triple_product(const Vector3D<T>& a, const Vector3D<T>& b, const Vector3D<T>& c) {
        return (
            dot(a, cross(b, c))
        );        
    }
}