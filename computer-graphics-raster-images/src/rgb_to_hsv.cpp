#include "rgb_to_hsv.h"
#include <cmath>

void rgb_to_hsv(
    const double r,
    const double g,
    const double b,
    double& h,
    double& s,
    double& v)
{
    ////////////////////////////////////////////////////////////////////////////
    // Replace with your code here:
    // Cite Formula: https://www.rapidtables.com/convert/color/rgb-to-hsv.html
    double cmax = std::fmax(std::fmax(r, g), b);
    double cmin = std::fmin(std::fmin(r, g), b);
    
    double delta = cmax - cmin;

    if (cmax == r) {
        h = (g - b)/delta;
    }
    else if (cmax == g) {
        h = (b - r)/delta + 2;
    }
    else if (cmax == b) {
        h = (r - g)/delta + 4;
    }
    else if (delta == 0){
        exit(0);
    }
    if(h > 6) h = std::fmod(h, 6);
    if(h < 0) h = std::fmod(h, 6) + 6;
    h *= 60;
    
    v = cmax;

    if (cmax == 0) s = 0;
    else s = delta/cmax;
    ////////////////////////////////////////////////////////////////////////////
}