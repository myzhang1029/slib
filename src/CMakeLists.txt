aux_source_directory(. LIBFILES)

add_library(sbl_static STATIC ${LIBFILES})
target_include_directories(sbl_static PRIVATE ${CMAKE_BINARY_DIR})
target_compile_options(sbl_static PRIVATE "-DHAVE_CONFIG_H=1")
set_target_properties(sbl_static PROPERTIES
    OUTPUT_NAME sbl)

add_library(sbl SHARED ${LIBFILES})
target_include_directories(sbl PRIVATE ${CMAKE_BINARY_DIR})
target_compile_options(sbl PRIVATE "-DHAVE_CONFIG_H=1")
set_target_properties(sbl PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
    OUTPUT_NAME sbl)

if (NOT WIN32)
    # Only use same names for shared/static if not Windows
    set_target_properties(sbl_static PROPERTIES OUTPUT_NAME sbl)
endif()

include(GNUInstallDirs)
install(TARGETS sbl
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(TARGETS sbl_static
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})
