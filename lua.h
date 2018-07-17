#ifndef lua_h
#define lua_h



typedef void (*lua_CFunction) (void);
typedef struct Object *lua_Object;

#define lua_register(n,f)	(lua_pushcfunction(f), lua_storeglobal(n))


void           lua_errorfunction    	(void (*fn) (char *s));
void           lua_error		(char *s);
int            lua_dofile 		(char *filename);
int            lua_dostring 		(char *string);
int            lua_call 		(char *functionname, int nparam);

lua_Object     lua_getparam 		(int number);
float          lua_getnumber 		(lua_Object object);
char          *lua_getstring 		(lua_Object object);
char 	      *lua_copystring 		(lua_Object object);
lua_CFunction  lua_getcfunction 	(lua_Object object);
void          *lua_getuserdata  	(lua_Object object);
lua_Object     lua_getfield         	(lua_Object object, char *field);
lua_Object     lua_getindexed         	(lua_Object object, float index);
lua_Object     lua_getglobal 		(char *name);

lua_Object     lua_pop 			(void);

int 	       lua_pushnil 		(void);
int            lua_pushnumber 		(float n);
int            lua_pushstring 		(char *s);
int            lua_pushcfunction	(lua_CFunction fn);
int            lua_pushuserdata     	(void *u);
int            lua_pushobject       	(lua_Object object);

int            lua_storeglobal		(char *name);
int            lua_storefield		(lua_Object object, char *field);
int            lua_storeindexed		(lua_Object object, float index);

int            lua_isnil 		(lua_Object object);
int            lua_isnumber 		(lua_Object object);
int            lua_isstring 		(lua_Object object);
int            lua_istable          	(lua_Object object);
int            lua_iscfunction 		(lua_Object object);
int            lua_isuserdata 		(lua_Object object);


// --------------------------------------------------------
#ifndef real
#define real float
#endif

typedef unsigned char  Byte;

typedef unsigned short Word;

typedef enum 
{ 
 NOP,
 PUSHNIL,
 PUSH0, PUSH1, PUSH2,
 PUSHBYTE,
 PUSHWORD,
 PUSHFLOAT,
 PUSHSTRING,
 PUSHLOCAL0, PUSHLOCAL1, PUSHLOCAL2, PUSHLOCAL3, PUSHLOCAL4,
 PUSHLOCAL5, PUSHLOCAL6, PUSHLOCAL7, PUSHLOCAL8, PUSHLOCAL9,
 PUSHLOCAL,
 PUSHGLOBAL,
 PUSHINDEXED,
 PUSHMARK,
 PUSHOBJECT,
 STORELOCAL0, STORELOCAL1, STORELOCAL2, STORELOCAL3, STORELOCAL4,
 STORELOCAL5, STORELOCAL6, STORELOCAL7, STORELOCAL8, STORELOCAL9,
 STORELOCAL,
 STOREGLOBAL,
 STOREINDEXED0,
 STOREINDEXED,
 STOREFIELD,
 ADJUST,
 CREATEARRAY,
 EQOP,
 LTOP,
 LEOP,
 ADDOP,
 SUBOP,
 MULTOP,
 DIVOP,
 CONCOP,
 MINUSOP,
 NOTOP,
 ONTJMP,
 ONFJMP,
 JMP,
 UPJMP,
 IFFJMP,
 IFFUPJMP,
 POP,
 CALLFUNC,
 RETCODE,
 HALT,
 SETFUNCTION,
 SETLINE,
 RESET
} OpCode;

typedef enum
{
 T_MARK,
 T_NIL,
 T_NUMBER,
 T_STRING,
 T_ARRAY,
 T_FUNCTION,
 T_CFUNCTION,
 T_USERDATA
} Type; 

typedef void (*Cfunction) (void);
typedef int  (*Input) (void);
typedef void (*Unput) (int );

typedef union
{
 Cfunction 	 f;
 real    	 n;
 char      	*s;
 Byte      	*b;
 struct Hash    *a;
 void           *u;
} Value;

typedef struct Object
{
 Type  tag;
 Value value;
} Object;

typedef struct
{
 char   *name;
 Object  object;
} Symbol;

// .......
// y_tab.h
typedef union  
{
 int   vInt;
 long  vLong;
 float vFloat;
 Word  vWord;
 Byte *pByte;
} YYSTYPE;


// opcode.h
//char  	      	      **lua_constant;

#ifndef STACKGAP
#define STACKGAP	128
#endif 

// Macros to access structure members 
#define tag(o)		((o)->tag)
#define nvalue(o)	((o)->value.n)
#define svalue(o)	((o)->value.s)
#define bvalue(o)	((o)->value.b)
#define avalue(o)	((o)->value.a)
#define fvalue(o)	((o)->value.f)
#define uvalue(o)	((o)->value.u)

// Macros to access symbol table 
#define s_name(i)	(lua_table[i].name)
#define s_object(i)	(lua_table[i].object)
#define s_tag(i)	(tag(&s_object(i)))
#define s_nvalue(i)	(nvalue(&s_object(i)))
#define s_svalue(i)	(svalue(&s_object(i)))
#define s_bvalue(i)	(bvalue(&s_object(i)))
#define s_avalue(i)	(avalue(&s_object(i)))
#define s_fvalue(i)	(fvalue(&s_object(i)))
#define s_uvalue(i)	(uvalue(&s_object(i)))

int     lua_execute   (Byte *pc);
void    lua_markstack (void);
char   *lua_strdup (char *l);

void    lua_setinput   (Input fn);	// from "lua.lex" module 
void    lua_setunput   (Unput fn);	// from "lua.lex" module 
char   *lua_lasttext   (void);		// from "lua.lex" module 
int     lua_parse      (void); 		// from "lua.stx" module 
void    lua_type       (void);
void 	lua_obj2number (void);
void 	lua_print      (void);

// hash.h
typedef struct node
{
 Object ref;
 Object val;
 struct node *next;
} Node;

typedef struct Hash
{
 char           mark;
 unsigned int   nhash;
 Node         **list;
} Hash;

Hash 	*lua_hashcreate (unsigned int nhash);
void 	 lua_hashdelete (Hash *h);
Object 	*lua_hashdefine (Hash *t, Object *ref);
void 	 lua_hashmark   (Hash *h);
#define markarray(t)		((t)->mark)
void     lua_next (void);

//inout.h
int lua_debugline;
int  lua_openfile     (char *fn);
void lua_closefile    (void);
int  lua_openstring   (char *s);
int  lua_pushfunction (int file, int function);
void lua_popfunction  (void);
void lua_reportbug    (char *s);

int lua_linenumber;
int lua_debug;

// table.h
int   lua_findsymbol           (char *s);
int   lua_findenclosedconstant (char *s);
int   lua_findconstant         (char *s);
void  lua_markobject           (Object *o);
char *lua_createstring         (char *s);
void *lua_createarray          (void *a);
int   lua_addfile              (char *fn);
char *lua_filename             (void);
void  lua_nextvar              (void);

#ifndef MAXSYMBOL
#define MAXSYMBOL	512
#endif
static Symbol  		tablebuffer[MAXSYMBOL] = {
                                    {"type",{T_CFUNCTION,{lua_type}}},
                                    {"tonumber",{T_CFUNCTION,{lua_obj2number}}},
                                    {"next",{T_CFUNCTION,{lua_next}}},
                                    {"nextvar",{T_CFUNCTION,{lua_nextvar}}},
                                    {"print",{T_CFUNCTION,{lua_print}}}
                                                 };
Symbol	       	       *lua_table=tablebuffer;
Word   	 		lua_ntable=5;

//yylex.h
int yylex(void);

// ========================== modules =====================
#include "./primitives/table.h"
#include "./primitives/hash.h"
#include "./primitives/inout.h"

#include "./parse/y_tab.h"
#include "./parse/lex_yy.h"

#include "./system/opcode.h"




// ========================== libs =====================
#include "libs/iolib.h"
#include "libs/mathlib.h"
#include "libs/strlib.h"

#endif
