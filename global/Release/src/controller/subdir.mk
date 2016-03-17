################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../src/controller/controller_base.o \
../src/controller/controller_factory.o \
../src/controller/controller_test.o 

CPP_SRCS += \
../src/controller/controller_base.cpp \
../src/controller/controller_factory.cpp \
../src/controller/controller_test.cpp 

OBJS += \
./src/controller/controller_base.o \
./src/controller/controller_factory.o \
./src/controller/controller_test.o 

CPP_DEPS += \
./src/controller/controller_base.d \
./src/controller/controller_factory.d \
./src/controller/controller_test.d 


# Each subdirectory must supply rules for building sources it contributes
src/controller/%.o: ../src/controller/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	arm-linux-gnueabi-g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


