#include "DirectionalLight.h"
#include <limits>

void DirectionalLight::direction(
  const Eigen::Vector3d & q, Eigen::Vector3d & d, double & max_t) const
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  // The direction of the directional light is predefined, so we just assign it
  // to d, where `this->d` is the fixed light direction.
  d = -this->d;  // Negate because light shines *toward* objects.

  // For a directional light, the light is considered infinitely far away.
  max_t = std::numeric_limits<double>::infinity();
  d = d.normalized();
  ////////////////////////////////////////////////////////////////////////////
}

