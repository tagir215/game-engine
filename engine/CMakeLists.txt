##
## Use C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE ENGINE_INC_FILES "include/**/*.h")
file(GLOB_RECURSE ENGINE_SRC_FILES "src/**/*.cpp")

add_library(engine ${ENGINE_INC_FILES} ${ENGINE_SRC_FILES})

target_link_libraries(engine PUBLIC sfml-graphics PUBLIC glm PUBLIC glfw)
target_include_directories(engine PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include> 
  ${GLFW_SOURCE_DIR}/deps
)

