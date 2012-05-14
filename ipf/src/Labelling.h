#ifndef _LABELLING_H_
#define _LABELLING_H_

#include "Pixel.h"
#include "HelperFunctions.h"

#include <vector>
#include <map>

namespace ipf
{
  struct Label_State
  {
    Pixel * 		image;
    int   *		pixel_ids;
    int			image_size;
    
    std::vector<int> 	object_vector;
    std::map<int,int>	assoc_map;
  };
  
  int * 	label_image(Pixel * pixels, int size, int width);
  
  Label_State* 	label_pass_one(Pixel* image, int size, int width);
  int*       	label_pass_two(Label_State * label);
  
  int * 	find_boundary(Pixel* image, int * labels, int size, int width);
  
  void 		free(Label_State * label);
};

#endif
