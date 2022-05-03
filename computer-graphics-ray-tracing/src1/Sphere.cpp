#include "Sphere.h"
#include "Ray.h"

bool Sphere::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  ////////////////////////////////////////////////////////////////////////////
  double a;
  double b;
  double c;
  Eigen::Vector3d vec = ray.origin - center;

  Eigen::Vector3d point;

  //a = (ray.direction - vec).dot(ray.direction - vec);
  a = ray.direction.dot(ray.direction);
  b = 2 *vec.dot(ray.direction);
  c = vec.dot(vec) - radius * radius;
  double temp = b * b - 4 * a * c;

  if (temp < 0 ) return false;
  double t1 = (-b + sqrt(temp)) / (2 * a);
  double t2 = (-b - sqrt(temp)) / (2 * a);

  if (t2 >= min_t){
      t = t2;
      point = ray.origin + t * ray.direction;
      Eigen::Vector3d temp = point - center;
      n = temp.normalized();
      return true;
  }else if (t1 >= min_t){
      t = t1;
      point = ray.origin + t * ray.direction;
      Eigen::Vector3d temp = point - center;
      n = temp.normalized();
      return true;
  }else return false;
}

