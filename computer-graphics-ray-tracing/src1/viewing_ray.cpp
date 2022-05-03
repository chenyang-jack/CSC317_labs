#include "viewing_ray.h"
#include <vector>
#include <unordered_map>


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
  ////////////////////////////////////////////////////////////////////////////

  double u;
  double v;
  // u and v
//  u = camera.width * ((double)i + 0.5 ) / (double)width- camera.width / 2;
//  v = camera.height * ((double)j + 0.5 ) / (double)height- camera.height / 2;

  u = (camera.width * (j + 0.5 ) / width )- (camera.width / 2.0);
  v = (camera.height * (i + 0.5 ) / height) - (camera.height / 2.0);

  ray.origin = camera.e;
  ray.direction = u * camera.u - v * camera.v - camera.d * camera.w;

}

