################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/backupkey.c \
../src/cert.c \
../src/common.c \
../src/key.c \
../src/main.c \
../src/mtd.c 

OBJS += \
./src/backupkey.o \
./src/cert.o \
./src/common.o \
./src/key.o \
./src/main.o \
./src/mtd.o 

C_DEPS += \
./src/backupkey.d \
./src/cert.d \
./src/common.d \
./src/key.d \
./src/main.d \
./src/mtd.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	mipsel-linux-gcc -O0 -g3 -Wall -c -fmessage-length=0 -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


