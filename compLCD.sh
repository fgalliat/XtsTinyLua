rm luaLCD 2>/dev/null
g++ -Wall -Wno-write-strings -fpermissive -fPIC -I . -DUSE_LCD -c lua.c libs_xts/BridgedScreen.cpp libs_xts/Serial.cpp
g++ -o luaLCD lua.o BridgedScreen.o Serial.o
rm *.o

