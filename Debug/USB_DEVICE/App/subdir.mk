################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../USB_DEVICE/App/usb_device.c \
../USB_DEVICE/App/usbd_desc.c \
../USB_DEVICE/App/usbd_dfu_if.c 

OBJS += \
./USB_DEVICE/App/usb_device.o \
./USB_DEVICE/App/usbd_desc.o \
./USB_DEVICE/App/usbd_dfu_if.o 

C_DEPS += \
./USB_DEVICE/App/usb_device.d \
./USB_DEVICE/App/usbd_desc.d \
./USB_DEVICE/App/usbd_dfu_if.d 


# Each subdirectory must supply rules for building sources it contributes
USB_DEVICE/App/usb_device.o: ../USB_DEVICE/App/usb_device.c USB_DEVICE/App/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -Ddebug_sound_vibration -DSTM32L433xx -DDEBUG -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/DFU/Inc -O0 -ffunction-sections -fdata-sections -Wall -Wextra -Wfatal-errors -pedantic -Wmissing-include-dirs -fstack-usage -MMD -MP -MF"USB_DEVICE/App/usb_device.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
USB_DEVICE/App/usbd_desc.o: ../USB_DEVICE/App/usbd_desc.c USB_DEVICE/App/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -Ddebug_sound_vibration -DSTM32L433xx -DDEBUG -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/DFU/Inc -O0 -ffunction-sections -fdata-sections -Wall -Wextra -Wfatal-errors -pedantic -Wmissing-include-dirs -fstack-usage -MMD -MP -MF"USB_DEVICE/App/usbd_desc.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
USB_DEVICE/App/usbd_dfu_if.o: ../USB_DEVICE/App/usbd_dfu_if.c USB_DEVICE/App/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -Ddebug_sound_vibration -DSTM32L433xx -DDEBUG -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/DFU/Inc -O0 -ffunction-sections -fdata-sections -Wall -Wextra -Wfatal-errors -pedantic -Wmissing-include-dirs -fstack-usage -MMD -MP -MF"USB_DEVICE/App/usbd_dfu_if.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

