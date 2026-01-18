# =============================================================================
# PLCOpen 嵌入式运行时 - ARM Cortex-M4 交叉编译工具链
# =============================================================================
# 使用方法:
#   cmake -DCMAKE_TOOLCHAIN_FILE=cmake/toolchain-arm.cmake ..
# =============================================================================

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

# 工具链前缀
set(TOOLCHAIN_PREFIX arm-none-eabi-)

# 查找工具链
find_program(CMAKE_C_COMPILER ${TOOLCHAIN_PREFIX}gcc)
find_program(CMAKE_CXX_COMPILER ${TOOLCHAIN_PREFIX}g++)
find_program(CMAKE_ASM_COMPILER ${TOOLCHAIN_PREFIX}gcc)
find_program(CMAKE_AR ${TOOLCHAIN_PREFIX}ar)
find_program(CMAKE_OBJCOPY ${TOOLCHAIN_PREFIX}objcopy)
find_program(CMAKE_OBJDUMP ${TOOLCHAIN_PREFIX}objdump)
find_program(CMAKE_SIZE ${TOOLCHAIN_PREFIX}size)

# 验证工具链
if(NOT CMAKE_C_COMPILER)
    message(FATAL_ERROR "未找到ARM工具链，请安装 arm-none-eabi-gcc")
endif()

# Cortex-M4 编译选项
set(CPU_FLAGS "-mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard")

# 编译选项
set(CMAKE_C_FLAGS_INIT "${CPU_FLAGS} -ffunction-sections -fdata-sections")
set(CMAKE_C_FLAGS_DEBUG "-Og -g3 -DDEBUG")
set(CMAKE_C_FLAGS_RELEASE "-O2 -DNDEBUG")

# 链接选项
set(CMAKE_EXE_LINKER_FLAGS_INIT "-Wl,--gc-sections -specs=nosys.specs -specs=nano.specs")

# 禁用共享库（嵌入式不支持）
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
set(BUILD_SHARED_LIBS OFF)

# 查找程序时只在主机上查找
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# 查找库和头文件时只在目标环境查找
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

# ARM特定定义
add_definitions(-DARM_CORTEX_M4)
add_definitions(-DPLCOPEN_EMBEDDED)

message(STATUS "ARM Cortex-M4 交叉编译工具链已配置")
message(STATUS "  编译器: ${CMAKE_C_COMPILER}")
message(STATUS "  CPU选项: ${CPU_FLAGS}")
