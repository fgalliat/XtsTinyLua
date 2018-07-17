#ifndef __SPE_STYSTEM_H_
#define __SPE_STYSTEM_H_ 1

_CRTIMP int __cdecl	remove (const char* file) {
        // delete a file from fs
        return 0;
}

_CRTIMP int __cdecl	system	(const char* cmd) {
        //execute a native process
        return 0;
}

#endif
