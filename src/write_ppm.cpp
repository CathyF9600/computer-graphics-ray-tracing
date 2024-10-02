#include "write_ppm.h"
#include <fstream>
#include <cassert>
#include <iostream>

bool write_ppm(
  const std::string & filename,
  const std::vector<unsigned char> & data,
  const int width,
  const int height,
  const int num_channels)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code from computer-graphics-raster-images
  // Open file and insert PPM header format
  std::ofstream file;
  file.open(filename);
  if (!file.is_open()) {
    std::cerr << "Error: Could not open the file " << filename << std::endl;
    return false;
  }
  
  if (num_channels == 3) {
    file << "P3\n" << width << " " << height << "\n255\n";
  } else if (num_channels == 1) {
    file << "P2\n" << width << " " << height << "\n255\n";
  }
  file << std::endl;

  // Write the pixel data
  // file.write(reinterpret_cast<const char *>(data.data()), data.size());
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      for (int k = 0; k < num_channels; k++) {
        // reflected[k + num_channels * ((width - 1 - j) + width * i)] = input[k + num_channels*(i + width * j)];
        if (!(j == width - 1 && k == num_channels - 1) ){
          file << (int) data[k + num_channels*(j + width * i)] << " ";
        } else {
          file << (int) data[k + num_channels*(j + width * i)] << std::endl;
        }
      }
    }
  }
  // Close the file
  file << std::endl;
  file.close();

  return true;
  ////////////////////////////////////////////////////////////////////////////
}