# CMakeList.txt : CMake project for main, include source and define
# project specific logic here.
#

# Add source to this project's executable.
set(GLAD_GL "${GLFW_SOURCE_DIR}/deps/glad/gl.h" "${GLFW_SOURCE_DIR}/deps/glad_gl.c")
add_executable (main "main_project1.cpp"    "application.h" "application.cpp" ${GLAD_GL} "game/gameobject.h" "game/gameobject.cpp"  "shader/shader.h" "shader/shader.cpp"  "game/camera.h" "texture_components/texture.h" "texture_components/texture.cpp" "texture_components/texturefactory.h" "texture_components/texturefactory.cpp" "texture_components/texturestorage.h"  "texture_components/playerkeyframes.h" "texture_components/playerkeyframes.cpp" "texture_components/keyframes.h" "components/transform.h" "systems/renderer.h" "systems/renderer.cpp" "components/mesh.h" "components/mesh.cpp" "input/inputmanager.h" "input/inputmanager.cpp" "systems/systembase.h" "systems/playerbehavior.h" "systems/playerbehavior.cpp" "util/transformer.h" "util/transformer.cpp" "systems/gravitysystem.h" "systems/gravitysystem.cpp" "components/mass.h" "game/gameobject_factories/gameobjectfactory.h" "game/gameobject_factories/playerfactory.h" "game/gameobject_factories/playerfactory.cpp" "components/velocity.h" "scenes/level1.h" "scenes/level.h" "scenes/level.cpp" "scenes/level1.cpp" "systems/movementsystem.h" "systems/movementsystem.cpp"   "scenes/levelfactory.h"  "scenes/level1factory.h" "scenes/level1factory.cpp" "components/shaderinfo.h")

target_link_libraries(main PUBLIC glfw PUBLIC glm)


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET main PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
