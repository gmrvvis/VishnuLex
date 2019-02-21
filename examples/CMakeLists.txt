# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
#
#   Vishnu Lex
#   2015-2019 (c) GMRV / Universidad Rey Juan Carlos
#   gmrv@gmrv.es
#   www.gmrv.es
#
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

set( VISHNULEXPUBLISHER_SOURCES
  publisher.cpp
)

set( VISHNULEXSUBSCRIBER_SOURCES
  subscriber.cpp
)

include_directories( ../vishnulex )


set( VISHNULEXPUBLISHER_LINK_LIBRARIES
  vishnulex
)

set( VISHNULEXSUBSCRIBER_LINK_LIBRARIES
  vishnulex
)

common_application( vishnulexPublisher )
common_application( vishnulexSubscriber )

