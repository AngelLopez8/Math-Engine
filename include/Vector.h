#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <cmath>

using std::ostream;

namespace A4DEngine {
    class Vector {
        public:
            virtual ~Vector() {}

            // Print out Vector
            virtual void show(ostream&) const = 0;

            // Overloaded cout
            friend ostream& operator<<(ostream& os, const Vector& v) {
                v.show(os);
                return os;
            }
    };
}

#endif