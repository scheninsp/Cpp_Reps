project(project2)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

include(GNUInstallDirs)

message(CMAKE_MODULE_PATH="${CMAKE_MODULE_PATH}")
#must unset Python3_EXECUTABLE first when multiple python versions are installed
unset(Python3_EXECUTABLE)
set(Python3_EXECUTABLE "F:/venv/pybind_env/pybind_env/Scripts/python.exe")
#set(Python3_EXECUTABLE "C:/Python3.11.1/python.exe")
find_package(Python3 3.11 EXACT COMPONENTS Interpreter Development REQUIRED) 
message(Python3_EXECUTABLE="${Python3_EXECUTABLE}")
message(Python3_INCLUDE_DIRS="${Python3_INCLUDE_DIRS}")
message(Python3_LIBRARIES="${Python3_LIBRARIES}")
message(Python3_LIBRARY_DIRS="${Python3_LIBRARY_DIRS}")


find_package(pybind11 CONFIG REQUIRED)
message(PYBIND11_INCLUDE_DIR="${PYBIND11_INCLUDE_DIR}")

set(SOURCES 
    ${PROJECT_SOURCE_DIR}/Source/b.cpp)

file(GLOB_RECURSE PROJECT2_HEADERS Include/project2/*.h)
source_group("Headers2" FILES ${PROJECT2_HEADERS})

file(GLOB_RECURSE External_HEADERS ${PYBIND11_INCLUDE_DIR}/**.h)
source_group("pybind11" FILES ${External_HEADERS})

file(GLOB_RECURSE Python_HEADERS ${Python3_INCLUDE_DIRS}/**.h)
source_group("python" FILES ${Python_HEADERS})

file(GLOB_RECURSE PROJECT1_HEADERS ${PROJECT_ROOT_FOLDER}/project1/Include/**.h)
source_group("Headers1" FILES ${PROJECT1_HEADERS})

include_directories(Include ${PROJECT_ROOT_FOLDER}/project1/Include ${PYBIND11_INCLUDE_DIR} ${Python3_INCLUDE_DIRS})


message(PROJECT_ROOT_FOLDER="${PROJECT_ROOT_FOLDER}")

add_library(project2 SHARED ${SOURCES} ${PROJECT1_HEADERS} ${PROJECT2_HEADERS} ${External_HEADERS} ${Python_HEADERS})

link_directories(Python3_LIBRARY_DIRS)
target_link_libraries(project2 project1 pybind11::headers ${Python3_LIBRARIES})

pybind11_add_module(py_project2 ${PROJECT_SOURCE_DIR}/Source/b.cpp)

set(BUILD_FLAGS "-DMY_MACRO" )
set_target_properties(project2 PROPERTIES COMPILE_FLAGS ${BUILD_FLAGS})

set_target_properties(project2 PROPERTIES
    CXX_STANDARD 17
    PREFIX ""
	SUFFIX ".pyd"
    SOVERSION ${SOVERSION}
    VERSION ${LIB_VERSION}
    COMPILE_PDB_NAME "project2"
)

install(TARGETS project2
	RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
	ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
	LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
	)