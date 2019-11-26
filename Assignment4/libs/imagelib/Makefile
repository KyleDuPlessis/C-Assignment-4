# DPLKYL002
# Makefile in /libs/imagelib folder to compile a shared library

CPP=g++
CPPFLAGS=-fPIC -shared -std=c++11
LIBNAME=libimage.so

# first compile - create binary object files
%.o: %.cpp
	$(CPP) -c -o $@ $< $(CPPFLAGS)

# then link - link binary object files together to create the shared library
$(LIBNAME): Image.o Image.h
	$(CPP) -o $(LIBNAME) Image.o $(CPPFLAGS)

# other rules
# never submit binary object / shared object files
clean:
	@rm *.o *.so
