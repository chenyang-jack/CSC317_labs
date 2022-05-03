#include "sphere.h"
#include <iostream>
#include <math.h>

void sphere(
  const int num_faces_u,
  const int num_faces_v,
  Eigen::MatrixXd & V,
  Eigen::MatrixXi & F,
  Eigen::MatrixXd & UV,
  Eigen::MatrixXi & UF,
  Eigen::MatrixXd & NV,
  Eigen::MatrixXi & NF)
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here:
  // https://en.wikipedia.org/wiki/Spherical_coordinate_system
  int totalNumF = num_faces_u * num_faces_v;
  int totalNumV = (num_faces_u+1) * (num_faces_v+1);

  V.resize(totalNumV, 3);
  NV.resize(totalNumV, 3);
  UV.resize(totalNumV, 2);

  F.resize(totalNumF, 4);
  UF.resize(totalNumF, 4);
  NF.resize(totalNumF, 4);

  // Vertices
  for (int curU = 0; curU <= num_faces_u; curU++){
    for (int curV = 0; curV <= num_faces_v; curV++){
      double u = (double)curU/num_faces_u;
      double v = (double)curV/num_faces_v;

      double theta = u * M_PI;
      double gamma = v * 2 * M_PI;

      double x = cos(gamma) * sin(theta);
      double y = sin(gamma) * sin(theta);
      double z = cos(theta);

      int curR = curU * (num_faces_v+1) + curV;
      V.row(curR) = Eigen::RowVector3d(x, y, z);
      NV.row(curR) = Eigen::RowVector3d(x, y, z);
      UV.row(curR) = Eigen::RowVector2d(v, u);
    }
  }
  //Faces
  for (int curU = 0; curU < num_faces_u; curU++){
    for (int curV = 0; curV < num_faces_v; curV++){
      int a = curU * (num_faces_v+1) + curV;
      int b = (curU + 1) * (num_faces_v+1) + curV;
      int c = b + 1;
      int d = a + 1;

      int curR = curU * num_faces_v + curV;
      F.row(curR) = Eigen::RowVector4i(a, b, c, d);
      UF.row(curR) = Eigen::RowVector4i(a, b, c, d);
      NF.row(curR) = Eigen::RowVector4i(a, b, c, d);
    }
  }
  ////////////////////////////////////////////////////////////////////////////
}
