#include "reflect.h"

void reflect(
  const std::vector<unsigned char> & input,
  const int width,
  const int height,
  const int num_channels,
  std::vector<unsigned char> & reflected)
{
  reflected.resize(width*height*num_channels);
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  for(int h = 0; h < height; h++){
    int head = h * width * num_channels;
    for(int w = 0; w < width; w++){

      for (int i = 0; i < num_channels; i++)
      {
        reflected[head + w * num_channels + i] = input[head + ((width-1)-w) * num_channels + i];
      }
    }
  }
  ////////////////////////////////////////////////////////////////////////////
}