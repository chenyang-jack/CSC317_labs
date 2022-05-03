#include "PointLight.h"
#include <Eigen/Eigen>

void PointLight::direction(
  const Eigen::Vector3d & q, Eigen::Vector3d & d, double & max_t) const
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here:
  ////////////////////////////////////////////////////////////////////////////

  d = (this->p - q).normalized();
  // not sure about the max_t here
  max_t = (this->p - q).norm();
}
