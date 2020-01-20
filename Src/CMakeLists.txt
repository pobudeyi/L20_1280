project(L20)
cmake_minimum_required(VERSION 3.6)

#---------------------------------------------------------------------------------------
# Target
#---------------------------------------------------------------------------------------

file(GLOB ${PROJECT_NAME}_SOURCES
        "${CMAKE_CURRENT_LIST_DIR}/*.c"
        "${CMAKE_CURRENT_LIST_DIR}/sx1280/*.c"
)

add_executable(${PROJECT_NAME}
                            ${${PROJECT_NAME}_SOURCES}
                            $<TARGET_OBJECTS:driver>
							$<TARGET_OBJECTS:rtos>
)

#target_compile_definitions(${PROJECT_NAME} PRIVATE ACTIVE_REGION=${ACTIVE_REGION})
#add_definitions(-DASSERT_ENABLE)
#target_compile_definitions(${PROJECT_NAME} PUBLIC -DUSE_HAL_DRIVER -DUSE_STM32L4XX_NUCLEO -DNTAG_2k)
#add_definitions(-DUSE_SW_IIC)

#target_compile_definitions(${PROJECT_NAME}-${CLASS}  PUBLIC
#    $<BUILD_INTERFACE:$<TARGET_PROPERTY:mac,INTERFACE_COMPILE_DEFINITIONS>>
#)

target_include_directories(
    ${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/sx1280
    ${CMAKE_CURRENT_SOURCE_DIR}/../inc
    ${CMAKE_CURRENT_SOURCE_DIR}/../Drivers/CMSIS/Include
    ${CMAKE_CURRENT_SOURCE_DIR}/../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS
    ${CMAKE_CURRENT_SOURCE_DIR}/../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F
    ${CMAKE_CURRENT_SOURCE_DIR}/../Middlewares/Third_Party/FreeRTOS/Source/include
    $<BUILD_INTERFACE:$<TARGET_PROPERTY:driver,INTERFACE_INCLUDE_DIRECTORIES>>
    $<BUILD_INTERFACE:$<TARGET_PROPERTY:rtos>>
)

set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD 11)

#add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/linktag)

#---------------------------------------------------------------------------------------
# Debugging and Binutils
#---------------------------------------------------------------------------------------

include(debug-helper)
include(binutils-arm-none-eabi)

# Generate debugger configurations
generate_vscode_launch_cortex_debug(${PROJECT_NAME})

# Print section sizes of target
print_section_sizes(${PROJECT_NAME})

# Create output in hex and binary format
create_bin_output(${PROJECT_NAME})
create_hex_output(${PROJECT_NAME})
#create_bin_with_boot(${PROJECT_NAME})
