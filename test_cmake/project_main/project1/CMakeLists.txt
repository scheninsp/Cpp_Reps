project(project1)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

include(GNUInstallDirs)

set(SOURCES 
    ${PROJECT_SOURCE_DIR}/Source/a.cpp)

include_directories(Include)

file(GLOB_RECURSE PROJECT1_HEADERS Include/**.h)
source_group("Headers" FILES ${PROJECT1_HEADERS})

add_library(project1 ${SOURCES} ${PROJECT1_HEADERS})

set(BUILD_FLAGS "-DMY_MACRO" )
set_target_properties(project1 PROPERTIES COMPILE_FLAGS ${BUILD_FLAGS})

# set_target_properties(project1 PROPERTIES DEBUG_POSTFIX -d)
set_target_properties(project1 PROPERTIES
    CXX_STANDARD 17
    PREFIX ""
    SOVERSION ${SOVERSION}
    VERSION ${LIB_VERSION}
    COMPILE_PDB_NAME "project1"
)

install(TARGETS project1
	RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
	ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
	LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
	)