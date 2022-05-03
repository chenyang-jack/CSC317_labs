#include "Triangle.h"
#include "Ray.h"

bool Triangle::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  // GAMES101 Ray Tracing 01 (00:49::51): https://www.bilibili.com/video/BV1X7411F744?p=13 
  Eigen::Vector3d p0, p1, p2;
  std::tie(p0, p1, p2) = corners;

  Eigen::Vector3d e1 = p1 - p0;
  Eigen::Vector3d e2 = p2 - p0;
  Eigen::Vector3d s = ray.origin - p0;
  Eigen::Vector3d s1 = ray.direction.cross(e2);
  Eigen::Vector3d s2 = s.cross(e1);

  double det = s1.dot(e1);
  double tempT = s2.dot(e2)/det;
  double b1 = s1.dot(s)/det;
  double b2 = s2.dot(ray.direction)/det;

  if(tempT > min_t && b1 >= 0 && b2 >= 0 && (b1+b2) <= 1){
    t = tempT;
    n = e1.cross(e2).normalized();
    return true;
  }
  return false;
  ////////////////////////////////////////////////////////////////////////////
}


