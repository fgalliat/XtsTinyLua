#ifndef __STR_LIB_
#define __STR_LIB_ 1



//#include "lua.h"

/*
** Return the position of the first caracter of a substring into a string
** LUA interface:
**			n = strfind (string, substring)
*/
static void str_find (void)
{
 int n;
 char *s1, *s2;
 lua_Object o1 = lua_getparam (1);
 lua_Object o2 = lua_getparam (2);
 if (!lua_isstring(o1) || !lua_isstring(o2))
 { lua_error ("incorrect arguments to function `strfind'"); return; }
 s1 = lua_getstring(o1);
 s2 = lua_getstring(o2);
 n = strstr(s1,s2) - s1 + 1;
 lua_pushnumber (n);
}

/*
** Return the string length
** LUA interface:
**			n = strlen (string)
*/
static void str_len (void)
{
 lua_Object o = lua_getparam (1);
 if (!lua_isstring(o))
 { lua_error ("incorrect arguments to function `strlen'"); return; }
 lua_pushnumber(strlen(lua_getstring(o)));
}


/*
** Return the substring of a string, from start to end
** LUA interface:
**			substring = strsub (string, start, end)
*/
static void str_sub (void)
{
 int start, end;
 char *s;
 lua_Object o1 = lua_getparam (1);
 lua_Object o2 = lua_getparam (2);
 lua_Object o3 = lua_getparam (3);
 if (!lua_isstring(o1) || !lua_isnumber(o2) || !lua_isnumber(o3))
 { lua_error ("incorrect arguments to function `strsub'"); return; }
 s = strdup (lua_getstring(o1));
 start = lua_getnumber (o2);
 end = lua_getnumber (o3);
 if (end < start || start < 1 || end > strlen(s))
  lua_pushstring ("");
 else
 {
  s[end] = 0;
  lua_pushstring (&s[start-1]);
 }
 free (s);
}

/*
** Convert a string to lower case.
** LUA interface:
**			lowercase = strlower (string)
*/
static void str_lower (void)
{
 char *s, *c;
 lua_Object o = lua_getparam (1);
 if (!lua_isstring(o))
 { lua_error ("incorrect arguments to function `strlower'"); return; }
 c = s = strdup(lua_getstring(o));
 while (*c != 0)
 {
  *c = tolower(*c);
  c++;
 }
 lua_pushstring(s);
 free(s);
} 


/*
** Convert a string to upper case.
** LUA interface:
**			uppercase = strupper (string)
*/
static void str_upper (void)
{
 char *s, *c;
 lua_Object o = lua_getparam (1);
 if (!lua_isstring(o))
 { lua_error ("incorrect arguments to function `strlower'"); return; }
 c = s = strdup(lua_getstring(o));
 while (*c != 0)
 {
  *c = toupper(*c);
  c++;
 }
 lua_pushstring(s);
 free(s);
} 

static void str_hex (void)
{
 char s[3]; int num;
 lua_Object o = lua_getparam (1);
 if (!lua_isnumber(o))
 { lua_error ("incorrect arguments to function `strhex'"); return; }
 num = (int)lua_getnumber(o);
 
 s[2] = 0x00;
 sprintf(s, "%02X", num);

 lua_pushstring(s);
// free(s);
} 

static void str_chr (void)
{
 char s[2]; int num;
 lua_Object o = lua_getparam (1);
 if (!lua_isnumber(o))
 { lua_error ("incorrect arguments to function `strhex'"); return; }
 num = (int)lua_getnumber(o);
 
 s[1] = 0x00;
 //sprintf(s, "%02X", num);
 s[0] = (char)num;

 lua_pushstring(s);
// free(s);
} 


/*
** Open string library
*/
void strlib_open (void)
{
 lua_register ("strfind", str_find);
 lua_register ("strlen", str_len);
 lua_register ("strsub", str_sub);
 lua_register ("strlower", str_lower);
 lua_register ("strupper", str_upper);

 lua_register ("strhex", str_hex);
 lua_register ("strchr", str_chr);
}


#endif

