#ifndef _PIXEL_FACTORY_H_
#define _PIXEL_FACTORY_H_

#include <IPF/Pixel.h>

typedef unsigned char UCHAR;

class PixelFactory
{
public:
  static Pixel * BytesToPixels(unsigned char * p_bytes, int size, int n);
};

#endif
