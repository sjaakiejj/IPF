#ifndef _GREY_LEVEL_H_
#define _GREY_LEVEL_H_

#include <QaD_GL/gl_lib.h>
#include <IPF/ipf.h>
#include <sstream>
#include <cmath>
#include <ctime>

enum STATE
{ 
  UNDEFINED,
  ORIGINAL_STATE
};

class Program : public gl_Lib
{
private:
  STATE m_current_state;
  std::stringstream m_oss;
  
  // Base Object
  int     m_number_vertices;
  GLuint  m_vbo_id;
  
  // Base Image
  Image * m_base_image;
  Pixel * m_base_pixels;
  int	  m_number_pixels;
  
  // Simple Thresholding
  GLuint  m_texture_obj;
  
public:
  //Inherited
  virtual void display();
  virtual void menuItemSelected(int entry);
  virtual void keyPressed(unsigned char c, int x, int y);

  //Custom
  void load(std::string image);
  
  void increase(STATE state);
  void decrease(STATE state);
};

#endif
