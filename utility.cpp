#include "utility.h"

int string_to_int(const string& s){
   istringstream instr(s);
   int n;
   instr >> n;
   return n;
}

bool isNumber(const string& str)
{
    for (char const &c : str) {
        if (std::isdigit(c) == 0) return false;
    }
    return !str.empty();
}