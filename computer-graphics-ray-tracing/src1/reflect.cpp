#include <Eigen/Core>
#include <iostream>

Eigen::Vector3d reflect(const Eigen::Vector3d & in, const Eigen::Vector3d & n)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  ////////////////////////////////////////////////////////////////////////////
  Eigen::Vector3d out_ray;

  Eigen::Matrix3d Id;
  Id.setIdentity();
  Eigen::Matrix3d Mat =  2 * n * n.transpose() ;

  out_ray = (Id - Mat) * (in);
  out_ray.normalize();
  return out_ray;
}
