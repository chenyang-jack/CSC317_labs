#include "Plane.h"
#include "Ray.h"
#include <iostream>
bool Plane::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  ////////////////////////////////////////////////////////////////////////////
  double num = ray.direction.dot(normal);

  if (num == 0) return false;
  double temp = normal.dot(point) - normal.dot(ray.origin);
  t = temp / num;
  if (t >= min_t){
  n = normal.normalized();
  return true;
  }
  else return false;
}

