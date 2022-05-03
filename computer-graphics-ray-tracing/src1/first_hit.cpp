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
  ////////////////////////////////////////////////////////////////////////////
  double close_t = std::numeric_limits<double>::infinity();
  double temp_t;
  int temp_id = -1;
  Eigen::Vector3d temp_n;

  for(int i =0; i < objects.size(); i++){
      if (objects[i]->intersect(ray,min_t,temp_t,temp_n)){
          if(temp_t < close_t){
              temp_id = i;
              n = temp_n;
              close_t = temp_t;
          }
      }
  }

  if (temp_id != -1) {
      hit_id = temp_id;
      t = close_t;
      return true;}
  else return false;
}
