#include "Operation.h"


/*******************************************************/
/** Bitwise Operations				       */
/*******************************************************/
/////////////////////////////////////////////////////////
Pixel * ipf::bitwise_or (Pixel * p_image_A, Pixel * p_image_B, int p_size)
{  
  Pixel * pixels = new Pixel[p_size];
  
  for(int i = 0; i < p_size; i++)
  {
    pixels[i].R = p_image_A[i].R | p_image_B[i].R;
    pixels[i].G = p_image_A[i].G | p_image_B[i].G;
    pixels[i].B = p_image_A[i].B | p_image_B[i].B;
    pixels[i].A = p_image_A[i].A | p_image_B[i].A;
  }
  
  return pixels;
}
/////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////
Pixel * ipf::bitwise_and(Pixel * p_image_A, Pixel * p_image_B, int p_size)
{  
  Pixel * pixels = new Pixel[p_size];
  
  for(int i = 0; i < p_size; i++)
  {
    pixels[i].R = p_image_A[i].R & p_image_B[i].R;
    pixels[i].G = p_image_A[i].G & p_image_B[i].G;
    pixels[i].B = p_image_A[i].B & p_image_B[i].B;
    pixels[i].A = p_image_A[i].A & p_image_B[i].A;
  }
  
  return pixels;
}
/////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////
Pixel * ipf::bitwise_not(Pixel * p_image, int p_size)
{  
  Pixel * pixels = new Pixel[p_size];
  
  for(int i = 0; i < p_size; i++)
  {
    pixels[i].R = p_image[i].R == 0 ? 255 : 0;
    pixels[i].G = p_image[i].G == 0 ? 255 : 0;
    pixels[i].B = p_image[i].B == 0 ? 255 : 0;
    pixels[i].A = p_image[i].A == 0 ? 255 : 0;
  }
  
  return pixels;
}
/////////////////////////////////////////////////////////



/*******************************************************/
/** Common Operations  		  		       */
/*******************************************************/
/////////////////////////////////////////////////////////
Pixel * ipf::mirror(Pixel * p_image, int p_size, int p_width)
{
  Pixel * pixels = new Pixel[p_size];
  int height = p_size / p_width;
  
  for(int i = 0; i < p_size; i++)
  {
    int x = i % p_width;
    int y = i / p_width;
    
    pixels[i] = p_image[y * p_width + (p_width - x)];
  }
  
  return pixels;
}
/////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////
Pixel * ipf::add(Pixel * p_image, int p_size, uint8_t p_amount)
{
  Pixel * pixels = new Pixel[p_size];
  
  for(int i = 0; i < p_size; i++)
  {
    int R = (int)p_image[i].R + p_amount;
    int G = (int)p_image[i].G + p_amount;
    int B = (int)p_image[i].B + p_amount;
    int A = (int)p_image[i].A + p_amount;
    
    pixels[i].R = R > 255 ? 255 : R;
    pixels[i].G = G > 255 ? 255 : G;
    pixels[i].B = B > 255 ? 255 : B;
    pixels[i].A = A > 255 ? 255 : A;
  }
  
  return pixels;
}
/////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////
Pixel * ipf::multiply(Pixel * p_image, int p_size, double p_amount)
{
  Pixel * pixels = new Pixel[p_size];
  
  for(int i = 0; i < p_size; i++)
  {
    int R = (int)p_image[i].R * p_amount;
    int G = (int)p_image[i].G * p_amount;
    int B = (int)p_image[i].B * p_amount;
    int A = (int)p_image[i].A * p_amount;
    
    pixels[i].R = R > 255 ? 255 : R;
    pixels[i].G = G > 255 ? 255 : G;
    pixels[i].B = B > 255 ? 255 : B;
    pixels[i].A = A > 255 ? 255 : A;
  }
  
  return pixels;
}
/////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////
Pixel * ipf::subtract(Pixel * p_image, int p_size, uint8_t p_amount)
{ 
  Pixel * pixels = new Pixel[p_size];
  
  for(int i = 0; i < p_size; i++)
  {
    int R = (int)p_image[i].R + p_amount;
    int G = (int)p_image[i].G + p_amount;
    int B = (int)p_image[i].B + p_amount;
    int A = (int)p_image[i].A + p_amount;
    
    pixels[i].R = R < 0 ? 0 : R;
    pixels[i].G = G < 0 ? 0 : G;
    pixels[i].B = B < 0 ? 0 : B;
    pixels[i].A = A < 0 ? 0 : A;
  }
  
  return pixels;
}
/////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////
Pixel * ipf::strength_image(Pixel * p_image_A, Pixel * p_image_B, int p_size)
{
  Pixel * pixels = new Pixel[p_size];
  
  for(int i = 0; i < p_size; i++)
  {
    int A_R = (int)p_image_A[i].R - 128;
    int A_G = (int)p_image_A[i].G - 128;
    int A_B = (int)p_image_A[i].B - 128;
    int A_A = (int)p_image_A[i].A - 128;
    
    int B_R = (int)p_image_B[i].R - 128;
    int B_G = (int)p_image_B[i].G - 128;
    int B_B = (int)p_image_B[i].B - 128;
    int B_A = (int)p_image_B[i].A - 128;
      
    pixels[i].R = sqrt(A_R * A_R + B_R * B_R);
    pixels[i].G = sqrt(A_G * A_G + B_G * B_G);
    pixels[i].B = sqrt(A_B * A_B + B_B * B_B);
    pixels[i].A = sqrt(A_A * A_A + B_A * B_A);
  }
  
  return pixels;
}
/////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////
Pixel * ipf::difference(Pixel * p_image_A, Pixel * p_image_B, int p_size)
{
  Pixel * pixels = new Pixel[p_size];
  
  for(int i = 0; i < p_size; i++)
  {
    int R = (int)p_image_A[i].R - p_image_B[i].R;
    int G = (int)p_image_A[i].G - p_image_B[i].G;
    int B = (int)p_image_A[i].B - p_image_B[i].B;
    int A = (int)p_image_A[i].A - p_image_B[i].A;
    
    pixels[i].R = R < 0 ? 0 : R;
    pixels[i].G = G < 0 ? 0 : G;
    pixels[i].B = B < 0 ? 0 : B;
    pixels[i].A = A < 0 ? 0 : A;
  }
  
  return pixels;
}
/////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////
Pixel * ipf::invert(Pixel * p_image, int p_size)
{
  Pixel * pixels = new Pixel[p_size];
  
  for(int i = 0; i < p_size; i++)
  {
    pixels[i].R = 255 - p_image[i].R;
    pixels[i].G = 255 - p_image[i].G;
    pixels[i].B = 255 - p_image[i].B;
    pixels[i].A = 255 - p_image[i].A;
  }
  
  return pixels;
}
/////////////////////////////////////////////////////////


/*******************************************************/
/** Image Processing Operators			       */
/*******************************************************/
/////////////////////////////////////////////////////////
Pixel * ipf::threshold(Pixel * p_image, int p_size, uint8_t p_threshold)
{
  Pixel * pixels = new Pixel[p_size];
  
  for(int i = 0; i < p_size; i++)
  {
    uint8_t val = ((int)p_image[i].R + (int)p_image[i].G + (int)p_image[i].B) / 3;
    
    pixels[i].R = val > p_threshold ? 0 : 255;
    pixels[i].G = pixels[i].R;
    pixels[i].B = pixels[i].R;
    pixels[i].A = pixels[i].R;
  }

  return pixels;
}
/////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////
Pixel * ipf::erode(Pixel * p_image, int p_size, int p_width)
{
  Pixel * pixels = new Pixel[p_size];
  int 	  height = p_size / p_width;
  
  for(int i = 0; i < p_size; i++)
  {
    int * neighbours = get_neighbours(i, p_size, p_width, height);
    
    pixels[i].R = pixels[i].G = pixels[i].B = get_minimum(p_image, neighbours, 9);
    
    delete [] neighbours;
  }
  
  return pixels;
}
/////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////
Pixel * ipf::dilate(Pixel * p_image, int p_size, int p_width)
{
  Pixel * pixels = new Pixel[p_size];
  int 	  height = p_size / p_width;
  
  for(int i = 0; i < p_size; i++)
  {
    int * neighbours = get_neighbours(i, p_size, p_width, height);
    
    pixels[i].R = pixels[i].G = pixels[i].B = get_maximum(p_image, neighbours, 9);
    
    delete [] neighbours;
  }
  
  return pixels;
}
/////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////
Pixel * ipf::open(Pixel * p_image, int p_size, int p_width)
{
  Pixel * eroded  = erode(p_image, p_size, p_width);
  Pixel * dilated = dilate(eroded, p_size, p_width);
  
  free(eroded);
  
  return dilated;
}
/////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////
Pixel * ipf::close(Pixel * p_image, int p_size, int p_width)
{
  Pixel * dilated = dilate(p_image, p_size, p_width);
  Pixel * eroded  = erode( dilated, p_size, p_width);
  
  free(dilated);
  
  return eroded;
}
/////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////
Pixel * ipf::smooth(Pixel * p_image, int p_size, int p_width)
{
  Pixel * pixels = new Pixel[p_size];
  int w = p_width;
  int h = p_size / p_width;
  
  for(int i = 0; i < p_size; i++)
  {
    int x = i % w;
    int y = i / w;
    
    int tl = i - w - 1,tc = i - w,tr = i - w + 1;
    int cl = i - 1    ,cc = i,    cr = i + 1;
    int bl = i + w - 1,bc = i + w,br = i + w + 1;
    
    if(x == 0)
    {
      tl = tc; cl = cc; bl = bc;
    }
    else if(x == w-1)
    {
      tr = tc; cr = cc; br = bc; 
    }
    
    if(y == 0)
    {
      tl = cl; tc = cc; tr = cr;
    }
    else if(y == h - 1)
    {
      bl = cl; bc = cc; br = cr;
    }
    
    int averageR = p_image[tl].R + p_image[tc].R + p_image[tr].R 
    		 + p_image[cl].R + p_image[cc].R + p_image[cr].R
		 + p_image[bl].R + p_image[bc].R + p_image[br].R;
		 
    int averageG = p_image[tl].G + p_image[tc].G + p_image[tr].G 
    		 + p_image[cl].G + p_image[cc].G + p_image[cr].G
		 + p_image[bl].G + p_image[bc].G + p_image[br].G;
		 
    int averageB = p_image[tl].B + p_image[tc].B + p_image[tr].B 
    		 + p_image[cl].B + p_image[cc].B + p_image[cr].B
		 + p_image[bl].B + p_image[bc].B + p_image[br].B;
		 
    int averageA = p_image[tl].A + p_image[tc].A + p_image[tr].A 
    		 + p_image[cl].A + p_image[cc].A + p_image[cr].A
		 + p_image[bl].A + p_image[bc].A + p_image[br].A;
    
    pixels[i].R = averageR / 9;
    pixels[i].G = averageG / 9;
    pixels[i].B = averageB / 9;
    pixels[i].A = averageA / 9;
    
  }
  
  return pixels;
}
/////////////////////////////////////////////////////////


/*******************************************************/
/** Copy Operations				       */
/*******************************************************/
/////////////////////////////////////////////////////////
Pixel * ipf::copy(Pixel * p_image, int p_size)
{
  Pixel * pixels = new Pixel[p_size];
  
  for(int i = 0; i < p_size; i++)
    pixels[i] = p_image[i];
  
  return pixels;
}
/////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////
void ipf::free(Pixel * pixels)
{
  delete [] pixels;
}
