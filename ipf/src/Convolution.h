#ifndef _CONVOLUTION_H_
#define _CONVOLUTION_H_

#include "Pixel.h"
#include "HelperFunctions.h"

namespace ipf
{
  //////////////////////////////////////////
  //////////////////////////////////////////
  int8_t * sobel_horizontal_matrix();
  int8_t * sobel_vertical_matrix();
  
  int8_t * prewitt_horizontal_matrix();
  int8_t * prewitt_vertical_matrix();
  
  int8_t * gaussian_matrix(int8_t A, int w, int & se_width); 
  int8_t * laplacian_gaussian_matrix(int w, int & se_width);
  int8_t * mean_matrix();
  int8_t * weighted_mean_matrix();
  
  //////////////////////////////////////////
  //////////////////////////////////////////
  //Old
  Pixel *apply_convolution(Pixel * pixels, int size, int width, int8_t * conv);
  Pixel *apply_normalized_convolution(Pixel * pixels, int size, int width, int8_t * conv);
  
  //New
  Pixel *apply_convolution(Pixel * pixels, int size, int width, int8_t * conv, int conv_width);
  Pixel *apply_normalized_convolution(Pixel * pixels, int size, int width, int8_t * conv, int conv_width);
};

#endif
