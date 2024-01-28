# CMakeList.txt : CMake project for main, include source and define
# project specific logic here.
#

# Add source to this project's executable.
set(GLAD_GL "${GLFW_SOURCE_DIR}/deps/glad/gl.h" "${GLFW_SOURCE_DIR}/deps/glad_gl.c")
add_executable (main "main_project1.cpp"    "application.h" "application.cpp" ${GLAD_GL} "game/gameobject.h" "game/gameobject.cpp"  "shader/shader.h" "shader/shader.cpp"  "game/camera.h" "texture/texture.h" "texture/texture.cpp" "texture/texturefactory.h" "texture/texturefactory.cpp" "texture/texturestorage.h"  "texture/playerkeyframes.h" "texture/playerkeyframes.cpp" "texture/keyframes.h" "game/transform.h" "game/renderer.h" "game/renderer.cpp" "game/mesh.h" "game/mesh.cpp" "input/inputmanager.h" "input/inputmanager.cpp" "behaviors/systembase.h" "behaviors/playerbehavior.h" "behaviors/playerbehavior.cpp" "behaviors/transformer.h" "behaviors/transformer.cpp")

target_link_libraries(main PUBLIC glfw PUBLIC glm)


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET main PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
