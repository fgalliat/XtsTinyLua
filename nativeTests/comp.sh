rm serialLCD 2>/dev/null
g++ -Wall -Wno-write-strings -fPIC -I . -c screenTest.cpp BridgedScreen.cpp Serial.cpp
g++ -o serialLCD screenTest.o BridgedScreen.o Serial.o
rm *.o

