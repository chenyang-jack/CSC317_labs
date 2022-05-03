#include "cube.h"

#include <iostream>
using namespace std;

void cube(
  Eigen::MatrixXd & V,
  Eigen::MatrixXi & F,
  Eigen::MatrixXd & UV,
  Eigen::MatrixXi & UF,
  Eigen::MatrixXd & NV,
  Eigen::MatrixXi & NF)
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here:
  ////////////////////////////////////////////////////////////////////////////

  //Hint:
  V.resize(8,3);
  F.resize(6,4);
  UV.resize(14,2);
  UF.resize(6,4);
  NV.resize(6,3);
  NF.resize(6,4);

  V = Eigen::MatrixXd::Zero(8,3);
  F = Eigen::MatrixXi::Zero(6,4); 
  UV = Eigen::MatrixXd::Zero(14,2);
  UF = Eigen::MatrixXi::Zero(6,4);
  NV = Eigen::MatrixXd::Zero(6,3);
  NF = Eigen::MatrixXi::Zero(6,4);

  V << 0,0,0,
       0,1,0,
       0,0,1,
       0,1,1,
       -1,0,0,
       -1,1,0,
       -1,0,1,
       -1,1,1;

  F << 0, 1, 3, 2, // GREEN
       1, 5, 7, 3, // BLUE
       2, 3, 7, 6, // YELLOW
       4, 0, 2, 6, // RED
       5, 4, 6, 7, // ORANGE
       0, 4, 5, 1; // WHITE

  UV << 1,0,
        2,0,

        0,1,
        1,1,
        2,1,
        3,1,
        4,1,

        0,2,
        1,2,
        2,2,
        3,2,
        4,2,

        1,3,
        2,3;
  UV = UV * 0.25;

  UF << 3, 4, 9, 8,
        4, 5, 10, 9,
        8, 9, 13, 12,
        2, 3, 8, 7,
        5, 6, 11, 10,
        3, 0, 1, 4;


  NV << 1, 0, 0,
        0, 1, 0,
        0, 0, 1,
        0, -1, 0,
        -1, 0, 0,
        0, 0, -1;

  NF << 0, 0, 0, 0,
        1, 1, 1, 1,
        2, 2, 2, 2,
        3, 3, 3, 3,
        4, 4, 4, 4,
        5, 5, 5, 5;
}
