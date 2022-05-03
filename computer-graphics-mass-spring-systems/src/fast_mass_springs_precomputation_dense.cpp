#include "fast_mass_springs_precomputation_dense.h"
#include "signed_incidence_matrix_dense.h"
#include <Eigen/Dense>

bool fast_mass_springs_precomputation_dense(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & E,
  const double k,
  const Eigen::VectorXd & m,
  const Eigen::VectorXi & b,
  const double delta_t,
  Eigen::VectorXd & r,
  Eigen::MatrixXd & M,
  Eigen::MatrixXd & A,
  Eigen::MatrixXd & C,
  Eigen::LLT<Eigen::MatrixXd> & prefactorization)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code

  r.resize(E.rows());
  for (int i = 0; i < E.rows(); i++)
  {
    r[i] = ( V.row(E(i,0)) - V.row(E(i,1)) ).norm();
  }
  
  M = Eigen::MatrixXd::Zero(V.rows(),V.rows());
  for (int i = 0; i < V.rows(); i++)
  {
    M(i,i) = m[i];
  }
  
  signed_incidence_matrix_dense(V.rows(), E, A);

  C = Eigen::MatrixXd::Zero(b.rows(), V.rows());
  for (int i = 0; i < b.rows(); i++)
  {
    C( i, b(i) ) = 1;
  }
  
  double w = 1e10;

  // Eigen::MatrixXd Q = Eigen::MatrixXd::Identity(V.rows(),V.rows());
  // Q = k * A.transpose * A + 1/(deltaT pow2) * M
  Eigen::MatrixXd Q = (k * A.transpose() * A) + (M/delta_t/delta_t) + (w * C.transpose() * C);


  /////////////////////////////////////////////////////////////////////////////
  prefactorization.compute(Q);
  return prefactorization.info() != Eigen::NumericalIssue;
}
