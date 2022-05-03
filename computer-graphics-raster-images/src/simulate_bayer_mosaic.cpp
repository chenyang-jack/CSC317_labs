#include "simulate_bayer_mosaic.h"
void simulate_bayer_mosaic(
  const std::vector<unsigned char> & rgb,
  const int & width,
  const int & height,
  std::vector<unsigned char> & bayer)
{
  bayer.resize(width*height);
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  bool isGreen = true, isBlue = true;
  for(int h = 0; h < height; h++){
    if(h%2 == 0){
      isGreen = true;
      isBlue = true;
    }else{
      isGreen = false;
      isBlue = false;
    }
    for(int w = 0; w < width; w++){
      int idx = h*width*3 + w*3;

      if(isGreen){
        bayer[h*width + w] = rgb[idx+1];
        isGreen = false;
        continue;
      }
      isGreen = true;
      if(isBlue) {
        bayer[h*width + w] = rgb[idx+2];
      }else{
        bayer[h*width + w] = rgb[idx];
      }
    }
  }
  ////////////////////////////////////////////////////////////////////////////
}
