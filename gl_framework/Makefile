sources = lib/*.cpp
objects = *.o

filename=libqad_gl.so

LIB_DIR=/usr/local/lib
INC_DIR=/usr/local/include

#OpenGL Libs
OGL_CFLAGS=-DGL_GLEXT_PROTOTYPES
OGL_LDFLAGS=-lGL -lglut -lGLU -lGLEW

#main linking
CFLAGS= -Wall -fPIC -c
LDFLAGS=-ldl $(OGL_LDFLAGS) -lipf

LIBFLAGS= $(OGL_CFLAGS) -shared -Wl,-soname,libqad_gl.so.1
LIBSOURCES= 

libs: $(sources)
	g++ $(LIBFLAGS) -c $(sources)
	g++ -shared -o $(filename).1.0 $(objects) -ldl -rdynamic  
	rm $(objects)
#	g++ $(LIBFLAGS) -o $(filename) $(libobjects) -ldl -fPIC -shared 

install: $(libs)
	cp $(filename).1.0 $(LIB_DIR)/$(filename).1.0
	mkdir -p $(INC_DIR)/QaD_GL
	cp -rf lib/*.h $(INC_DIR)/QaD_GL
	ln -sf $(LIB_DIR)/$(filename).1.0 $(LIB_DIR)/$(filename)
	ln -sf $(LIB_DIR)/$(filename).1.0 $(LIB_DIR)/$(filename).1
	
uninstall:
	rm -rf /usr/include/QaD_GL
	rm -f $(LIB_DIR)/$(filename)

clean:
	rm *.bck
	rm $(objects)
	
