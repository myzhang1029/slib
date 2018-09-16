aux_source_directory(. LIBFILES)
add_library(sbl ${LIBFILES})
set_target_properties(sbl PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
    COMPILE_FLAGS "-O3")

add_library(sbl_g ${LIBFILES})
set_target_properties(sbl_g PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
    COMPILE_FLAGS "-g -O0")

include(GNUInstallDirs)
install(TARGETS sbl DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(TARGETS sbl_g DESTINATION ${CMAKE_INSTALL_LIBDIR})
