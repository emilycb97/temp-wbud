################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/MyEeprom.c \
../src/cr_startup_lpc17.c \
../src/eeprom.c \
../src/main.c \
../src/myAcc.c \
../src/myBarometr.c \
../src/myEmbededTemp.c \
../src/myJoystick.c \
../src/myLight.c \
../src/myOled.c \
../src/myRgb.c \
../src/myTemp.c 

OBJS += \
./src/MyEeprom.o \
./src/cr_startup_lpc17.o \
./src/eeprom.o \
./src/main.o \
./src/myAcc.o \
./src/myBarometr.o \
./src/myEmbededTemp.o \
./src/myJoystick.o \
./src/myLight.o \
./src/myOled.o \
./src/myRgb.o \
./src/myTemp.o 

C_DEPS += \
./src/MyEeprom.d \
./src/cr_startup_lpc17.d \
./src/eeprom.d \
./src/main.d \
./src/myAcc.d \
./src/myBarometr.d \
./src/myEmbededTemp.d \
./src/myJoystick.d \
./src/myLight.d \
./src/myOled.d \
./src/myRgb.d \
./src/myTemp.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__USE_CMSIS=CMSISv1p30_LPC17xx -D__CODE_RED -D__NEWLIB__ -I"C:\Users\student\Desktop\Rakieta - 10.06\Rakieta\Lib_CMSISv1p30_LPC17xx\inc" -I"C:\Users\student\Desktop\Rakieta - 10.06\Rakieta\Lib_EaBaseBoard\inc" -I"C:\Users\student\Desktop\Rakieta - 10.06\Rakieta\Lib_MCU\inc" -O0 -g3 -gdwarf-4 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m3 -mthumb -D__NEWLIB__ -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


