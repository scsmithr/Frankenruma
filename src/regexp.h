#ifndef FRANKEN_REGEXP_H
#define FRANKEN_REGEXP_H

#include<emscripten/bind.h>

#include "oniguruma.h"

using namespace emscripten;
using std::string;

class Regexp {
public:
    Regexp(const string& str);

    ~Regexp();

    regex_t* GetRegex() {return regex_;}

private:
    regex_t *regex_;
};

#endif