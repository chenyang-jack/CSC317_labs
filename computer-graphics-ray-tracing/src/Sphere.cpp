#include "Sphere.h"
#include "Ray.h"

bool Sphere::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  // center, radius, ray.origin, ray.direction

  Eigen::Vector3d o_c = ray.origin - center; 

  double a = ray.direction.dot(ray.direction);
  double b = 2 * (ray.direction).dot(o_c);
  double c = o_c.dot(o_c) - radius * radius;

  double sqrtTemp = b * b - 4 * a * c;
  if(sqrtTemp < 0) return false;
  double t1 = (-b + sqrt(sqrtTemp))/(2*a);
  double t2 = (-b - sqrt(sqrtTemp))/(2*a);


  if(t1 < min_t && t2 >= min_t) t = t2;
  else if(t1 >= min_t && t2 < min_t) t = t1;
  else{
    t = std::fmin(t1, t2);
    if(t < min_t) return false;
  }
  n = ((ray.origin + (t * ray.direction)) - center).normalized();
  return true;
  ////////////////////////////////////////////////////////////////////////////
}
