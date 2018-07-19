rm starLCD 2>/dev/null
g++ -Wall -Wno-write-strings -fPIC -I . -c starfield.cpp BridgedScreen.cpp Serial.cpp
g++ -o starLCD starfield.o BridgedScreen.o Serial.o
rm *.o

