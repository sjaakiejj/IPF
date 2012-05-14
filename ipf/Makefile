SRC_DIR = src

sources = $(SRC_DIR)/*.cpp
objects = *.o

filename=libipf.so
LIB_NAME=IPF

LIB_DIR=/usr/local/lib
INC_DIR=/usr/local/include

#OpenGL Libs
OGL_CFLAGS=-DGL_GLEXT_PROTOTYPES
OGL_LDFLAGS=-lGL -lglut -lGLU -lGLEW

#main linking
CFLAGS= -Wall -fPIC -c
LDFLAGS=-ldl $(OGL_LDFLAGS)

LIBFLAGS= $(OGL_CFLAGS) -shared -Wl,-soname,$(filename).1
LIBSOURCES= 

libs: $(sources)
	g++ $(LIBFLAGS) -c $(sources)
	g++ -shared -o $(filename).1.0 $(objects) -ldl -rdynamic  
	rm $(objects)
#	g++ $(LIBFLAGS) -o $(filename) $(libobjects) -ldl -fPIC -shared 

install: $(libs)
	cp $(filename).1.0 $(LIB_DIR)/$(filename).1.0
	mkdir -p $(INC_DIR)/$(LIB_NAME)
	cp -rf $(SRC_DIR)/*.h $(INC_DIR)/$(LIB_NAME)
	ln -sf $(LIB_DIR)/$(filename).1.0 $(LIB_DIR)/$(filename)
	ln -sf $(LIB_DIR)/$(filename).1.0 $(LIB_DIR)/$(filename).1
	ldconfig
	
uninstall:
	rm -rf $(INC_DIR)/$(LIB_NAME)
	rm -f $(LIB_DIR)/$(filename)

clean:
	rm *.bck
	rm $(objects)
	
