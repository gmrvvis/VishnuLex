# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
#
#   Vishnu Lex
#   2015-2019 (c) GMRV / Universidad Rey Juan Carlos
#   gmrv@gmrv.es
#   www.gmrv.es
#
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

source_group(\\ FILES CMakeLists.txt)

list(APPEND CPPCHECK_EXTRA_ARGS
  --suppress=*:${CMAKE_CURRENT_BINARY_DIR}/*_generated.h)

include(zerobufGenerateCxx)
set(__outdir ${PROJECT_BINARY_DIR}/include/vishnulex)

set(VISHNULEX_DATA_DIR ${__outdir})
set(VISHNULEX_DATA_FBS 
  ChangeColorGroup.fbs
  ChangeNameGroup.fbs
  DestroyGroup.fbs
  SyncGroup.fbs
  SyncNeeded.fbs
  SyncXml.fbs
  SyncTransferFunc.fbs
)

zerobuf_generate_cxx(VISHNULEX_DATA ${VISHNULEX_DATA_DIR} ${VISHNULEX_DATA_FBS})

set(VISHNULEX_PUBLIC_HEADERS
  ${COMMON_INCLUDES}
  ${VISHNULEX_DATA_HEADERS}
)

set(VISHNULEX_HEADERS )

set(VISHNULEX_SOURCES
  ${COMMON_SOURCES}
  ${VISHNULEX_DATA_SOURCES}
)
set(VISHNULEX_LINK_LIBRARIES ZeroEQ ZeroBuf)

if(MSVC)
  list(APPEND VISHNULEX_LINK_LIBRARIES Ws2_32)
endif()

set( PROJECT_INCLUDE_NAME vishnulex )
add_definitions(-DZEROEQ_SHARED)
common_library(vishnulex)
