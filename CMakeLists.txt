cmake_minimum_required (VERSION 3.8)
project ("CMakeProject1")

set(CMAKE_CXX_STANDARD 20)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_image CONFIG REQUIRED)
find_package(SDL2_ttf CONFIG REQUIRED)
find_package(OpenGL REQUIRED)

find_package(Lua REQUIRED)
find_package(sol2 CONFIG REQUIRED)

find_package(yaml-cpp CONFIG REQUIRED)

# Add source to this project's executable.
add_executable (CMakeProject1 "src/main.cpp"    "src/Window.cpp" "src/Window.h" "src/CShape.h"  "src/EntityManager.h" "src/EntityManager.cpp" "src/Entity.h" "src/Entity.cpp"  "src/Engine.h" "src/Engine.cpp" "src/Vector2.cpp" "src/Vector2.h" "src/CTransform.h"  "src/Color.h" "src/CCollision.h" "src/CScore.h" "src/CLifespan.h" "src/CInput.h" "src/Random.h"    "src/Scenes/Scene.h" "src/Assets.h" "src/sdl/Texture.h" "src/sdl/Texture.cpp" "src/sdl/Sprite.h"  "src/Scenes/GeometryWarsScene.h" "src/Camera.h" "src/Scenes/GeometryWarsScene.cpp"  "src/Scenes/MenuScene.h" "src/Scenes/MenuScene.cpp" "src/Action.h" "src/ActionManager.h" "src/ActionManager.cpp" "src/sdl/Text.h" "src/sdl/Text.cpp" "src/CText.h" "src/SceneManager.h" "src/SceneManager.cpp" "src/Scenes/MegamarioScene.h" "src/Scenes/MegamarioScene.cpp")

target_link_libraries(CMakeProject1
    PRIVATE
    $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
    $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
)
target_link_libraries(CMakeProject1 PRIVATE $<IF:$<TARGET_EXISTS:SDL2_image::SDL2_image>,SDL2_image::SDL2_image,SDL2_image::SDL2_image-static>)
target_link_libraries(CMakeProject1 PRIVATE $<IF:$<TARGET_EXISTS:SDL2_ttf::SDL2_ttf>,SDL2_ttf::SDL2_ttf,SDL2_ttf::SDL2_ttf-static>)
target_link_libraries(CMakeProject1 PRIVATE OpenGL::GL)

target_include_directories(CMakeProject1 PRIVATE ${LUA_INCLUDE_DIR})
target_link_libraries(CMakeProject1 PRIVATE ${LUA_LIBRARIES})
target_link_libraries(CMakeProject1 PRIVATE sol2)

target_link_libraries(CMakeProject1 PRIVATE yaml-cpp::yaml-cpp)

# Copy Lua scripts to the build directory where the executable is generated
add_custom_command(TARGET CMakeProject1 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/scripts
    $<TARGET_FILE_DIR:CMakeProject1>/scripts)

# Copy config files
add_custom_command(TARGET CMakeProject1 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/config
    $<TARGET_FILE_DIR:CMakeProject1>/config)

# Copy assets
add_custom_command(TARGET CMakeProject1 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets
    $<TARGET_FILE_DIR:CMakeProject1>/assets)
