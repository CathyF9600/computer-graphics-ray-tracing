#include "blinn_phong_shading.h"
// Hint:
#include "first_hit.h"
#include <iostream>

Eigen::Vector3d ambient_light(
  const Eigen::Vector3d & ka,
  // Assume ia is pure white (r,g,b) = (1,1,1)
  const Eigen::Vector3d & ia = Eigen::Vector3d(1,1,1))
{
  ////////////////////////////////////////////////////////////////////////////
  // Returns ambient component of shaded color collected by this ray as rgb 3-vector.
  // L_a = k_a I_a
  return (ka.array() * ia.array()).matrix();
}


Eigen::Vector3d blinn_phong_shading(
  const Ray & ray,
  const int & hit_id, 
  const double & t,
  const Eigen::Vector3d & n,
  const std::vector< std::shared_ptr<Object> > & objects,
  const std::vector<std::shared_ptr<Light> > & lights)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  // Initialize the final color to the ambient color
  Eigen::Vector3d rgb = Eigen::Vector3d(0, 0, 0);
  // Get the material properties of the hit object
  std::shared_ptr<Material> material = objects[hit_id]->material;
  // Ambient term (constant contribution)
  Eigen::Vector3d ambient = material->ka;
  // ambient = ambient_light(ambient);
  // rgb += ambient;
  // Intersection point
  Eigen::Vector3d hit_point = ray.origin + t * ray.direction;
  // Iterate over all light sources
  for (const auto & light : lights) {
    // Get the light direction and maximum parametric distance
    Eigen::Vector3d light_dir;
    double max_t;
    light->direction(hit_point, light_dir, max_t);
    // Shadow Ray: Shoot a ray towards the light to check for occlusion
    Ray shadow_ray;
    shadow_ray.origin = hit_point;
    shadow_ray.direction = light_dir.normalized();
    // Check if the light is occluded by another object
    int shadow_hit_id;
    double shadow_t;
    Eigen::Vector3d shadow_normal;
    bool is_shadowed = first_hit(shadow_ray, 1e-4, objects, shadow_hit_id, shadow_t, shadow_normal) && shadow_t < max_t;

    // If not in shadow, compute the diffuse and specular components
    if (!is_shadowed || shadow_t > max_t) {
      // Compute the light's intensity (could be a color in RGB)
      Eigen::Vector3d I = light->I; // intensities

      // 1. Diffuse term: Lambert's cosine law
      double diffuse_intensity = std::max(0.0, n.dot(light_dir.normalized()));
      Eigen::Vector3d diffuse = (material->kd.array() * I.array()).matrix() * diffuse_intensity;

      // 2. Specular term: Blinn-Phong model
      Eigen::Vector3d view_dir = -ray.direction.normalized();  // View direction (from the point back to the camera)
      Eigen::Vector3d half_vector = (light_dir.normalized() + view_dir).normalized();
      double specular_intensity = std::pow(std::max(0.0, n.dot(half_vector)), material->phong_exponent);
      Eigen::Vector3d specular = (material->ks.array() * I.array()).matrix() * specular_intensity;

      // Add diffuse and specular components to the final color
      rgb += diffuse + specular;
      
    }
  }
  return rgb;

  ////////////////////////////////////////////////////////////////////////////
}
