#include "transformed_tips.h"
#include "forward_kinematics.h"

Eigen::VectorXd transformed_tips(
  const Skeleton & skeleton, 
  const Eigen::VectorXi & b)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
  Eigen::VectorXd boneTipRes(3*b.size());

  std::vector<Eigen::Affine3d,Eigen::aligned_allocator<Eigen::Affine3d> > T;
  forward_kinematics(skeleton, T);

  Eigen::Vector4d tipPos; 

  for(int i=0; i < b.size(); i++){
    tipPos = Eigen::Vector4d(skeleton[b[i]].length, 0, 0, 1);

    tipPos = T[b[i]] * skeleton[b[i]].rest_T * tipPos;

    boneTipRes[3*i] = tipPos[0];
    boneTipRes[3*i+1] = tipPos[1];
    boneTipRes[3*i+2] = tipPos[2];
  }

  return boneTipRes;
  /////////////////////////////////////////////////////////////////////////////
}
