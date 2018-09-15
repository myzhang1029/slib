cmake_minimum_required(VERSION 3.0)
include(GNUInstallDirs)

project(libsbl VERSION 3.7.0
    DESCRIPTION "A C library providing many useful operations")
include_directories(include)
add_subdirectory(src)

configure_file(sbl.pc.in sbl.pc @ONLY)

add_custom_target(distclean
    COMMAND ${CMAKE_BUILD_TOOL} clean
    COMMAND ${CMAKE_COMMAND} -P
        ${CMAKE_SOURCE_DIR}/cmake/distclean.cmake
    COMMAND ${CMAKE_COMMAND} -DRUNNING_DIR=src -P
        ${CMAKE_SOURCE_DIR}/cmake/distclean.cmake)
    add_custom_target(uninstall
        COMMAND ${CMAKE_SOURCE_DIR}/cmake/uninstall.sh)
install(FILES include/slib.h DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(DIRECTORY include/slib DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(FILES ${CMAKE_BINARY_DIR}/sbl.pc
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig)
