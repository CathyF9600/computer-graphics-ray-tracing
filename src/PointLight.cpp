#include "PointLight.h"

void PointLight::direction(
  const Eigen::Vector3d & q, Eigen::Vector3d & d, double & max_t) const
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here:
  // q is the query vector
  // Compute the direction vector (d) from point q to the light source
  d = this->p - q;

  // Compute the parametric distance (max_t) as the length of the direction vector
  max_t = d.norm();

  // Normalize the direction vector to have a unit length
  d = d.normalized();
  ////////////////////////////////////////////////////////////////////////////
}
