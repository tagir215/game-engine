##
## Use C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE ENGINE_INC_FILES "include/**/*.h")
file(GLOB_RECURSE ENGINE_SRC_FILES "src/*.cpp" "src/**/*.cpp" "src/*.c")
file(GLOB ASSET_HEADERS "assets/basicShapes/*.h")
file(GLOB ASSET_SOURCES "assets/basicShapes/*.cpp")

add_library(engine ${ENGINE_INC_FILES} ${ENGINE_SRC_FILES} ${ASSET_HEADERS} ${ASSET_SOURCES})

target_link_libraries(engine PUBLIC sfml-graphics PUBLIC glm PUBLIC glfw PUBLIC tinyxml2)
target_include_directories(engine PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include> 
  ${GLFW_SOURCE_DIR}/deps
  ${PROJECT_SOURCE_DIR}/ext/stb-master}
)

file(GLOB TEST_SOURCES "test/*.cpp")
file(GLOB TEST_HEADERS "test/*.h")

# TESTIT
add_executable(engine_tests ${TEST_HEADERS} ${TEST_SOURCES})
target_link_libraries(engine_tests PRIVATE engine)
