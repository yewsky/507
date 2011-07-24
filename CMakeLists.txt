cmake_minimum_required(VERSION 2.6)

###
### Project settings
###
project(linux-sdk)

set(CP cp)
set(STRIP strip)

set(PRJ_VERSION_MAJOR "1")
set(PRJ_VERSION_MINOR "0")
set(PRJ_VERSION_PATCH "0")
set(PRJ_VERSION "${PRJ_VERSION_MAJOR}.${PRJ_VERSION_MINOR}.${PRJ_VERSION_PATCH}")

###
### Project options
###
option(BUILD_STATIC_LIBS "Build Static Libraries" OFF)
option(BUILD_SHARED_LIBS "Build Shared Libraries" OFF)

add_definitions(-DLINUX)
#add_definitions(-DLINUX -D_ISOC99_SOURCE -D_BSD_SOURCE -D_GNU_SOURCE )

file(
	GLOB
	sources
	"src/[a-zA-Z]*.cpp"
	"src/[a-zA-Z]*/[a-zA-Z]*.cpp"
)

file(
	GLOB
	headers
	"src/[a-zA-Z]*.h"
	"src/[a-zA-Z]*/[a-zA-Z]*.h"	
)

if(CMAKE_COMPILER_IS_GNUCC)
#	set(CMAKE_C_FLAGS_RELEASE "-std=c99 -O2")
#	set(CMAKE_C_FLAGS_RELWITHDEBINFO "-O2 -g")
#	set(CMAKE_C_FLAGS_DEBUG "-std=c99 -g -DDEBUG")
#	set(CMAKE_C_FLAGS_MINSIZEREL "-Os")

	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2 -DNDEBUG")
	set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Winvalid-pch -DDEBUG")
	set(CMAKE_CXX_FLAGS_MINSIZEREL "-Os")
endif()

include_directories(
	src
	$ENV{HOME}/devel/linux-sdk/contrib
    $ENV{HOME}/devel/linux-sdk/thirdparty/include
)

link_directories(
	$ENV{HOME}/devel/linux-sdk/contrib/lib
	$ENV{HOME}/devel/linux-sdk/thirdparty/lib
)

###
### Program
###

set(CMAKE_BUILD_TYPE Debug)

add_executable(
	${PROJECT_NAME}
	${sources}
)

target_link_libraries(
	${PROJECT_NAME}
	boost_system
	boost_thread
	pugixml.a
	md5.a
)

###
### Install
###
install(
	TARGETS ${PROJECT_NAME} 
	RUNTIME DESTINATION $ENV{HOME}/devel/linux-sdk/bin
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
)

###
### Release
###
add_custom_target(
	release
	COMMAND ${CMAKE_COMMAND} -E echo -- "Stripping: ${PROJECT_NAME}"
	COMMAND ${STRIP} ${PROJECT_NAME}
	COMMAND ${CMAKE_COMMAND} -E echo -- "Installing: $ENV{RELEASE_PREFIX}/bin/${PROJECT_NAME}"
	COMMAND ${CP} -P ${PROJECT_NAME} $ENV{RELEASE_PREFIX}/bin/
	DEPENDS ${PROJECT_NAME}
)

add_custom_target(
	prepare
	COMMAND ${CMAKE_COMMAND} -E echo -- "建立预编译头: ${PROJECT_NAME}"
	COMMAND ${CMAKE_CXX_COMPILER}  -DLINUX -g -Wall -Winvalid-pch -DDEBUG -o ${PROJECT_SOURCE_DIR}/src/Common.h.gch -x c++-header -c ${PROJECT_SOURCE_DIR}/src/Common.h -I$ENV{HOME}/devel/linux-sdk/thirdparty/include
)

MESSAGE(STATUS "1234567890 "${CMAKE_COMMAND})

###  -I$ENV{HOME}/devel/linux-sdk/thirdparty/include;

	
