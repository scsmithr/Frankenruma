#ifndef FRANKEN_BASE_SCANNER_H
#define FRANKEN_BASE_SCANNER_H

#include<emscripten/bind.h>

#include "oniguruma.h"

#include "regexp.h"

using namespace emscripten;
using std::string;

class OnScanResultListener {
public:
    OnScanResultListener(val callback) : callback(callback) {}

    void fire(int index, int length) {
        callback(index, length);
    } 

private:
    val callback;
};

class BaseScanner {
public:
    BaseScanner(Regexp* reg);

    void onScanResult(val callback);

    void scan(const string& text);

private:
    int processScan(OnigRegion* region);

    static int scanCallback(int n, int r, OnigRegion* region, void* arg);

    OnScanResultListener *listener_;
    Regexp *reg_;

};

EMSCRIPTEN_BINDINGS(base_scanner) {
    class_<BaseScanner>("BaseScanner")
        .constructor<Regexp*>()
        .function("onScanResult", &BaseScanner::onScanResult)
        .function("scan", &BaseScanner::scan)
        ;
}

EMSCRIPTEN_BINDINGS(regexp) {
    class_<Regexp>("Regexp")
        .constructor<const string&>()
        ;
}

#endif