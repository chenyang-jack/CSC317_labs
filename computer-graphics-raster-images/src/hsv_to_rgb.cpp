#include "hsv_to_rgb.h"
#include <cmath>
#include <iostream>

void hsv_to_rgb(
    const double h, 
    const double s, 
    const double v,
    double& r,
    double& g,
    double& b)
{
    ////////////////////////////////////////////////////////////////////////////
    // Replace with your code here:
    // Cite Formula: https://cs.stackexchange.com/questions/64549/convert-hsv-to-rgb-colors
    double c = v * s;

    double tempH = h / 60;
    double x = c * (1 - std::fabs(std::fmod(tempH, 2) - 1));

    if (0 <= tempH && tempH < 1) {
        r = c; g = x; b = 0;
    }
    else if (1 <= tempH && tempH < 2) {
        r = x; g = c; b = 0;
    }
    else if (2 <= tempH && tempH < 3) {
        r = 0; g = c; b = x;
    }
    else if (3 <= tempH && tempH < 4) {
        r = 0; g = x; b = c;
    }
    else if (4 <= tempH && tempH < 5) {
        r = x; g = 0; b = c;
    }
    else if (5 <= tempH && tempH < 6) {
        r = c; g = 0; b = x;
    }
    else {
        r = 0; g = 0; b = 0;
    }

    double m = v - c;
    r += m;
    g += m;
    b += m;
    ////////////////////////////////////////////////////////////////////////////
}