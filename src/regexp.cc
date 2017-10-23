#include "regexp.h"

#include <emscripten.h>

using std::string;

Regexp::Regexp(const string& str) {
    UChar *c_str = (UChar*)str.c_str();
    UChar *pattern_end = c_str + onigenc_str_bytelen_null(ONIG_ENCODING_UTF8, c_str);
    int status = onig_new(&regex_, (UChar*)c_str, pattern_end, ONIG_OPTION_CAPTURE_GROUP, ONIG_ENCODING_UTF8, ONIG_SYNTAX_DEFAULT, NULL);
    if (status != ONIG_NORMAL) {
        EM_ASM(throw 'unable to build regexp');
        return;
    }
}

Regexp::~Regexp() {
    if (regex_ != NULL) {
        onig_free(regex_);
    }
}