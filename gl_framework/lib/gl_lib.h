#ifndef _GL_LIB_H_
#define _GL_LIB_H_

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <string>
#include <sys/time.h>
#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <vector>

#include "PixelFactory.h"
#include "stb_image.h"

struct Vertex
{
  Vertex() : X(0),Y(0),Z(0),nX(0), nY(0), nZ(0), tX(0), tY(0) {}
  Vertex(float x, float y, float z) : X(x), Y(y), Z(z) {}
  
  float X,Y,Z;
  float nX, nY, nZ;
  float tX, tY;
};

struct Image
{
  Image(int x, int y, int n, unsigned char * d) 
  		: width(x), height(y), bytes(n), data(d) {}
  int width, height, bytes;
  unsigned char * data;
};

class gl_Lib
{
private:
  static gl_Lib * mInstance;
  
  static int WIN_WIDTH;
  static int WIN_HEIGHT;
  static bool m_2D;
  
  static std::vector<GLuint> m_allocated_textures;
  static std::vector<GLuint> m_allocated_vbos;

public:
  // Custom Functions
  virtual void menuItemSelected(int entry) = 0;
  virtual void keyPressed(unsigned char c, int x, int y) = 0;
  virtual void display() = 0;
  
  // OpenGL Initialisation
  static void Init(int argc, char ** argv, 
  		   int width, int height, std::string, gl_Lib*, bool p_2D = false);
  static void Start();
  
  // Textures
  static Image * load_img(std::string image);
  static GLuint  gen_tex_obj(Image * p_img, Pixel * test);
  static GLuint update_tex_obj(Image * p_img, Pixel * p_pixels, 
  					GLuint p_tex_obj);
  static void free_image(Image * p_img);
  
  // Vertex Buffers
  static Vertex* gen_plane(int width, int height);
  static Vertex* gen_vertices( Vertex * pVertices, int pNumberVertices, int p_grid_width, int &pActualVertices);
  static GLuint  gen_vbo( Vertex* pVertices, int pNumberVertices );
  
  // Helper Functions
  static long GetTimeMillis();
  static void AddMenuEntry( int id, std::string text );
  static void RenderText2D( void * font, std::string text, int x, int y );
  static void RenderPlane2D( );
  static void CleanUp();
  
  // Callbacks
  static void Keyboard(unsigned char c, int x, int y); 
  static void Menu( int entry );
  static void Reshape( int, int );
  static void Reshape2D( int, int );
  static void Display ();
};

#endif
