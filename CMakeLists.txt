cmake_minimum_required(VERSION 3.6)

project(jngl-template LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fdiagnostics-color")

add_subdirectory(subprojects/jngl)

set(BOX2D_BUILD_TESTBED OFF CACHE BOOL "Build the Box2D testbed" FORCE)
add_subdirectory(subprojects/box2d)

add_subdirectory(subprojects/spine-runtimes/spine-c)

file(GLOB SOURCES CONFIGURE_DEPENDS
	src/*.cpp
	src/engine/*.cpp
	src/engine/effects/*.cpp
	src/gui/*.cpp
)
if(ANDROID)
	# build native_app_glue as a static lib
	set(${CMAKE_C_FLAGS}, "${CMAKE_C_FLAGS}")
	add_library(native_app_glue STATIC
		${ANDROID_NDK}/sources/android/native_app_glue/android_native_app_glue.c)

	# now build app's shared lib
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall")

	# Export ANativeActivity_onCreate(),
	# Refer to: https://github.com/android-ndk/ndk/issues/381.
	set(CMAKE_SHARED_LINKER_FLAGS
		"${CMAKE_SHARED_LINKER_FLAGS} -u ANativeActivity_onCreate")

	add_library(jngl-template SHARED ${SOURCES})

	target_include_directories(jngl-template PRIVATE
		${ANDROID_NDK}/sources/android/native_app_glue
		../../../../../../src
		../../../../../include
	)

	# add lib dependencies
	target_link_libraries(jngl-template
		android
		native_app_glue
		EGL
		GLESv3
		OpenSLES
		log
		z
		jngl
	)


	add_library(bootstrap SHARED android/app/src/main/cpp/bootstrap.cpp)

	target_include_directories(bootstrap PRIVATE
		${ANDROID_NDK}/sources/android/native_app_glue)

	# add lib dependencies
	target_link_libraries(bootstrap
		android
		native_app_glue
		log)
else()
	if(WIN32)
		set_source_files_properties(windows/main.rc PROPERTIES LANGUAGE RC)
		add_executable(jngl-template ${SOURCES} windows/main.rc)
	else()
		add_executable(jngl-template ${SOURCES})
	endif()
	if(APPLE)
		target_link_libraries(jngl-template PRIVATE "-framework AppKit")
	elseif(NOT WIN32)
		target_link_libraries(jngl-template PRIVATE
			stdc++fs
		)
	endif()
	target_link_libraries(jngl-template PRIVATE
		jngl box2d spine-c
	)
endif()

file(GLOB GFX_FILES RELATIVE ${CMAKE_SOURCE_DIR}/data CONFIGURE_DEPENDS data/*.webp data/*.png
                                                                        data/*/*.webp)
file(GLOB SFX_FILES RELATIVE ${CMAKE_SOURCE_DIR}/data data/sfx/*.ogg)
configure_file(src/engine/datafiles.hpp.in include/datafiles.hpp @ONLY)
target_include_directories(jngl-template PRIVATE ${CMAKE_BINARY_DIR}/include subprojects/cereal/include
                                           subprojects/spine-runtimes/spine-c/spine-c/include)

if(WIN32)
	target_compile_definitions(jngl-template PRIVATE _USE_MATH_DEFINES)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Release")
	set_target_properties(jngl-template PROPERTIES WIN32_EXECUTABLE 1)
endif()
