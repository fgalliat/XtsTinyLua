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

unsigned char rxBuff[1];

void flushRX(Serial* serial) {
   serial->read( rxBuff, 1 ); // 0xFF ok -- 0xFE failed
}

unsigned char txBuff[32];

    BridgedScreen::BridgedScreen(Serial* serial) {
        this->serial = serial;
    }
    BridgedScreen::~BridgedScreen() {

    }

    bool BridgedScreen::init() {
        return true;
    }

    void BridgedScreen::close() {
    }

    void BridgedScreen::blitt(uint8_t mode) {
        int len = 2; txBuff[0] = SIG_SCR_BLITT; txBuff[1] = mode; 
	    serial->write( txBuff, len );
	    flushRX(serial);
    }

    void BridgedScreen::cls() {
        int len = 1; txBuff[0] = 0x22; 
	    serial->write( txBuff, len );
	    flushRX(serial);
    }

    // int nb of TTY chars
    void BridgedScreen::setCursor(int x, int y) {
        int len = 3; txBuff[0] = 0x23; txBuff[1] = (uint8_t)x; txBuff[1] = (uint8_t)y; 
	    serial->write( txBuff, len );
	    flushRX(serial);
    }

    void BridgedScreen::print(int val) {
        char txt[17+1];
        sprintf( txt, "%d", val );
        this->print( txt );
    }
    void BridgedScreen::print(float val) {
        char txt[17+1];
        sprintf( txt, "%f", val );
        this->print( txt );
    }
    void BridgedScreen::print(char* str) {
        // TODO : 30 chars max
        int len = 1; txBuff[0] = 0x32; 
        serial->write( txBuff, len );
        serial->writestr( str );
        len = 1; txBuff[0] = 0x00; 
        serial->write( txBuff, len );
        flushRX(serial);
    }
    void BridgedScreen::println(char* str) {
        this->print(str);
        this->print((char*)"\n");
    }

    void BridgedScreen::drawBPP(char* name, int x, int y) {
        int len = 1; txBuff[0] = 0x46; 
        serial->write( txBuff, len );
        
        len = 2; txBuff[0] = (uint8_t)( x/256 ); txBuff[1] = (uint8_t)( x%256 );  // X
        serial->write( txBuff, len );

        len = 2; txBuff[0] = (uint8_t)( y/256 ); txBuff[1] = (uint8_t)( y%256 );  // Y
        serial->write( txBuff, len );

        // uart_writestr( "/CARO.PCT" ); // asset name
        serial->writestr( name ); // asset name
        
        len = 1; txBuff[0] = 0x00; 
        serial->write( txBuff, len );
        flushRX(serial);
    }

    void BridgedScreen::drawPCT(char* name, int x, int y) {
        int len = 1; txBuff[0] = 0x47; 
        serial->write( txBuff, len );
        
        len = 2; txBuff[0] = (uint8_t)( x/256 ); txBuff[1] = (uint8_t)( x%256 );  // X
        serial->write( txBuff, len );

        len = 2; txBuff[0] = (uint8_t)( y/256 ); txBuff[1] = (uint8_t)( y%256 );  // Y
        serial->write( txBuff, len );

        // uart_writestr( "/CARO.PCT" ); // asset name
        serial->writestr( name ); // asset name
        
        len = 1; txBuff[0] = 0x00; 
        serial->write( txBuff, len );
        flushRX(serial);
    }
    void BridgedScreen::drawPCTSprite(char* name, int x, int y, int w, int h, int sx, int sy) {
        int len = 1; txBuff[0] = 0x48; 
        serial->write( txBuff, len );
        
        len = 2; txBuff[0] = (uint8_t)( x/256 ); txBuff[1] = (uint8_t)( x%256 );  // X
        serial->write( txBuff, len );

        len = 2; txBuff[0] = (uint8_t)( y/256 ); txBuff[1] = (uint8_t)( y%256 );  // Y
        serial->write( txBuff, len );

        len = 2; txBuff[0] = (uint8_t)( w/256 ); txBuff[1] = (uint8_t)( w%256 );  // W
        serial->write( txBuff, len );

        len = 2; txBuff[0] = (uint8_t)( h/256 ); txBuff[1] = (uint8_t)( h%256 );  // H
        serial->write( txBuff, len );

        len = 2; txBuff[0] = (uint8_t)( sx/256 ); txBuff[1] = (uint8_t)( sx%256 );  // sX
        serial->write( txBuff, len );

        len = 2; txBuff[0] = (uint8_t)( sy/256 ); txBuff[1] = (uint8_t)( sy%256 );  // sY
        serial->write( txBuff, len );

        // uart_writestr( "/CARO.PCT" ); // asset name
        serial->writestr( name ); // asset name
        
        len = 1; txBuff[0] = 0x00; 
        serial->write( txBuff, len );
        flushRX(serial);
    }

    void BridgedScreen::drawPixel(int x, int y, uint16_t color) {
        int len = 1; txBuff[0] = 0x41; 
        serial->write( txBuff, len );
        
        len = 2; txBuff[0] = (uint8_t)( x/256 ); txBuff[1] = (uint8_t)( x%256 );  // X
        serial->write( txBuff, len );

        len = 2; txBuff[0] = (uint8_t)( y/256 ); txBuff[1] = (uint8_t)( y%256 );  // Y
        serial->write( txBuff, len );

        len = 2; txBuff[0] = (uint8_t)( color/256 ); txBuff[1] = (uint8_t)( color%256 );  // COLOR
        serial->write( txBuff, len );

        flushRX(serial);
    }
    void BridgedScreen::drawLine(int x, int y, int x2, int y2, uint16_t color) {
        int len = 1; txBuff[0] = 0x42; 
        serial->write( txBuff, len );
        
        len = 2; txBuff[0] = (uint8_t)( x/256 ); txBuff[1] = (uint8_t)( x%256 );  // X
        serial->write( txBuff, len );

        len = 2; txBuff[0] = (uint8_t)( y/256 ); txBuff[1] = (uint8_t)( y%256 );  // Y
        serial->write( txBuff, len );

        len = 2; txBuff[0] = (uint8_t)( x2/256 ); txBuff[1] = (uint8_t)( x2%256 );  // X2
        serial->write( txBuff, len );

        len = 2; txBuff[0] = (uint8_t)( y2/256 ); txBuff[1] = (uint8_t)( y2%256 );  // Y2
        serial->write( txBuff, len );

        len = 2; txBuff[0] = (uint8_t)( color/256 ); txBuff[1] = (uint8_t)( color%256 );  // COLOR
        serial->write( txBuff, len );

        flushRX(serial);
    }
    void BridgedScreen::drawRect(int x, int y, int w, int h, uint8_t mode, uint16_t color) {
        int len = 1; txBuff[0] = 0x43; 
        serial->write( txBuff, len );
        
        len = 2; txBuff[0] = (uint8_t)( x/256 ); txBuff[1] = (uint8_t)( x%256 );  // X
        serial->write( txBuff, len );

        len = 2; txBuff[0] = (uint8_t)( y/256 ); txBuff[1] = (uint8_t)( y%256 );  // Y
        serial->write( txBuff, len );

        len = 2; txBuff[0] = (uint8_t)( w/256 ); txBuff[1] = (uint8_t)( w%256 );  // W
        serial->write( txBuff, len );

        len = 2; txBuff[0] = (uint8_t)( h/256 ); txBuff[1] = (uint8_t)( h%256 );  // H
        serial->write( txBuff, len );

        len = 1; txBuff[0] = mode; 
        serial->write( txBuff, len );

        len = 2; txBuff[0] = (uint8_t)( color/256 ); txBuff[1] = (uint8_t)( color%256 );  // COLOR
        serial->write( txBuff, len );

        flushRX(serial);
    }
    void BridgedScreen::drawCircle(int x, int y, int radius, uint8_t mode, uint16_t color) {
        int len = 1; txBuff[0] = 0x44; 
        serial->write( txBuff, len );
        
        len = 2; txBuff[0] = (uint8_t)( x/256 ); txBuff[1] = (uint8_t)( x%256 );  // X
        serial->write( txBuff, len );

        len = 2; txBuff[0] = (uint8_t)( y/256 ); txBuff[1] = (uint8_t)( y%256 );  // Y
        serial->write( txBuff, len );

        len = 2; txBuff[0] = (uint8_t)( radius/256 ); txBuff[1] = (uint8_t)( radius%256 );  // radius
        serial->write( txBuff, len );

        len = 1; txBuff[0] = mode; 
        serial->write( txBuff, len );

        len = 2; txBuff[0] = (uint8_t)( color/256 ); txBuff[1] = (uint8_t)( color%256 );  // COLOR
        serial->write( txBuff, len );

        flushRX(serial);
    }
    void BridgedScreen::drawTriangle(int x, int y, int x2, int y2, int x3, int y3, uint8_t mode, uint16_t color) {
        int len = 1; txBuff[0] = 0x45; 
        serial->write( txBuff, len );
        
        len = 2; txBuff[0] = (uint8_t)( x/256 ); txBuff[1] = (uint8_t)( x%256 );  // X
        serial->write( txBuff, len );

        len = 2; txBuff[0] = (uint8_t)( y/256 ); txBuff[1] = (uint8_t)( y%256 );  // Y
        serial->write( txBuff, len );

        len = 2; txBuff[0] = (uint8_t)( x2/256 ); txBuff[1] = (uint8_t)( x2%256 );  // X2
        serial->write( txBuff, len );

        len = 2; txBuff[0] = (uint8_t)( y2/256 ); txBuff[1] = (uint8_t)( y2%256 );  // Y2
        serial->write( txBuff, len );

        len = 2; txBuff[0] = (uint8_t)( x3/256 ); txBuff[1] = (uint8_t)( x3%256 );  // X3
        serial->write( txBuff, len );

        len = 2; txBuff[0] = (uint8_t)( y3/256 ); txBuff[1] = (uint8_t)( y3%256 );  // Y3
        serial->write( txBuff, len );

        len = 1; txBuff[0] = mode; 
        serial->write( txBuff, len );

        len = 2; txBuff[0] = (uint8_t)( color/256 ); txBuff[1] = (uint8_t)( color%256 );  // COLOR
        serial->write( txBuff, len );

        flushRX(serial);
    }

    void BridgedScreen::drawBall(int x, int y, int radius, uint16_t color) {
        int len = 1; txBuff[0] = 0x51; 
        serial->write( txBuff, len );
        
        len = 2; txBuff[0] = (uint8_t)( x/256 ); txBuff[1] = (uint8_t)( x%256 );  // X
        serial->write( txBuff, len );

        len = 2; txBuff[0] = (uint8_t)( y/256 ); txBuff[1] = (uint8_t)( y%256 );  // Y
        serial->write( txBuff, len );

        len = 2; txBuff[0] = (uint8_t)( radius/256 ); txBuff[1] = (uint8_t)( radius%256 );  // radius
        serial->write( txBuff, len );

        len = 2; txBuff[0] = (uint8_t)( color/256 ); txBuff[1] = (uint8_t)( color%256 );  // COLOR
        serial->write( txBuff, len );

        flushRX(serial);
    }


    void BridgedScreen::drawAnimatedBackground(int mode, int m1, int m2, int m3, int m4) {
        int len = 1; txBuff[0] = 0x61; 
        serial->write( txBuff, len );
        
        len = 1; txBuff[0] = mode; 
        serial->write( txBuff, len );
        
        len = 2; txBuff[0] = (uint8_t)( m1/256 ); txBuff[1] = (uint8_t)( m1%256 );  // X
        serial->write( txBuff, len );

        len = 2; txBuff[0] = (uint8_t)( m2/256 ); txBuff[1] = (uint8_t)( m2%256 );  // X
        serial->write( txBuff, len );

        len = 2; txBuff[0] = (uint8_t)( m3/256 ); txBuff[1] = (uint8_t)( m3%256 );  // X
        serial->write( txBuff, len );

        len = 2; txBuff[0] = (uint8_t)( m4/256 ); txBuff[1] = (uint8_t)( m4%256 );  // X
        serial->write( txBuff, len );

        flushRX(serial);      
    }

