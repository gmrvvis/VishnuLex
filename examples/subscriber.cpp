/*
 * Copyright (c) 2015-2019 GMRV/URJC.
 *
 * Authors: Cristian Rodriguez Bernal <ccrisrober@gmail.com>
 *          Gonzalo Bayo Martinez <gonzalo.bayo@urjc.es>
 *
 * This file is part of VishnuLex <https://gitlab.gmrv.es/cbbsp1/vishnulex>
 *
 * This library is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License version 3.0 as published
 * by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 */

#include <iostream>

#include <zeroeq/zeroeq.h>
#include <servus/uri.h>

#include <functional>

#include <vishnulex/vishnulex.h>

vishnulex::SyncGroup receivedSyncGroup;

using SerializablePtr = std::shared_ptr< servus::Serializable >;

void onSyncGroupReceive( )
{
  std::cout << "Received SyncGroup: ";
  vishnulex::SyncGroup::Ids& ids = receivedSyncGroup.getIds( );
  vishnulex::SyncGroup::Color& color = receivedSyncGroup.getColor( );

  std::cout << "Key: " << receivedSyncGroup.getKeyString( ) << std::endl;
  std::cout << "Name: " << receivedSyncGroup.getNameString( ) << std::endl;
  std::cout << "Owner: " << receivedSyncGroup.getOwnerString( ) << std::endl;
  std::cout << "Ids: ";
  for( unsigned int i = 0; i < ids.size( ); ++i )
  {
    std::cout << ids[ i ] << " ";
  }
  std::cout << std::endl;
  std::cout << "Color: " << color[0] << ", " << color[1] << ", " << color[2] 
    << std::endl;
}

int main( int /*argc*/, char ** /*argv[]*/ )
{

  std::cout << "Creating subscriber..." << std::endl;

  zeroeq::Subscriber subscriber;
  receivedSyncGroup.registerDeserializedCallback( 
    [ & ] { onSyncGroupReceive( ); } );

  subscriber.subscribe( receivedSyncGroup );

  while ( true )
  {
    std::cout << "Waiting... " << std::endl;

    if ( !subscriber.receive( 5000 ) )
    {
      break;
    }
  }

  return 0;
}

