#include "point_box_squared_distance.h"
#include <cmath>
double point_box_squared_distance(
  const Eigen::RowVector3d & query,
  const BoundingBox & box)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here
  double x = std::max({0.0, query(0) - box.max_corner(0), box.min_corner(0) - query(0)});
  double y = std::max({0.0, query(1) - box.max_corner(1), box.min_corner(1) - query(1)});
  double z = std::max({0.0, query(2) - box.max_corner(2), box.min_corner(2) - query(2)});
  return x*x + y*y + z*z;
  ////////////////////////////////////////////////////////////////////////////
}
