project(project2)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

include(GNUInstallDirs)

set(SOURCES 
    ${PROJECT_SOURCE_DIR}/Source/b.cpp)

file(GLOB_RECURSE PROJECT2_HEADERS Include/**.h)
source_group("Headers2" FILES ${PROJECT2_HEADERS})

file(GLOB_RECURSE PROJECT1_HEADERS ${PROJECT_ROOT_FOLDER}/project1/Include/**.h)
source_group("Headers1" FILES ${PROJECT1_HEADERS})

include_directories(Include ${PROJECT_ROOT_FOLDER}/project1/Include)


message(PROJECT_ROOT_FOLDER="${PROJECT_ROOT_FOLDER}")

add_library(project2 ${SOURCES} ${PROJECT1_HEADERS} ${PROJECT2_HEADERS})

target_link_libraries(project2 project1)

set(BUILD_FLAGS "-DMY_MACRO" )
set_target_properties(project2 PROPERTIES COMPILE_FLAGS ${BUILD_FLAGS})

# set_target_properties(project2 PROPERTIES DEBUG_POSTFIX -d)
set_target_properties(project2 PROPERTIES
    CXX_STANDARD 17
    PREFIX ""
    SOVERSION ${SOVERSION}
    VERSION ${LIB_VERSION}
    COMPILE_PDB_NAME "project2"
)

install(TARGETS project2
	RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
	ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
	LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
	)