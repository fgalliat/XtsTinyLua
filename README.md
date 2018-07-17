## Lite LUA for c++ 

** Xtase refacto (I don't remember where I found this source code ~10years
ago....) **

no libdeps (.so) required for initial impl

./comp.sh -> regular build script
./compLCD.sh -> build w/ Optional serial GPU routines (lcdlib)


mount OPTIONAL lcdlib,mp3lib,gpiolib
 - note that as long as lcd/mp3 uses SerialBridge : no .so are required !
