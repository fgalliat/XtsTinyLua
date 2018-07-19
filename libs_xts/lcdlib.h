#ifndef __XTS_LCD_LIB_
#define __XTS_LCD_LIB_ 1

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

// for Trigo fcts
//#include <tgmath.h>
#include <cmath>

static bool inited = false;

// =====================================
static Serial serial("/dev/ttyS1");
static BridgedScreen screen( &serial );

#define CLR_PINK  8
#define CLR_GREEN 6
#define CLR_BLACK 0
#define CLR_WHITE 1

// =====================================



// prepare LCD bridge
// to be called first
static void lcd_setup (void)
{
  screen.cls();
  
  printf("LCD initialized !\n");
  
  inited = true;
}


static void lcd_cls (void){
  screen.cls();
}


/*
** Print obj to LCD.
** LUA interface:
**			lcdprint(string)
*/
static void lcd_print (void)
{
 char *s;
 lua_Object o = lua_getparam (1);
 
 if (!lua_isstring(o)) { lua_error ("incorrect arguments to function `lcdprint'"); return; }
 
 s = lua_getstring(o);
 
 if ( !inited ) {
   printf("(!!)-[not initialized]-(LCD) %s", s);
 } else {
   screen.print( s );
   // printf("(LCD) %s", s);
 }
 
 //lua_pushstring(s); // as return
 free(s);
} 

static void lcd_bpp (void)
{
 char *s;
 lua_Object o = lua_getparam (1);
 
 if (!lua_isstring(o)) { lua_error ("incorrect arguments to function `lcdbpp'"); return; }
 
 s = lua_getstring(o);
 
 if ( !inited ) {
   printf("(!!)-[not initialized]-(LCD) %s", s);
 } else {
   screen.drawBPP( s, 0, 0 );
 }
 
 //lua_pushstring(s); // as return
 free(s);
} 

static void lcd_pct (void) {
 char *s;
 lua_Object o = lua_getparam (1);
 if (!lua_isstring(o)) { lua_error ("incorrect arguments to function `lcdbpp'"); return; } 
 s = lua_getstring(o);
 
 lua_Object o2 = lua_getparam (2);
 if (!lua_isnumber(o2)) { lua_error ("incorrect arguments to function `lcdbpp'"); return; } 
 float sx = lua_getnumber(o2);
 lua_Object o3 = lua_getparam (3);
 if (!lua_isnumber(o3)) { lua_error ("incorrect arguments to function `lcdbpp'"); return; } 
 float sy = lua_getnumber(o3);
 
 if ( !inited ) {
   printf("(!!)-[not initialized]-(LCD) %s", s);
 } else {
   screen.drawPCT( s, (int)sx, (int)sy );
 }
 
 //lua_pushstring(s); // as return
 free(s);
} 

static void lcd_rect (void) {
 lua_Object o2 = lua_getparam (1);
 if (!lua_isnumber(o2)) { lua_error ("incorrect arguments to function `lcdrect'"); return; } 
 float sx = lua_getnumber(o2);
 lua_Object o3 = lua_getparam (2);
 if (!lua_isnumber(o3)) { lua_error ("incorrect arguments to function `lcdrect'"); return; } 
 float sy = lua_getnumber(o3);
 o2 = lua_getparam (3);
 if (!lua_isnumber(o2)) { lua_error ("incorrect arguments to function `lcdrect'"); return; } 
 float sw = lua_getnumber(o2);
 o3 = lua_getparam (4);
 if (!lua_isnumber(o3)) { lua_error ("incorrect arguments to function `lcdrect'"); return; } 
 float sh = lua_getnumber(o3);
 o2 = lua_getparam (5);
 if (!lua_isnumber(o2)) { lua_error ("incorrect arguments to function `lcdrect'"); return; } 
 int mode = (int)lua_getnumber(o2);
 o3 = lua_getparam (6);
 if (!lua_isnumber(o3)) { lua_error ("incorrect arguments to function `lcdrect'"); return; } 
 int color = (int)lua_getnumber(o3);
 
 if ( !inited ) {
   printf("(!!)-[not initialized]-(LCD) RECT\n");
 } else {
   screen.drawRect( (int)sx, (int)sy, (int)sw, (int)sh, mode, color );
 }
 
} 

// drawAnimatedBackground
static void lcd_backg (void) {
 lua_Object o2 = lua_getparam (1);
 if (!lua_isnumber(o2)) { lua_error ("incorrect arguments to function `lcdbackg'"); return; } 
 int mode = (int)lua_getnumber(o2);
 lua_Object o3 = lua_getparam (2);
 if (!lua_isnumber(o3)) { lua_error ("incorrect arguments to function `lcdbackg'"); return; } 
 int m1 = (int)lua_getnumber(o3);
 o2 = lua_getparam (3);
 if (!lua_isnumber(o2)) { lua_error ("incorrect arguments to function `lcdbackg'"); return; } 
 int m2 = (int)lua_getnumber(o2);
 o3 = lua_getparam (4);
 if (!lua_isnumber(o3)) { lua_error ("incorrect arguments to function `lcdbackg'"); return; } 
 int m3 = (int)lua_getnumber(o3);
 o2 = lua_getparam (5);
 if (!lua_isnumber(o2)) { lua_error ("incorrect arguments to function `lcdbackg'"); return; } 
 int m4 = (int)lua_getnumber(o2);
 
 if ( !inited ) {
   printf("(!!)-[not initialized]-(LCD) BACKG\n");
 } else {
   screen.drawAnimatedBackground( mode, m1, m2, m3, m4 );
 }
 
} 





static void lcd_blitt (void) {
 lua_Object o2 = lua_getparam (1);
 if (!lua_isnumber(o2)) { lua_error ("incorrect arguments to function `lcdrect'"); return; } 
 int mode = (int)lua_getnumber(o2);

 if ( !inited ) {
   //printf("(!!)-[not initialized]-(LCD) RECT\n");
 } else {
   screen.blitt( mode );
 }
 
} 

/*
// tmp here
static void lua_dofilexts (void)
{
 char *s;
 lua_Object o = lua_getparam (1);
 
 if (!lua_isstring(o)) { lua_error ("incorrect arguments to function `dofile'"); return; }
 
 s = lua_getstring(o);
 
 lua_dofile(s);
 
 //lua_pushstring(s); // as return
 free(s);
} 

*/



/*
** Open string library
*/
void lcdlib_open (void)
{
 //lua_register ("strfind", str_find);
 //lua_register ("strlen", str_len);
 //lua_register ("strsub", str_sub);
 //lua_register ("strlower", str_lower);
 lua_register ("lcdsetup", lcd_setup);
 lua_register ("lcdprint", lcd_print);
 
 lua_register ("lcdbpp", lcd_bpp); 
 lua_register ("lcdpct", lcd_pct); 
 lua_register ("lcdrect", lcd_rect); 

 lua_register ("lcdbackg", lcd_backg); 

 lua_register ("lcdcls", lcd_cls); 
 lua_register ("lcdblitt", lcd_blitt); 

 // tmp here ....
 //lua_register ("dofile", lua_dofilexts); 

}


#endif

