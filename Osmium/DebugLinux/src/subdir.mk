################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/block.c \
../src/bmodel.c \
../src/entity.c \
../src/gui.c \
../src/ingame.c \
../src/inventory.c \
../src/json.c \
../src/main.c \
../src/models.c \
../src/nbt.c \
../src/network.c \
../src/render.c \
../src/world.c \
../src/xstring.c 

OBJS += \
./src/block.o \
./src/bmodel.o \
./src/entity.o \
./src/gui.o \
./src/ingame.o \
./src/inventory.o \
./src/json.o \
./src/main.o \
./src/models.o \
./src/nbt.o \
./src/network.o \
./src/render.o \
./src/world.o \
./src/xstring.o 

C_DEPS += \
./src/block.d \
./src/bmodel.d \
./src/entity.d \
./src/gui.d \
./src/ingame.d \
./src/inventory.d \
./src/json.d \
./src/main.d \
./src/models.d \
./src/nbt.d \
./src/network.d \
./src/render.d \
./src/world.d \
./src/xstring.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -std=gnu11 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


