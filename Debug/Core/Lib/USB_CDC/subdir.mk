################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Lib/USB_CDC/usbd_cdc.c \
../Core/Lib/USB_CDC/usbd_cdc_if.c 

OBJS += \
./Core/Lib/USB_CDC/usbd_cdc.o \
./Core/Lib/USB_CDC/usbd_cdc_if.o 

C_DEPS += \
./Core/Lib/USB_CDC/usbd_cdc.d \
./Core/Lib/USB_CDC/usbd_cdc_if.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Lib/USB_CDC/usbd_cdc.o: ../Core/Lib/USB_CDC/usbd_cdc.c Core/Lib/USB_CDC/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32L433xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/DFU/Inc -O0 -ffunction-sections -fdata-sections -Wall -Wextra -Wfatal-errors -pedantic -Wmissing-include-dirs -fstack-usage -MMD -MP -MF"Core/Lib/USB_CDC/usbd_cdc.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Lib/USB_CDC/usbd_cdc_if.o: ../Core/Lib/USB_CDC/usbd_cdc_if.c Core/Lib/USB_CDC/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32L433xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/DFU/Inc -O0 -ffunction-sections -fdata-sections -Wall -Wextra -Wfatal-errors -pedantic -Wmissing-include-dirs -fstack-usage -MMD -MP -MF"Core/Lib/USB_CDC/usbd_cdc_if.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

