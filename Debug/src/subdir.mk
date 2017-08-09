################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/AbstractEventHandle.cpp \
../src/Acceptor.cpp \
../src/Epoll_Demultiplexer.cpp \
../src/Global.cpp \
../src/NetWorking.cpp \
../src/Reactor.cpp \
../src/ReactorImp.cpp \
../src/RedisProxy.cpp \
../src/SocketEventHandle.cpp 

OBJS += \
./src/AbstractEventHandle.o \
./src/Acceptor.o \
./src/Epoll_Demultiplexer.o \
./src/Global.o \
./src/NetWorking.o \
./src/Reactor.o \
./src/ReactorImp.o \
./src/RedisProxy.o \
./src/SocketEventHandle.o 

CPP_DEPS += \
./src/AbstractEventHandle.d \
./src/Acceptor.d \
./src/Epoll_Demultiplexer.d \
./src/Global.d \
./src/NetWorking.d \
./src/Reactor.d \
./src/ReactorImp.d \
./src/RedisProxy.d \
./src/SocketEventHandle.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I../include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


