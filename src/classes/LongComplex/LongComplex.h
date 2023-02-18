#ifndef MEGA_CALCAPP_LONGCOMPLEX_H
#define MEGA_CALCAPP_LONGCOMPLEX_H

#include "../LongNumber/LongNumber.h"

class LongComplex {
private:
    LongNumber real;
    LongNumber imag;
public:
    LongComplex();

    explicit LongComplex(std::string);

    ~LongComplex();
};

#endif
