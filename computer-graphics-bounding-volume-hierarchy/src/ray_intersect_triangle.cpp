#include "ray_intersect_triangle.h"
#include <Eigen/Geometry>
bool ray_intersect_triangle(
  const Ray & ray,
  const Eigen::RowVector3d & A,
  const Eigen::RowVector3d & B,
  const Eigen::RowVector3d & C,
  const double min_t,
  const double max_t,
  double & t)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  Eigen::RowVector3d e1 = B - A;
  Eigen::RowVector3d e2 = C - A;
  Eigen::RowVector3d s = ray.origin.transpose() - A;

  Eigen::RowVector3d s1 = ray.direction.transpose().cross(e2);
  Eigen::RowVector3d s2 = s.transpose().cross(e1);

  double det = s1.dot(e1);
  double tempT = s2.dot(e2)/det;
  double b1 = s1.dot(s)/det;
  double b2 = s2.dot(ray.direction)/det;

  if(tempT < max_t && tempT > min_t && b1 >= 0 && b2 >= 0 && (b1+b2) <= 1){
    t = tempT;
    return true;
  }
  return false;
  ////////////////////////////////////////////////////////////////////////////
}

