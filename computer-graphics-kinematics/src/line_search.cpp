#include "line_search.h"
#include <iostream>

double line_search(
  const std::function<double(const Eigen::VectorXd &)> & f,
  const std::function<void(Eigen::VectorXd &)> & proj_z,
  const Eigen::VectorXd & z,
  const Eigen::VectorXd & dz,
  const double max_step)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
  double sigma = max_step;
  double Ebefore = f(z), Eafter;

  do{
    Eigen::VectorXd tempz = z - sigma * dz;
    proj_z(tempz);
    Eafter = f(tempz);
    sigma/=2;
  }while(Eafter > Ebefore);

  return sigma;
  /////////////////////////////////////////////////////////////////////////////
}
