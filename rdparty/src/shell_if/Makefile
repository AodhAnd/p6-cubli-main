VPATH =
CXX = g++-4.3
CXXFLAGS = -Wall -g3 
LDLIBS = -lpthread
DEPS = shell_client.hpp  shell_server.hpp AauPwmLib.hpp
OBJ = shell_client.o shell_server.o AauPwmLib.o set.o

%.o: %.cpp $(DEPS)
	$(CXX) $(CFLAGS) -c -o $@ $<

test: $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDLIBS)

clean:
	rm -rf *.o

	
