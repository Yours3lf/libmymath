#this builds the example raytracing program

#cmake ver req
cmake_minimum_required(VERSION 2.6)

add_subdirectory(precompile)

set(project_name libmymath_raytracing_example)

#project name
project(${project_name})

#so that it talks to us
set(CMAKE_VERBOSE_MAKEFILE ON)
add_definitions( "-Wall -Wno-long-long -ansi -pedantic -std=c++0x" )

#header files source
include_directories(${CMAKE_SOURCE_DIR}/src/)
link_directories(${CMAKE_SOURCE_DIR}/src/)

include_directories(${CMAKE_SOURCE_DIR}/external/include/)
link_directories(${CMAKE_SOURCE_DIR}/external/lib/)
link_directories(${CMAKE_SOURCE_DIR}/external/lib/tbb)

include_directories(${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/old_raytracer)
include_directories(${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/new_raytracer)

set(${project_name}_external_libs sfml-window sfml-system sfml-graphics GLEW GL tbb gsl gslcblas)

#adding the project's exe
add_executable(${project_name} glsl_code/main)
#add_executable(${project_name} new_raytracer/main)
#add_executable(${project_name} old_raytracer/main)

add_precompiled_header(${project_name} #add precompiled headers
${CMAKE_SOURCE_DIR}/mymath/mm_common.h
${CMAKE_SOURCE_DIR}/mymath/mm_vec2_impl.h
${CMAKE_SOURCE_DIR}/mymath/mm_vec3_impl.h
${CMAKE_SOURCE_DIR}/mymath/mm_vec4_impl.h
${CMAKE_SOURCE_DIR}/mymath/includes/vec2_swizzle_declarations.h
${CMAKE_SOURCE_DIR}/mymath/includes/vec3_swizzle_declarations.h
${CMAKE_SOURCE_DIR}/mymath/includes/vec4_swizzle_declarations.h
${CMAKE_SOURCE_DIR}/mymath/mm_vec_swizzle_out.h
${CMAKE_SOURCE_DIR}/mymath/mm_vec_func.h
${CMAKE_SOURCE_DIR}/mymath/mm_mat2_impl.h
${CMAKE_SOURCE_DIR}/mymath/mm_mat3_impl.h
${CMAKE_SOURCE_DIR}/mymath/mm_mat4_impl.h
${CMAKE_SOURCE_DIR}/mymath/mm_mat_func.h
${CMAKE_SOURCE_DIR}/mymath/mm_util.h
${CMAKE_SOURCE_DIR}/mymath/mm_frame.h
${CMAKE_SOURCE_DIR}/mymath/mm_camera.h
${CMAKE_SOURCE_DIR}/mymath/mm_matrix_stack.h
${CMAKE_SOURCE_DIR}/mymath/mm_pipeline.h
${CMAKE_SOURCE_DIR}/mymath/mymat.h)

target_link_libraries(${project_name} ${${project_name}_external_libs})