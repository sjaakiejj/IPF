#ifndef _OPERATION_H_
#define _OPERATION_H_

#include <stdint.h>

#include "Pixel.h"
#include "HelperFunctions.h"

namespace ipf
{
  /////////////////////////////////////////////////////////////////
  // Bitwise
  /////////////////////////////////////////////////////////////////
  
  Pixel * bitwise_or (Pixel * image_A, Pixel * image_B, int size);
  Pixel * bitwise_and(Pixel * image_A, Pixel * image_B, int size);
  Pixel * bitwise_not(Pixel * image, int size);
  
  ////////////////////////////////////////////////////////////////
  // Common Operations
  ////////////////////////////////////////////////////////////////
  
  Pixel * mirror(Pixel * image, int size, int p_width);
  
  Pixel * multiply(Pixel * image, int size, double amount);
  Pixel * add(Pixel * image, int size, uint8_t amount);
  Pixel * subtract(Pixel * image, int size, uint8_t amount);
  
  Pixel * difference(Pixel * image_A, Pixel * image_B, int size);
  Pixel * strength_image(Pixel * image_A, Pixel * image_B, int size);
  Pixel * invert(Pixel * image, int size);
  
  /////////////////////////////////////////////////////////////////
  // Image Processing
  /////////////////////////////////////////////////////////////////
  
  Pixel * threshold(Pixel * p_image, int p_size, uint8_t p_threshold);
  
  Pixel * erode(Pixel * p_image, int p_size, int p_width);
  Pixel * dilate(Pixel * p_image, int p_size, int p_width);
  
  Pixel * open(Pixel * p_image, int p_size, int p_width);
  Pixel * close(Pixel * p_image, int p_size, int p_width);
  
  Pixel * smooth(Pixel * image, int size, int width);
  
  /////////////////////////////////////////////////////////////////
  // Copy Operations
  /////////////////////////////////////////////////////////////////
  
  Pixel * copy(Pixel * image, int size);
  void	  free(Pixel * image);
};

#endif
