#ifndef FRANKEN_RESULT_H
#define FRANKEN_RESULT_H

#include<emscripten/bind.h>

#include "oniguruma.h"

using namespace emscripten;

class Result {
public:
    Result(int index);
private:
    int index;
};

EMSCRIPTEN_BINDINGS(result) {
    class_<Result>("Result")
        .constructor<int>()
        ;
}

#endif