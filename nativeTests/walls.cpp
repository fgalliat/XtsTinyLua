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


void trsf(int val) {
 int height = (int) ((float) ((val >> 2) % 64) * 3.80f);
 int attr   = val % 4;

 printf(">> %d <= %d %d \n\n", val, height, attr);
}

int itrsf(int height, int attr) {
 attr %= 4;
 if (height < 0)   { height = 0; }
 if (height > 240) { height = 240; }
 
 int hh = (int)((float)height/3.80f);
 
 int val = ( hh << 2) | ( attr );

 printf(" $> %d %d -> (%d) %d \n", height, attr, hh, val);
 return val;
}


int main(int argc, char** argv) {

 int val = 240 + 15;
 
 printf("Hello \n");
 
 //trsf(val);

 trsf( itrsf(0,0) ); // no wall
 trsf( itrsf(1,3) ); // too much tiny
 trsf( itrsf(4,3) ); // enought to make 1bloc height
 
 trsf( itrsf(4,1) );
 trsf( itrsf(240,3) );


}