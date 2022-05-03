#include "triangle_triangle_intersection.h"

#include "ray_intersect_triangle.h"
#include <cmath>

bool triangle_triangle_intersection(
  const Eigen::RowVector3d & A0,
  const Eigen::RowVector3d & A1,
  const Eigen::RowVector3d & A2,
  const Eigen::RowVector3d & B0,
  const Eigen::RowVector3d & B1,
  const Eigen::RowVector3d & B2)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  double t;
  Eigen::RowVector3d dir = A1 - A0;
  if(ray_intersect_triangle({A0, dir}, B0, B1, B2, 0, dir.norm(), t)) return true;
  dir = A2 - A0;
  if(ray_intersect_triangle({A0, dir}, B0, B1, B2, 0, dir.norm(), t)) return true;
  dir = A2 - A1;
  if(ray_intersect_triangle({A1, dir}, B0, B1, B2, 0, dir.norm(), t)) return true;
  dir = B1 - B0;
  if(ray_intersect_triangle({B0, dir}, A0, A1, A2, 0, dir.norm(), t)) return true;
  dir = B2 - B0;
  if(ray_intersect_triangle({B0, dir}, A0, A1, A2, 0, dir.norm(), t)) return true;
  dir = B2 - B1;
  if(ray_intersect_triangle({B1, dir}, A0, A1, A2, 0, dir.norm(), t)) return true;
  return false; 
  ////////////////////////////////////////////////////////////////////////////
}
// http://web.stanford.edu/class/cs277/resources/papers/Moller1997b.pdf
// // Alpha Plane
//   Eigen::Vector3d alphaNorm = (A1 - A0).cross(A2 - A1).transpose();
//   double aplhaDis = - alphaNorm.dot(A0.transpose());

//   Eigen::Vector3d betaRD;
//   betaRD(0) = alphaNorm.dot(B0.transpose()) + aplhaDis;
//   betaRD(1) = alphaNorm.dot(B1.transpose()) + aplhaDis;
//   betaRD(2) = alphaNorm.dot(B2.transpose()) + aplhaDis;
  
//   if(betaRD(0) == 0 && betaRD(1) == 0 && betaRD(2) == 0){
//     // Exception when two triangle on same plane
//   }

//   if((betaRD(0) < 0 && betaRD(1) < 0 && betaRD(2) < 0)
//     ||(betaRD(0) > 0 && betaRD(1) > 0 && betaRD(2) > 0))
//     return false;
  
//   // Beta Plane
//   Eigen::Vector3d betaNorm = (B1 - B0).cross(B2 - B1).transpose();
//   double betaDis = - betaNorm.dot(B0.transpose());

//   Eigen::Vector3d alphaRD;
//   alphaRD(0) = betaNorm.dot(A0.transpose()) + betaDis;
//   alphaRD(1) = betaNorm.dot(A1.transpose()) + betaDis;
//   alphaRD(2) = betaNorm.dot(A2.transpose()) + betaDis;

//   if((alphaRD(0) < 0 && alphaRD(1) < 0 && alphaRD(2) < 0)
//     ||(alphaRD(0) > 0 && alphaRD(1) > 0 && alphaRD(2) > 0))
//     return false;

//   // Projection Line
//   Eigen::Vector3d D = alphaNorm.cross(betaNorm);
//   Eigen::Vector3d alphaP, betaP;
//   alphaP(0) = D.dot(A0.transpose());
//   alphaP(1) = D.dot(A1.transpose());
//   alphaP(2) = D.dot(A2.transpose());
//   betaP(0) = D.dot(B0.transpose());
//   betaP(1) = D.dot(B1.transpose());
//   betaP(2) = D.dot(B2.transpose());

//   // x1 * x2 if neg not same sign, if pos same sign
//   // --- exclude
//   // --+
//   // -+-
//   // -++
//   // +--
//   // +-+
//   // ++-
//   // +++ exclude

//   int alphaMark = -1;
//   for (int i = 0; i < 3; i++){
    
//   }