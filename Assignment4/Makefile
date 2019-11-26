# DPLKYL002
# Makefile in ./Assignment4_DPLKYL002 project folder to compile the driver and link it against the newly created shared libraries

CPP=g++ 
INCLUDES=-I./libs/imagelib
LIBDIRS=-L./libs/imagelib
LIBS= -limage
CPPFLAGS=-std=c++11 $(INCLUDES) $(LIBDIRS) $(LIBS)
TARGET=imageops

# first compile - IMPLICIT PATTERN RULE for creating binary object files
%.o: %.cpp
	$(CPP) -c -o $@ $< $(CPPFLAGS)

# then link - LINKING RULE for linking binary object files together to create an executable
$(TARGET): Driver.o 
	$(CPP) -o $(TARGET) Driver.o $(CPPFLAGS)
  
# other rules
Test.o: Test.cpp
		$(CPP) -c -o $@ $< $(CPPFLAGS)

Test: 
	make compile_test
	
compile_test:Test.o
		$(CPP) -o Test Test.o $(CPPFLAGS)


# never submit binary object / executable files
clean:
	@rm *.o imageops Test
	@rm ./libs/*.so
	cd ./libs/imagelib && make clean

# build entire project
all:
	
	cd ./libs/imagelib && make
	@cp -f ./libs/imagelib/*.so ./libs
	make
	make Test
