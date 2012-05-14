
#include "Program.h"
#include <string>
#include <QaD_GL/stb_image.h>

int main(int p_argc, char ** p_argv)
{
  Program program;
  
  if(p_argc > 1)
  {		  
  
    int width, height, n;
    unsigned char * data = stbi_load(p_argv[1], &width, &height, &n, 4);
    stbi_image_free(data);
    float asp_x = width / (double)height;
  
    Program::Init(p_argc, p_argv, 600 * asp_x, 600, 
  		  "Rank Filtering", &program, true);
		  
    program.load(std::string(p_argv[1]));
    
    Program::AddMenuEntry(1, "Original Image");
    Program::AddMenuEntry(2, "Rank Filtering: First");
    Program::AddMenuEntry(3, "Rank Filtering: Last");
    Program::AddMenuEntry(4, "Rank Filtering: Median");
  
    Program::Start();
    
    Program::CleanUp();
  }
  else
  {
    std::cout << "Please supply an image" << std::endl;
  }
  
}
