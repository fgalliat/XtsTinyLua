#ifndef __spe_CTYPE_H_
#define __spe_CTYPE_H_

//__CRT_INLINE int __cdecl isspace(int c) {return c == ' ' || c == '\t' || c == '\n' || c == '\r';}
//__CRT_INLINE int __cdecl _tolower(int c) {return ( c -'A'+'a');}
//__CRT_INLINE int __cdecl _toupper(int c) {return ( c -'a'+'A');}

_CRTIMP int __cdecl isspace(int c) {return c == ' ' || c == '\t' || c == '\n' || c == '\r';}
_CRTIMP int __cdecl tolower(int c) {return ( c -'A'+'a');}
_CRTIMP int __cdecl toupper(int c) {return ( c -'a'+'A');}

//__CRT_INLINE int __cdecl isdigit(int c) {return __ISCTYPE(c, _DIGIT);}
_CRTIMP int __cdecl isdigit(int c) {return c >= '0' && c <= '9' ;}


#endif
