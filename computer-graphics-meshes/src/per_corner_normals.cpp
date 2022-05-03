#include "per_corner_normals.h"
#include "triangle_area_normal.h"
// Hint:
#include "vertex_triangle_adjacency.h"
#include <iostream>

void per_corner_normals(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const double corner_threshold,
  Eigen::MatrixXd & N)
{
  N = Eigen::MatrixXd::Zero(F.rows()*3,3);
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here:
  std::vector<std::vector<int>> VF;
  vertex_triangle_adjacency(F,V.rows(),VF);

  Eigen::RowVector3d a, b, c;
  for (int f = 0; f < F.rows(); f++)
  {
    a = V.row(F(f, 0));
    b = V.row(F(f, 1));
    c = V.row(F(f, 2));
    Eigen::Vector3d curFN = triangle_area_normal(a, b, c);

    for (int idx = 0; idx < 3; idx++)
    {
      Eigen::RowVector3d normalSum(0,0,0);
      std::vector<int> adjFL = VF[F(f,idx)]; // adj Face to this vertex (three vectex perface)
      for (int adjF : adjFL)
      {
        Eigen::RowVector3d adjFN(0,0,0);
        a = V.row(F(adjF, 0));
        b = V.row(F(adjF, 1));
        c = V.row(F(adjF, 2));
        adjFN = triangle_area_normal(a, b, c);
        
        if(adjFN.normalized().dot(curFN.normalized()) < cos((M_PI * corner_threshold) / 180)) continue;
        normalSum += adjFN;
      }
      // for corner F(i,j) is at N.row(i*3+j)
      N.row(f*3 + idx) = normalSum.normalized();
    }
  }
  ////////////////////////////////////////////////////////////////////////////
}
