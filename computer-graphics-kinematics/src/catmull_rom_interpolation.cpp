#include "catmull_rom_interpolation.h"
#include <Eigen/Dense>

Eigen::Vector3d catmull_rom_interpolation(
  const std::vector<std::pair<double, Eigen::Vector3d> > & keyframes,
  double t)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
  if(keyframes.empty()) return Eigen::Vector3d(0,0,0);

  // While in time domain, might periodly repeat keyframes procedure
  // mod out the actual time
  double actualT = std::fmod(t, keyframes.back().first);

  // Could use sortingAlgo
  int zeroPos = 0;
  for (int i = 0; i < keyframes.size()-1; i++){
    if(actualT > keyframes[i].first && actualT < keyframes[i+1].first){
      zeroPos = i;
      break;
    }
  }
  
  int frontOffset = !(zeroPos == 0);
  int backOffset = !((zeroPos+2)==keyframes.size());

  double t0 = keyframes[zeroPos - frontOffset].first;
  double t1 = keyframes[zeroPos].first;
  double t2 = keyframes[zeroPos+1].first;
  double t3 = keyframes[zeroPos+2 - backOffset].first;

  Eigen::Vector3d P0 = keyframes[zeroPos - frontOffset].second;
  Eigen::Vector3d P1 = keyframes[zeroPos].second;
  Eigen::Vector3d P2 = keyframes[zeroPos+1].second;
  Eigen::Vector3d P3 = keyframes[zeroPos+2 - backOffset].second;


  // Direct Solution(NOT TESTED):
  // https://en.wikipedia.org/wiki/Centripetal_Catmull%E2%80%93Rom_spline
  /*
  Eigen::Vector3d A1 = (t1 - actualT)/(t1 - t0) * P0 + (actualT - t0)/(t1 - t0) * P1;
  Eigen::Vector3d A2 = (t2 - actualT)/(t2 - t1) * P0 + (actualT - t1)/(t2 - t1) * P1;
  Eigen::Vector3d A3 = (t3 - actualT)/(t3 - t2) * P0 + (actualT - t2)/(t3 - t2) * P1;

  Eigen::Vector3d B1 = (t2 - actualT)/(t2 - t0) * A1 + (actualT - t0)/(t2 - t0) * A2;
  Eigen::Vector3d B2 = (t3 - actualT)/(t3 - t1) * A2 + (actualT - t1)/(t3 - t1) * A3;

  Eigen::Vector3d C = (t2 - actualT)/(t2 - t1) * B1 + (actualT - t1)/(t2 - t1) * B2;

  return C; 
  */

  // Solution Related de Casteljau algorithm:(Faster Implementation)
  // https://en.wikipedia.org/wiki/Cubic_Hermite_spline#Catmull%E2%80%93Rom_spline
  
  // "Two additional points are required on either end of the curve."
  // Meant p1 p2, are p0, p1 in wikiformula

  Eigen::Vector3d m1 = (P2 - P0) / (t2 - t0) / 2;
  Eigen::Vector3d m2 = (P3 - P1) / (t3 - t1) / 2;
  
  double ratioT = (actualT - t1) / (t2 - t1);

  Eigen::Vector3d P = (2 * std::pow(ratioT, 3) - 3 * std::pow(ratioT, 2) + 1) * P1
                    + (std::pow(ratioT, 3) - 2 * std::pow(ratioT, 2) + ratioT) * m1
                    + (-2 * std::pow(ratioT, 3) + 3 * std::pow(ratioT, 2)) * P2
                    + (std::pow(ratioT, 3) - std::pow(ratioT, 2)) * m2;

  return P;
  /////////////////////////////////////////////////////////////////////////////
}
