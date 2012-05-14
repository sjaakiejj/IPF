#ifndef _HELPER_FUNCTIONS_H_
#define _HELPER_FUNCTIONS_H_

#include <cmath>

#include "Pixel.h"

namespace ipf
{
  int *   get_neighbours(int i, int size, int width, int height);
  int *   get_neighbours_25(int i, int size, int width, int height);
  int *   get_neighbours(int i, int size, int width, int height, int se_width);
  uint8_t get_minimum   (Pixel * image, int * neigbours, int size);
  uint8_t get_maximum   (Pixel * image, int * neigbours, int size);
  
  uint8_t gaussian	(int8_t A, int a, int b, int w);
  int8_t laplacian_gaussian(int a, int b, int w);
};

#endif
