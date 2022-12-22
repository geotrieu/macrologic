################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../stm32-ws2812b/ws2812b.c 

OBJS += \
./stm32-ws2812b/ws2812b.o 

C_DEPS += \
./stm32-ws2812b/ws2812b.d 


# Each subdirectory must supply rules for building sources it contributes
stm32-ws2812b/%.o stm32-ws2812b/%.su: ../stm32-ws2812b/%.c stm32-ws2812b/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../stm32-ws2812b -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-stm32-2d-ws2812b

clean-stm32-2d-ws2812b:
	-$(RM) ./stm32-ws2812b/ws2812b.d ./stm32-ws2812b/ws2812b.o ./stm32-ws2812b/ws2812b.su

.PHONY: clean-stm32-2d-ws2812b

