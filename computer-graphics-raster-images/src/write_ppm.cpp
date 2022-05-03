#include "write_ppm.h"
#include <fstream>
#include <cassert>
#include <iostream>
#include <iomanip>

bool write_ppm(
  const std::string & filename,
  const std::vector<unsigned char> & data,
  const int width,
  const int height,
  const int num_channels)
{
  assert(
    (num_channels == 3 || num_channels ==1 ) &&
    ".ppm only supports RGB or grayscale images");
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  std::ofstream ppmFile (filename);
  if (ppmFile.is_open())
  {
    if(num_channels == 3)
      ppmFile << "P3\n";
    else
      ppmFile << "P2\n";
    ppmFile << (std::to_string(width) + " " + std::to_string(height) + "\n");
    ppmFile << "255\n";
    
    int counterL = 0, counterC = 0;
    for(int a : data) {
      ppmFile << std::setw(3) << a << " ";
      if(a < 0 || a > 255) std::cout << "Wrong";
      counterC++;
      if(counterC == num_channels){
        ppmFile << "\n";
        counterC = 0;
      }
    }
    ppmFile.close();
    return true;
  }
  return false;
  ////////////////////////////////////////////////////////////////////////////
}
