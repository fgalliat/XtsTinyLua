/*
** lua.c
** Linguagem para Usuarios de Aplicacao
** TeCGraf - PUC-Rio
** 28 Apr 93
*/

#include <stdio.h>
//#include "speio.h"

#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <time.h>
#include <unistd.h>

#ifdef __GNUC__
#include "floatingpoint.h"
#endif


#include "lua.h"
#include "lualib.h"

#ifdef USE_LCD
#include "libs_xts/lcdlib.h"
#endif

#include "libs_xts/syslib.h"


void test (void)
{
  lua_pushobject(lua_getparam(1));
  lua_call ("c", 1);
}


static void callfunc (void)
{
 lua_Object obj = lua_getparam (1);
 if (lua_isstring(obj)) lua_call(lua_getstring(obj),0);
}

static void execstr (void)
{
 lua_Object obj = lua_getparam (1);
 if (lua_isstring(obj)) lua_dostring(lua_getstring(obj));
}

int main (int argc, char *argv[])
{
 int i;
 if (argc < 2)
 {
  puts ("usage: lua filename [functionnames]");
  return 1;
 }

 lua_register ("callfunc", callfunc);
 lua_register ("execstr", execstr);
 lua_register ("test", test);

// lua_register ("dofile", lua_dofile);

 iolib_open ();
 strlib_open ();
 mathlib_open ();

 //==============================
 syslib_open();
 
#ifdef USE_LCD
 lcdlib_open();
#endif
 //==============================

 lua_dofile (argv[1]);
 for (i=2; i<argc; i++)
 {
  lua_call (argv[i],0);
 }
 return 0;
}


