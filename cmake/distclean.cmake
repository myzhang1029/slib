set(cmake_generated
    ${CMAKE_BINARY_DIR}/${RUNNING_DIR}/CMakeCache.txt
    ${CMAKE_BINARY_DIR}/${RUNNING_DIR}/cmake_install.cmake
    ${CMAKE_BINARY_DIR}/${RUNNING_DIR}/install_manifest.txt
    ${CMAKE_BINARY_DIR}/${RUNNING_DIR}/Makefile
    ${CMAKE_BINARY_DIR}/${RUNNING_DIR}/CTestTestfile.cmake
    ${CMAKE_BINARY_DIR}/${RUNNING_DIR}/rules.ninja
    ${CMAKE_BINARY_DIR}/${RUNNING_DIR}/build.ninja
    ${CMAKE_BINARY_DIR}/${RUNNING_DIR}/.ninja_deps
    ${CMAKE_BINARY_DIR}/${RUNNING_DIR}/.ninja_log
    ${CMAKE_BINARY_DIR}/${RUNNING_DIR}/CMakeFiles
    ${CMAKE_BINARY_DIR}/${RUNNING_DIR}/Testing
    ${CMAKE_BINARY_DIR}/${RUNNING_DIR}/sbl.pc
    ${CMAKE_BINARY_DIR}/${RUNNING_DIR}/testdrv.h
    ${CMAKE_BINARY_DIR}/${RUNNING_DIR}/config.h
)
foreach(file ${cmake_generated})
    if (EXISTS ${file})
        message(STATUS "Removing file " ${file})
        file(REMOVE_RECURSE ${file})
    endif()
endforeach(file)

# if running dir is not . and is empty, delete it
if (RUNNING_DIR AND NOT RUNNING_DIR EQUAL "."
        AND NOT RUNNING_DIR EQUAL "./"
        AND NOT RUNNING_DIR EQUAL "")
    string(CONCAT PATT ${RUNNING_DIR} "/*")
    file(GLOB RES ${PATT})
    list(LENGTH RES RES_LEN)
    if(RES_LEN EQUAL 0)
        file(REMOVE_RECURSE ${RUNNING_DIR})
    endif()
endif()
