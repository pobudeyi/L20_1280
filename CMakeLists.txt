project(RinLink-L20)
cmake_minimum_required(VERSION 3.6)

#---------------------------------------------------------------------------------------
# Options
#---------------------------------------------------------------------------------------

# Allow switching of target platform
set(BOARD_LIST nucleo-l476rg linktag)
set(BOARD linktag CACHE STRING "Default target platform is linktag")
set_property(CACHE BOARD PROPERTY STRINGS ${BOARD_LIST})
# Allow switching of Applications
set(APPLICATION_LIST L20 linkwan pingpong peripheral_test factory_mode rx-sense tx-cw BootLoader unittest)
set(APPLICATION L20 CACHE STRING "Default Application is L20")
#set(APPLICATION factory_mode CACHE STRING "factory_mode")
set_property(CACHE APPLICATION PROPERTY STRINGS ${APPLICATION_LIST})

# Allow switching of MBED shields

# Allow switching of pingpong modulation

# Allow switching of active region

# Allow selection of region

# Switch for USB-Uart support, enable it for some Applications who needs it.

#---------------------------------------------------------------------------------------
# Target Boards
#---------------------------------------------------------------------------------------


    add_definitions(-DSTM32L433xx)
    add_definitions(-DUSE_HAL_DRIVER)
    set(MCU_CHIP "STM32L433CC")
    set(LINKER_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/STM32L433CCTx_FLASH.ld)
    #set(DEVICE_SVD ${CMAKE_CURRENT_SOURCE_DIR}/STM32L4x3.svd)
    include(stm32l4)
    # Build platform specific board implementation
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Drivers)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Middlewares)
    # Configure radio
    #set(RADIO sx1262 CACHE INTERNAL "Radio sx1262 selected")

#---------------------------------------------------------------------------------------
# Applications
#---------------------------------------------------------------------------------------

if(APPLICATION STREQUAL L20)

    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)

elseif(APPLICATION STREQUAL linkwan)

    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/apps/${APPLICATION})

elseif(APPLICATION STREQUAL pingpong)

    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/apps/${APPLICATION})

elseif(APPLICATION STREQUAL rx-sense)

    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/apps/${APPLICATION})

elseif(APPLICATION STREQUAL tx-cw)

    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/apps/${APPLICATION})

elseif(APPLICATION STREQUAL factory_mode)

    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/apps/${APPLICATION})

elseif(APPLICATION STREQUAL peripheral_test)

    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/apps/${APPLICATION})

elseif(APPLICATION STREQUAL rx-sensi)

    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/apps/rx-sensi)

elseif(APPLICATION STREQUAL tx-cw)

    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/apps/tx-cw)

elseif(APPLICATION STREQUAL BootLoader)

    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/apps/BootLoader)

elseif(APPLICATION STREQUAL unittest)

    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/ut)

endif()

#---------------------------------------------------------------------------------------
# Copy python scripts and prebuilt firmware
#---------------------------------------------------------------------------------------

#---------------------------------------------------------------------------------------
# General Components
#---------------------------------------------------------------------------------------

#add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Drivers)
#add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Src)

message(STATUS "-----------------Configuration-------------------")
message(STATUS "Host: " ${CMAKE_HOST_SYSTEM_NAME})
message(STATUS "Chip: " ${MCU_CHIP})
message(STATUS "Board: " ${BOARD})

message(STATUS "Application: " ${APPLICATION})

message(STATUS "-------------------------------------------------")
