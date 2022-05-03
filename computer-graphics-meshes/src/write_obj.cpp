#include "write_obj.h"
#include <fstream>
#include <cassert>

#include <iostream>
using namespace std;

bool write_obj(
  const std::string & filename,
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const Eigen::MatrixXd & UV,
  const Eigen::MatrixXi & UF,
  const Eigen::MatrixXd & NV,
  const Eigen::MatrixXi & NF)
{
  assert((F.size() == 0 || F.cols() == 3 || F.cols() == 4) && "F must have 3 or 4 columns");
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here:
  std::ofstream objFile (filename);
  if (!objFile.is_open()) return false;

  //Point in 3D Space
  int row = V.rows();
  for (int r = 0; r < row; r++){
    objFile << "v " << V.row(r) << "\n";
  }objFile << "\n\n";

  // Texture mapping
  row = UV.rows();
  for (int c = 0; c < row; c++){
    objFile << "vt " << UV.row(c) << "\n";
  }objFile << "\n\n";

  // Normal vec
  row = NV.rows();
  for (int r = 0; r < row; r++){
    objFile << "vn " << NV.row(r) << "\n";
  }objFile << "\n\n";

  // space/uv/normal combin list
  row = F.rows();
  int col = F.cols();
  for (int r = 0; r < row; r++){
    objFile << "f ";
    for (int c = 0; c < col; c++){
      objFile << 1 + F(r,c) << "/" << 1 + UF(r,c) << "/" << 1 + NF(r,c) << " "; 
    }
    objFile << "\n";
  }
  

  ////////////////////////////////////////////////////////////////////////////
  return false;
}
