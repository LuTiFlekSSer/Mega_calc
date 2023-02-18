#ifndef MEGA_CALCAPP_CRINGE_H
#define MEGA_CALCAPP_CRINGE_H


class cringe {
private:
    friend class LongNumber;

    std::string par;

    explicit cringe(const std::string &par_) {
        par = par_;
    }
};


#endif
