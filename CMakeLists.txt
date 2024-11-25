cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

project ("CMakeProject1" VERSION 0.0.1 LANGUAGES CXX)


add_executable (main "src/main.cpp"    "src/Window.cpp" "src/EntityManager.cpp" "src/Entity.cpp" "src/Engine.cpp" "src/sdl/Texture.cpp" "src/Scenes/GeometryWarsScene.cpp" "src/Scenes/MenuScene.cpp" "src/ActionManager.cpp" "src/sdl/Text.cpp" "src/SceneManager.cpp" "src/Scenes/MegamarioScene.cpp" "src/Physics.cpp")

target_compile_features(main PRIVATE cxx_std_23)
target_include_directories(main PRIVATE "./include")

if(MSVC)
    target_compile_options(main PRIVATE
        /permissive- /W4 /w14640
    )
else()
    target_compile_options(main PRIVATE
        -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic
    )
endif()

find_package(plog CONFIG REQUIRED)
target_link_libraries(main PRIVATE plog::plog)

find_package(SDL2 CONFIG REQUIRED)
target_link_libraries(main
    PRIVATE
    $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
    $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
)

find_package(SDL2_image CONFIG REQUIRED)
target_link_libraries(main PRIVATE $<IF:$<TARGET_EXISTS:SDL2_image::SDL2_image>,SDL2_image::SDL2_image,SDL2_image::SDL2_image-static>)

find_package(SDL2_ttf CONFIG REQUIRED)
target_link_libraries(main PRIVATE $<IF:$<TARGET_EXISTS:SDL2_ttf::SDL2_ttf>,SDL2_ttf::SDL2_ttf,SDL2_ttf::SDL2_ttf-static>)

find_package(OpenGL REQUIRED)
target_link_libraries(main PRIVATE OpenGL::GL)

find_package(Lua REQUIRED)
target_include_directories(main PRIVATE ${LUA_INCLUDE_DIR})
target_link_libraries(main PRIVATE ${LUA_LIBRARIES})

find_package(sol2 CONFIG REQUIRED)
target_link_libraries(main PRIVATE sol2)

find_package(yaml-cpp CONFIG REQUIRED)
target_link_libraries(main PRIVATE yaml-cpp::yaml-cpp)

# Copy Lua scripts to the build directory where the executable is generated
add_custom_command(TARGET main POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/scripts
    $<TARGET_FILE_DIR:main>/scripts)

# Copy config files
add_custom_command(TARGET main POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/config
    $<TARGET_FILE_DIR:main>/config)

# Copy assets
add_custom_command(TARGET main POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets
    $<TARGET_FILE_DIR:main>/assets)
