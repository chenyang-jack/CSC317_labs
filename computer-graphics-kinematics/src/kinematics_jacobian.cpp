#include "kinematics_jacobian.h"
#include "transformed_tips.h"
#include <iostream>

void kinematics_jacobian(
  const Skeleton & skeleton,
  const Eigen::VectorXi & b,
  Eigen::MatrixXd & J)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code

  // Each cell is the change in skeleton bone[j](one euler angle),
  // cause a change in different Endpoint[i](one euler angle).

  // Loop through skeleton and calculate "change in specific bone angle" will cause 
  // how Endpoint deform in, 
  // formula J[i,j,k] = { X(alpha + change in skel[j].angle[k]) - X(alpha) } / change delta

  // -------- all bones in skeleton[j]
  // |                            bone0(x1 z x2)            bone1(x1 z x2)          ..........
  // |            EP0(x1          [detx1] [detz] [detx2]    [detx1] [detz] [detx2]
  // end              z           [detx1] [detz] [detx2]    [detx1] [detz] [detx2]
  // point            x2)         [detx1] [detz] [detx2]    [detx1] [detz] [detx2]
  // to           :
  // consid       :
  // [i]          :   

  J = Eigen::MatrixXd::Zero(b.size()*3,skeleton.size()*3);
  
  // Delta
  double h = 1e-7;
  
  // X(alpha)
  Eigen::VectorXd destEP = transformed_tips(skeleton, b);

  // DeltaEndPoint
  Eigen::VectorXd changedEP;

  //Loop through all skeleton
  for(int skelIdx = 0; skelIdx < skeleton.size(); skelIdx++){
    
    //Loop through three euler angle in specific skeleton bone
    for (int angleIdx = 0; angleIdx < 3; angleIdx++){
      
      // set the aphla with change
      Skeleton deltaSlel = skeleton;
      deltaSlel[skelIdx].xzx[angleIdx] += h;

      // Get the changed End point position
      changedEP = transformed_tips(deltaSlel, b);

      // Store into J
      J.col(skelIdx * 3 + angleIdx) << ( (changedEP - destEP)/h );
    }
  }
  /////////////////////////////////////////////////////////////////////////////
}
