#ifndef MEGA_CALCAPP_CRINGE_H
#define MEGA_CALCAPP_CRINGE_H

#include "string"

class cringe {
private:
    friend class LongNumber;

    friend class LongComplex;

    std::string par;

    explicit cringe(const std::string &par_) {
        par = par_;
    }
};


#endif
