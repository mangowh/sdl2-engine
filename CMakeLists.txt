cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("CMakeProject1")

find_package(SDL2 CONFIG REQUIRED)
find_package(OpenGL REQUIRED)

# Add source to this project's executable.
add_executable (CMakeProject1 "src/main.cpp"    "src/Window.cpp" "src/Window.h" "src/CShape.h"  "src/EntityManager.h" "src/EntityManager.cpp" "src/Entity.h" "src/Entity.cpp"  "src/Engine.h" "src/Engine.cpp" "src/Vector2.cpp" "src/Vector2.h" "src/CTransform.h"  "src/Color.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET CMakeProject1 PROPERTY CXX_STANDARD 20)
endif()

target_link_libraries(CMakeProject1
    PRIVATE
    $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
    $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
)
 target_link_libraries(CMakeProject1 PRIVATE OpenGL::GL)

# TODO: Add tests and install targets if needed.
