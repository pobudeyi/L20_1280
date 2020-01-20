##
##   ______                              _
##  / _____)             _              | |
## ( (____  _____ ____ _| |_ _____  ____| |__
##  \____ \| ___ |    (_   _) ___ |/ ___)  _ \
##  _____) ) ____| | | || |_| ____( (___| | | |
## (______/|_____)_|_|_| \__)_____)\____)_| |_|
## (C)2013-2017 Semtech
##  ___ _____ _   ___ _  _____ ___  ___  ___ ___
## / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
## \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
## |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
## embedded.connectivity.solutions.==============
##
## License:  Revised BSD License, see LICENSE.TXT file included in the project
## Authors:  Johannes Bruder ( STACKFORCE ), Miguel Luis ( Semtech )
##
##
## CMake arm-none-eabi binutils integration and helper functions
##


#---------------------------------------------------------------------------------------
# Set tools
#---------------------------------------------------------------------------------------
set(CMAKE_OBJCOPY ${TOOLCHAIN_BIN_DIR}/${TOOLCHAIN}-objcopy${TOOLCHAIN_EXT})
set(CMAKE_OBJDUMP ${TOOLCHAIN_BIN_DIR}/${TOOLCHAIN}-objdump${TOOLCHAIN_EXT})
set(CMAKE_SIZE ${TOOLCHAIN_BIN_DIR}/${TOOLCHAIN}-size${TOOLCHAIN_EXT})

#set(CMAKE_MERGE_FIRMWARWE ${PYTHON} ${CMAKE_BINARY_DIR}/src/apps/${APPLICATION}/firmware_merge.py)

#---------------------------------------------------------------------------------------
# Prints the section sizes
#---------------------------------------------------------------------------------------
function(print_section_sizes TARGET)
    add_custom_command(TARGET ${TARGET} POST_BUILD COMMAND ${CMAKE_SIZE} ${TARGET})
endfunction()

#---------------------------------------------------------------------------------------
# Creates output in hex format
#---------------------------------------------------------------------------------------
function(create_hex_output TARGET)
    add_custom_target(${TARGET}.hex ALL DEPENDS ${TARGET} COMMAND ${CMAKE_OBJCOPY} -Oihex ${TARGET} ${TARGET}.hex)
endfunction()

#---------------------------------------------------------------------------------------
# Creates output in binary format
#---------------------------------------------------------------------------------------
function(create_bin_output TARGET)
    add_custom_target(${TARGET}.bin ALL DEPENDS ${TARGET} COMMAND ${CMAKE_OBJCOPY} -Obinary ${TARGET} ${TARGET}.bin)
endfunction()

#---------------------------------------------------------------------------------------
# Creates binary with header
#---------------------------------------------------------------------------------------
# function(create_bin_with_boot TARGET)
#     add_custom_target(TARGET1 ALL DEPENDS ${TARGET}.bin COMMAND ${CMAKE_MERGE_FIRMWARWE} -b bootloader_no_secure_no_ota.bin -t ${TARGET} -o 0)
#     add_custom_target(TARGET2 ALL DEPENDS ${TARGET}.bin COMMAND ${CMAKE_MERGE_FIRMWARWE} -b bootloader_no_secure.bin -t ${TARGET} -o 0)
#     add_custom_target(TARGET3 ALL DEPENDS ${TARGET}.bin COMMAND ${CMAKE_MERGE_FIRMWARWE} -b bootloader_with_secure.bin -t ${TARGET} -o 1)
# endfunction()
