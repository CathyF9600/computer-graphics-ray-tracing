#include "Plane.h"
#include "Ray.h"

bool Plane::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  // t = (p*n - e*n)/ d*n
  double pn = this->point.dot(normal);
  double en = ray.origin.dot(normal);
  double dn = ray.direction.dot(normal);
  double top = pn - en; // O - C
 if (std::abs(dn) < 1e-6) {
    return false;
  }
  t = top / dn;
    if (t >= min_t) {
    // The ray intersects the plane at t, and the normal at the intersection is the plane normal
    n = normal.normalized();  // Ensure the normal is normalized
    return true;
  }
  return false;
  ////////////////////////////////////////////////////////////////////////////
}

