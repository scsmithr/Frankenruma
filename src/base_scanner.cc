#include "base_scanner.h"

#include<emscripten.h>

using std::string;

BaseScanner::BaseScanner(Regexp* reg) : reg_(reg) {}

void BaseScanner::onScanResult(val callback) {
    if (callback.typeof().as<std::string>() != "function") {
        EM_ASM(throw "callback not a function");
        return;
    }
    listener_ = new OnScanResultListener(callback);
}

void BaseScanner::scan(const string& text, int offset) {
    OnigRegion *region = onig_region_new();
    offset_ = offset;

    UChar *c_str = (UChar*)text.c_str() + offset_;
    UChar *end = c_str + onigenc_str_bytelen_null(ONIG_ENCODING_UTF8, c_str);
    int status = onig_scan(reg_->GetRegex(), c_str, end, region, ONIG_OPTION_CAPTURE_GROUP, BaseScanner::scanCallback, this);
    if (status < 0) {
        EM_ASM(throw "error scanning");
        return;
    }
    
    onig_region_free(region, 1);
}

int BaseScanner::scanCallback(int n, int r, OnigRegion* region, void* arg) {
    BaseScanner *s = static_cast<BaseScanner*>(arg);
    return s->processScan(region);
}

int BaseScanner::processScan(OnigRegion* region) {
    for (int i = 0; i < region->num_regs; i++) {
        int length = region->end[i] - region->beg[i];
        listener_->fire(region->beg[i] + offset_, length);
    }
    return 0;
}