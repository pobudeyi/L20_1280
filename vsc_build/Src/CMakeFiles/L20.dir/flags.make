# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.14

# compile ASM with D:/software/gcc-arm-none-eabi-7-2017-q4-major-win32/bin/arm-none-eabi-gcc.exe
# compile C with D:/software/gcc-arm-none-eabi-7-2017-q4-major-win32/bin/arm-none-eabi-gcc.exe
ASM_FLAGS = -Os -g -mthumb -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -Wall  -ffunction-sections -fdata-sections -fomit-frame-pointer -mabi=aapcs -fno-unroll-loops -ffast-math -ftree-vectorize -Wl,--defsym=SE_APP_SetSecParameter=0x08001655 -Wl,--defsym=SE_APP_GetSecParameter=0x0800167b -x assembler-with-cpp  -g -Wall  

ASM_DEFINES = -DSTM32L433xx -DUSE_HAL_DRIVER

ASM_INCLUDES = E:\code\L20\L20_1280\Src\sx1280 E:\code\L20\L20_1280\Src\BMA2x2 E:\code\L20\L20_1280\Src\..\inc E:\code\L20\L20_1280\Src\..\Drivers\CMSIS\Include E:\code\L20\L20_1280\Src\..\Middlewares\Third_Party\FreeRTOS\Source\CMSIS_RTOS E:\code\L20\L20_1280\Src\..\Middlewares\Third_Party\FreeRTOS\Source\portable\GCC\ARM_CM4F E:\code\L20\L20_1280\Src\..\Middlewares\Third_Party\FreeRTOS\Source\include E:\code\L20\L20_1280\Drivers\STM32L4xx_HAL_Driver\Inc E:\code\L20\L20_1280\Drivers\STM32L4xx_HAL_Driver\Inc\Legacy E:\code\L20\L20_1280\Drivers\CMSIS\Device\ST\STM32L4xx\Include E:\code\L20\L20_1280\Drivers\CMSIS\Include E:\code\L20\L20_1280\Drivers\..\inc 

C_FLAGS = -Os -g -mthumb -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -Wall  -ffunction-sections -fdata-sections -fomit-frame-pointer -mabi=aapcs -fno-unroll-loops -ffast-math -ftree-vectorize -Wl,--defsym=SE_APP_SetSecParameter=0x08001655 -Wl,--defsym=SE_APP_GetSecParameter=0x0800167b -std=c99  -Og -g -Wall   -std=gnu11

C_DEFINES = -DSTM32L433xx -DUSE_HAL_DRIVER

C_INCLUDES = -IE:\code\L20\L20_1280\Src\sx1280 -IE:\code\L20\L20_1280\Src\BMA2x2 -IE:\code\L20\L20_1280\Src\..\inc -IE:\code\L20\L20_1280\Src\..\Drivers\CMSIS\Include -IE:\code\L20\L20_1280\Src\..\Middlewares\Third_Party\FreeRTOS\Source\CMSIS_RTOS -IE:\code\L20\L20_1280\Src\..\Middlewares\Third_Party\FreeRTOS\Source\portable\GCC\ARM_CM4F -IE:\code\L20\L20_1280\Src\..\Middlewares\Third_Party\FreeRTOS\Source\include -IE:\code\L20\L20_1280\Drivers\STM32L4xx_HAL_Driver\Inc -IE:\code\L20\L20_1280\Drivers\STM32L4xx_HAL_Driver\Inc\Legacy -IE:\code\L20\L20_1280\Drivers\CMSIS\Device\ST\STM32L4xx\Include -IE:\code\L20\L20_1280\Drivers\CMSIS\Include -IE:\code\L20\L20_1280\Drivers\..\inc 

