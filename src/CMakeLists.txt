aux_source_directory(. LIBFILES)
add_library(sbl ${LIBFILES})
set_target_properties(sbl PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR})

include(GNUInstallDirs)
install(TARGETS sbl DESTINATION ${CMAKE_INSTALL_LIBDIR})
