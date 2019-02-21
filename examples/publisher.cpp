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

#include <ctime>

#include <vishnulex/vishnulex.h>

#define NUM_SELECTIONS 100

void delay( unsigned int delay_ )
{
  std::clock_t starTime = std::clock( );
  bool endTime = false;

  while( !endTime )
  {
    endTime = (( unsigned int ) (( std::clock( ) - starTime ) * 1000 /
      CLOCKS_PER_SEC )) >= delay_;
  }

}

int main( int /*argc*/, char ** /*argv[]*/ )
{
  zeroeq::Publisher publisher;

  for ( unsigned int i = 0; i < NUM_SELECTIONS; i++ )
  {
    std::string iStr = std::to_string( i );
    vishnulex::SyncGroup syncGroup;
    syncGroup.setKey( "key" + iStr );
    syncGroup.setName( "name" + iStr );
    syncGroup.setOwner( "owner" + iStr );
    syncGroup.setIds( "1|2|3|4|5" );
    syncGroup.setColor( {255, 0, 0 } );

    publisher.publish( syncGroup );
    std::cout << "Sent SyncGroup Event" << std::endl;
    delay( 100 );
  }

  return 0;
}

