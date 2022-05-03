#include "forward_kinematics.h"
#include "euler_angles_to_transform.h"
#include <functional> // std::function

std::vector<int> bcalculated;

void spaghetti_transform(
  int idx,
  const Skeleton & skeleton,
  std::vector<Eigen::Affine3d,Eigen::aligned_allocator<Eigen::Affine3d> > & T)
{
  // parent's affine3d transformation already pre-calculated & stored in T
  if(bcalculated[idx] == 1) return;

  // root of the spaghetti tree
  if(skeleton[idx].parent_index == -1){
    T[idx] = Eigen::Affine3d::Identity();
    return;
  }

  spaghetti_transform(skeleton[idx].parent_index, skeleton, T);

  // forward transformation including parent's transformation
  T[idx] = T[skeleton[idx].parent_index] 
          * skeleton[idx].rest_T 
          * euler_angles_to_transform(skeleton[idx].xzx)
          * skeleton[idx].rest_T.inverse();
  
  bcalculated[idx] = 1;
}


void forward_kinematics(
  const Skeleton & skeleton,
  std::vector<Eigen::Affine3d,Eigen::aligned_allocator<Eigen::Affine3d> > & T)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
  T.resize(skeleton.size(),Eigen::Affine3d::Identity());

  bcalculated.resize(skeleton.size(), 0);

  for(int i = 0; i < skeleton.size(); i++){
    spaghetti_transform(i, skeleton, T);
  }

  bcalculated.clear();
  /////////////////////////////////////////////////////////////////////////////
}
