#include "Labelling.h"


int * ipf::label_image(Pixel * p_pixels, int p_size, int p_width)
{
  Label_State *  label = label_pass_one(p_pixels, p_size, p_width);
  int   * image_labels = label_pass_two(label);
  
  free(label);
  
  return image_labels;
}

ipf::Label_State* ipf::label_pass_one(Pixel* p_image, int p_size, int p_width)
{
  Label_State * label 	= new Label_State();
  
  
  label->image	 	= new Pixel[p_size];
  label->pixel_ids	= new int[p_size];
  label->image_size 	= p_size;
  
  
  int current_id 	= 0; 
  int height 		= p_size / p_width;
  
  for(int i = 0; i < p_size; i++)
    label->pixel_ids[i] = -1;
  
  
 // if(label->object_vector.size() == 0)
  //{
   // label->object_vector.push_back( Pixel(255,0,255,0) );
 // }
  
  for(int i = 0; i < p_size; i++)
  {
   
    if(p_image[i].R == 255)
    {
       int * neighbours = get_neighbours(i, p_size, p_width, height);
       
       /* Is it next to a labelled object? */
       for(int j = 0; j < 9; j++)
       {
         if(neighbours[j] == i) continue; // Skip ourselves
	 
         /* If YES we share the pixel */
         if( label->pixel_ids[ neighbours[j] ] != -1 
	 	&& label->pixel_ids[i] == -1 )
	 {
	   /* Label the pixel */
	   label->pixel_ids[i] = label->pixel_ids[ neighbours[j] ];
	 }
	 
	 /* If there is an inconsistency */
	 else if ( label->pixel_ids[ neighbours[j] ] != -1 && 
	 	     label->pixel_ids[ neighbours[j] ] != label->pixel_ids[i] )
	 {
	   if( label->pixel_ids[ neighbours[j] ] < label->pixel_ids[i] )
	   {
	     int cur_id = label->pixel_ids[ neighbours[j] ];
	     
	     label->assoc_map[ label->pixel_ids[i] ] = cur_id;
	     
	     label->pixel_ids[ i ] = cur_id;
	   }
	   else
	   {
	     int cur_id = label->pixel_ids[i];
	     
	     label->assoc_map[ label->pixel_ids[ neighbours[j] ] ] = cur_id;
	     
	     label->pixel_ids[ neighbours[j] ] = cur_id;
	   }
	 }
	 
       }
       
       /* If NO we increment the label */
       if(label->pixel_ids[i] == -1)
       {
         ++ current_id;
//	 if( current_id >= label->object_vector.size() )
       //    label->object_vector.push_back( get_color_id(current_id) );
	 
	 label->pixel_ids[i] = current_id;
       }
       
       delete [] neighbours;
    }
    
  }
  
 // for(int i = 0; i < p_size; i++)
 // {
  //  label->image[i] = label->object_vector[ label->pixel_ids[i] ];
 // }
  
  return label;
}

int * ipf::label_pass_two(Label_State * p_label)
{
  //Pixel * pixels = new Pixel[p_label->image_size];
  
  for(int i = 0; i < p_label->image_size; i++)
  {
    if(p_label->pixel_ids[i] != -1)
    {
      if(p_label->assoc_map.count( p_label->pixel_ids[i] ) > 0)
      {
        int cur_id = p_label->pixel_ids[i];
	
        while(p_label->assoc_map[cur_id] != 0) cur_id = p_label->assoc_map[cur_id];
	
        //pixels[i] = p_label->object_vector[ cur_id ];
	p_label->pixel_ids[i] = cur_id;
      }
      //else
        //pixels[i] = p_label->object_vector[ p_label->pixel_ids[i] ];
    }
  }
  
  return p_label->pixel_ids;
}

int * ipf::find_boundary(Pixel* p_image, int * p_labels, int p_size, int p_width)
{
//  std::map<int,int>  index_map;
//  std::map<int,int>  id_map;
  
  int height = p_size / p_width;
  int * boundary = new int[p_size];
  
  for(int i = 0; i < p_size; i++)
  {
    if( p_labels[i] != -1 )
    {
      int * neighbours = get_neighbours(i, p_size, p_width, height);
      bool  foundBackground = false;
      
      for(int j = 0; j < 9; j++)
      {
        if( p_labels[ neighbours[j] ] == -1 ) foundBackground = true;
      }
      
      if(foundBackground)
      {
        boundary[i] = p_labels[i];
        /*
        if(index_map.count( m_pixel_ids[i] ) > 0)
	{
	  ++(*boundaries)[ index_map[ p_labels[i] ] ];
	  p_boundary[i] = id_map[ p_labels[i] ];
	}
	else
	{
	  index_map[ m_pixel_ids[i] ] = boundaries->size();
	  boundaries->push_back(1);
	  
	  p_boundary_img[i] = *color;
	  colorMap[ m_pixel_ids[i] ] = *color;
	}
	*/
      }
      else
        boundary[i] = -1;
      
      delete [] neighbours;
    }
  }
  
  return boundary;
}

void ipf::free(Label_State * p_label)
{
  delete [] p_label->image;
  
  p_label->assoc_map.clear();
  p_label->object_vector.clear();
  
  delete p_label;
}
