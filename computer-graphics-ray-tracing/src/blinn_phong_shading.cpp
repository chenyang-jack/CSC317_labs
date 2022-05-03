#include "blinn_phong_shading.h"
// Hint:
#include "first_hit.h"
#include <iostream>

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
  
  Eigen::Vector3d rgb = Eigen::Vector3d(0,0,0);
  Eigen::Vector3d matOrigin = ray.origin+t*ray.direction;
  std::shared_ptr<Material> mat = objects[hit_id]->material;

  double epsilon = 0.001;

  // Ambient light
  rgb += mat->ka * 0.1;

  for(auto lt:lights){
    Eigen::Vector3d ltdir;
    double max_t;
    // output: unit light direction & distance
    lt->direction(matOrigin, ltdir, max_t);


    // Shadow
    // Check Any obj block this light, If true skip curr lt
    bool skipLt = false, wDist = false;
    double tempT; Eigen::Vector3d tempN;
    if(max_t != std::numeric_limits<double>::infinity())
      wDist = true;
    for(auto obj:objects){
      if(obj->intersect({matOrigin, ltdir}, epsilon, tempT, tempN)){
        if(tempT < max_t){
          skipLt = true;
          break;
        }
      } 
    }if(skipLt) continue;

    // Blinn-phong Shading Model
    // Diffuse reflection
    rgb += (mat->kd.array() * lt->I.array()).matrix() * fmax(0, ltdir.dot(n));

    // Specular light
    Eigen::Vector3d hlf = (ltdir - ray.direction/t).normalized();
    rgb += (mat->ks.array() * lt->I.array()).matrix() * pow(fmax(0, hlf.dot(n)), mat->phong_exponent);
  }

  return rgb;
  ////////////////////////////////////////////////////////////////////////////
}
