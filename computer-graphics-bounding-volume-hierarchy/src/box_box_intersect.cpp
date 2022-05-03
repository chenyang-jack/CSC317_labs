#include "box_box_intersect.h"

bool isOverlapping(double minA, double maxA, double minB, double maxB){
  if(minB <= maxA && minA <= maxB) return true;
  else return false;
}

bool box_box_intersect(
  const BoundingBox & A,
  const BoundingBox & B)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  bool val = isOverlapping(A.min_corner(0), A.max_corner(0), B.min_corner(0), B.max_corner(0)) &
             isOverlapping(A.min_corner(1), A.max_corner(1), B.min_corner(1), B.max_corner(1)) &
             isOverlapping(A.min_corner(2), A.max_corner(2), B.min_corner(2), B.max_corner(2));
  return val;
  ////////////////////////////////////////////////////////////////////////////
}

