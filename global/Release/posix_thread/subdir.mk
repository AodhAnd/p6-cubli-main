################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../src/posix_thread/posix_thread.o 

CPP_SRCS += \
../src/posix_thread/posix_thread.cpp \
../src/posix_thread/test.cpp 

OBJS += \
./src/posix_thread/posix_thread.o \
./src/posix_thread/test.o 

CPP_DEPS += \
./src/posix_thread/posix_thread.d \
./src/posix_thread/test.d 


# Each subdirectory must supply rules for building sources it contributes
src/posix_thread/%.o: ../src/posix_thread/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	arm-linux-gnueabi-g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


