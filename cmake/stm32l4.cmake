if(NOT DEFINED LINKER_SCRIPT)
message(FATAL_ERROR "No linker script defined")
endif(NOT DEFINED LINKER_SCRIPT)
message("Linker script: ${LINKER_SCRIPT}")


#---------------------------------------------------------------------------------------
# Set compiler/linker flags
#---------------------------------------------------------------------------------------
# Object build options
# -fno-builtin
#set(OBJECT_GEN_FLAGS "-mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard -Og -Wall -fdata-sections -ffunction-sections")
set(OBJECT_GEN_FLAGS "-Os -g -mthumb -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -Wall  -ffunction-sections -fdata-sections -fomit-frame-pointer -mabi=aapcs -fno-unroll-loops -ffast-math -ftree-vectorize -Wl,--defsym=SE_APP_SetSecParameter=0x08001655 -Wl,--defsym=SE_APP_GetSecParameter=0x0800167b")
set(CMAKE_C_FLAGS "${OBJECT_GEN_FLAGS} -std=c99 " CACHE INTERNAL "C Compiler options")
set(CMAKE_CXX_FLAGS "${OBJECT_GEN_FLAGS} -std=c++11 " CACHE INTERNAL "C++ Compiler options")
set(CMAKE_ASM_FLAGS "${OBJECT_GEN_FLAGS} -x assembler-with-cpp " CACHE INTERNAL "ASM Compiler options")

# Linker flags
#set(CMAKE_EXE_LINKER_FLAGS "-mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard --specs=nosys.specs -T${LINKER_SCRIPT} -Wl,-Map=${CMAKE_PROJECT_NAME}.map,--cref -Wl,--gc-sections" CACHE INTERNAL "Linker options")
set(CMAKE_EXE_LINKER_FLAGS "-Wl,--gc-sections --specs=nano.specs --specs=nosys.specs -mthumb -mcpu=cortex-m4  -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mabi=aapcs -T${LINKER_SCRIPT} -lc -lm -lnosys -Wl,-Map=${CMAKE_PROJECT_NAME}.map" CACHE INTERNAL "Linker options")
