#include "raycolor.h"
#include "first_hit.h"
#include "blinn_phong_shading.h"
#include "reflect.h"
#include <math.h>

bool raycolor(
  const Ray & ray, 
  const double min_t,
  const std::vector< std::shared_ptr<Object> > & objects,
  const std::vector< std::shared_ptr<Light> > & lights,
  const int num_recursive_calls,
  Eigen::Vector3d & rgb)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  ////////////////////////////////////////////////////////////////////////////
  if (num_recursive_calls > 10) return false;

  // epsilon
  double epsilon = 1e-6;

  // for first_hit use
  int hit_id;
  double min_reflect_t = 0;
  double t;
  Eigen::Vector3d n, new_color;

  bool fh = first_hit(ray,min_t,objects,hit_id, t, n);

  if (fh){
      rgb = blinn_phong_shading(ray, hit_id, t, n, objects, lights);

      Ray new_ray;
      new_ray.direction = reflect(ray.direction, n);
      new_ray.origin = ray.origin + t * ray.direction + epsilon * n;

      if(raycolor(new_ray, min_reflect_t, objects, lights, num_recursive_calls + 1, new_color)){
          rgb += (objects[hit_id]->material->km.array() * new_color.array()).matrix();
      }
  }
  return fh;

}
