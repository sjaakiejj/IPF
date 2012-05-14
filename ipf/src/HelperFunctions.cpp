#include "HelperFunctions.h"
#include <iostream>

/*******************************************************/
/** Neighbourhood Processing			       */
/*******************************************************/
/////////////////////////////////////////////////////////
int * ipf::get_neighbours(int i, int p_size, int p_width, int p_height)
{
  int * neighbours = new int[9];
  
  int w =  p_width;
  int h =  p_height;
  
  int x = i % w;
  int y = i / w;
  
  neighbours[0] = (x-1)+(y-1)*w; neighbours[1] = (x)+(y-1)*w; neighbours[2] = (x+1)+(y-1)*w;
  neighbours[3] = (x-1)+(y)*w;   neighbours[4] = (x)+(y)*w;   neighbours[5] = (x+1)+(y)*w;
  neighbours[6] = (x-1)+(y+1)*w; neighbours[7] = (x)+(y+1)*w; neighbours[8] = (x+1)+(y+1)*w;
 
  if(x == 0)
  {
    neighbours[0] = neighbours[1]; 
    neighbours[3] = neighbours[4];
    neighbours[6] = neighbours[7];
  } 
  else if(x == w-1)
  {
    neighbours[2] = neighbours[1]; 
    neighbours[5] = neighbours[4];
    neighbours[8] = neighbours[7];
  }
  
  if(y == 0)
  { 
    neighbours[0] = neighbours[3];
    neighbours[1] = neighbours[4];
    neighbours[2] = neighbours[5];
  }
  else if(y == h - 1)
  {
    neighbours[6] = neighbours[3];
    neighbours[7] = neighbours[4];
    neighbours[8] = neighbours[5];
  }
  
  return neighbours;
}
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
int * ipf::get_neighbours(int i, int p_size, int p_width, int p_height, int p_se_width)
{
  int * neighbours = new int[p_se_width * p_se_width];
  
  int w =  p_width;
  int h =  p_height;
  
  int x_center = i % w;
  int y_center = i / w;
  
  int startx = x_center - (p_se_width/2);
  int starty = y_center - (p_se_width/2);
  
  int start_x_ind = 0;
  int start_y_ind = 0;
  
  int end_x_ind = p_se_width;
  int end_y_ind = p_se_width;
  
  if(startx < 0)
  {
    start_x_ind = 0 - startx;
  }
  else if(startx + p_se_width > p_width)
  {
    end_x_ind = (startx + p_se_width) - p_width;
  }
  
  if(starty < 0)
  {
    start_y_ind = 0 - starty;
  }
  else if(starty + p_se_width > p_height)
  {
    end_y_ind = (starty + p_se_width) - p_height;
  }
  
  for(int i = 0; i < p_se_width * p_se_width; i++)
    neighbours[i] = -1;
  
  for(int x = start_x_ind; x < end_x_ind; x++)
  {
    for(int y = start_y_ind; y < end_y_ind; y++)
    {
      //First we do bounds checking
      int x_current = startx + x;
      int y_current = starty + y;
      
      neighbours[x + y*p_se_width] = x_current + y_current * p_width;
    }
  }
  
  return neighbours;
}
/////////////////////////////////////////////////////////

int * ipf::get_neighbours_25(int i, int p_size, int p_width, int p_height)
{
  int * neighbours = get_neighbours(i, p_size, p_width, p_height);
  int * topleft    = get_neighbours(neighbours[0], p_size, p_width, p_height);
  int * topright   = get_neighbours(neighbours[2], p_size, p_width, p_height);
  int * botleft    = get_neighbours(neighbours[6], p_size, p_width, p_height);
  int * botright   = get_neighbours(neighbours[8], p_size, p_width, p_height);
  
  int * all_neighbours = new int[25];
  
  all_neighbours[0] = topleft[0]; all_neighbours[1] = topleft[1]; 
  all_neighbours[2] = topleft[2]; all_neighbours[3] = topright[1]; all_neighbours[4] = topright[2];
  
  all_neighbours[5] = topleft[3]; all_neighbours[6] = topleft[4]; 
  all_neighbours[7] = topleft[5]; all_neighbours[8] = topright[4]; all_neighbours[9] = topright[5];
  
  all_neighbours[10] = topleft[6]; all_neighbours[11] = topleft[7]; 
  all_neighbours[12] = topleft[8]; all_neighbours[13] = topright[7]; all_neighbours[14] = topright[8];
  
  all_neighbours[15] = botleft[3]; all_neighbours[16] = botleft[4]; 
  all_neighbours[17] = botleft[5]; all_neighbours[18] = botright[4]; all_neighbours[19] = botright[5];
  
  all_neighbours[20] = botleft[6]; all_neighbours[21] = botleft[7]; 
  all_neighbours[22] = botleft[8]; all_neighbours[23] = botright[7]; all_neighbours[24] = botright[8];
  
  delete [] neighbours;
  delete [] topleft;
  delete [] topright;
  delete [] botleft;
  delete [] botright;
  
  return all_neighbours;
}

/////////////////////////////////////////////////////////
uint8_t ipf::get_minimum(Pixel * p_image, int * p_neighbours, int p_size)
{
  uint8_t minimum = 255;
  
  //Note that in this context, it's assumed the specified neigbours are 
  //within the scope of the image array. p_size is therefore used to
  //specify the size of the _neighbours_ array.
  
  for(int i = 0; i < p_size; i++)
  {
    if(p_image[ p_neighbours[i] ].R < minimum)
    {
      minimum = p_image[ p_neighbours[i] ].R;
    }
  }
  
  return minimum;
}
/////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////
uint8_t ipf::get_maximum(Pixel * p_image, int * p_neighbours, int p_size)
{
  uint8_t maximum = 255;
  
  //Note that in this context, it's assumed the specified neigbours are 
  //within the scope of the image array. p_size is therefore used to
  //specify the size of the _neighbours_ array.
  
  for(int i = 0; i < p_size; i++)
  {
    if(p_image[ p_neighbours[i] ].R > maximum)
    {
      maximum = p_image[ p_neighbours[i] ].R;
    }
  }
  
  return maximum;
}
/////////////////////////////////////////////////////////
uint8_t ipf::gaussian (int8_t A, int a, int b, int w)
{
  return (double)A * exp( -((int)a * a + (int)b * b) / (double)(2.0 * w*w));
}
/////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////
int8_t ipf::laplacian_gaussian(int a, int b, int w)
{
  double lap = (double)-(1.0 / (M_PI * w * w * w * w)) 
       * (1.0-(a*a + b*b)/(2.0*w*w)) 
       * exp( -((int)a * a + (int)b * b) / (double)(2.0 * w*w));
  return lap * 255.0;
}
/////////////////////////////////////////////////////////
