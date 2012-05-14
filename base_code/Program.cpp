#include "Program.h"

void Program::load(std::string p_image)
{
  glEnable(GL_TEXTURE_2D);
  srand(time(NULL));
  
  m_current_state    = ORIGINAL_STATE;
  
  /* Setup the image */
  m_base_image  = load_img(p_image);
  m_number_pixels = m_base_image->width * m_base_image->height;
  m_base_pixels = PixelFactory::BytesToPixels(m_base_image->data,
  					      m_number_pixels,
					      m_base_image->bytes);
  
  /* Load the something */
  Pixel * my_pixels = NULL;
  m_texture_obj = gen_tex_obj(m_base_image, my_pixels);
  //delete [] my_pixels;
  
}

void Program::menuItemSelected(int entry)
{
  m_current_state = (STATE)entry;
}

void Program::increase(STATE p_state)
{
  switch(p_state)
  {
    case ORIGINAL_STATE:
      break;
      
    default:
      break;
  }
}

void Program::decrease(STATE p_state)
{  
  switch(p_state)
  {
    case ORIGINAL_STATE:
      break;
      
    default:
      break;
  }
}

void Program::keyPressed(unsigned char c, int x, int y)
{ 
  if( '+' == c )
  {
     increase(m_current_state);
  }
  else if( '-' == c )
  {
     decrease(m_current_state);
  }
  
}

void Program::display()
{  
  glEnable(GL_TEXTURE_2D);

  void * font = GLUT_BITMAP_HELVETICA_18;
      
  glColor3f(1.0,1.0,1.0); 
  
  switch(m_current_state)
  {
    case ORIGINAL_STATE:
       m_oss << std::endl << "Increase with '+', decrease with '-'";
       glBindTexture( GL_TEXTURE_2D, m_texture_obj );
       break;
    default:
       break;
  }
  
  RenderPlane2D();
  
  glDisable(GL_TEXTURE_2D);
  RenderText2D(font, m_oss.str(), 80, -150);
  
  m_oss.str("");
}
