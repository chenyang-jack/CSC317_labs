#include "vertex_triangle_adjacency.h"

void vertex_triangle_adjacency(
  const Eigen::MatrixXi & F,
  const int num_vertices,
  std::vector<std::vector<int> > & VF)
{
  VF.resize(num_vertices);
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here:
  for (int v = 0; v < num_vertices; v++){
    for (int f = 0; f < F.rows(); f++){
      for (int i = 0; i < F.cols(); i++){
        if(F(f,i) == v){
          VF[v].push_back(f);
        }
      }
    }
  }
  ////////////////////////////////////////////////////////////////////////////
}

