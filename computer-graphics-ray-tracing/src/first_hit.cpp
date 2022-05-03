#include "first_hit.h"

bool first_hit(
  const Ray & ray, 
  const double min_t,
  const std::vector< std::shared_ptr<Object> > & objects,
  int & hit_id, 
  double & t,
  Eigen::Vector3d & n)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  t = std::numeric_limits<double>::infinity();
  hit_id = -1;
  bool isIntersect;
  double tempT;
  Eigen::Vector3d tempN;

  for(int i = 0; i < objects.size(); i++){
    isIntersect = objects[i]->intersect(ray, min_t, tempT, tempN);
    if(isIntersect && tempT < t){
      t = tempT;
      n = tempN;
      hit_id = i;
    }
  }
  return (hit_id != -1);
  ////////////////////////////////////////////////////////////////////////////
}