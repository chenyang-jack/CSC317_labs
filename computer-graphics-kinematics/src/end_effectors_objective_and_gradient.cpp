#include "end_effectors_objective_and_gradient.h"
#include "transformed_tips.h"
#include "kinematics_jacobian.h"
#include "copy_skeleton_at.h"
#include <iostream>
#include <algorithm>

void end_effectors_objective_and_gradient(
  const Skeleton & skeleton,
  const Eigen::VectorXi & b,
  const Eigen::VectorXd & xb0,
  std::function<double(const Eigen::VectorXd &)> & f,
  std::function<Eigen::VectorXd(const Eigen::VectorXd &)> & grad_f,
  std::function<void(Eigen::VectorXd &)> & proj_z)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code

  /* 
   * least-squares objective value 
   */
  f = [&](const Eigen::VectorXd & A)->double
  {
    // given a #bones list of Euler angles need to be set
    Skeleton cpySkel = copy_skeleton_at(skeleton, A);
    Eigen::VectorXd boneTips = transformed_tips(skeleton, b);

    // end-effector tip position xb0
    return (boneTips - xb0).squaredNorm();
  };


  /* 
   * least-squares objective gradient
   */
  grad_f = [&](const Eigen::VectorXd & A)->Eigen::VectorXd
  {
    Skeleton cpySkel = copy_skeleton_at(skeleton, A);
    Eigen::VectorXd EP = transformed_tips(skeleton,b);

    Eigen::MatrixXd J;
    kinematics_jacobian(cpySkel, b, J);

    Eigen::VectorXd dEdx = 2*(EP - xb0);

    return J.transpose() * dEdx;
  };


  /* 
   * projects a set of Euler angles onto input skeleton's joint angles
   */
  proj_z = [&](Eigen::VectorXd & A)
  {
    assert(skeleton.size()*3 == A.size());

    for (int skelIdx = 0; skelIdx < skeleton.size(); skelIdx++){
      
      for (int angleIdx = 0; angleIdx < 3; angleIdx++){
        
        // Bound the calculated angles with its min/max
        A[3*skelIdx + angleIdx] = 
              std::fmax(  
                skeleton[skelIdx].xzx_min[angleIdx],

                std::fmin(
                  A[3*skelIdx + angleIdx], 
                  
                  skeleton[skelIdx].xzx_max[angleIdx]
                )
              );
      }
    }
  };
  /////////////////////////////////////////////////////////////////////////////
}