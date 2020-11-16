cmake_minimum_required(VERSION 3.0)

# Extract version from general.h
file(READ include/slib/general.h GENERAL_H)
string(REGEX MATCH "SBLLIB_VERSION [0-9]+\n" VER_MAJOR ${GENERAL_H})
string(REGEX MATCH "[0-9]+" VER_MAJOR ${VER_MAJOR})
string(REGEX MATCH "SBLLIB_MINOR [0-9]+\n" VER_MINOR ${GENERAL_H})
string(REGEX MATCH "[0-9]+" VER_MINOR ${VER_MINOR})
string(REGEX MATCH "SBLLIB_PATCHLEVEL [0-9]+\n" VER_PL ${GENERAL_H})
string(REGEX MATCH "[0-9]+" VER_PL ${VER_PL})

project(libsbl VERSION ${VER_MAJOR}.${VER_MINOR}.${VER_PL}
    LANGUAGES "C")
set(PROJECT_DESCRIPTION "A C library providing many useful operations")

include(GNUInstallDirs)
include(CheckIncludeFiles)
include(CheckFunctionExists)
include(CheckLibraryExists)
include(CheckTypeSize)

enable_testing()
include_directories(include)
add_subdirectory(src)
add_subdirectory(test)

add_executable(sbltool sbltool.c)
target_link_libraries(sbltool sbl)
check_library_exists(m sin "" HAVE_LIBM)
if (HAVE_LIBM)
    target_link_libraries(sbltool m)
endif()

# checks
check_include_files(alloca.h HAVE_ALLOCA_H)
check_include_files(fcntl.h HAVE_FCNTL_H)
check_include_files(stdbool.h HAVE_STDBOOL_H)
check_include_files(stdint.h HAVE_STDINT_H)
check_include_files(termios.h HAVE_TERMIOS_H)
check_include_files(unistd.h HAVE_UNISTD_H)
check_function_exists(alloca HAVE_ALLOCA)
check_type_size(size_t SIZE_T)
check_type_size(intptr_t INTPTR_T)
if(NOT SIZE_T)
    set(size_t int)
endif()
if(NOT INTPTR_T)
    set(intptr_t int)
endif()

if(NOABRT)
    set(S_NOABRT on)
else()
    set(S_NOABRT 0)
endif()

# pkg-config file
configure_file(sbl.pc.in sbl.pc @ONLY)

# config.h
configure_file(config.h.cm config.h)
set(CMAKE_CPP_FLAGS "-DHAVE_CONFIG_H")

# distclean target
add_custom_target(distclean
    ${CMAKE_BUILD_TOOL} clean
    COMMAND ${CMAKE_COMMAND} -D "subdirs=.\;src\;test" -P
    ${CMAKE_SOURCE_DIR}/cmake/distclean.cmake)
# uninstall target    
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/uninstall.cmake"
    IMMEDIATE @ONLY)
add_custom_target(uninstall
    COMMAND "${CMAKE_COMMAND}" -P "${CMAKE_CURRENT_BINARY_DIR}/uninstall.cmake")

install(TARGETS sbltool DESTINATION ${CMAKE_INSTALL_BINDIR})
install(FILES include/slib.h DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(DIRECTORY include/slib DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(FILES ${CMAKE_BINARY_DIR}/sbl.pc
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig)
set(CPACK_INSTALL_CMAKE_PROJECT_NAME "libsbl")
include(CPack)
