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

#define SCREEN_HEIGHT 240

int irnd(int max) {
  return rand() % max;
}

void drawRect(int x, int y, int w, int h, int light) {
  int mode = 1;
  int color = 1;
  
  if ( light == 0 ) {
    color = 4; // dark gray
    mode = 1;
  } else if ( light == 1 ) {
    color = 3;
    mode = 1;
  } else if ( light == 2 ) {
    color = 2; // light gray
    mode = 1;
  } else if ( light == 3 ) {
    color = 1; // white
    mode = 1;
  }  
  
  screen.drawRect( x, y, w, h, mode, color );
}

void drawStrip(int i, int h, int light) {
  drawRect( 5+(i*10), (SCREEN_HEIGHT-h)/2, 10, h, light );
}

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
  
  // STILL TODO : draw floor & sky
  //screen.cls();
  screen.drawRect(15, 0, 290, 120, 1, 9); // light-blue sky
  screen.drawRect(15, 120, 290, 120, 1, 5); // light-green floor
  
  
  uint8_t wall;
  for(int i=0; i < 30; i++) {
    wall = w_scene[2+i];

    int height = (int) ((float) ((wall >> 2) % 64) * 3.80f);
    int attr   = wall % 4;

    drawStrip( i, height, attr );
  }
}


int main(int argc, char** argv) {

 int val = 240 + 15;
 
 printf("Hello \n");
 screen.cls();


 w_scene[0] = 1;
 w_scene[1] = 1;
 for(int i=0; i < 30; i++) { w_scene[2+i] = w_itrsf(irnd( 240 ), i%4); }
 w_drawScene();
 
 //trsf(val);

 w_trsf( w_itrsf(0,0) ); // no wall
 w_trsf( w_itrsf(1,3) ); // too much tiny
 w_trsf( w_itrsf(4,3) ); // enought to make 1bloc height
 
 w_trsf( w_itrsf(4,1) );
 w_trsf( w_itrsf(240,3) );


}