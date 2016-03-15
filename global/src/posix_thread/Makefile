VPATH =
CXX = g++-4.6
CXXFLAGS = -Wall -g3 
LDLIBS = -lpthread
DEPS = posix_thread.hpp
OBJ = posix_thread.o test.o

%.o: %.cpp $(DEPS)
	$(CXX) $(CFLAGS) -c -o $@ $<

test: $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDLIBS)
    
clean:
	rm -rf *.o

	
