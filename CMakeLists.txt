#this builds the example raytracing program

#cmake ver req
cmake_minimum_required(VERSION 2.6)
 
#on win you have to do it manually
if(UNIX)
	add_subdirectory(precompile)
endif()

set(project_name libmymath_raytracing_example)

#project name
project(${project_name})

#so that it talks to us
set(CMAKE_VERBOSE_MAKEFILE ON)

set( use_32_bit false )
set( use_new_gcc true )
set( use_explicit_sse2 true )

#32 bits
if( use_32_bit )
	set(CMAKE_CXX_FLAGS "-m32") #compile, link, etc. with 32 bits
	set(CMAKE_C_FLAGS "-m32")
	set(CMAKE_SHARED_LINKER_FLAGS "-m32")
	add_definitions("-march=i686") #go with generic 32 bits
else()
	add_definitions("-march=x86-64") #go with generic 64 bits
endif()

add_definitions("-mtune=nocona -mfpmath=sse") #default to compiler optimizations

if( use_explicit_sse2 )
	message("With sse2")
	add_definitions("-DMYMATH_USE_SSE2") #go with our tinkering
	add_definitions("-msse3") #need this for explicit sse intrinsics
endif()

#gcc/4.8.2/bin/gcc
if( use_new_gcc )
  message("With new gcc")
  set(CMAKE_C_COMPILER $ENV{HOME}/gcc/4.8.2/bin/gcc)
  set(CMAKE_CXX_COMPILER $ENV{HOME}/gcc/4.8.2/bin/g++)
endif()

if(UNIX)
	add_definitions( "-Wall -Wno-long-long -ansi -pedantic -std=c++0x" ) #enable ALL warnings
endif()

if(${CMAKE_BUILD_TYPE} STREQUAL Debug)
  add_definitions("-DDebug")
  message("Debug mode")
endif()

if(${CMAKE_BUILD_TYPE} STREQUAL Release)
  add_definitions("-DRelease")
  message("Release mode")
endif()

#header files source
include_directories(${CMAKE_SOURCE_DIR}/src/)
link_directories(${CMAKE_SOURCE_DIR}/src/)

include_directories(${CMAKE_SOURCE_DIR}/external/include/)
if( use_32_bit )
	link_directories(${CMAKE_SOURCE_DIR}/external/lib/32_bit)
	link_directories(${CMAKE_SOURCE_DIR}/external/lib/32_bit/tbb)
else()
	link_directories(${CMAKE_SOURCE_DIR}/external/lib/64_bit)
	link_directories(${CMAKE_SOURCE_DIR}/external/lib/64_bit/tbb)
endif()

include_directories(${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/old_raytracer)
include_directories(${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/new_raytracer)

if(WIN32)
	set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../)
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../)
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../)
endif()

if(UNIX)
	#set(${project_name}_external_libs sfml-window sfml-system sfml-graphics GLEW GL tbb gsl gslcblas)
	set(${project_name}_external_libs sfml-system)
endif()

if(WIN32)
	set(${project_name}_external_libs optimized sfml-window debug sfml-window-d optimized sfml-system debug sfml-system-d 
	optimized sfml-graphics debug sfml-graphics-d OpenGL32 GLEW32 tbb tbbproxy tbbmalloc tbbmalloc_proxy tbb_preview)
endif()

#adding the project's exe
add_executable(${project_name} test)
#add_executable(${project_name} glsl_code/main)
#add_executable(${project_name} new_raytracer/main)
#add_executable(${project_name} old_raytracer/main)

if(UNIX)
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
endif()

target_link_libraries(${project_name} ${${project_name}_external_libs})