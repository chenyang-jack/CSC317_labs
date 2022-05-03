#include "over.h"
#include <iostream>
#include <cmath>
void over(
  const std::vector<unsigned char> & A,
  const std::vector<unsigned char> & B,
  const int & width,
  const int & height,
  std::vector<unsigned char> & C)
{
  C.resize(A.size());
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  // Alpha Value [0, 255] DO CONVERSTION
  int idx;
  double alphaA, alphaB;
  for(int h = 0; h < height; h++){
    for(int w = 0; w < width; w++){
      idx = h*width*4 + w*4;

      alphaA = (double)A[idx+3]/255;
      alphaB = (double)B[idx+3]/255;

      double aplhaOvr = alphaA + alphaB * (1 - alphaA);
      C[idx] = std::round((A[idx] * alphaA + B[idx] * alphaB * (1-alphaA)) / aplhaOvr);
      C[idx+1] = std::round((A[idx+1] * alphaA + B[idx+1] * alphaB * (1-alphaA)) / aplhaOvr);
      C[idx+2] = std::round((A[idx+2] * alphaA + B[idx+2] * alphaB * (1-alphaA)) / aplhaOvr);
      C[idx+3] = std::round(aplhaOvr * 255);
    }
  }
  ////////////////////////////////////////////////////////////////////////////
}
