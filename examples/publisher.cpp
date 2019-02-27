/* 
 * Copyright (c) 2015-2019 GMRV/URJC.
 * 
 * Authors: Cristian Rodriguez Bernal <cristian.rodriguez@urjc.es>
 *          Gonzalo Bayo Martinez <gonzalo.bayo@urjc.es>
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

