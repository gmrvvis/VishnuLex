# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
#
#   Vishnu Lex
#   2015-2019 (c) GMRV / Universidad Rey Juan Carlos
#   gmrv@gmrv.es
#   www.gmrv.es
#
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

cmake_minimum_required(VERSION 3.1)

# vishnulex project and version
project(vishnulex VERSION 0.1.0)
set( PROJECT_VERSION_MAJOR "0" )
set( PROJECT_VERSION_MINOR "1" )
set( PROJECT_VERSION_PATCH "0" )
set( PROJECT_VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH} )
set( vishnulex_VERSION_ABI 1 )

# Disable in source building
if("${PROJECT_SOURCE_DIR}" STREQUAL "${PROJECT_BINARY_DIR}")
  message(FATAL "no in source building allowed.")
endif()

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMake
  ${CMAKE_SOURCE_DIR}/CMake/common)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif(NOT CMAKE_BUILD_TYPE)

if (CMAKE_BUILD_TYPE MATCHES "Debug")
  add_definitions(-DDEBUG)
endif()

include(GitExternal)

configure_file( 
  ${PROJECT_SOURCE_DIR}/CMake/FindZeroMQ.cmake
  ${CMAKE_SOURCE_DIR}/CMake/common/FindZeroMQ.cmake
  COPYONLY
)

# description
set( VISHNULEX_DESCRIPTION "Vishnu Lex" )
set( VISHNULEX_MAINTAINER "Gonzalo Bayo Martinez <gonzalo.bayo@urjc.es>" )
set( VISHNULEX_LICENSE "LGPLv3" )
set( COMMON_PROJECT_DOMAIN gmrv.es )

include( Common )

common_find_package( ZeroEQ REQUIRED )
common_find_package( ZeroBuf REQUIRED )

common_find_package_post( )

list(APPEND VISHNULEX_DEPENDENT_LIBRARIES ZeroEQ ZeroBuf )

add_subdirectory( vishnulex )
add_subdirectory( examples )

if( MSVC )
  # Allow warnings
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -w")
  
  # Set vishnulex as startup project on Visual Studio, CMake v3.6
  if( CMAKE_VERSION VERSION_GREATER 3.6 )
    set_property( DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT vishnulex )
  endif( )
  
  # Excluded because they fail on win compilations
  set(EXCLUDED_FROM_BUILD
    "Servus-test-serializable"
	"Servus-test-servus"
	"Servus-test-uint128_t"
	"Servus-test-uri"
    "ZeroEQHTTP"
	"ZeroBuf-test-constAllocator"
	"ZeroBuf-test-doubleString"
	"ZeroBuf-test-empty"
	"ZeroBuf-test-jsonSerialization"
	"ZeroBuf-test-nestedDynamicZerobuf"
	"ZeroBuf-test-serialization"
	"ZeroBuf-test-zerobufVector"
    "ZeroEQ-test-uri"
	"ZeroEQ-test-pubSub"
	"ZeroEQ-test-perf"
	"ZeroEQ-test-http-server"
	"ZeroEQ-test-connection-broker"
	"ZeroEQ-test-publisher"
	"ZeroEQ-test-receiver"
	"ZeroEQ-test-subscriber"
  )
  set_target_properties(${EXCLUDED_FROM_BUILD} PROPERTIES EXCLUDE_FROM_ALL "TRUE")
endif( )

include(CPackConfig)
include(DoxygenRule)
