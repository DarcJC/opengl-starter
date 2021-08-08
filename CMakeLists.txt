cmake_minimum_required(VERSION 3.20)
project(opengl_starter)

set(CMAKE_CXX_STANDARD 23)
set(GLSL_VALIDATOR "/usr/bin/glslangValidator")

file(GLOB_RECURSE GLSL_SOURCE_FILES "shaders/*.glsl")

foreach(GLSL ${GLSL_SOURCE_FILES})
    get_filename_component(FILE_NAME ${GLSL} NAME)
    set(SPIRV "${PROJECT_BINARY_DIR}/shaders/${FILE_NAME}")
    message(${GLSL})
    add_custom_command(
            OUTPUT ${SPIRV}
            COMMAND ${CMAKE_COMMAND} -E make_directory "${PROJECT_BINARY_DIR}/shaders/"
            COMMAND ${GLSL_VALIDATOR} -E ${GLSL} > ${SPIRV}
            DEPENDS ${GLSL}
    )
    list(APPEND SPIRV_BINARY_FILES ${SPIRV})
endforeach()

add_custom_target(Shaders DEPENDS ${SPIRV_BINARY_FILES})

add_executable(opengl_starter main.cpp glad.c draw.cpp draw.h shader.cpp shader.h)
target_link_libraries(opengl_starter ${CMAKE_DL_LIBS})
target_link_libraries(opengl_starter GLEW glfw GL X11 pthread Xrandr Xi)

add_dependencies(opengl_starter Shaders)

add_custom_command(TARGET opengl_starter POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:opengl_starter>/shaders/"
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_BINARY_DIR}/shaders"
        "$<TARGET_FILE_DIR:opengl_starter>/shaders"
        )

