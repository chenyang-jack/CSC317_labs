#include "viewing_ray.h"
#include <Eigen/Geometry>

#include <iostream>
using namespace std;

void viewing_ray(
  const Camera & camera,
  const int i,
  const int j,
  const int width,
  const int height,
  Ray & ray)
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  double uShift = (width/2 - (double)j + 0.5)/width * camera.width;
  double vShift = (height/2 - (double)i + 0.5)/height * camera.height;

  ray.origin = camera.e;
  ray.direction = -camera.w*camera.d - uShift * camera.u + vShift * camera.v;
  ////////////////////////////////////////////////////////////////////////////
}

