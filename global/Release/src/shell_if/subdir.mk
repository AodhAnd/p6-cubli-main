################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../src/shell_if/shell_client.o \
../src/shell_if/shell_server.o 

CPP_SRCS += \
../src/shell_if/set.cpp \
../src/shell_if/shell_client.cpp \
../src/shell_if/shell_server.cpp \
../src/shell_if/test.cpp 

OBJS += \
./src/shell_if/set.o \
./src/shell_if/shell_client.o \
./src/shell_if/shell_server.o \
./src/shell_if/test.o 

CPP_DEPS += \
./src/shell_if/set.d \
./src/shell_if/shell_client.d \
./src/shell_if/shell_server.d \
./src/shell_if/test.d 


# Each subdirectory must supply rules for building sources it contributes
src/shell_if/%.o: ../src/shell_if/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	arm-linux-gnueabi-g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<" 
	@echo 'Finished building: $<'
	@echo ' '


