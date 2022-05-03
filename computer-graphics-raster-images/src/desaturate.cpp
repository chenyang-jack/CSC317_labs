#include "desaturate.h"
#include "hsv_to_rgb.h"
#include "rgb_to_hsv.h"

void desaturate(
  const std::vector<unsigned char> & rgb,
  const int width,
  const int height,
  const double factor,
  std::vector<unsigned char> & desaturated)
{
  desaturated.resize(rgb.size());
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
      
      s*=(1-factor);

      hsv_to_rgb(h, s, v, r, g, b);
      desaturated[idx] = r * 256;
      desaturated[idx+1] = g * 256;
      desaturated[idx+2] = b * 256;
    }
  }
  ////////////////////////////////////////////////////////////////////////////
}
