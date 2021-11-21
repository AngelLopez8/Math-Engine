#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <string>

using std::string;

namespace AMathEngine {
    class Exception {
        private:
            string msg_;
        public:
            Exception(const string& msg) : msg_(msg) {}
            ~Exception() {}
            
            string getMessage() const {return(msg_);}
    };
}

#endif