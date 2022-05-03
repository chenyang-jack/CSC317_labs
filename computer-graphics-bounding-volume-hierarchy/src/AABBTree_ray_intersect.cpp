#include "AABBTree.h"

#include <limits>

// See AABBTree.h for API
bool AABBTree::ray_intersect(
  const Ray& ray,
  const double min_t,
  const double max_t,
  double & t,
  std::shared_ptr<Object> & descendant) const 
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  // Expection if Statement: doesnot hit current AABB
  if(!ray_intersect_box(ray, this->box, min_t, max_t))
    return false;
  

  // if reaches the leaf, call ray_intersect Implemented in MeshTriangle/CloudPoint.h
  bool leftHit = false, rightHit = false;
  double leftT = std::numeric_limits<double>::infinity();
  double rightT = std::numeric_limits<double>::infinity();
  std::shared_ptr<Object>leftDec, rightDec;
  if(this->left != NULL)
    leftHit = ray_intersect(ray, min_t, max_t, leftT, leftDec);
  if(this->right != NULL)
    rightHit = ray_intersect(ray, min_t, max_t, rightT, rightDec);


  // No hit occurs
  if(!leftHit && !rightHit) return false;
  // Hit occurs, check closest
  if(leftT < rightT && leftT < t){
    t = leftT;
    descendant = leftDec;
  }
  if(rightT < leftT && rightT < t){
    t = rightT;
    descendant = rightDec;
  }
  return true;
  ////////////////////////////////////////////////////////////////////////////
}

