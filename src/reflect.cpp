#include <Eigen/Core>

Eigen::Vector3d reflect(const Eigen::Vector3d & in, const Eigen::Vector3d & n)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  // return Eigen::Vector3d(0,0,0);
  // n.normalized();
  Eigen::Vector3d reflected = in - 2 * (n.dot(in)) * n;
  return reflected;
  ////////////////////////////////////////////////////////////////////////////
}
