cmake_minimum_required (VERSION 3.8)
project ("CMakeProject1")

set(CMAKE_CXX_STANDARD 20)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

 set(LUA_SCRIPTS ${CMAKE_SOURCE_DIR}/lua/*)

find_package(SDL2 CONFIG REQUIRED)
find_package(OpenGL REQUIRED)

find_package(Lua REQUIRED)
find_package(sol2 CONFIG REQUIRED)


# Add source to this project's executable.
add_executable (CMakeProject1 "src/main.cpp"    "src/Window.cpp" "src/Window.h" "src/CShape.h"  "src/EntityManager.h" "src/EntityManager.cpp" "src/Entity.h" "src/Entity.cpp"  "src/Engine.h" "src/Engine.cpp" "src/Vector2.cpp" "src/Vector2.h" "src/CTransform.h"  "src/Color.h" "src/CCollision.h" "src/CScore.h" "src/CLifespan.h" "src/CInput.h" "src/Random.h" )

target_link_libraries(CMakeProject1
    PRIVATE
    $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
    $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
)
 target_link_libraries(CMakeProject1 PRIVATE OpenGL::GL)

 target_include_directories(CMakeProject1 PRIVATE ${LUA_INCLUDE_DIR})
 target_link_libraries(CMakeProject1 PRIVATE ${LUA_LIBRARIES})
 target_link_libraries(CMakeProject1 PRIVATE sol2)

# Copy Lua scripts to the build directory where the executable is generated
add_custom_command(TARGET CMakeProject1 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/lua
    $<TARGET_FILE_DIR:CMakeProject1>/lua)