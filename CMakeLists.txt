#this builds the example raytracing program

#cmake ver req
cmake_minimum_required(VERSION 2.6)

# - Try to find precompiled headers support for GCC 3.4 and 4.x
# Once done this will define:
#
# Variable:
#   PCHSupport_FOUND
#
# Macro:
#   ADD_PRECOMPILED_HEADER

IF(CMAKE_COMPILER_IS_GNUCXX)
    EXEC_PROGRAM(
        ${CMAKE_CXX_COMPILER} 
        ARGS                    --version 
        OUTPUT_VARIABLE _compiler_output)
    STRING(REGEX REPLACE ".* ([0-9]\\.[0-9]\\.[0-9]) .*" "\\1" 
           gcc_compiler_version ${_compiler_output})
    #MESSAGE("GCC Version: ${gcc_compiler_version}")
    IF(gcc_compiler_version MATCHES "4\\.[0-9]\\.[0-9]")
        SET(PCHSupport_FOUND TRUE)
    ELSE(gcc_compiler_version MATCHES "4\\.[0-9]\\.[0-9]")
        IF(gcc_compiler_version MATCHES "3\\.4\\.[0-9]")
            SET(PCHSupport_FOUND TRUE)
        ENDIF(gcc_compiler_version MATCHES "3\\.4\\.[0-9]")
    ENDIF(gcc_compiler_version MATCHES "4\\.[0-9]\\.[0-9]")
ENDIF(CMAKE_COMPILER_IS_GNUCXX)

MACRO(ADD_PRECOMPILED_HEADER _targetName _input )

        IF(NOT CMAKE_BUILD_TYPE)
                MESSAGE(FATAL_ERROR 
                        "This is the ADD_PRECOMPILED_HEADER macro. " 
                        "You must set CMAKE_BUILD_TYPE!"
                )
        ENDIF(NOT CMAKE_BUILD_TYPE)

    GET_FILENAME_COMPONENT(_name ${_input} NAME)
        GET_FILENAME_COMPONENT(_path ${_input} PATH)
    SET(_outdir "${CMAKE_CURRENT_BINARY_DIR}/${_name}.gch")
        SET(_output "${_outdir}/${CMAKE_BUILD_TYPE}.c++")

    ADD_CUSTOM_COMMAND(
                OUTPUT ${_outdir}
                COMMAND mkdir ${_outdir} # TODO: {CMAKE_COMMAND} -E ... 
        )
        #MAKE_DIRECTORY(${_outdir})
    
        STRING(TOUPPER "CMAKE_CXX_FLAGS_${CMAKE_BUILD_TYPE}" _flags_var_name)
    SET(_compile_FLAGS ${${_flags_var_name}})
    
    GET_DIRECTORY_PROPERTY(_directory_flags INCLUDE_DIRECTORIES)
                

        SET(_CMAKE_CURRENT_BINARY_DIR_included_before_path FALSE)
        FOREACH(item ${_directory_flags})
                IF(${item}  STREQUAL ${_path} AND NOT 
_CMAKE_CURRENT_BINARY_DIR_included_before_path )
                        MESSAGE(FATAL_ERROR 
                                "This is the ADD_PRECOMPILED_HEADER macro. "
                                "CMAKE_CURREN_BINARY_DIR has to mentioned at 
INCLUDE_DIRECTORIES's argument list before ${_path}, where ${_name} is located"
                        )       
                ENDIF(${item}  STREQUAL ${_path} AND NOT 
_CMAKE_CURRENT_BINARY_DIR_included_before_path )
        
                IF(${item}  STREQUAL ${CMAKE_CURRENT_BINARY_DIR})
                        SET(_CMAKE_CURRENT_BINARY_DIR_included_before_path TRUE)
                ENDIF(${item}  STREQUAL ${CMAKE_CURRENT_BINARY_DIR})
        
                LIST(APPEND _compile_FLAGS "-I${item}")
    ENDFOREACH(item)

        GET_DIRECTORY_PROPERTY(_directory_flags DEFINITIONS)
    LIST(APPEND _compile_FLAGS ${_directory_flags})
        LIST(APPEND _compile_FLAGS ${CMAKE_CXX_FLAGS} )

    SEPARATE_ARGUMENTS(_compile_FLAGS)
    #MESSAGE("_compiler_FLAGS: ${_compiler_FLAGS}")
        #message(${_compile_FLAGS} )
    #message("COMMAND ${CMAKE_CXX_COMPILER}     ${_compile_FLAGS} -x c++-header -o ${_output} ${_input}")
        
        ADD_CUSTOM_COMMAND(
                OUTPUT  ${CMAKE_CURRENT_BINARY_DIR}/${_name} 
                COMMAND ${CMAKE_COMMAND} -E copy  ${_input} 
${CMAKE_CURRENT_BINARY_DIR}/${_name} # ensure same directory! Required by gcc
        )

    ADD_CUSTOM_COMMAND(
        OUTPUT ${_output}       
                COMMAND ${CMAKE_CXX_COMPILER}
                                ${_compile_FLAGS}
                                -x c++-header
                                -o ${_output} 
                                ${_input}
        DEPENDS ${_input} ${_outdir} ${CMAKE_CURRENT_BINARY_DIR}/${_name}       
        )
        ADD_CUSTOM_TARGET(${_targetName}_gch 
                DEPENDS ${_output}      
        )
    ADD_DEPENDENCIES(${_targetName} ${_targetName}_gch )
    SET_TARGET_PROPERTIES(${_targetName} 
                PROPERTIES      
                        COMPILE_FLAGS "-include ${_name} -Winvalid-pch"
    )
ENDMACRO(ADD_PRECOMPILED_HEADER)

set(project_name libmymath_raytracing_example)

#project name
project(${project_name})

#so that it talks to us
set(CMAKE_VERBOSE_MAKEFILE ON)
add_definitions( "-Wall -Wno-long-long -ansi -pedantic" )

#header files source
include_directories(${CMAKE_SOURCE_DIR}/src/)
link_directories(${CMAKE_SOURCE_DIR}/src/)

include_directories(${CMAKE_SOURCE_DIR}/external/include/)
link_directories(${CMAKE_SOURCE_DIR}/external/lib/)

include_directories(${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR})

set(${project_name}_external_libs sfml-window sfml-system GLEW GL)

#adding the project's exe
add_executable(${project_name} main)
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