#include "rotate.h"

void rotate(
  const std::vector<unsigned char> & input,
  const int width,
  const int height,
  const int num_channels,
  std::vector<unsigned char> & rotated)
{
  rotated.resize(height*width*num_channels);
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  for(int h = 0; h < height; h++){
    for(int w = 0; w < width; w++){
      int tw = h;
      int th = width - 1 - w;

      int pos = h * width * num_channels + w * num_channels;
      int tpos = th * height * num_channels + tw * num_channels;

      for (size_t i = 0; i < num_channels; i++)
      {
        rotated[tpos + i] = input[pos + i];
      }
    }
  }
  ////////////////////////////////////////////////////////////////////////////
}
