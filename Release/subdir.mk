################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Intersection.cpp \
../MultiPoly.cpp \
../Point.cpp \
../Polygon.cpp \
../Rectangle.cpp \
../Segment.cpp \
../Shape.cpp \
../ShapeHandler.cpp \
../Union.cpp \
../main.cpp 

OBJS += \
./Intersection.o \
./MultiPoly.o \
./Point.o \
./Polygon.o \
./Rectangle.o \
./Segment.o \
./Shape.o \
./ShapeHandler.o \
./Union.o \
./main.o 

CPP_DEPS += \
./Intersection.d \
./MultiPoly.d \
./Point.d \
./Polygon.d \
./Rectangle.d \
./Segment.d \
./Shape.d \
./ShapeHandler.d \
./Union.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


