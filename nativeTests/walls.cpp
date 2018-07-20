/**

  32 chars, 0terminated
  
  1+1+30
  \ \  \_ 0-240 wall height + 0-15 wall attribs (color)
   \ \___ ground attribs  
    \____ sky attribs
    
    ---------------------------
    need to use a pow of 2
    
    2 bits + 6bits
    [0-3]    [0-63]
     light    height -> 3.75px => 240px
    
    1 byte -> sky+ground attrib
    1 byte -> walls attribs (color)
    30 bytes -> walls
    [0]    -> termination
*/

#include <stdio.h>
#include <math.h>

#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

#include <stdint.h> // uintX_t

#include "Serial.h"
#include "BridgedScreen.h"
Serial serial("/dev/ttyS1");
BridgedScreen screen( &serial );




uint8_t w_scene[32];

void w_trsf(int val) {
 int height = (int) ((float) ((val >> 2) % 64) * 3.80f);
 int attr   = val % 4;

 printf(">> %d <= %d %d \n\n", val, height, attr);
}

int w_itrsf(int height, int attr) {
 attr %= 4;
 if (height < 0)   { height = 0; }
 if (height > 240) { height = 240; }
 
 int hh = (int)((float)height/3.80f);
 
 int val = ( hh << 2) | ( attr );

 printf(" $> %d %d -> (%d) %d \n", height, attr, hh, val);
 return val;
}


void w_drawScene() {
  int bckAttribs = w_scene[0];
  int wllAttribs = w_scene[1];
  
  uint8_t wall;
  for(int i=0; i < 30; i++) {
    wall = w_scene[2+i];
  }
}


int main(int argc, char** argv) {

 int val = 240 + 15;
 
 printf("Hello \n");
 
 //trsf(val);

 w_trsf( w_itrsf(0,0) ); // no wall
 w_trsf( w_itrsf(1,3) ); // too much tiny
 w_trsf( w_itrsf(4,3) ); // enought to make 1bloc height
 
 w_trsf( w_itrsf(4,1) );
 w_trsf( w_itrsf(240,3) );


}