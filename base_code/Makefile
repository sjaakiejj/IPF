# plugin.make

# first name a variable objects for all object files

name = rank_filtering
sources = *.cpp
objects = *.o

#OpenGL Libs
OGL_CFLAGS=-DGL_GLEXT_PROTOTYPES
OGL_LDFLAGS=-lGL -lglut -lGLU -lGLEW

#main linking
CFLAGS= -I/usr/X11R6/include -I/usr/local/include -I/usr/include
LDFLAGS= -ldl -fPIC -lqad_gl -lipf $(OGL_LDFLAGS)

LIBFLAGS= $(OGL_CFLAGS)
LIBSOURCES= 

# now give target as lab1 with objects as variable dependencies + command line

$(name): $(objects)
	g++ $(LIBFLAGS) -o $(name) $(objects) $(LDFLAGS) 
	rm $(objects)
	
# list the dependencies for object files - those header files which help build objects

# how to build all object files from all dependent source files


$(objects): $(sources)
	g++ -c $(CFLAGS) $(sources)

clean:
	rm *.bck
	rm $(objects)
	
