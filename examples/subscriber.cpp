/* 
 * Copyright (c) 2015-2019 GMRV/URJC.
 * 
 * Authors: Cristian Rodriguez Bernal <ccrisrober@gmail.com>
 *          Gonzalo Bayo Martinez <gonzalo.bayo@urjc.es>
 * 
 * This file is part of VishnuLex <https://gitlab.gmrv.es/cbbsp1/vishnulex>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of his software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
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

