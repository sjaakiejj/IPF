#ifndef _PIXEL_H_
#define _PIXEL_H_

#include <stdint.h>


struct Pixel
{
  Pixel() : R(0), G(0), B(0), A(0) {}
  Pixel(uint8_t r, uint8_t g, uint8_t b, uint8_t a) : R(r), G(g), B(b), A(a) {}
  uint8_t R, G, B, A;
};

#endif
