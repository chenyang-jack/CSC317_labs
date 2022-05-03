#include "linear_blend_skinning.h"

void linear_blend_skinning(
  const Eigen::MatrixXd & V,
  const Skeleton & skeleton,
  const std::vector<Eigen::Affine3d,Eigen::aligned_allocator<Eigen::Affine3d> > & T,
  const Eigen::MatrixXd & W,
  Eigen::MatrixXd & U)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
  U = Eigen::MatrixXd::Zero(V.rows(), 3);

  // loop throught all vertices
  for(int vidx = 0; vidx < V.rows(); vidx++){

    // expand to Homogeneous coord
    // Eigen::Vector4d vertex(V(vidx,0),V(vidx,1),V(vidx,2), 1);
    
    Eigen::Vector4d vertex(V(vidx, 0), V(vidx, 1), V(vidx, 2), 1);
    Eigen::Vector4d res(0,0,0,0);
    // loop through and find weighted bone that effect cur vertex
    // weightIndex == -1 determines that no skin are related to this bone
    // non_related bone's weight are set to 0 in Matrix W
    for(int bidx = 0; bidx < skeleton.size(); bidx++){
      if(skeleton[bidx].weight_index == -1) continue;

      // Transpose local vertex to world then weighted
      res += W(vidx, skeleton[bidx].weight_index) * (T[bidx] * vertex);
    }

    U.row(vidx) = res.head<3>();
  }
  /////////////////////////////////////////////////////////////////////////////
}
