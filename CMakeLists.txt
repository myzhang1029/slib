cmake_minimum_required(VERSION 2.6)
project(sbl)

# version 3.7.0
set(libsbl_VERSION_MAJOR 3)
set(libsbl_VERSION_MINOR 7)

include_directories(include)
aux_source_directory(src LIBFILES)
add_library(sbl ${LIBFILES})

install(TARGETS sbl DESTINATION lib)
install(FILES include/slib.h DESTINATION include)
install(DIRECTORY include/slib DESTINATION include)
