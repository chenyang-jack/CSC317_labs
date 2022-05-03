#include "Plane.h"
#include "Ray.h"
#include <iostream>
bool Plane::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  t = (point - ray.origin).dot(normal) / ray.direction.dot(normal);
  if(t < min_t) return false;
  n = normal;
  return true;
  ////////////////////////////////////////////////////////////////////////////
}
