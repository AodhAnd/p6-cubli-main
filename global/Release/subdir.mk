################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../src/AauPwmLib.o \
../src/bbb_adc.o \
../src/bbb_gpio.o \
../src/i2c.o \
../src/imu.o \
../src/main.o \
../src/momentum_motor.o 

CPP_SRCS += \
../src/AauPwmLib.cpp \
../src/adc_dac.cpp \
../src/bbb_adc.cpp \
../src/bbb_gpio.cpp \
../src/i2c.cpp \
../src/imu.cpp \
../src/io_service.cpp \
../src/main.cpp \
../src/momentum_motor.cpp \
../src/parser.cpp \
../src/reverse_polish_notation_calculator.cpp \
../src/shunting_yard.cpp \
../src/thread.cpp 

OBJS += \
./src/AauPwmLib.o \
./src/adc_dac.o \
./src/bbb_adc.o \
./src/bbb_gpio.o \
./src/i2c.o \
./src/imu.o \
./src/io_service.o \
./src/main.o \
./src/momentum_motor.o \
./src/parser.o \
./src/reverse_polish_notation_calculator.o \
./src/shunting_yard.o \
./src/thread.o 

CPP_DEPS += \
./src/AauPwmLib.d \
./src/adc_dac.d \
./src/bbb_adc.d \
./src/bbb_gpio.d \
./src/i2c.d \
./src/imu.d \
./src/io_service.d \
./src/main.d \
./src/momentum_motor.d \
./src/parser.d \
./src/reverse_polish_notation_calculator.d \
./src/shunting_yard.d \
./src/thread.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	arm-linux-gnueabi-g++ -std=c++11 -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


