#include "Triangle.h"
#include "Ray.h"
#include <tuple>
#include <Eigen/Dense>

bool Triangle::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  // Vertices of the triangle
  using std::get;
  const Eigen::Vector3d & v0 = get<0>(corners);
  const Eigen::Vector3d & v1 = get<1>(corners);
  const Eigen::Vector3d & v2 = get<2>(corners);

  // Edge vectors
  Eigen::Vector3d e1 = v1 - v0;
  Eigen::Vector3d e2 = v2 - v0;

  // Compute the determinant
  Eigen::Vector3d A = ray.direction.cross(e2);
  double det = e1.dot(A);

  // If the determinant is near zero, the ray is parallel to the triangle plane
  if (std::abs(det) < 1e-8) { // does not have an inverse
    return false;
  }

  // Compute inverse determinant
  double inv_det = 1.0 / det;

  // Vector from ray origin to v0
  Eigen::Vector3d T = ray.origin - v0;

  // Compute u parameter and test bounds
  double u = T.dot(A) * inv_det; // det(A-1) = 1 / det(A)
  if (u < 0.0 || u > 1.0) {
    return false;
  }

  // Compute the Q vector
  Eigen::Vector3d Q = T.cross(e1);

  // Compute v parameter and test bounds
  double v = ray.direction.dot(Q) * inv_det;
  if (v < 0.0 || u + v > 1.0) {
    return false;
  }

  // Compute t (the parametric distance along the ray)
  t = e2.dot(Q) * inv_det;

  // Check if t is greater than or equal to min_t
  if (t < min_t) {
    return false;
  }

  // Compute the normal of the triangle
  n = e1.cross(e2).normalized();  // Normal vector of the triangle

  return true;  // Intersection found
  ////////////////////////////////////////////////////////////////////////////
}


