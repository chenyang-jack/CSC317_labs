#include "hue_shift.h"
#include "hsv_to_rgb.h"
#include "rgb_to_hsv.h"
#include <cmath>
#include <iostream>

void hue_shift(
  const std::vector<unsigned char> & rgb,
  const int width,
  const int height,
  const double shift,
  std::vector<unsigned char> & shifted)
{
  shifted.resize(rgb.size());
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  double h, s ,v;
  double r, g, b;

  for(int hei = 0; hei < height; hei++){
    for(int w = 0; w < width; w++){
      h = 0; s = 0; v = 0; r = 0; g = 0; b = 0;
      int idx = hei*width*3 + w*3;

      rgb_to_hsv(((double)rgb[idx]/256), 
                  ((double)rgb[idx+1]/256), 
                  ((double)rgb[idx+2]/256), 
                  h, s, v);
      
      h+=shift;
      if(h > 360) h = std::fmod(h, 360);
      if(h < 0) h = std::fmod(h, 360) + 360;

      hsv_to_rgb(h, s, v, r, g, b);
      shifted[idx] = r * 256;
      shifted[idx+1] = g * 256;
      shifted[idx+2] = b * 256;
    }
  }
  ////////////////////////////////////////////////////////////////////////////
}
