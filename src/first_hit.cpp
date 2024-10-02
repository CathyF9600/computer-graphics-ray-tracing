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
  bool intersect = false;
  double t_min = INFINITY;
  Eigen::Vector3d n_min;
  int hit_id_min = -1;
  for (size_t i = 0; i < objects.size(); ++i) {
    std::shared_ptr<Object> obj = objects[i];
    if (obj->intersect(ray, min_t, t, n)){
      intersect = true;
      if (t < t_min){
        t_min = t;
        n_min = n;
        hit_id_min = i;
      }
    }
  }
  if (intersect) {
    t = t_min;
    n = n_min;
    hit_id = hit_id_min;
  }
  return intersect;
  ////////////////////////////////////////////////////////////////////////////
}

