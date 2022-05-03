#include "insert_box_into_box.h"
#include <cmath>
void insert_box_into_box(
  const BoundingBox & A,
  BoundingBox & B)
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  for(int i=0; i < 3; i++){
    B.min_corner(i) = std::fmin(A.min_corner(i), B.min_corner(i));
    B.max_corner(i) = std::fmax(A.max_corner(i), B.max_corner(i));
  }
  ////////////////////////////////////////////////////////////////////////////
}

