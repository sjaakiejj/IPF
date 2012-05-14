#include "gl_lib.h"

int gl_Lib::WIN_HEIGHT = 600;
int gl_Lib::WIN_WIDTH = 800;
bool gl_Lib::m_2D = false;
gl_Lib * gl_Lib::mInstance = NULL;
std::vector<GLuint> gl_Lib::m_allocated_textures;
std::vector<GLuint> gl_Lib::m_allocated_vbos;

void gl_Lib::Init(int argc, char ** argv, int width, int height, std::string caption, gl_Lib * p_instance, bool p_2D)
{
  mInstance = p_instance;
  m_2D	    = p_2D;
  WIN_WIDTH = width; WIN_HEIGHT = height;
  
  glutInit(&argc, argv);
  
  if(!m_2D)  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  
  glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);   // Set the initial Window's width and height
  glutInitWindowPosition(50, 50); // Position the initial Window's top-left corner
  glutCreateWindow(caption.c_str());  // Create window with the given title
  glutDisplayFunc(Display); 
  
  if(p_2D)  glutReshapeFunc(Reshape2D);
  else      glutReshapeFunc(Reshape);
    
  glutKeyboardFunc(Keyboard);
  
  glEnable(GL_DEPTH_TEST);
  glClearColor(0.0, 0.0, 0.0, 1.0);
//  Camera::get()->init();
  glPointSize(3.0f);
  
  glewInit();
  
  if(p_2D) glDisable(GL_DEPTH_TEST);
  
  glutCreateMenu(Menu);
  glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void gl_Lib::Start()
{
  glutMainLoop();
}

void gl_Lib::Display()
{
  if(m_2D)  glClear(GL_COLOR_BUFFER_BIT);
  else      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  
    mInstance->display();
    
  glutSwapBuffers();
  if(!m_2D) glutPostRedisplay();
}

void gl_Lib::RenderPlane2D( )
{
  glBegin(GL_QUADS);
    glTexCoord2f (0.0, 0.0);
    glVertex3f (0.0, 0.0, 0.0);
    glTexCoord2f (1.0, 0.0);
    glVertex3f (WIN_WIDTH, 0.0, 0.0);
    glTexCoord2f (1.0, 1.0);
    glVertex3f (WIN_WIDTH, WIN_HEIGHT, 0.0);
    glTexCoord2f (0.0, 1.0);
    glVertex3f (0.0, WIN_HEIGHT, 0.0);
  glEnd();
  
}

void gl_Lib::Reshape(int w, int h)
{
   glViewport(0, 0, (GLsizei) w, (GLsizei) h); 
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(80, 1, 0.001, 10000 );
   glMatrixMode(GL_MODELVIEW);
}

void gl_Lib::Reshape2D(int w, int h)
{
  glViewport(0, 0, (GLsizei) w, (GLsizei) h); 
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();
  glOrtho (0, w, h, 0, 0, 1);
  glMatrixMode (GL_MODELVIEW);
//  glutPostRedisplay();
}

/* Gets the time in milliseconds */
long gl_Lib::GetTimeMillis()
{
    struct timeval start;

    long mtime, seconds, useconds;    

    gettimeofday(&start, NULL);
    
    seconds  = start.tv_sec;
    useconds = start.tv_usec;
    
    return ((seconds) * 1000 + useconds/1000.0) + 0.5;
}

Image * gl_Lib::load_img(std::string image)
{
    int x, y, n;
    unsigned char * data = stbi_load(image.c_str(), &x, &y, &n, 0);
    return new Image(x,y,n,data);
}

GLuint gl_Lib::gen_tex_obj(Image * p_img, Pixel * p_pixels)
{
    GLuint texture_object  = 0;
    GLint  internal_format = GL_RGBA;
    GLint  pixel_format    = GL_RGBA;
    void * data		   = p_pixels;
    
    // Create a texture object
    glGenTextures( 1, &texture_object );
    glBindTexture(GL_TEXTURE_2D, texture_object);

    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE );
     
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Switch formats if neccessary
    if(p_pixels == NULL)
    {
      if(p_img->bytes <= 1)
      {
        internal_format = GL_INTENSITY8;
        pixel_format	= GL_RED;
      }
      else if(p_img->bytes == 2)
      {
        internal_format = GL_RGB;
        pixel_format	= GL_RGB;
      }
      
      data = p_img->data;
    }
    
    
    // Load the texture into memory
    glTexImage2D(GL_TEXTURE_2D,
    		 0, 
  	  	 internal_format,
	  	 p_img->width, p_img->height,
		 0,
	  	 pixel_format,
	  	 GL_UNSIGNED_BYTE,
//		 p_img->data);
	  	 data);
    
    /* Store the texture ID for easy cleanup */
    m_allocated_textures.push_back(texture_object);
    
    return texture_object;
}

GLuint gl_Lib::update_tex_obj(Image * p_img, Pixel * p_pixels, GLuint p_tex_obj)
{
    GLuint texture_object = p_tex_obj;
    GLint  internal_format = GL_RGBA;
    GLint  pixel_format    = GL_RGBA;
    
    // Remove the old object
    glDeleteTextures(1, &p_tex_obj);
    
    // Create a texture object
    // glGenTextures( 1, &texture_object );
    glBindTexture(GL_TEXTURE_2D, texture_object);

    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE );
     
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Switch formats if neccessary
    if(p_pixels == NULL)
    {
      if(p_img->bytes <= 1)
      {
        internal_format = GL_INTENSITY8;
        pixel_format	= GL_RED;
      }
      else if(p_img->bytes == 2)
      {
        internal_format = GL_RGB;
        pixel_format	= GL_RGB;
      }
    }
    
    // Load the texture into memory
    glTexImage2D(GL_TEXTURE_2D,
    		 0, 
  	  	 internal_format,
	  	 p_img->width, p_img->height,
		 0,
	  	 pixel_format,
	  	 GL_UNSIGNED_BYTE,
//		 p_img->data);
	  	 p_pixels);
    
    /* Store the texture ID for easy cleanup */
    m_allocated_textures.push_back(texture_object);
    
    return texture_object;
}

void gl_Lib::free_image(Image * p_img)
{
    stbi_image_free(p_img->data);
}

Vertex* gl_Lib::gen_plane(int width, int height)
{  
  Vertex * vertices = new Vertex[ 4 ];
  vertices[0] = *(new Vertex(0,      0,		 0));
  vertices[1] = *(new Vertex(width,  0,		 0));
  vertices[2] = *(new Vertex(0,	     0,     height));
  vertices[3] = *(new Vertex(width,  0,     height));
  
  vertices[0].tX = 0.0; vertices[0].tY = 0.0;
  vertices[1].tX = 1.0; vertices[1].tY = 0.0;
  vertices[2].tX = 0.0; vertices[2].tY = 1.0;
  vertices[3].tX = 1.0; vertices[3].tY = 1.0;
  
  return vertices;
}

Vertex* gl_Lib::gen_vertices( Vertex * pVertices, int pNumberVertices, 
		      int p_grid_width, int &pActualVertices)
{
  int width  = p_grid_width;
  int height = pNumberVertices / p_grid_width;
  
  int number_triangles= (width - 1) * (height - 1) * 2;
  int number_vertices = number_triangles * 3;
  Vertex * vertices = new Vertex[number_vertices];
  int vert_index = 0;
  
  for(int i = 0; i < number_triangles; i++)
  {
    int x = (i/2) % (width - 1);
    int y = (i/2) / (width - 1);
    
    if (i % 2 == 0)
    { 
      vertices[vert_index++] = pVertices[x + y * (width)];
      vertices[vert_index++] = pVertices[x + (y+1) * (width)];
      vertices[vert_index++] = pVertices[x + 1 + y * (width)];
    }
    else
    {
      vertices[vert_index++] = pVertices[x + 1 + (y+1) * (width)];
      vertices[vert_index++] = pVertices[x + (y+1) * (width)];
      vertices[vert_index++] = pVertices[x + y * (width) + 1]; 
    }
  }
  
  pActualVertices = number_vertices;
  return vertices;
}

GLuint gl_Lib::gen_vbo( Vertex* pVertices, int pNumberVertices )
{
  GLuint pVertexBufferObj;
  
  /* Generate a buffer object, and bind it with the data */
  glGenBuffers(1, &pVertexBufferObj);
  glBindBuffer(GL_ARRAY_BUFFER, pVertexBufferObj);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * pNumberVertices, pVertices, 										GL_STATIC_DRAW);
  
  /* Tell OpenGL we're now done providing it our data */
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  
  /* We're now done with the data in CPU memory, so we can remove it */
  delete [] pVertices;
  
  /* Store the VBO in a local vector, to support cleanup operations */
  m_allocated_vbos.push_back(pVertexBufferObj);
  
  /* Finally, return a new Model */
  return pVertexBufferObj;
}

void gl_Lib::CleanUp()
{
  glDeleteTextures(m_allocated_textures.size(), &m_allocated_textures[0]);
  m_allocated_textures.clear();
  
  glDeleteBuffers(m_allocated_vbos.size(), &m_allocated_vbos[0]);
  m_allocated_vbos.clear();
}

void gl_Lib::Keyboard(unsigned char c, int x, int y)
{
    if(c == 27)
    {
      glutDestroyWindow( 0 );
      exit(0);
    }
    mInstance->keyPressed(c,x,y);
    if(m_2D) glutSwapBuffers();
    if(m_2D) glutPostRedisplay();
}

void gl_Lib::Menu( int entry )
{
    mInstance->menuItemSelected(entry);
}

void gl_Lib::AddMenuEntry( int id, std::string text )
{
    glutAddMenuEntry(text.c_str(), id);
}


void gl_Lib::RenderText2D( void * font, std::string text, int x, int y )
{
   glMatrixMode(GL_PROJECTION);
   glPushMatrix();
   glLoadIdentity();
   gluOrtho2D(0.0, 800, 0.0, 800);

   glMatrixMode(GL_MODELVIEW);
   glPushMatrix();
   glLoadIdentity();
   
      glColor3f(0.1f, 0.2f, 1.0f); 
      glRasterPos2f(x, WIN_HEIGHT - y);

      glutBitmapString(font, (const unsigned char*)text.c_str());
    
   glMatrixMode(GL_MODELVIEW);
   glPopMatrix();

   glMatrixMode(GL_PROJECTION);
   glPopMatrix();
   glMatrixMode(GL_MODELVIEW);
}
