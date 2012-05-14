#include "PixelFactory.h"

#include <iostream>

Pixel * PixelFactory::BytesToPixels(unsigned char * p_data, int p_size, int p_n)
{
  int stride     = p_n+1;
  Pixel * pixels = new Pixel[ p_size ];
  unsigned char  *   data = new unsigned char[4];
  
  for(int i = 0; i < p_size; i++)
  {
     int    base_index = i * p_n;
     
     for(int j = 0; j < 4; j++)
     {
       if(j <= stride)
         data[j] = p_data[ base_index + j ];
       else
         data[j] = 255;
     }
     
     if(data[0] < 0)
      std::cout << p_data[base_index] << std::endl;
     
     pixels[i] = *(new Pixel(data[0],data[1],data[2],data[3]));
    // delete [] data;
  }
  
  delete [] data;
  return pixels;
}
