#include "Triangle.h"
#include "Ray.h"
#include <Eigen/Geometry>
#include <iostream>

bool Triangle::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  ////////////////////////////////////////////////////////////////////////////
  Eigen::Vector3d t0, t1, normal;
  t0 = std::get<2>(corners) - std::get<0>(corners);
  t1 = std::get<1>(corners) - std::get<0>(corners);

  Eigen::Matrix3d M;
  M.col(0) = t1;
  M.col(1) = t0;
  M.col(2) = - ray.direction;

  //Eigen::Vector3d x = M.colPivHouseholderQr().solve(ray.origin- std::get<0>(corners));
  Eigen::Vector3d x = M.householderQr().solve(ray.origin- std::get<0>(corners));

  normal = t1.cross(t0);
  double a = x[0];
  double b = x[1];
  t = x[2];
  if (t < min_t) return false;

  if((a >= 0) && (b >= 0) && (a + b <= 1)){
      n = normal.normalized();
      return true;
  }else return false;
}


