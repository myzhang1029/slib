aux_source_directory(. LIBFILES)
add_library(sbl ${LIBFILES})
set_target_properties(sbl PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR})
target_include_directories(sbl PRIVATE ${CMAKE_BINARY_DIR})
target_compile_options(sbl PRIVATE "-DHAVE_CONFIG_H=1")

include(GNUInstallDirs)
install(TARGETS sbl DESTINATION ${CMAKE_INSTALL_LIBDIR})
