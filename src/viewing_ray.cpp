#include "viewing_ray.h"
#include <Eigen/Core>
#include <iostream>

void viewing_ray(
  const Camera & camera,
  const int i,
  const int j,
  const int width,
  const int height,
  Ray & ray)
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  double u = (- camera.width / 2) + (camera.width / width) * (j + 0.5);
  double v = (camera.height / 2) - (camera.height / height) * (i + 0.5);
  // std::cout << camera.u; // [-0, 1]
  // Eigen::Vector3d cur_origin(- camera.d * camera.w, u * camera.u, v * camera.v); 
  // Eigen::Vector3d cur_origin(u, v, -camera.d); 
  // std::cout << cur_origin;
  ray.origin = camera.e;
  // double dir_w = - camera.d * camera.w(0) + u * camera.u(0) + v * camera.v(0);
  // std::cout << dir_w;
  // double dir_u = - camera.d * camera.w(1) + u * camera.u(1) + v * camera.v(1);
  // double dir_v = - camera.d * camera.w(2) + u * camera.u(2) + v * camera.v(2);
  ray.direction = - camera.w * camera.d + camera.u * u + camera.v * v;

  ////////////////////////////////////////////////////////////////////////////
}

