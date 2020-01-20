# Get the path of this module
set(CURRENT_MODULE_DIR ${CMAKE_CURRENT_LIST_DIR})

#---------------------------------------------------------------------------------------
# Generates a Visual Studio Code launch configuration for debugging with openOCD.
#---------------------------------------------------------------------------------------
function(generate_vscode_launch_cortex_debug TARGET)
    get_target_property( TARGET_NAME ${TARGET} NAME )

    # Set the OPENOCD_TARGET and OPENOCD_INTERFACE variables according to BOARD
    if(BOARD STREQUAL nucleo-l476rg OR  BOARD STREQUAL linktag)
        configure_file(${CURRENT_MODULE_DIR}/launch.json-jlink.in ${CMAKE_SOURCE_DIR}/.vscode/launch.json @ONLY)
    else()
        message(STATUS "Unkown board seclected")
    endif()

    
endfunction()
