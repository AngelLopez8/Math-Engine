#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <cmath>

using std::ostream;

namespace A4DEngine {
    class Matrix{
        virtual ~Matrix() {}

        // Print out Vector
        virtual void show(ostream&) const = 0;

        // Overloaded cout
        friend ostream& operator<<(ostream& os, const Matrix& M) {
            M.show(os);
            return os;
        }
    };
}

#endif