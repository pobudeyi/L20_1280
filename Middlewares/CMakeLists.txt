project(rtos)
cmake_minimum_required(VERSION 3.6)
enable_language(ASM)

#---------------------------------------------------------------------------------------
# Target
#---------------------------------------------------------------------------------------

list(APPEND ${PROJECT_NAME}_SOURCES
"${CMAKE_CURRENT_SOURCE_DIR}/Third_Party/FreeRTOS/Source/croutine.c"
"${CMAKE_CURRENT_SOURCE_DIR}/Third_Party/FreeRTOS/Source/event_groups.c"
"${CMAKE_CURRENT_SOURCE_DIR}/Third_Party/FreeRTOS/Source/list.c"
"${CMAKE_CURRENT_SOURCE_DIR}/Third_Party/FreeRTOS/Source/queue.c"
"${CMAKE_CURRENT_SOURCE_DIR}/Third_Party/FreeRTOS/Source/tasks.c"
"${CMAKE_CURRENT_SOURCE_DIR}/Third_Party/FreeRTOS/Source/timers.c"
"${CMAKE_CURRENT_SOURCE_DIR}/Third_Party/FreeRTOS/Source/CMSIS_RTOS/cmsis_os.c"
"${CMAKE_CURRENT_SOURCE_DIR}/Third_Party/FreeRTOS/Source/portable/MemMang/heap_4.c"
"${CMAKE_CURRENT_SOURCE_DIR}/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F/port.c"
)

add_library(${PROJECT_NAME} OBJECT EXCLUDE_FROM_ALL ${${PROJECT_NAME}_SOURCES})

#target_compile_definitions(${PROJECT_NAME} PUBLIC -DUSE_HAL_DRIVER -DUSE_STM32L4XX_NUCLEO -DNTAG_2k)

# Add define if debbuger support is enabled
#target_compile_definitions(${PROJECT_NAME} PUBLIC $<$<BOOL:${USE_DEBUGGER}>:USE_DEBUGGER>)

# Get the current working branch

# Get the latest abbreviated commit hash of the working branch

target_include_directories(
${PROJECT_NAME} PUBLIC
${CMAKE_CURRENT_SOURCE_DIR}/Third_Party/FreeRTOS/Source/include
${CMAKE_CURRENT_SOURCE_DIR}/../inc
${CMAKE_CURRENT_SOURCE_DIR}/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F
${CMAKE_CURRENT_SOURCE_DIR}/Third_Party/FreeRTOS/Source/CMSIS_RTOS
${CMAKE_CURRENT_SOURCE_DIR}/../Drivers/CMSIS/Include
)

set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD 11)
