#ifndef __XTS_SYS_LIB_
#define __XTS_SYS_LIB_ 1

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


/*
** Open system library
*/
void syslib_open (void)
{

 lua_register ("dofile", lua_dofilexts); 

}


#endif

