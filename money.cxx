#include <cmath>
#include <sstream>
#include "money.h"

std::string to_string(usd ll) {
    double re = (1.0 / pow(10, 6)) * ll;
    std::stringstream ss;
    ss.precision(2);
    ss.setf(std::ios_base::fixed);
    ss << "$" << re;
    return ss.str();
}

