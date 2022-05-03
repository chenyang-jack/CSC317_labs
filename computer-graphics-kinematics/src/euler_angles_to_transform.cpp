#include "euler_angles_to_transform.h"

Eigen::Affine3d euler_angles_to_transform(
  const Eigen::Vector3d & xzx)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code

  double r1 = xzx[2] * M_PI / 180;
  double r2 = xzx[1] * M_PI / 180;
  double r3 = xzx[0] * M_PI / 180;


  Eigen::Affine3d A;
    A.matrix() << 
    cos(r2),            -cos(r3)*sin(r2),                          sin(r2)*sin(r3),                           0,
    cos(r1)*sin(r2),    cos(r1)*cos(r2)*cos(r3)-sin(r1)*sin(r3),   -cos(r3)*sin(r1)-cos(r1)*cos(r2)*sin(r3),  0,
    sin(r1)*sin(r2),    cos(r1)*sin(r3)+cos(r2)*cos(r3)*sin(r1),   cos(r1)*cos(r3)-cos(r2)*sin(r1)*sin(r3),   0,
    0,                  0,                                          0,                                        1;
  return A;
  /////////////////////////////////////////////////////////////////////////////
}
