rm ballLCD 2>/dev/null
g++ -Wall -Wno-write-strings -fPIC -I . -c roteyBall.cpp BridgedScreen.cpp Serial.cpp
g++ -o ballLCD roteyBall.o BridgedScreen.o Serial.o
rm *.o

