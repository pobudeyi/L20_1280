project(driver)
cmake_minimum_required(VERSION 3.6)
enable_language(ASM)

#---------------------------------------------------------------------------------------
# Target
#---------------------------------------------------------------------------------------

list(APPEND ${PROJECT_NAME}_SOURCES
"${CMAKE_CURRENT_SOURCE_DIR}/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_tim.c"
"${CMAKE_CURRENT_SOURCE_DIR}/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_tim_ex.c"
"${CMAKE_CURRENT_SOURCE_DIR}/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_uart.c"
"${CMAKE_CURRENT_SOURCE_DIR}/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_uart_ex.c"
"${CMAKE_CURRENT_SOURCE_DIR}/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal.c"
"${CMAKE_CURRENT_SOURCE_DIR}/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_i2c.c"
"${CMAKE_CURRENT_SOURCE_DIR}/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_i2c_ex.c"
"${CMAKE_CURRENT_SOURCE_DIR}/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_rcc.c"
"${CMAKE_CURRENT_SOURCE_DIR}/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_rcc_ex.c"
"${CMAKE_CURRENT_SOURCE_DIR}/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_flash.c"
"${CMAKE_CURRENT_SOURCE_DIR}/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_flash_ex.c"
"${CMAKE_CURRENT_SOURCE_DIR}/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_flash_ramfunc.c"
"${CMAKE_CURRENT_SOURCE_DIR}/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_gpio.c"
"${CMAKE_CURRENT_SOURCE_DIR}/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_dma.c"
"${CMAKE_CURRENT_SOURCE_DIR}/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_dma_ex.c"
"${CMAKE_CURRENT_SOURCE_DIR}/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_pwr.c"
"${CMAKE_CURRENT_SOURCE_DIR}/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_pwr_ex.c"
"${CMAKE_CURRENT_SOURCE_DIR}/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_cortex.c"
"${CMAKE_CURRENT_SOURCE_DIR}/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_exti.c"
"${CMAKE_CURRENT_SOURCE_DIR}/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_spi.c"
"${CMAKE_CURRENT_SOURCE_DIR}/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_spi_ex.c"
"${CMAKE_CURRENT_SOURCE_DIR}/../startup_stm32l433xx.s"
)

add_library(${PROJECT_NAME} OBJECT EXCLUDE_FROM_ALL ${${PROJECT_NAME}_SOURCES})

#target_compile_definitions(${PROJECT_NAME} PUBLIC -DUSE_HAL_DRIVER -DUSE_STM32L4XX_NUCLEO -DNTAG_2k)

# Add define if debbuger support is enabled
#target_compile_definitions(${PROJECT_NAME} PUBLIC $<$<BOOL:${USE_DEBUGGER}>:USE_DEBUGGER>)

# Get the current working branch

# Get the latest abbreviated commit hash of the working branch

target_include_directories(${PROJECT_NAME} PUBLIC
${CMAKE_CURRENT_SOURCE_DIR}/STM32L4xx_HAL_Driver/Inc
${CMAKE_CURRENT_SOURCE_DIR}/STM32L4xx_HAL_Driver/Inc/Legacy
${CMAKE_CURRENT_SOURCE_DIR}/CMSIS/Device/ST/STM32L4xx/Include
${CMAKE_CURRENT_SOURCE_DIR}/CMSIS/Include
${CMAKE_CURRENT_SOURCE_DIR}/../inc
)

set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD 11)
