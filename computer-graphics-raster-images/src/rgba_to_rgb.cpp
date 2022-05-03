#include "rgba_to_rgb.h"

void rgba_to_rgb(
  const std::vector<unsigned char> & rgba,
  const int & width,
  const int & height,
  std::vector<unsigned char> & rgb)
{
  rgb.resize(height*width*3);
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  for(int i = 0, index = 0; i < rgba.size(); i++){
    if(i%4 == 3) continue;
    else rgb[index] = rgba[i];
    index++;
  }
  ////////////////////////////////////////////////////////////////////////////
}
