#include "raycolor.h"
#include "first_hit.h"
#include "blinn_phong_shading.h"
#include "reflect.h"
#include <cstdio>
#include <iostream>


bool raycolor(
  const Ray & ray, 
  const double min_t,
  const std::vector< std::shared_ptr<Object> > & objects,
  const std::vector< std::shared_ptr<Light> > & lights,
  const int num_recursive_calls,
  Eigen::Vector3d & rgb)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  // Define a maximum recursion depth to prevent infinite recursion.
  const int max_recursive_depth = 5;
  if (num_recursive_calls >= max_recursive_depth) {
    return false;
  }
  rgb = Eigen::Vector3d(0,0,0);

  // Structure to store hit information.
  int hit_id;
  double t;
  Eigen::Vector3d normal;
  // Shoot the ray into the scene and find the first hit.
  if (first_hit(ray, min_t, objects, hit_id, t, normal)) {
    Eigen::Vector3d hit_point = ray.origin + t * ray.direction;
    // Get the object that was hit.
    std::shared_ptr<Object> hit_object = objects[hit_id];
    // Compute the shading at the hit point using Blinn-Phong shading.
    Eigen::Vector3d hit_color = blinn_phong_shading(ray, hit_id, t, normal, objects, lights);
    // Add the shading color to the output color.
    rgb += hit_color;

    // Compute the reflected ray direction
    Eigen::Vector3d reflected_dir = reflect(ray.direction, normal);
    // Create the reflected ray
    Ray reflected_ray;
    reflected_ray.origin = hit_point;
    reflected_ray.direction = reflected_dir;
    // Recursively trace the reflected ray
    Eigen::Vector3d reflected_rgb(0, 0, 0);
    if (raycolor(reflected_ray, 1e-4, objects, lights, num_recursive_calls + 1, reflected_rgb)) {
      Eigen::Vector3d km = hit_object->material->km;
      rgb += (km.array() * reflected_rgb.array()).matrix();
    }
    // Return true indicating that the ray hit an object
    return true;
  }

  return false;
  ////////////////////////////////////////////////////////////////////////////
}
