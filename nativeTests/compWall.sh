rm wallLCD 2>/dev/null
g++ -Wall -Wno-write-strings -fPIC -I . -c walls.cpp BridgedScreen.cpp Serial.cpp
g++ -o wallLCD walls.o BridgedScreen.o Serial.o
rm *.o

