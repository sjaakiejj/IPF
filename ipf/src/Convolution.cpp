#include "Convolution.h"
#include <iostream>
/*************************************/
/** Matrices			     */
/*************************************/
///////////////////////////////////////
int8_t * ipf::sobel_horizontal_matrix()
{
  int8_t * matrix = new int8_t[9];
  
  matrix[0] =  1; matrix[1] =  2; matrix[2] =  1;
  matrix[3] =  0; matrix[4] =  0; matrix[5] =  0;
  matrix[6] = -1; matrix[7] = -2; matrix[8] = -1;
  
  return matrix;
}
///////////////////////////////////////

///////////////////////////////////////
int8_t * ipf::sobel_vertical_matrix()
{
  int8_t * matrix = new int8_t[9];
  
  matrix[0] = -1; matrix[1] = 0; matrix[2] = 1;
  matrix[3] = -2; matrix[4] = 0; matrix[5] = 2;
  matrix[6] = -1; matrix[7] = 0; matrix[8] = 1;
  
  return matrix;
}
///////////////////////////////////////

///////////////////////////////////////
int8_t * ipf::prewitt_horizontal_matrix()
{
  int8_t * matrix = new int8_t[9];
  
  matrix[0] =  1; matrix[1] =  1; matrix[2] =  1;
  matrix[3] =  0; matrix[4] =  0; matrix[5] =  0;
  matrix[6] = -1; matrix[7] = -1; matrix[8] = -1;
  
  return matrix;
}
///////////////////////////////////////

///////////////////////////////////////
int8_t * ipf::prewitt_vertical_matrix()
{
  int8_t * matrix = new int8_t[9];
  
  matrix[0] = -1; matrix[1] = 0; matrix[2] = 1;
  matrix[3] = -1; matrix[4] = 0; matrix[5] = 1;
  matrix[6] = -1; matrix[7] = 0; matrix[8] = 1;
  
  return matrix;
}
///////////////////////////////////////

///////////////////////////////////////
int8_t * ipf::gaussian_matrix(int8_t A, int w, int & se_width)
{
  se_width = w * 2 + 1;
  
  int8_t * matrix = new int8_t[se_width * se_width];
  
  for(int x = 0; x < se_width; x++)
  {
    for(int y = 0; y < se_width; y++)
    {
      matrix[x + y * se_width] = gaussian(A, 0 - (se_width/2) + x, 
      					     0 - (se_width/2) + y, w);
    }
  }
  
  return matrix;
}
///////////////////////////////////////

///////////////////////////////////////
int8_t * ipf::laplacian_gaussian_matrix(int w, int & se_width)
{
  se_width = w * 2 + 1;
  
  int8_t * matrix = new int8_t[se_width * se_width];
  
  for(int y = 0; y < se_width; y++)
  {
    for(int x = 0; x < se_width; x++)
    {
      matrix[x + y * se_width] = laplacian_gaussian(0 - (se_width/2) + x, 
      					     0 - (se_width/2) + y, w);
      std::cout << (int)matrix[x + y * se_width] << " ";
    }
    std::cout << std::endl;
  }
  
  return matrix;
}
////////////////////////////////////////
///////////////////////////////////////
int8_t * ipf::mean_matrix()
{
  int8_t * matrix = new int8_t[9];
  
  matrix[0] =  1; matrix[1] =  1; matrix[2] =  1;
  matrix[3] =  1; matrix[4] =  1; matrix[5] =  1;
  matrix[6] =  1; matrix[7] =  1; matrix[8] =  1;
  
  return matrix;
}
///////////////////////////////////////

///////////////////////////////////////
int8_t * ipf::weighted_mean_matrix()
{
  int8_t * matrix = new int8_t[9];
  
  matrix[0] =  1; matrix[1] =  2; matrix[2] =  1;
  matrix[3] =  2; matrix[4] =  4; matrix[5] =  2;
  matrix[6] =  1; matrix[7] =  2; matrix[8] =  1;
  
  return matrix;
}
///////////////////////////////////////

/*************************************/
/** Operations			     */
/*************************************/
///////////////////////////////////////
Pixel * ipf::apply_convolution(Pixel * p_image, int p_size, int p_width, int8_t * p_conv)
{
  Pixel * pixels = new Pixel[p_size];
  int 	  height = p_size / p_width;
  
  int denominator= 0;
  for(int i = 0; i < 9; i++)
  {
    denominator += p_conv[i];
  }
  
  if(denominator == 0)
  {
    return apply_normalized_convolution(p_image, p_size, p_width, p_conv);
  }
    
  for(int i = 0; i < p_size; i++)
  {
    int * neighbours = get_neighbours(i, p_size, p_width, height);
    
    int R = 0, G = 0, B = 0, A = 0;
    for(int j = 0; j < 9; j++)
    {
      R += (int)p_image[ neighbours[j] ].R * (int)p_conv[j];
      G += (int)p_image[ neighbours[j] ].G * (int)p_conv[j];
      B += (int)p_image[ neighbours[j] ].B * (int)p_conv[j];
      A += (int)p_image[ neighbours[j] ].A * (int)p_conv[j];
    }
    
    pixels[i].R = R / denominator;
    pixels[i].G = G / denominator;
    pixels[i].B = B / denominator;
    pixels[i].A = A / denominator;
    
    delete [] neighbours;
  }
  
  return pixels;
}
///////////////////////////////////////

///////////////////////////////////////
Pixel * ipf::apply_normalized_convolution(Pixel * p_image, int p_size, int p_width, int8_t * p_conv)
{
  Pixel * pixels = new Pixel[p_size];
  int 	  height = p_size / p_width;
  int 	  minimum= 255;
  int  	  maximum= 0;
  
  int * R = new int[p_size];
  int * G = new int[p_size];
  int * B = new int[p_size];
  int * A = new int[p_size];
  
  int denominator= 0;
  for(int i = 0; i < 9; i++)
  {
    denominator += p_conv[i];
  }
  
  if(denominator == 0)
    denominator = 1;
  std::cout<<"____________________"<<std::endl<< "---------------"<<std::endl;
  for(int i = 0; i < p_size; i++)
  {
    int * neighbours = get_neighbours(i, p_size, p_width, height);
    
    for(int j = 0; j < 9; j++)
    {
      R[i] += (int)p_image[ neighbours[j] ].R * (int)p_conv[j];
      G[i] += (int)p_image[ neighbours[j] ].G * (int)p_conv[j];
      B[i] += (int)p_image[ neighbours[j] ].B * (int)p_conv[j];
      A[i] += (int)p_image[ neighbours[j] ].A * (int)p_conv[j];
    }
    
    if(R[i] < minimum)
      minimum = R[i];
    if(R[i] > maximum)
      maximum = R[i];
    
    R[i] = R[i] / denominator;
    G[i] = G[i] / denominator;
    B[i] = B[i] / denominator;
    A[i] = A[i] / denominator;
    
    delete [] neighbours;
  }
  
  // Now Normalise it
  int range = maximum - minimum;
  
  for(int i = 0; i < p_size; i++)
  {
    pixels[i].R = 128 + ((R[i] / (double)range) * 128.0);
    pixels[i].G = 128 + ((G[i] / (double)range) * 128.0);
    pixels[i].B = 128 + ((B[i] / (double)range) * 128.0);
    pixels[i].A = 128 + ((A[i] / (double)range) * 128.0);
  }
  
  delete [] R;
  delete [] G;
  delete [] B;
  delete [] A;
  
  return pixels;
}
///////////////////////////////////////

///////////////////////////////////////
Pixel * ipf::apply_convolution(Pixel * p_image, int p_size, int p_width, int8_t * p_conv, int p_conv_width)
{
  Pixel * pixels = new Pixel[p_size];
  int 	  height = p_size / p_width;
  
  int denominator= 0;
  int conv_size  = p_conv_width * p_conv_width;
  
  for(int i = 0; i < conv_size; i++)
  {
    denominator += p_conv[i];
  }
  
  if(denominator == 0)
  {
    return apply_normalized_convolution(p_image, p_size, p_width, p_conv, p_conv_width);
  }
    
  for(int i = 0; i < p_size; i++)
  {
    int * neighbours = get_neighbours(i, p_size, p_width, height, p_conv_width);
    
    bool was_edge = false;
    int R = 0, G = 0, B = 0, A = 0;
    for(int j = 0; j < conv_size; j++)
    {
      if(neighbours[j] != -1)
      {
        R += (int)p_image[ neighbours[j] ].R * (int)p_conv[j];
        G += (int)p_image[ neighbours[j] ].G * (int)p_conv[j];
        B += (int)p_image[ neighbours[j] ].B * (int)p_conv[j];
        A += (int)p_image[ neighbours[j] ].A * (int)p_conv[j];
      }
      else
      {
        was_edge = true;
      }
    }
    
    if(was_edge)
    {
      pixels[i] = p_image[i];
    }
    else
    {
      pixels[i].R = R / denominator;
      pixels[i].G = G / denominator;
      pixels[i].B = B / denominator;
      pixels[i].A = A / denominator;
    }
    
    delete [] neighbours;
  }
  
  return pixels;
}
///////////////////////////////////////


///////////////////////////////////////
Pixel * ipf::apply_normalized_convolution(Pixel * p_image, int p_size, int p_width, int8_t * p_conv, int p_conv_width)
{
  Pixel * pixels = new Pixel[p_size];
  int 	  height = p_size / p_width;
  int 	  minimum= 255;
  int  	  maximum= 0;
  
  int * R = new int[p_size];
  int * G = new int[p_size];
  int * B = new int[p_size];
  int * A = new int[p_size];
  
  int conv_size  = p_conv_width * p_conv_width;
  int denominator= 0;
  
  for(int i = 0; i < conv_size; i++)
  {
    denominator += p_conv[i];
  }
  
  
  for(int i = 0; i < p_size; i++)
  {
    int * neighbours = get_neighbours(i, p_size, p_width, height);
    
    
    bool was_edge;
    for(int j = 0; j < conv_size; j++)
    {
      if(neighbours[j] != -1)
      {
        R[i] += (int)p_image[ neighbours[j] ].R * (int)p_conv[j];
        G[i] += (int)p_image[ neighbours[j] ].G * (int)p_conv[j];
        B[i] += (int)p_image[ neighbours[j] ].B * (int)p_conv[j];
        A[i] += (int)p_image[ neighbours[j] ].A * (int)p_conv[j];
      }
      else
      {
        was_edge = true;
      }
    }
    
    if(R[i] < minimum)
      minimum = R[i];
    if(R[i] > maximum)
      maximum = R[i];
    
    if(was_edge)
    {
      R[i] = p_image[i].R;
      G[i] = p_image[i].G;
      B[i] = p_image[i].B;
      A[i] = p_image[i].A;
    }
    else
    {
      R[i] = R[i] / denominator;
      G[i] = G[i] / denominator;
      B[i] = B[i] / denominator;
      A[i] = A[i] / denominator;
    }
    delete [] neighbours;
  }
  
  // Now Normalise it
  int range = maximum - minimum;
  
  for(int i = 0; i < p_size; i++)
  {
    pixels[i].R = 128 + ((R[i] / (double)range) * 128.0);
    pixels[i].G = 128 + ((G[i] / (double)range) * 128.0);
    pixels[i].B = 128 + ((B[i] / (double)range) * 128.0);
    pixels[i].A = 128 + ((A[i] / (double)range) * 128.0);
  }
  
  delete [] R;
  delete [] G;
  delete [] B;
  delete [] A;
  
  return pixels;
}
///////////////////////////////////////
