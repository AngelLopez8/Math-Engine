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
    Vector3D<T>::Vector3D(const Vector3D& a) {
        length = a.length;
        data = new T[length];
        data[0] = a.data[0];
        data[1] = a.data[1];
        data[2] = a.data[2];
    }

    /* Move Constructor 
     * @param Vector Object
    */
    template <class T>
    Vector3D<T>::Vector3D(Vector3D<T>&& a) {
        length = a.length;
        data = new T[length];
        data[0] = a.data[0];
        data[1] = a.data[1];
        data[2] = a.data[2];

        delete[] a.data;
        a.data = nullptr;
        a.length = 0;
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
    Vector3D<T> cross(const Vector3D<T>& a, const Vector3D<T>& b) {
        return (
            Vector3D<T>(
                a[1]*b[2] - a[2]*b[1],
                a[2]*b[0] - a[0]*b[2],
                a[0]*b[1] - a[1]*b[0]
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