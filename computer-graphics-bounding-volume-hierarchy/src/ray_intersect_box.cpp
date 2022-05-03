#include "ray_intersect_box.h"
#include <iostream>
#include <limits>
#include <algorithm>
#include <math.h>

bool ray_intersect_box(
  const Ray & ray,
  const BoundingBox& box,
  const double min_t,
  const double max_t)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  // https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-box-intersection
  // https://zhuanlan.zhihu.com/p/231201961
  
  double txmin = -std::numeric_limits<double>::infinity(), txmax = std::numeric_limits<double>::infinity();
  double tymin = -std::numeric_limits<double>::infinity(), tymax = std::numeric_limits<double>::infinity();
  double tzmin = -std::numeric_limits<double>::infinity(), tzmax = std::numeric_limits<double>::infinity();
  
  if(ray.direction(0) != 0.f){
    txmin = (box.min_corner(0) - ray.origin(0)) / ray.direction(0);
    txmax = (box.max_corner(0) - ray.origin(0)) / ray.direction(0);
    if(ray.direction(0) < 0.f)
      std::swap(txmax, txmin);
  }else{
    if(ray.origin(0) < box.min_corner(0) || ray.origin(0) > box.max_corner(0))
      return false;
  }
  
  if(ray.direction(1) != 0.f){
    tymin = (box.min_corner(1) - ray.origin(1)) / ray.direction(1);
    tymax = (box.max_corner(1) - ray.origin(1)) / ray.direction(1);
    if(ray.direction(1) < 0.f)
      std::swap(tymax, tymin);
  }else{
    if(ray.origin(1) < box.min_corner(1) || ray.origin(1) > box.max_corner(1))
      return false;
  }

  if(ray.direction(2) != 0.f){
    tzmin = (box.min_corner(2) - ray.origin(2)) / ray.direction(2);
    tzmax = (box.max_corner(2) - ray.origin(2)) / ray.direction(2);
    if(ray.direction(2) < 0.f)
      std::swap(tzmax, tzmin);  
  }else{
    if(ray.origin(2) < box.min_corner(2) || ray.origin(2) > box.max_corner(2))
      return false;
  }

  double tenter = std::fmax(txmin, std::fmax(tymin, tzmin));
  double texit = std::fmax(txmin, std::fmax(tymin, tzmin));

  if(tenter < texit && tenter <= max_t && texit >= min_t)
    return true;

  return false;
  ////////////////////////////////////////////////////////////////////////////
}
