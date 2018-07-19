#include <errno.h>
#include <fcntl.h> 
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "Serial.h"
#include "BridgedScreen.h"

/*
 Idea => mcu#2 Serial  => linked to UART0 of onionOmega2 => Cf DUMMY boot debug ????? / need to be switchable by Bridge CMD
               Serial2 => DFPlayer
               Serial3 => Bridge

*/


int main(int argc, char* argv[] ) {
  Serial serial("/dev/ttyS1");
  BridgedScreen screen( &serial );

  screen.cls();

  for (int i=0; i < 50; i++) {
    //screen.cls();
    screen.drawRect(10 + ((i-1)*2),10,20,20,1,0); // BLACK FLAT RECT

    // screen.drawCircle(10 + (i*2) , 10+30, 20, 1,5); // LIGHTGREEN FLAT CIRCLE -- doesn't display
    screen.drawCircle(10 + (i*2) , 10+30, 20, 1,8); // PINK FLAT CIRCLE -- doesn't display
    //screen.drawRect(10 + (i*2),10,20,20,1,8); // PINK FLAT RECT
  }

  screen.drawBPP("/BLAST.BPP", 0, 0);
  screen.drawPCT("/CARO.PCT", 160, 90);

  screen.drawPCTSprite("/CARO.PCT", 160, 0, 64, 64, 0, 0);
  screen.drawPCTSprite("", 160+64+4, 0, 64, 64, 0, 0);

  screen.println("Hello world from LCD controller !"); // BEWARE max 30 chars
  screen.print(128);
  screen.println("");
  screen.print(3.14f);
  screen.println("");

  screen.drawRect(10,10,20,20,1,8); // PINK FLAT RECT
  screen.drawLine(10,10,10+20,1+20,7); // DARKGREEN LINE
  //screen.drawCircle(10,10+30,10,1,5); // LIGHTGREEN FLAT CIRCLE -- doesn't show
  screen.drawCircle(10,10+30,10,0,5); // LIGHTGREEN FLAT CIRCLE

  screen.drawTriangle(100,10, 100+20,10+30, 100,10+60  ,1,5); // LIGHTGREEN FLAT TRIANGLE


}