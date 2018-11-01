cmake_minimum_required(VERSION 3.0)
include(GNUInstallDirs)
include(CheckIncludeFiles)
include(CheckFunctionExists)
include(CheckTypeSize)

project(libsbl VERSION 4.0.0
    LANGUAGES "C")
set(PROJECT_DESCRIPTION "A C library providing many useful operations")
enable_testing()
include_directories(include)
add_subdirectory(src)
add_subdirectory(test)

add_executable(sbltool sbltool.c)
target_link_libraries(sbltool sbl)
target_link_libraries(sbltool m)

# checks
check_include_files(alloca.h HAVE_ALLOCA_H)
check_include_files(fcntl.h HAVE_FCNTL_H)
check_include_files(termios.h HAVE_TERMIOS_H)
check_include_files(unistd.h HAVE_UNISTD_H)
check_function_exists(alloca HAVE_ALLOCA)
check_type_size(size_t SIZE_T)
if(NOT SIZE_T)
    set(size_t int)
endif()

# pkg-config file
configure_file(sbl.pc.in sbl.pc @ONLY)

# config.h
configure_file(config.h.in config.h)
set(CMAKE_CPP_FLAGS "-DHAVE_CONFIG_H")

# distclean target
add_custom_target(distclean
    COMMAND ${CMAKE_BUILD_TOOL} clean
    COMMAND ${CMAKE_COMMAND} -P
    ${CMAKE_SOURCE_DIR}/cmake/distclean.cmake
    COMMAND ${CMAKE_COMMAND} -DRUNNING_DIR=test -P
    ${CMAKE_SOURCE_DIR}/cmake/distclean.cmake
    COMMAND ${CMAKE_COMMAND} -DRUNNING_DIR=src -P
    ${CMAKE_SOURCE_DIR}/cmake/distclean.cmake)
# uninstall target    
add_custom_target(uninstall
    COMMAND ${CMAKE_SOURCE_DIR}/cmake/uninstall.sh)

install(TARGETS sbltool DESTINATION ${CMAKE_INSTALL_BINDIR})
install(FILES include/slib.h DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(DIRECTORY include/slib DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(FILES ${CMAKE_BINARY_DIR}/sbl.pc
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig)
