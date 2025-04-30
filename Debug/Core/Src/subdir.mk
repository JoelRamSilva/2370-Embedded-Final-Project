################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/Button_Driver.c \
../Core/Src/Button_Task.c \
../Core/Src/Capacitor.c \
../Core/Src/Collision.c \
../Core/Src/Difficulty.c \
../Core/Src/Display_Task.c \
../Core/Src/Enemy.c \
../Core/Src/Gyro_Driver.c \
../Core/Src/LCD_Driver.c \
../Core/Src/Main_Menu.c \
../Core/Src/Railgun.c \
../Core/Src/Shield.c \
../Core/Src/fonts.c \
../Core/Src/freertos.c \
../Core/Src/main.c \
../Core/Src/pwm.c \
../Core/Src/stm32f4xx_hal_msp.c \
../Core/Src/stm32f4xx_it.c \
../Core/Src/stmpe811.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f4xx.c 

OBJS += \
./Core/Src/Button_Driver.o \
./Core/Src/Button_Task.o \
./Core/Src/Capacitor.o \
./Core/Src/Collision.o \
./Core/Src/Difficulty.o \
./Core/Src/Display_Task.o \
./Core/Src/Enemy.o \
./Core/Src/Gyro_Driver.o \
./Core/Src/LCD_Driver.o \
./Core/Src/Main_Menu.o \
./Core/Src/Railgun.o \
./Core/Src/Shield.o \
./Core/Src/fonts.o \
./Core/Src/freertos.o \
./Core/Src/main.o \
./Core/Src/pwm.o \
./Core/Src/stm32f4xx_hal_msp.o \
./Core/Src/stm32f4xx_it.o \
./Core/Src/stmpe811.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f4xx.o 

C_DEPS += \
./Core/Src/Button_Driver.d \
./Core/Src/Button_Task.d \
./Core/Src/Capacitor.d \
./Core/Src/Collision.d \
./Core/Src/Difficulty.d \
./Core/Src/Display_Task.d \
./Core/Src/Enemy.d \
./Core/Src/Gyro_Driver.d \
./Core/Src/LCD_Driver.d \
./Core/Src/Main_Menu.d \
./Core/Src/Railgun.d \
./Core/Src/Shield.d \
./Core/Src/fonts.d \
./Core/Src/freertos.d \
./Core/Src/main.d \
./Core/Src/pwm.d \
./Core/Src/stm32f4xx_hal_msp.d \
./Core/Src/stm32f4xx_it.d \
./Core/Src/stmpe811.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f4xx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/Button_Driver.cyclo ./Core/Src/Button_Driver.d ./Core/Src/Button_Driver.o ./Core/Src/Button_Driver.su ./Core/Src/Button_Task.cyclo ./Core/Src/Button_Task.d ./Core/Src/Button_Task.o ./Core/Src/Button_Task.su ./Core/Src/Capacitor.cyclo ./Core/Src/Capacitor.d ./Core/Src/Capacitor.o ./Core/Src/Capacitor.su ./Core/Src/Collision.cyclo ./Core/Src/Collision.d ./Core/Src/Collision.o ./Core/Src/Collision.su ./Core/Src/Difficulty.cyclo ./Core/Src/Difficulty.d ./Core/Src/Difficulty.o ./Core/Src/Difficulty.su ./Core/Src/Display_Task.cyclo ./Core/Src/Display_Task.d ./Core/Src/Display_Task.o ./Core/Src/Display_Task.su ./Core/Src/Enemy.cyclo ./Core/Src/Enemy.d ./Core/Src/Enemy.o ./Core/Src/Enemy.su ./Core/Src/Gyro_Driver.cyclo ./Core/Src/Gyro_Driver.d ./Core/Src/Gyro_Driver.o ./Core/Src/Gyro_Driver.su ./Core/Src/LCD_Driver.cyclo ./Core/Src/LCD_Driver.d ./Core/Src/LCD_Driver.o ./Core/Src/LCD_Driver.su ./Core/Src/Main_Menu.cyclo ./Core/Src/Main_Menu.d ./Core/Src/Main_Menu.o ./Core/Src/Main_Menu.su ./Core/Src/Railgun.cyclo ./Core/Src/Railgun.d ./Core/Src/Railgun.o ./Core/Src/Railgun.su ./Core/Src/Shield.cyclo ./Core/Src/Shield.d ./Core/Src/Shield.o ./Core/Src/Shield.su ./Core/Src/fonts.cyclo ./Core/Src/fonts.d ./Core/Src/fonts.o ./Core/Src/fonts.su ./Core/Src/freertos.cyclo ./Core/Src/freertos.d ./Core/Src/freertos.o ./Core/Src/freertos.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/pwm.cyclo ./Core/Src/pwm.d ./Core/Src/pwm.o ./Core/Src/pwm.su ./Core/Src/stm32f4xx_hal_msp.cyclo ./Core/Src/stm32f4xx_hal_msp.d ./Core/Src/stm32f4xx_hal_msp.o ./Core/Src/stm32f4xx_hal_msp.su ./Core/Src/stm32f4xx_it.cyclo ./Core/Src/stm32f4xx_it.d ./Core/Src/stm32f4xx_it.o ./Core/Src/stm32f4xx_it.su ./Core/Src/stmpe811.cyclo ./Core/Src/stmpe811.d ./Core/Src/stmpe811.o ./Core/Src/stmpe811.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32f4xx.cyclo ./Core/Src/system_stm32f4xx.d ./Core/Src/system_stm32f4xx.o ./Core/Src/system_stm32f4xx.su

.PHONY: clean-Core-2f-Src

