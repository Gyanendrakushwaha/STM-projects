################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ThirdParty/FreeRTOS/portable/MemMang/heap_4.c 

OBJS += \
./ThirdParty/FreeRTOS/portable/MemMang/heap_4.o 

C_DEPS += \
./ThirdParty/FreeRTOS/portable/MemMang/heap_4.d 


# Each subdirectory must supply rules for building sources it contributes
ThirdParty/FreeRTOS/portable/MemMang/%.o: ../ThirdParty/FreeRTOS/portable/MemMang/%.c ThirdParty/FreeRTOS/portable/MemMang/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F051x8 -c -I../Core/Inc -I"C:/Users/158184/STM32CubeIDE/workspace_1.7.0/07_RTOS_stm32f0Discovery/ThirdParty/FreeRTOS/portable" -I"C:/Users/158184/STM32CubeIDE/workspace_1.7.0/07_RTOS_stm32f0Discovery/ThirdParty/FreeRTOS" -I"C:/Users/158184/STM32CubeIDE/workspace_1.7.0/07_RTOS_stm32f0Discovery/ThirdParty/FreeRTOS/include" -I"C:/Users/158184/STM32CubeIDE/workspace_1.7.0/07_RTOS_stm32f0Discovery/ThirdParty/FreeRTOS/portable/GCC/ARM_CM0" -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

