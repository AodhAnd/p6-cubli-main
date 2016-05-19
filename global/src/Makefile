VPATH = ../inc
#CXX = g++-4.6
CXX = arm-linux-gnueabihf-g++
CXXFLAGS = -std=c++11 -Wall -g3 
LDLIBS = -lpthread
DEPS = shell_if/shell_server.hpp shell_if/shell_client.hpp momentum_motor.hpp
DEPS += controller/controller_base.hpp
DEPS += controller/controller_factory.hpp
DEPS += controller/controller_test.hpp

OBJ = shell_if/shell_server.o shell_if/shell_client.o momentum_motor.o main.o
OBJ += controller/controller_base.o
OBJ += controller/controller_test.o
OBJ += controller/controller_factory.o

DEPS += posix_thread/posix_thread.hpp
OBJ += posix_thread/posix_thread.o


DEPS += controller/controller_code/rt_nonfinite.hpp
DEPS += controller/controller_code/rtGetInf.hpp
DEPS += controller/controller_code/rtGetNaN.hpp
DEPS += controller/controller_code/rtwtypes.hpp

OBJ  += controller/controller_code/rtGetNaN.o
OBJ  += controller/controller_code/rtGetInf.o
OBJ  += controller/controller_code/rt_nonfinite.o

DEPS += controller/controller_code/AAU3_DiscLinFeedback_types.hpp
DEPS += controller/controller_code/AAU3_DiscLinFeedback.hpp
OBJ  += controller/controller_code/AAU3_DiscLinFeedback.o

DEPS += controller/controller_code/AAU3_DiscLinObserver_types.hpp
DEPS += controller/controller_code/AAU3_DiscLinObserver.hpp
OBJ  += controller/controller_code/AAU3_DiscLinObserver.o

DEPS += controller/controller_code/AAU3_DiscSlidingModeController_types.hpp
DEPS += controller/controller_code/AAU3_DiscSlidingModeController.hpp
OBJ  += controller/controller_code/AAU3_DiscSlidingModeController.o

DEPS += controller/controller_code/AAU3_InOutLinearization.hpp
DEPS += controller/controller_code/AAU3_InOutLinearization_types.hpp
OBJ  += controller/controller_code/AAU3_InOutLinearization.o

DEPS += controller/controller_code/AAU3_DiscSlidingModeController_new.hpp
DEPS += controller/controller_code/AAU3_DiscSlidingModeController_new_types.hpp
OBJ  += controller/controller_code/AAU3_DiscSlidingModeController_new.o

DEPS += controller/controller_code/DiscreteLurenbergerEstimator_take2.h
DEPS += controller/controller_code/DiscreteLurenbergerEstimator_take2_types.h
OBJ  += controller/controller_code/DiscreteLurenbergerEstimator_take2.o

DEPS += controller/controller_code/AAU3_DiscLinFeedback2.hpp
OBJ  += controller/controller_code/AAU3_DiscLinFeedback2.o

DEPS += controller/controller_code/AAU3_DiscSISOTool.hpp
OBJ  += controller/controller_code/AAU3_DiscSISOTool.o

DEPS += controller/controller_code/AAU3_PController.hpp
OBJ  += controller/controller_code/AAU3_PController.o

DEPS += i2c.hpp
OBJ += i2c.o

DEPS += imu.hpp
OBJ += imu.o

DEPS += bbb_gpio.hpp
OBJ += bbb_gpio.o

DEPS += bbb_adc.hpp
OBJ += bbb_adc.o

DEPS += AauPwmLib.hpp
OBJ += AauPwmLib.o

%.o: %.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

main: $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDLIBS)
    
clean:
	rm -rf *.o
	rm -rf controller/*.o
	rm -rf shell_if/*.o
	rm -rf posix_thread/*.o

	

