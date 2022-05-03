#include "raycolor.h"
#include "first_hit.h"
#include "blinn_phong_shading.h"
#include "reflect.h"

#define REFNUM 10

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
  rgb = Eigen::Vector3d(0,0,0);
  
  // calculate the first hit object
  int hit_id;
  double t;
  Eigen::Vector3d n;
  if(!first_hit(ray, min_t, objects, hit_id, t, n)) return false;


  // Calculate blinn-phong shading at hit point
  rgb = blinn_phong_shading(ray, hit_id, t, n, objects, lights);


  // Reflectance Model
  double epsilon = 0.001;
  // Reflectance recursion count, SET macro REFNUM to Enable
  if(num_recursive_calls < REFNUM){
    Eigen::Vector3d refRGB = Eigen::Vector3d(0,0,0);
    if(
    raycolor({ray.origin + ray.direction * t, reflect(ray.direction*t, n)},
              epsilon,
              objects,
              lights,
              num_recursive_calls-1,
              refRGB)
    ){
      rgb += (objects[hit_id]->material->km.array() 
            * refRGB.array()).matrix();
    }
  }

  for (int i = 0; i < 3; i++){
    if(rgb[i] > 1) rgb[i] = 1;
    if(rgb[i] < 0) rgb[i] = 0;
  }
  

  return true;
  ////////////////////////////////////////////////////////////////////////////
}
