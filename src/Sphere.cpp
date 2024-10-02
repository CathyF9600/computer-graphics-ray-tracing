#include "Sphere.h"
#include "Ray.h"
#include <iostream>

bool Sphere::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  Eigen::Vector3d oc = ray.origin - center; // O - C
  // std::cout << oc;
  double a = ray.direction.dot(ray.direction);  // D · D, should be 1 if D is normalized
  double b = 2.0 * oc.dot(ray.direction);      // 2 * (O - C) · D
  double c = oc.dot(oc) - radius * radius;     // (O - C) · (O - C) - r^2

  // Discriminant to check if ray intersects the sphere
  double discriminant = b * b - 4 * a * c;

  // If discriminant is negative, no real roots => no intersection
  if (discriminant < 0) {
    return false;
  }
  // Compute the two possible intersection points
  double sqrt_discriminant = std::sqrt(discriminant);
  double t1 = (-b - sqrt_discriminant) / (2.0 * a);
  double t2 = (-b + sqrt_discriminant) / (2.0 * a);

  // Find the closest t that is larger than min_t
  if (t1 >= min_t) {
    t = t1;
  } else if (t2 >= min_t) {
    t = t2;
  } else {
    return false; // Both t1 and t2 are behind the ray
  }

  // Compute the intersection point and normal
  Eigen::Vector3d intersection_point = ray.origin + t * ray.direction;
  n = (intersection_point - center).normalized();  // Normal at the intersection point

  return true;
  ////////////////////////////////////////////////////////////////////////////
}

