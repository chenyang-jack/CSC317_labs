#include "projected_gradient_descent.h"
#include "line_search.h"

#define MAXSTEP 10000.0

void projected_gradient_descent(
  const std::function<double(const Eigen::VectorXd &)> & f,
  const std::function<Eigen::VectorXd(const Eigen::VectorXd &)> & grad_f,
  const std::function<void(Eigen::VectorXd &)> & proj_z,
  const int max_iters,
  Eigen::VectorXd & z)
{
  /////////////////////////////////////////////////////////////////////////////
  // Add your code here
  for (int itrs = 0; itrs < max_iters; itrs++)
  {
    Eigen::VectorXd deltaZ = grad_f(z);

    z = z - line_search(f, proj_z, z, deltaZ, MAXSTEP) * deltaZ;

    proj_z(z);
  }
  /////////////////////////////////////////////////////////////////////////////
}
