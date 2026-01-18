# =============================================================================
# PLCOpen 嵌入式运行时 - CMake 主构建配置
# =============================================================================
# 项目: plcopen-runtime-py
# 版本: 1.0.0
# 描述: 嵌入式PLCOpen运行时，支持PID和一阶惯性功能块
# =============================================================================

cmake_minimum_required(VERSION 3.20)

project(plcopen_runtime
    VERSION 1.0.0
    DESCRIPTION "嵌入式PLCOpen运行时环境"
    LANGUAGES C
)

# =============================================================================
# 编译选项
# =============================================================================

# C标准
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# 默认构建类型
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "构建类型" FORCE)
endif()

# 编译警告
if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-Wall -Wextra -Wpedantic -Werror=return-type)
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        add_compile_options(-g -O0)
    else()
        add_compile_options(-O2)
    endif()
elseif(MSVC)
    add_compile_options(/W4 /utf-8)
endif()

# =============================================================================
# 平台检测与条件编译
# =============================================================================

option(BUILD_FOR_ARM "为ARM Cortex-M4目标构建" OFF)
option(BUILD_PYTHON_EXTENSION "构建Python C扩展模块" ON)
option(BUILD_TESTS "构建单元测试" ON)
option(BUILD_BENCHMARKS "构建性能基准测试" OFF)
option(ENABLE_FLOAT_POINT "启用浮点运算（ARM硬件浮点）" ON)

# 平台检测逻辑
if(BUILD_FOR_ARM)
    message(STATUS "目标平台: ARM Cortex-M4")

    # 设置交叉编译标志
    set(CMAKE_CROSSCOMPILING ON)
    set(PLCOPEN_TARGET_ARM ON)
    add_compile_definitions(PLCOPEN_ARM_TARGET=1)

    # ARM特定编译选项
    if(ENABLE_FLOAT_POINT)
        # 使用硬件浮点单元 (FPU)
        add_compile_options(-mfloat-abi=hard -mfpu=fpv4-sp-d16)
        add_compile_definitions(PLCOPEN_HAS_FPU=1)
    else()
        # 软件浮点模拟
        add_compile_options(-mfloat-abi=soft)
        add_compile_definitions(PLCOPEN_HAS_FPU=0)
    endif()

    # Cortex-M4特定优化
    add_compile_options(-mcpu=cortex-m4 -mthumb)

    # ARM目标不构建Python扩展（嵌入式环境）
    if(BUILD_PYTHON_EXTENSION)
        message(WARNING "ARM目标不支持Python扩展，已自动禁用")
        set(BUILD_PYTHON_EXTENSION OFF)
    endif()

    # ARM目标不构建测试（在宿主机运行）
    if(BUILD_TESTS)
        message(WARNING "ARM目标不构建测试，请在X86宿主机运行测试")
        set(BUILD_TESTS OFF)
    endif()
else()
    # X86/本地平台
    set(PLCOPEN_TARGET_ARM OFF)
    add_compile_definitions(PLCOPEN_ARM_TARGET=0)
    add_compile_definitions(PLCOPEN_HAS_FPU=1)

    # 检测处理器架构
    if(CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64|AMD64")
        message(STATUS "目标平台: X86_64 ${CMAKE_SYSTEM_NAME}")
        add_compile_definitions(PLCOPEN_X86_64=1)
    elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "i686|i386")
        message(STATUS "目标平台: X86_32 ${CMAKE_SYSTEM_NAME}")
        add_compile_definitions(PLCOPEN_X86_32=1)
    else()
        message(STATUS "目标平台: ${CMAKE_SYSTEM_NAME} ${CMAKE_SYSTEM_PROCESSOR}")
    endif()
endif()

# =============================================================================
# 依赖查找
# =============================================================================

if(BUILD_PYTHON_EXTENSION)
    find_package(Python3 REQUIRED COMPONENTS Interpreter Development)
    message(STATUS "Python版本: ${Python3_VERSION}")
    message(STATUS "Python库: ${Python3_LIBRARIES}")
    message(STATUS "Python头文件: ${Python3_INCLUDE_DIRS}")
endif()

# =============================================================================
# 头文件路径
# =============================================================================

include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/src
)

# =============================================================================
# 功能块静态库
# =============================================================================

add_library(plcopen_fb STATIC
    src/fb/pid.c
    src/fb/first_order.c
    src/fb/fb_registry.c
    src/common/error.c
    src/common/log.c
)

# 需要 -fPIC 以便链接到 Python 共享扩展模块
set_target_properties(plcopen_fb PROPERTIES POSITION_INDEPENDENT_CODE ON)

target_include_directories(plcopen_fb PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)

# =============================================================================
# Python C扩展模块
# =============================================================================

if(BUILD_PYTHON_EXTENSION)
    Python3_add_library(plcopen MODULE
        src/python/plcopen_module.c
        src/python/py_pid.c
        src/python/py_first_order.c
    )

    target_link_libraries(plcopen PRIVATE plcopen_fb)
    target_include_directories(plcopen PRIVATE ${Python3_INCLUDE_DIRS})

    # 设置输出目录
    set_target_properties(plcopen PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/plcopen
    )
endif()

# =============================================================================
# 单元测试 (Unity框架)
# =============================================================================

if(BUILD_TESTS)
    enable_testing()

    # 下载Unity测试框架
    include(FetchContent)
    FetchContent_Declare(
        unity
        GIT_REPOSITORY https://github.com/ThrowTheSwitch/Unity.git
        GIT_TAG v2.6.0
        GIT_SHALLOW TRUE
    )
    FetchContent_MakeAvailable(unity)

    # PID单元测试
    add_executable(test_pid
        tests/unit/c/test_pid.c
    )
    target_link_libraries(test_pid PRIVATE plcopen_fb unity)
    add_test(NAME test_pid COMMAND test_pid)

    # 一阶惯性单元测试
    add_executable(test_first_order
        tests/unit/c/test_first_order.c
    )
    target_link_libraries(test_first_order PRIVATE plcopen_fb unity m)
    add_test(NAME test_first_order COMMAND test_first_order)
endif()

# =============================================================================
# 性能基准测试
# =============================================================================

if(BUILD_BENCHMARKS)
    add_executable(bench_pid tests/benchmark/bench_pid.c)
    target_link_libraries(bench_pid PRIVATE plcopen_fb)

    add_executable(bench_first_order tests/benchmark/bench_first_order.c)
    target_link_libraries(bench_first_order PRIVATE plcopen_fb)

    add_executable(bench_memory tests/benchmark/bench_memory.c)
    target_link_libraries(bench_memory PRIVATE plcopen_fb)
endif()

# =============================================================================
# 安装规则
# =============================================================================

install(TARGETS plcopen_fb
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
)

install(DIRECTORY include/plcopen
    DESTINATION include
)

if(BUILD_PYTHON_EXTENSION)
    install(TARGETS plcopen
        LIBRARY DESTINATION ${Python3_SITEARCH}
    )
endif()

# =============================================================================
# 构建信息摘要
# =============================================================================

message(STATUS "")
message(STATUS "========== 构建配置摘要 ==========")
message(STATUS "构建类型:        ${CMAKE_BUILD_TYPE}")
message(STATUS "C编译器:         ${CMAKE_C_COMPILER}")
message(STATUS "ARM目标:         ${BUILD_FOR_ARM}")
message(STATUS "Python扩展:      ${BUILD_PYTHON_EXTENSION}")
message(STATUS "单元测试:        ${BUILD_TESTS}")
message(STATUS "基准测试:        ${BUILD_BENCHMARKS}")
message(STATUS "==================================")
message(STATUS "")
