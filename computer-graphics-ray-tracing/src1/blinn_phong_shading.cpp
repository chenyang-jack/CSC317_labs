#include "blinn_phong_shading.h"
// Hint:
#include "first_hit.h"
#include <iostream>
#include <math.h>

Eigen::Vector3d blinn_phong_shading(
  const Ray & ray,
  const int & hit_id, 
  const double & t,
  const Eigen::Vector3d & n,
  const std::vector< std::shared_ptr<Object> > & objects,
  const std::vector<std::shared_ptr<Light> > & lights)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  ////////////////////////////////////////////////////////////////////////////
  // full blinn-phong-shading: ka + kd max(0,n.dot light) + ks max (0, cos theta n/h) ^ p


  // epsilon
  double epsilon = 1e-6;

  // ambient constant ? material also has a ka ?
  double ia = 0.1;
  Eigen::Vector3d colors;
  colors << 0.0, 0.0, 0.0;

  //for first_hit use;
  Eigen::Vector3d normal = n;

  // half-vector:
  auto maters = objects[hit_id]->material;
  // auto object_material = objects[hit_id]->material;
  for(auto const& light: lights){

      Eigen::Vector3d d_light;
      Eigen::Vector3d p = ray.origin + t * ray.direction + normal * epsilon;
      double max_t = 0;
      Eigen::Vector3d v = - ray.direction.normalized();
      //half-vector:
      double cos_n_h, n_l;

      light->direction(p,d_light,max_t);

      Eigen::Vector3d new_dir = d_light;
      Eigen::Vector3d new_src = ray.origin + t * ray.direction + normal * epsilon;

      auto new_ray = new Ray;
      new_ray->direction = new_dir;
      new_ray->origin = new_src;

      int id2 = -1;
      double temp_t2;
      Eigen::Vector3d normal2;
      double mint2 = 0;

      if (!(first_hit(*new_ray, mint2, objects, id2, temp_t2, normal2))||temp_t2 > max_t){
          Eigen::Vector3d half_vector = (v + d_light).normalized();

          cos_n_h = half_vector.dot(normal);
          n_l = normal.dot(d_light);

          colors += (light->I.array() * maters->ks.array()).matrix() * pow(std::max(0.0, cos_n_h), maters->phong_exponent);
          colors += (light->I.array() * maters->kd.array()).matrix() * std::max(0.0, n_l);
      }

  }
  colors += ia * maters->ka;


  return colors;

}
